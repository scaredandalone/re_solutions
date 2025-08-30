/*
https://challenges.re/3/
What does this code do? The function has array of 64 32-bit integers, I removed it in each assembly code snippet to save space. The array is:
int v[64]=
	{ -1,31, 8,30, -1, 7,-1,-1, 29,-1,26, 6, -1,-1, 2,-1,
	  -1,28,-1,-1, -1,19,25,-1, 5,-1,17,-1, 23,14, 1,-1,
	   9,-1,-1,-1, 27,-1, 3,-1, -1,-1,20,-1, 18,24,15,10,
	  -1,-1, 4,-1, 21,-1,16,11, -1,22,-1,12, 13,-1, 0,-1 };
The algorithm is well-known, but I've changed constant so it wouldn't be googleable.

f:
	mov	edx, edi  						; input
	shr	edx       						; half the value of the input (BIT VALUE)
	or	edx, edi  						; OR operate the halfed value with the input
	mov	eax, edx  						; move the new value to EAX
	shr	eax, 2    						; shift EAX right 2 bits
	or	eax, edx  						; OR operate EDX on EAX
	mov	edx, eax  						; move the new value to EDX
	shr	edx, 4    						; shift EDX right 4 bits
	or	edx, eax  						; OR operate EAX on EDX
	mov	eax, edx  						; move the new value to EAX
	shr	eax, 8    						; shift EAX right 8 bits
	or	eax, edx  						; OR operate EDX on EAX
	mov	edx, eax  						; move the new value to EDX
	shr	edx, 16   						; shift EDX right 16 bits (original lower 16 bits of EDX will now occupy the higher 16 bits, 
										and the original higher 16 bits will be lost (shifted out and replaced by zeros)
	or	edx, eax  						; OR operate EAX on EDX
	imul	eax, edx, 79355661  		; MULTIPLY edx by 79355661 and STORE it in EAX
	shr	eax, 26 						; shift EAX right 26 bits
	mov	eax, DWORD PTR v[0+rax*4]		; this is where the array comes in, we move the value at v index [0+rax*4] to EAX
	ret
    

My Interpretation in C++
    */

#include <cstdint>
#include <iostream>

static const int v[64] =
{
    -1,31, 8,30, -1, 7,-1,-1, 29,-1,26, 6, -1,-1, 2,-1,
    -1,28,-1,-1, -1,19,25,-1, 5,-1,17,-1, 23,14, 1,-1,
     9,-1,-1,-1, 27,-1, 3,-1, -1,-1,20,-1, 18,24,15,10,
    -1,-1, 4,-1, 21,-1,16,11, -1,22,-1,12, 13,-1, 0,-1
};

int main()
{
    uint32_t x;
    std::cout << "RE challenge 3\nEnter a number: ";
    std::cin >> x;

    uint32_t y = x;
    y |= y >> 1;
    y |= y >> 2;
    y |= y >> 4;
    y |= y >> 8;
    y |= y >> 16;

    uint32_t idx = (y * 0x04D7651D) >> 26; 

    if (idx < 64)
        std::cout << "Final result: " << v[idx] << std::endl;
    else
        std::cout << "Error: index out of range!" << std::endl;

    return 0;
}

/*
	After some research, I found that this is actually a bit hack that uses a De Bruijn sequence 
	to find the index of the most significant set bit (MSB) quickly, without looping.
*/
