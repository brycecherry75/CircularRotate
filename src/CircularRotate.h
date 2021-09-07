#ifndef CircularRotate_h
#define CircularRotate_h

#include <Arduino.h>
#include <BitFieldManipulation.h>
#include <BitRWarray.h>

class CircularRotateClass {
  public:
    uint8_t rotate_byte(uint8_t data_source, int32_t ShiftsRequired);
    uint16_t rotate_word(uint16_t data_source, int32_t ShiftsRequired);
    uint32_t rotate_dword(uint32_t data_source, int32_t ShiftsRequired);
    uint64_t rotate_qword(uint64_t data_source, int32_t ShiftsRequired);
    void rotate_byteArray(uint8_t *data_source, int32_t ShiftsRequired, uint16_t ArraySize, uint16_t MSBlocation);
    void rotate_wordArray(uint16_t *data_source, int32_t ShiftsRequired, uint16_t ArraySize, uint16_t MSBlocation);
    void rotate_dwordArray(uint32_t *data_source, int32_t ShiftsRequired, uint16_t ArraySize, uint16_t MSBlocation);
    void rotate_qwordArray(uint64_t *data_source, int32_t ShiftsRequired, uint16_t ArraySize, uint16_t MSBlocation);
};

extern CircularRotateClass CircularRotate;

#endif