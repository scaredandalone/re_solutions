/*
https://challenges.re/4/
What does this code do?
Some versions have the 0x1010101 constant, some do not. Why?
<f>:
   0:          mov    edx,edi          ; first parameter
   2:          shr    edx,1            ; shift edx right 1 bit
   4:          and    edx,0x55555555   ; AND operate edx and 55555555
   a:          sub    edi,edx          ; subtract new value from the original value
   c:          mov    eax,edi          ; move the new value into eax
   e:          shr    edi,0x2          ; shift the original value by 2 bits
  11:          and    eax,0x33333333   ; AND operate on EAX with 33333333
  16:          and    edi,0x33333333   ; AND operate on EDI with 33333333
  1c:          add    edi,eax          ; ADD EAX to EDI
  1e:          mov    eax,edi          ; move EDI to EAX
  20:          shr    eax,0x4          ; shift eax right 4 bits
  23:          add    eax,edi          ; add EDI to EAX
  25:          and    eax,0xf0f0f0f    ; AND operate f0f0f0f
  2a:          imul   eax,eax,0x1010101; multiply EAX with 1010101 and store it in EAX
  30:          shr    eax,0x18         ; shift eax right 18 bits
  33:          ret
My Interpretation in C++
*/

#include <iostream>
#include <cstdint>
#include <limits>
#include <bitset>

int main() {
    uint32_t value; // corresponds to edi (initial val)
    uint32_t temp;  // corresponds to edx/eax (temp val)
    std::cout << "insert initial value: ";
    std::cin >> value;
    std::cout << "Initial binary: " << std::bitset<32>(value) << std::endl;
    temp = value >> 1;
    temp = temp & 0x55555555;
    value = value - temp;
    temp = value;
    temp = temp >> 2;
    value = value & 0x33333333;
    temp = temp & 0x33333333;
    value += temp;
    temp = value >> 4;
    value += temp;
    value = value & 0x0f0f0f0f; 
    value = value * 0x1010101;
    value = value >> 24;
    std::cout << "Final binary: " << std::bitset<32>(value) << std::endl;
    std::cout << "new value: " << value << std::endl;
    return 0;
}

/*
This code calculates the "Hamming Weight" of a 32 bit data-type.
https://en.wikipedia.org/wiki/Hamming_weight
*/