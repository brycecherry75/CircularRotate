/*

  CircularRotate demo by Bryce Cherry
  Also demo for BitRWarray

  Commands:
  MSB_BIT bit - Set MSB of array for circular bitshift
  ROTATE_ARRAY bits_to_rotate_signed - Circular rotate of array (positive value left, negative value right)
  ROTATE_ELEMENT element bits_to_rotate_signed - Circular rotate of element of array (positive value left, negative value right)
  (SET/CLEAR/READ)_BIT bit - Set/clear/read a bit

*/

#include <CircularRotate.h>
#include <BitFieldManipulation.h> // obtain at http://github.com/brycecherry75/BitFieldManipulation
#include <BitRWarray.h> // obtain at http://github.com/brycecherry75/BitRWarray

const uint8_t BFMsize = 6;
uint8_t ByteArray[BFMsize];
uint8_t MSBbit = ((BFMsize * 8) - 1);

// ensures that the serial port is flushed fully on request
const unsigned long SerialPortRate = 9600;
const byte SerialPortRateTolerance = 5; // +percent - increase to 50 for rates above 115200 up to 4000000
const byte SerialPortBits = 10; // start (1), data (8), stop (1)
const unsigned long TimePerByte = ((((1000000ULL * SerialPortBits) / SerialPortRate) * (100 + SerialPortRateTolerance)) / 100); // calculated on serial port rate + tolerance and rounded down to the nearest uS, long caters for even the slowest serial port of 75 bps

const word commandSize = 50;
char command[commandSize];
const byte FieldSize = 30;

void FlushSerialBuffer() {
  while (true) {
    if (Serial.available() > 0) {
      byte dummy = Serial.read();
      while (Serial.available() > 0) { // flush additional bytes from serial buffer if present
        dummy = Serial.read();
      }
      if (TimePerByte <= 16383) {
        delayMicroseconds(TimePerByte); // delay in case another byte may be received via the serial port
      }
      else { // deal with delayMicroseconds limitation
        unsigned long DelayTime = TimePerByte;
        DelayTime /= 1000;
        if (DelayTime > 0) {
          delay(DelayTime);
        }
        DelayTime = TimePerByte;
        DelayTime %= 1000;
        if (DelayTime > 0) {
          delayMicroseconds(DelayTime);
        }
      }
    }
    else {
      break;
    }
  }
}

void getField (char* buffer, int index) {
  int commandPos = 0;
  int fieldPos = 0;
  int spaceCount = 0;
  while (commandPos < commandSize) {
    if (command[commandPos] == 0x20) {
      spaceCount++;
      commandPos++;
    }
    else if (command[commandPos] == 0x0D || command[commandPos] == 0x0A) {
      break;
    }
    if (spaceCount == index) {
      buffer[fieldPos] = command[commandPos];
      fieldPos++;
    }
    commandPos++;
  }
  for (int ch = 0; ch < strlen(buffer); ch++) { // correct case of command
    buffer[ch] = toupper(buffer[ch]);
  }
  buffer[fieldPos] = '\0';
}

void PrintByteArray() {
  for (int BytesToPrint = 0; BytesToPrint < BFMsize; BytesToPrint++) {
    uint8_t mask = 0x80;
    for (int BitsToCheck = 0; BitsToCheck < 7; BitsToCheck++) {
      if ((ByteArray[BytesToPrint] & mask) == 0) {
        Serial.print(F("0"));
      }
      else {
        break;
      }
      mask >>= 1;
    }
    Serial.print(ByteArray[BytesToPrint], BIN);
    Serial.print(F(" "));
  }
  Serial.println(F(""));
}

void setup() {
  BitFieldManipulation.NullArray_byte(BFMsize, ByteArray);
  Serial.begin(SerialPortRate);
}

void loop() {
  static int ByteCount = 0;
  if (Serial.available() > 0) {
    char inData = Serial.read();
    if (inData != '\n' && ByteCount < commandSize) {
      command[ByteCount] = inData;
      ByteCount++;
    }
    else {
      ByteCount = 0;
      char field[FieldSize];
      getField(field, 0);
      bool ValidField = true;
      if (strcmp(field, "MSB_BIT") == 0) {
        getField(field, 1);
        uint8_t temp = atoi(field);
        if (temp <= ((BFMsize * 8) - 1)) {
          MSBbit = temp;
        }
        else {
          ValidField = false;
        }
      }
      else if (strcmp(field, "ROTATE_ARRAY") == 0) {
        getField(field, 1);
        int32_t ShiftsRequired = atol(field);
        CircularRotate.rotate_byteArray(ByteArray, ShiftsRequired, BFMsize, MSBbit);
        PrintByteArray();
      }
      else if (strcmp(field, "ROTATE_ELEMENT") == 0) {
        getField(field, 1);
        uint8_t ElementSelected = atoi(field);
        if (ElementSelected < BFMsize) {
          getField(field, 2);
          int32_t ShiftsRequired = atol(field);
          ByteArray[ElementSelected] = CircularRotate.rotate_byte(ByteArray[ElementSelected], ShiftsRequired);
          PrintByteArray();
        }
        else {
          ValidField = false;
        }
      }
      else if (strcmp(field, "SET_BIT") == 0) {
        getField(field, 1);
        uint8_t BitConcerned = atoi(field);
        if (BitConcerned <= ((BFMsize * 8) - 1)) {
          BitRWarray.writeByte(ByteArray, BitConcerned, HIGH, BFMsize);
          PrintByteArray();
        }
        else {
          ValidField = false;
        }
      }
      else if (strcmp(field, "CLEAR_BIT") == 0) {
        getField(field, 1);
        uint8_t BitConcerned = atoi(field);
        if (BitConcerned <= ((BFMsize * 8) - 1)) {
          BitRWarray.writeByte(ByteArray, BitConcerned, LOW, BFMsize);
          PrintByteArray();
        }
        else {
          ValidField = false;
        }
      }
      else if (strcmp(field, "READ_BIT") == 0) {
        getField(field, 1);
        uint8_t BitConcerned = atoi(field);
        if (BitConcerned <= ((BFMsize * 8) - 1)) {
          uint8_t BitState = BitRWarray.readByte(ByteArray, BitConcerned, BFMsize);
          Serial.print(F("Bit "));
          Serial.print(BitConcerned);
          Serial.print(F(" is "));
          Serial.println(BitState);
        }
        else {
          ValidField = false;
        }
      }
      else {
        ValidField = false;
      }
      FlushSerialBuffer();
      if (ValidField == true) {
        Serial.println(F("OK"));
      }
      else {
        Serial.println(F("ERROR"));
      }
    }
  }
}