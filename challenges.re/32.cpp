/*
                public f
f               proc near

var_C           = dword ptr -0Ch             ; local variable
var_8           = dword ptr -8               ; local variable
var_4           = dword ptr -4               ; local variable
arg_0           = dword ptr  8               ; argument 1
arg_4           = dword ptr  0Ch             ; argument 2
											 ;
                push    ebp                  ;
                mov     ebp, esp             ;
                sub     esp, 10h             ; allocate 16 bytes to the stack 
                mov     eax, [ebp+arg_0]     ; 
                mov     [ebp+var_4], eax     ; copy arg_0 to var_4
                mov     eax, [ebp+arg_4]     ; 
                movzx   eax, byte ptr [eax]  ; read one byte from arg_4, and move zero extend it back into eax (zero out top 24 bits)
                test    al, al               ; is last byte in eax 0
                jnz     short loc_8048443    ; if it isnt, jump to loc_8048443
                mov     eax, [ebp+arg_0]     ; if it is 0, copy arg_0 into eax
                jmp     short locret_8048453 ; jump to locret_8048453 (exit)
											 ;
loc_80483F4:                                 ;
                mov     eax, [ebp+var_4]     ; 
                mov     [ebp+var_8], eax     ; copy var_4 into var_8
                mov     eax, [ebp+arg_4]     ; 
                mov     [ebp+var_C], eax     ; copy arg_4 into var_C
                jmp     short loc_804840A    ; 
											 ;
loc_8048402:                                 ;
                add     [ebp+var_8], 1       ; var_8 += 1
                add     [ebp+var_C], 1       ; var_C += 1
											 ;
loc_804840A:                                 ;
                mov     eax, [ebp+var_8]     ; 
                movzx   eax, byte ptr [eax]  ; read one byte from var_8 and move zero extend it back into eax (zero out top 24 bits)
                test    al, al               ; is last byte in eax 0
                jz      short loc_804842E    ; jump if last byte in eax IS 0
                mov     eax, [ebp+var_C]     ;
                movzx   eax, byte ptr [eax]  ; read one byte from var_C and move zero extend it back into eax (zero out top 24 bits)
                test    al, al               ; is last byte in eax 0
                jz      short loc_804842E    ; jump if last byte in eax IS 0
                mov     eax, [ebp+var_8]     ; 
                movzx   edx, byte ptr [eax]  ; read one byte from var_8 and move zero extend it into edx (zero out top 24 bits)
                mov     eax, [ebp+var_C]     ;
                movzx   eax, byte ptr [eax]  ; read one byte from var_C and move zero extend it back into eax (zero out top 24 bits)
                cmp     dl, al               ; compare last bytes from eax and edx
                jz      short loc_8048402    ; if bytes are equal, jump to loc_8048402
											 ;
loc_804842E:                                 ;
                mov     eax, [ebp+var_C]     ;
                movzx   eax, byte ptr [eax]  ; read one byte from var_C and move zero extend it back into eax (zero out top 24 bits)
                test    al, al               ; is last byte in eax 0
                jnz     short loc_804843D    ; jump if last byte in eax IS NOT 0
                mov     eax, [ebp+var_4]     ;
                jmp     short locret_8048453 ;
											 ;
loc_804843D:                                 ;
                add     [ebp+var_4], 1       ; var4 += 1
                jmp     short loc_8048444    ; jump loc_8048444
											 ;
											 ;
loc_8048443:                                 ;
                nop                          ;
											 ;
loc_8048444:                                 ;
                mov     eax, [ebp+var_4]     ;
                movzx   eax, byte ptr [eax]  ; read one byte from var_4 and move zero extend it back into eax (zero out top 24 bits)
                test    al, al               ; is last byte in eax 0
                jnz     short loc_80483F4    ; jump if last byte in eax IS NOT 0
                mov     eax, 0               ; otherwise, copy 0 into eax
											 ;
locret_8048453:                              ;
                leave                        ;
                retn                         ;
f               endp                         ;


My interpretation in C++
*/

#include <iostream>
#include <string>

int main() {
    std::string needle, haystack;

    std::cout << "Enter haystack string: ";
    std::cin >> haystack;
    
    std::cout << "Enter needle string: ";
    std::cin >> needle;

    int result = -1;

    if(needle.empty()){
        result = 0;
    }
    else {
        size_t haystack_idx = 0;

        while(haystack_idx <= haystack.length() - needle.length()){
            size_t compare_idx = haystack_idx;
            size_t needle_idx = 0;

            while(compare_idx < haystack.length() && needle_idx < needle.length() && haystack[compare_idx] == needle[needle_idx]){
                compare_idx++;
                needle_idx++;
            }
            
            if(needle_idx == needle.length()) {
                result = haystack_idx;
                break;
            }
            
            haystack_idx++;
        }
    }

    if (result != -1) {
        std::cout << "Found needle at position: " << result << std::endl;
        std::cout << "Substring from match: " << haystack.substr(result) << std::endl;
    } else {
        std::cout << "Needle not found in haystack" << std::endl;
    }

    return 0;
}

/*
The assembly program implements a simple substring search algorithm, very similar to the standard library function strstr(). 
It searches for one string (the "needle") within another string (the "haystack") and returns the position of the first occurrence.
"searching for a needle in a haystack"
The algorithm uses a brute-force approach, checking each position in the haystack to see if the needle matches starting from that point.

The original assembly function:
- Takes two arguments: arg_0 (haystack pointer) and arg_4 (needle pointer)
- Returns a pointer to the first occurrence of needle in haystack, or 0 if not found
- Uses C-style null-terminated strings
- Implements a basic string search algorithm similar to strstr()

Key differences in my C++ version:
- Uses std::string instead of char pointers
- Returns integer index instead of pointer
- Adds user input/output functionality
- Uses modern C++ practices (size_t for indices)
- Returns -1 for "not found" instead of 0/NULL
*/