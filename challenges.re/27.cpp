/*
https://challenges.re/27/
_a$ = 8                             ;	defines variable _a$ = 8
mov	ecx, DWORD PTR _a$[esp-4]       ;	move the value of variable _a$(8) into ecx 
mov	eax, -968154503	; c64b2279H2     ;	move (hex)c64b2279 into eax 
imul	ecx                         ;   multiple eax with ecx (since ecx and eax are 32bit and the result is 64bit we need to split them. Through some research I found that
                                        the behaviour is EDX:EAX where EDX stores the top 32 bits and EAX stores the bottom).
add	edx, ecx                        ;   add ecx to edx (ECX HAS NOT CHANGED! IMUL DOES NOT ALTER IT)
sar	edx, 9                          ;   shift edx right 9 bits (ignore the MSB)
mov	eax, edx                        ;	move edx into eax
shr	eax, 31		; 0000001fH         ;	shift eax right by hex 0000001f
add	eax, edx                        ;	add edx to eax
ret	0                               ;
_fENDP                              ;

My Interpretation:
*/

#include <iostream>
#include <cstdint>
#include <bitset>


int main() {
    int32_t a;  
    std::cout << "input number: ";
    std::cin >> a;
    
    int64_t temp = (int64_t)a * (int32_t)0xc64b2279;
    
    // int32_t lower = (int32_t)(temp & 0xFFFFFFFF); // this is unused, but I included it anyways.
    int32_t upper = (int32_t)(temp >> 32);
    
    upper += a;              
    upper = upper >> 9;     
    int32_t result = upper;  
    result = result >> 31;   
    result = result + upper; 
    
    std::cout << "result = " << result << std::endl;


    uint64_t magic = 0xc64b2279;
    uint64_t power = 1ULL << (32 + 9); 
    double approx_divisor = (double)power / magic;
    std::cout << "Approximate divisor: " << approx_divisor << std::endl;
    return 0;
}
/*
This seems to be a compiler optimisation for division.

The magic constant 0xc64b2279 is a precomputed value that allows integer division
to be performed using multiplication and bit shifts instead of the expensive division
instruction.

Division is slow (takes many CPU cycles), but multiplication and shifts are fast.
So instead of doing input ÷ divisor, the compiler does:

Multiply input by a carefully chosen "magic number"
Take the high bits of the 64-bit result
Apply shifts and corrections to handle rounding and negative numbers
Result equals input ÷ divisor, but computed much faster

It's like using 100 × 0.25 instead of 100 ÷ 4 - different operation, same result.
The magic number is calculated so the math works out exactly right.

This optimization is commonly used by compilers when they detect division by a
constant, replacing the slow division with this faster sequence of operations.
*/