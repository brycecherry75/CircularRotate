#include "CircularRotate.h"

uint8_t CircularRotateClass::rotate_byte(uint8_t data_source, int32_t ShiftsRequired) {
  if (ShiftsRequired < 0) {
    ShiftsRequired ^= 0xFFFFFFFF;
    ShiftsRequired++;
    for (uint16_t i = 0; i < ShiftsRequired; i++) {
      uint8_t temp = data_source;
      temp &= 0x01;
      data_source >>= 1;
      data_source &= 0x7F; // deal with unwanted sign bit
      if (temp != 0) {
        data_source |= 0x80;
      }
    }
  }
  else {
    for (uint16_t i = 0; i < ShiftsRequired; i++) {
      uint8_t temp = data_source;
      temp &= 0x80;
      data_source <<= 1;
      if (temp != 0) {
        data_source |= 0x01;
      }
    }
  }
  return data_source;
}

uint16_t CircularRotateClass::rotate_word(uint16_t data_source, int32_t ShiftsRequired) {
  if (ShiftsRequired < 0) {
    ShiftsRequired ^= 0xFFFFFFFF;
    ShiftsRequired++;
    for (uint16_t i = 0; i < ShiftsRequired; i++) {
      uint16_t temp = data_source;
      temp &= 0x0001;
      data_source >>= 1;
      data_source &= 0x7FFF; // deal with unwanted sign bit
      if (temp != 0) {
        data_source |= 0x8000;
      }
    }
  }
  else {
    for (uint16_t i = 0; i < ShiftsRequired; i++) {
      uint16_t temp = data_source;
      temp &= 0x8000;
      data_source <<= 1;
      if (temp != 0) {
        data_source |= 0x0001;
      }
    }
  }
  return data_source;
}

uint32_t CircularRotateClass::rotate_dword(uint32_t data_source, int32_t ShiftsRequired) {
  if (ShiftsRequired < 0) {
    ShiftsRequired ^= 0xFFFFFFFF;
    ShiftsRequired++;
    for (uint16_t i = 0; i < ShiftsRequired; i++) {
      uint32_t temp = data_source;
      temp &= 0x00000001;
      data_source >>= 1;
      data_source &= 0x7FFFFFFF; // deal with unwanted sign bit
      if (temp != 0) {
        data_source |= 0x80000000;
      }
    }
  }
  else {
    for (uint16_t i = 0; i < ShiftsRequired; i++) {
      uint32_t temp = data_source;
      temp &= 0x80000000;
      data_source <<= 1;
      if (temp != 0) {
        data_source |= 0x00000001;
      }
    }
  }
  return data_source;
}

uint64_t CircularRotateClass::rotate_qword(uint64_t data_source, int32_t ShiftsRequired) {
  if (ShiftsRequired < 0) {
    ShiftsRequired ^= 0xFFFFFFFF;
    ShiftsRequired++;
    for (uint16_t i = 0; i < ShiftsRequired; i++) {
      uint64_t temp = data_source;
      temp &= 1;
      data_source >>= 1;
      data_source &= 922372036854775807ULL; // deal with unwanted sign bit
      if (temp != 0) {
        data_source |= 922372036854775808ULL;
      }
    }
    return data_source;
  }
  else {
    for (uint16_t i = 0; i < ShiftsRequired; i++) {
      uint64_t temp = data_source;
      temp &= 922372036854775808ULL;
      data_source <<= 1;
      if (temp != 0) {
        data_source |= 1;
      }
    }
  }
  return data_source;
}

void CircularRotateClass::rotate_byteArray(uint8_t *data_source, int32_t ShiftsRequired, uint16_t ArraySize, uint16_t MSBlocation) {
  if (ShiftsRequired != 0) {
    if (ShiftsRequired > 0) {
      for (uint16_t i = 0; i < ShiftsRequired; i++) {
        uint8_t TempBit = BitRWarray.readByte(data_source, MSBlocation, ArraySize);
        BitRWarray.writeByte(data_source, MSBlocation, LOW, ArraySize);
        BitFieldManipulation.BitshiftArray_byte(1, ArraySize, false, data_source);
        BitRWarray.writeByte(data_source, 0, TempBit, ArraySize);
      }
    }
    else {
      ShiftsRequired ^= 0xFFFFFFFF;
      ShiftsRequired++;
      for (uint16_t i = 0; i < ShiftsRequired; i++) {
        uint8_t TempBit = BitRWarray.readByte(data_source, 0, ArraySize);
        BitRWarray.writeByte(data_source, 0, LOW, ArraySize);
        BitFieldManipulation.BitshiftArray_byte(-1, ArraySize, false, data_source);
        BitRWarray.writeByte(data_source, MSBlocation, TempBit, ArraySize);
      }
    }
  }
}

void CircularRotateClass::rotate_wordArray(uint16_t *data_source, int32_t ShiftsRequired, uint16_t ArraySize, uint16_t MSBlocation) {
  if (ShiftsRequired != 0) {
    if (ShiftsRequired > 0) {
      for (uint16_t i = 0; i < ShiftsRequired; i++) {
        uint8_t TempBit = BitRWarray.readWord(data_source, MSBlocation, ArraySize);
        BitRWarray.writeWord(data_source, MSBlocation, LOW, ArraySize);
        BitFieldManipulation.BitshiftArray_word(1, ArraySize, false, data_source);
        BitRWarray.writeWord(data_source, 0, TempBit, ArraySize);
      }
    }
    else {
      ShiftsRequired ^= 0xFFFFFFFF;
      ShiftsRequired++;
      for (uint16_t i = 0; i < ShiftsRequired; i++) {
        uint8_t TempBit = BitRWarray.readWord(data_source, 0, ArraySize);
        BitRWarray.writeWord(data_source, 0, LOW, ArraySize);
        BitFieldManipulation.BitshiftArray_word(-1, ArraySize, false, data_source);
        BitRWarray.writeWord(data_source, MSBlocation, TempBit, ArraySize);
      }
    }
  }
}

void CircularRotateClass::rotate_dwordArray(uint32_t *data_source, int32_t ShiftsRequired, uint16_t ArraySize, uint16_t MSBlocation) {
  if (ShiftsRequired != 0) {
    if (ShiftsRequired > 0) {
      for (uint16_t i = 0; i < ShiftsRequired; i++) {
        uint8_t TempBit = BitRWarray.readDword(data_source, MSBlocation, ArraySize);
        BitRWarray.writeDword(data_source, MSBlocation, LOW, ArraySize);
        BitFieldManipulation.BitshiftArray_dword(1, ArraySize, false, data_source);
        BitRWarray.writeDword(data_source, 0, TempBit, ArraySize);
      }
    }
    else {
      ShiftsRequired ^= 0xFFFFFFFF;
      ShiftsRequired++;
      for (uint16_t i = 0; i < ShiftsRequired; i++) {
        uint8_t TempBit = BitRWarray.readDword(data_source, 0, ArraySize);
        BitRWarray.writeDword(data_source, 0, LOW, ArraySize);
        BitFieldManipulation.BitshiftArray_dword(-1, ArraySize, false, data_source);
        BitRWarray.writeDword(data_source, MSBlocation, TempBit, ArraySize);
      }
    }
  }
}

void CircularRotateClass::rotate_qwordArray(uint64_t *data_source, int32_t ShiftsRequired, uint16_t ArraySize, uint16_t MSBlocation) {
  if (ShiftsRequired != 0) {
    if (ShiftsRequired > 0) {
      for (uint16_t i = 0; i < ShiftsRequired; i++) {
        uint8_t TempBit = BitRWarray.readQword(data_source, MSBlocation, ArraySize);
        BitRWarray.writeQword(data_source, MSBlocation, LOW, ArraySize);
        BitFieldManipulation.BitshiftArray_qword(1, ArraySize, false, data_source);
        BitRWarray.writeQword(data_source, 0, TempBit, ArraySize);
      }
    }
    else {
      ShiftsRequired ^= 0xFFFFFFFF;
      ShiftsRequired++;
      for (uint16_t i = 0; i < ShiftsRequired; i++) {
        uint8_t TempBit = BitRWarray.readQword(data_source, 0, ArraySize);
        BitRWarray.writeQword(data_source, 0, LOW, ArraySize);
        BitFieldManipulation.BitshiftArray_qword(-1, ArraySize, false, data_source);
        BitRWarray.writeQword(data_source, MSBlocation, TempBit, ArraySize);
      }
    }
  }
}

CircularRotateClass CircularRotate;