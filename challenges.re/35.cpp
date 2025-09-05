/*
https://challenges.re/35/
_rt$1 = -4						; size = 4
_rt$2 = 8						; size = 4
_x$ = 8							; size = 4
_y$ = 12						; size = 4
?f@@YAIII@Z PROC					; f
	push	ecx							;				                 	
	push	esi                         ;
	mov	esi, DWORD PTR _x$[esp+4]       ; esi = x
	test	esi, esi                    ;  
	jne	SHORT $LN7@f                    ; jump if esi != 0
	mov	eax, DWORD PTR _y$[esp+4]       ; eax = y
	pop	esi                             ;
	pop	ecx                             ;
	ret	0                               ; exit
$LN7@f:                                 ;
	mov	edx, DWORD PTR _y$[esp+4]       ; edx = y
	mov	eax, esi                        ; eax = x
	test	edx, edx                    ;
	je	SHORT $LN8@f                    ; jump if edx == 0
	or	eax, edx                        ; eax = eax | edx
	push	edi                         ; 
	bsf	edi, eax                        ; find lowest set bit position in eax, place in edi
	bsf	eax, esi                        ; get index of first 1 bit
	mov	ecx, eax                        ; ecx = eax
	mov	DWORD PTR _rt$1[esp+12], eax    ; x = eax
	bsf	eax, edx                        ; find lowest set bit position in edx, place in eax
	shr	esi, cl                         ; esi = esi >> cl 
	mov	ecx, eax                        ; ecx = eax
	shr	edx, cl                         ; edx = edx >> cl
	mov	DWORD PTR _rt$2[esp+8], eax     ; x = eax
	cmp	esi, edx                        ; compare x y
	je	SHORT $LN22@f                   ; jump if equal
$LN23@f:                                ;
	jbe	SHORT $LN2@f                    ; jump if below or equal
	xor esi, edx    ; esi = esi ^ edx  
	xor edx, esi    ; edx = edx ^ esi (which is edx ^ esi ^ edx = esi)
	xor esi, edx    ; esi = esi ^ edx (which is esi ^ edx ^ esi = edx)
$LN2@f:                                 ;
	cmp	esi, 1                          ;
	je	SHORT $LN22@f                   ; jump if esi == 1
	sub	edx, esi                        ; edx -= esi
	bsf	eax, edx                        ; find lowest set bit position in edx, place in eax
	mov	ecx, eax                        ; ecx = eax
	shr	edx, cl                         ; edx = edx >> cl
	mov	DWORD PTR _rt$2[esp+8], eax     ; x = eax
	cmp	esi, edx                        ; 
	jne	SHORT $LN23@f                   ; jump if esi != edx
$LN22@f:                                ;
	mov	ecx, edi                        ; ecx = edi
	shl	esi, cl                         ; esi << cl
	pop	edi                             ; 
	mov	eax, esi                        ; eax = esi
$LN8@f:                                 ;
	pop	esi                             ;
	pop	ecx                             ;
	ret	0                               ; exit
?f@@YAIII@Z ENDP

We can demangle the function signature to find:
unsigned int __cdecl f(unsigned int,unsigned int)
We could have inferred this from the size of parameters and behaviour of the program but its nice.
*/

#include <iostream>

int bsf(unsigned int value) {
    if (value == 0) return 0; 
    return __builtin_ctz(value);
}

int main() {
    int x, y;
    std::cout << "X: "; std::cin >> x;
    std::cout << "Y: "; std::cin >> y;  
    
    if(x == 0) {
        std::cout << y;
        return 0;
    }
    
    if(y == 0) {
        std::cout << x;
        return 0;
    }
    
    int combined_pos = bsf(x | y);
    int x_pos = bsf(x);
    int y_pos = bsf(y);
    
    x = x >> x_pos;  
    y = y >> y_pos;
    
    while(x != y) {
		if(x > y){
		x = x ^ y;
		y = y ^ x;
		x = x ^ y;
		}
		if(x == 1){
			break;
		}
		y -= x;
		y_pos = bsf(y);
		y = y >> y_pos;
    }
    
    std::cout << (x << combined_pos);
    
    return 0;
}


/*
I researched into the behaviour and found that it is a binary GCD algorithm.
https://en.wikipedia.org/wiki/Binary_GCD_algorithm
This algorithm finds the greatest common denominator of two unsigned numbers (non-negative).

https://docs.oracle.com/cd/E19455-01/806-3773/instructionset-89/index.html

*/