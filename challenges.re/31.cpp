/*
https://challenges.re/31/

What does this code do?

Optimizing MSVC 2012 x64
__real@3fe0000000000000 DQ 03fe0000000000000r          ; 0.5
__real@3f50624dd2f1a9fc DQ 03f50624dd2f1a9fcr          ; 0.001
__real@3ff0000000000000 DQ 03ff0000000000000r          ; 1
													   ;
x$ = 8                                                 ;
f	PROC                                               ;
	movsdx	xmm2, QWORD PTR __real@3ff0000000000000    ; move 1 into xmm2 (only bottom 64 bits)
	movsdx	xmm5, QWORD PTR __real@3f50624dd2f1a9fc    ; move 0.001 into xmm5 (only bottom 64 bits)
	movsdx	xmm4, QWORD PTR __real@3fe0000000000000    ; move 0.5 into xmm4 (only bottom 64 bits)
	movapd	xmm3, xmm0                                 ; copies entire reg xmm0 to xmm3 (ill assume this is the user input)
	npad	4                                          ; padding (4 bytes)
$LL4@f:                                                ;
	movapd	xmm1, xmm2                                 ; copy xmm2 to xmm1
	mulsd	xmm1, xmm2                                 ; xmm1 = xmm1 * xmm2
	subsd	xmm1, xmm3                                 ; xmm1 = xmm1 - xmm3
	cvttsd2si eax, xmm1                                ; convert xmm1 to an integer and copy to eax (this truncates the mantisa, so there is no rounding up)
	cdq                                                ; sign extend eax into edx (converts doubleword to quadword)
	xor	eax, edx                                       ; operation eax XOR edx
	sub	eax, edx                                       ; eax = eax - edx
	movd	xmm0, eax                                  ; move doubleword eax to xmm0 (zero the upper bits)
	cvtdq2pd xmm0, xmm0                                ; this converts the int in xmm0 to 2 floating points, it would be what was in eax previously and 0
	comisd	xmm5, xmm0                                 ; compares xmm5(0.001) with xmm0 and sets flags accordingly (ZF=1 if equal, CF=1 if xmm5 < xmm0 and CF=0 ZF=0 if xmm5 > xmm0)
	ja	SHORT $LN18@f                                  ; jump if above (will only jump if CF=0 and ZF=0)
	movapd	xmm0, xmm3                                 ; copy xmm3 to xmm0
	divsd	xmm0, xmm2                                 ; xmm0 = xmm0 / xmm2
	addsd	xmm0, xmm2                                 ; xmm0 = xmm0 + xmm2
	movapd	xmm2, xmm0                                 ; copy xmm0 to xmm2
	mulsd	xmm2, xmm4                                 ; xmm2 = xmm2 * xmm4
	jmp	SHORT $LL4@f                                   ; jump to $LL4@f
$LN18@f:                                               ;
	movapd	xmm0, xmm2                                 ; copy xmm2 to xmm0
	ret	0                                              ;
f	                                                   ;
													   ;
													   ;
My interpretation in C++
*/

#include <iostream>
#include <cmath>

int main() {
    const double half = 0.5;
    const double precision = 0.001;
    const double whole = 1.0;
    double input;
	std::cout << "calculate square root\n" << "input: ";
	std::cin >> input;
    double backup_input = input;  
    double estimate = whole;      
    double temp;

    while(true) {
        temp = estimate * estimate;  
        temp -= backup_input;        
        
        int temp_int = (int)temp;
        temp_int = abs(temp_int);
        temp = (double)temp_int;

        if(temp <= precision) {
            std::cout << "Final result: " << estimate << std::endl;
            return 0;
        }
        
        input = backup_input / estimate;  
        input = input + estimate;          
        estimate = input * half;          
    }

    return 0;
}

/*
This program is implementing Newton's Method for Square Root Calculation.
Newton's Method formula: x_(n+1) = (x_n + a/x_n) / 2
Our formula: estimate_new = (estimate + backup_input/estimate) / 2

backup_input = a (the number we want the square root of)
estimate = x_n (current square root estimate)
estimate_new = x_(n+1) (improved estimate)

*/
