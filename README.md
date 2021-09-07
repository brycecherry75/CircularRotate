#CircularRotate Library#

CircularRotate performs circular rotate operations on individual elements and arrays.

Requires the following libraries:

BitFieldManipulation (version 1.1.0 or later) http://github.com/brycecherry75/BitFieldManipulation

BitRWarray http://github.com/brycecherry75/BitRWarray

Revisions:
1.0.0	First release

## Usage

rotate_(byte/word/dword/qword)(data_source, ShiftsRequired) - returns a byte/word/dword/qword after circular rotation for ShiftsRequired (positive for left, negative for right)

rotate_(byte/word/dword/qword)Array(*data_souce, ShiftsRequired, ArraySize, MSBlocation) - performs a circular rotation on an array with respect to MSBlocation - on a right shift (negative ShiftsRequired value), the LSB of the array will be shifted to MSBlocation and on a left shift (positive ShiftsRequired value), the bit at MSBlocation will be shifted to the LSB of the array

In many programming lanugages, data_source elements start at 0 from the left and additionally in many component datasheets, MSB to LSB is read from left to right.

Quad word (uint64_t/long long) is currently untested and requires compiler support inclduing bitshift operations.