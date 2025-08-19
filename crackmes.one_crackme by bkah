/*
   written by scaredandalone
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
link to the original crackmes.one page: https://crackmes.one/crackme/63f06e1233c5d447bc76149d
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

 Original Code from Ghidra diassembler:
 This is the main function which gives us all the password calculation logic from the challenge.
 This function takes the username input from the user, executes some bitwise operations and hash constant adjustments ON the username to create a valid password.
 The output of this function is passed into the main function to check the validity of the login.
 I have renamed some of the variables to be more closely linked to their functionality.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void generate_password(char *username,ulonglong *password)
{
  char *pcVar1;
  char cVar2;
  code *pcVar3;
  BOOL BVar4;
  HANDLE pvVar5;
  longlong lVar6;
  ulonglong i;
  int iVar7;
  ulonglong index;
  char *pcVar8;
  int j;
  ulonglong uVar9;
  undefined1 auStack_148 [32];
  ulonglong local_128 [30];
  BOOL local_38 [2];
  char local_30 [32];
  ulonglong local_10;
  
  local_10 = DAT_140005008 ^ (ulonglong)auStack_148;
  local_38[0] = 0;
  pvVar5 = GetCurrentProcess();
  BVar4 = CheckRemoteDebuggerPresent(pvVar5,local_38);
  if ((BVar4 == 0) || (BVar4 = IsDebuggerPresent(), BVar4 != 0)) {
    debugger_found();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  local_30[0] = '0';
  local_30[1] = '\0';
  local_30[0x12] = '\0';
  local_30[0x13] = '\0';
  local_30[0x14] = '\0';
  local_30[0x15] = '\0';
  local_30[0x16] = '\0';
  local_30[0x17] = '\0';
  local_30[0x18] = '\0';
  local_30[0x19] = '\0';
  local_30[0x1a] = '\0';
  local_30[0x1b] = '\0';
  local_30[0x1c] = '\0';
  local_30[0x1d] = '\0';
  local_30[2] = '\0';
  local_30[3] = '\0';
  local_30[4] = '\0';
  local_30[5] = '\0';
  local_30[6] = '\0';
  local_30[7] = '\0';
  local_30[8] = '\0';
  local_30[9] = '\0';
  local_30[10] = '\0';
  local_30[0xb] = '\0';
  local_30[0xc] = '\0';
  local_30[0xd] = '\0';
  local_30[0xe] = '\0';
  local_30[0xf] = '\0';
  local_30[0x10] = '\0';
  local_30[0x11] = '\0';
  memset(local_128,0,0xf0);
  uVar9 = 0xffffffffffffffff;
  j = 0;
  lVar6 = -0x1;
  do {
    lVar6 = lVar6 + 1;
  } while (username[lVar6] != '\0');
  if (lVar6 != 0) {
    index = 0;


----------------------------------------------------------------------------------------------------

Step 1: position-based XOR with 0x30
takes each position, adds 1, XORs with 0x30, then adds result to character at that position
----------------------------------------------------------------------------------------------------

do {
  username[index] = username[index] + ((char)j + 1U ^ 0x30);
  i = 0xffffffffffffffff;
  j = j + 1;
  index = (ulonglong)j;
  do {
    i = i + 1;
  } while (username[i] != '\0');
} while (index < i);

j = 0;
lVar6 = -0x1;
do {
  lVar6 = lVar6 + 1;
} while (username[lVar6] != '\0');

----------------------------------------------------------------------------------------------------

Step 2: bitwise AND with 0x10
checks if bit 4 is set in position index, adds either 0 or 16 to each character
----------------------------------------------------------------------------------------------------

if (lVar6 != 0) {
  index = 0;
  do {
    username[index] = username[index] + ((byte)j & 0x10);
    i = 0xffffffffffffffff;
    j = j + 1;
    index = (ulonglong)j;
    do {
      i = i + 1;
    } while (username[i] != '\0');
  } while (index < i);
}

j = 0;
lVar6 = -0x1;
do {
  lVar6 = lVar6 + 1;
} while (username[lVar6] != '\0');

pcVar8 = username;

----------------------------------------------------------------------------------------------------

Step 3: add tilde character (126)
adds 126 to each character, shifting them way up in the ASCII table
----------------------------------------------------------------------------------------------------

if (lVar6 != 0) {
  do {
    *pcVar8 = *pcVar8 + '~';
    j = j + 1;
    index = 0xffffffffffffffff;
    do {
      index = index + 1;
    } while (username[index] != '\0');
    pcVar8 = pcVar8 + 1;
  } while ((ulonglong)(longlong)j < index);
}

index = 0xffffffffffffffff;
do {
  index = index + 1;
} while (username[index] != '\0');

j = 0;
----------------------------------------------------------------------------------------------------

Step 4: multiply by 5 and copy to buffer
takes each character, multiplies by 5, stores in temp buffer for later use
----------------------------------------------------------------------------------------------------

if (index != 0) {
  pcVar8 = local_30;
  do {
    j = j + 1;
    *pcVar8 = pcVar8[(longlong)username - (longlong)local_30] * '\x05';
    pcVar8 = pcVar8 + 1;
  } while ((ulonglong)(longlong)j < index);
}
----------------------------------------------------------------------------------------------------

Step 5: concatenate the multiplied buffer
finds end of username string, appends the x5 buffer to double the length
----------------------------------------------------------------------------------------------------

pcVar8 = username + -1;
do {
  pcVar1 = pcVar8 + 1;
  pcVar8 = pcVar8 + 1;
} while (*pcVar1 != '\0');

lVar6 = 0;
do {
  cVar2 = local_30[lVar6];
  pcVar8[lVar6] = cVar2;
  lVar6 = lVar6 + 1;
} while (cVar2 != '\0');

do {
  uVar9 = uVar9 + 1;
} while (username[uVar9] != '\0');

j = 0;
index = local_128[0];
----------------------------------------------------------------------------------------------------

Step 6: generate quadratic hash
adds each character plus position squared to create final checksum
----------------------------------------------------------------------------------------------------

if (uVar9 != 0) {
  do {
    cVar2 = *username;
    username = username + 1;
    iVar7 = j * j;
    j = j + 1;
    local_128[0] = local_128[0] + (longlong)(cVar2 + iVar7);
    index = local_128[0];
  } while ((ulonglong)(longlong)j < uVar9);
}

----------------------------------------------------------------------------------------------------
  local_38[0] = 0;
  pvVar5 = GetCurrentProcess();
  BVar4 = CheckRemoteDebuggerPresent(pvVar5,local_38);

----------------------------------------------------------------------------------------------------

Step 7: anti-debug check and password generation
checks for debuggers, if clear then runs 3-round hash on the index value
first round: shifts index right by 30 bits, XORs with original, multiplies by hash constant
second round: shifts result right by 27 bits, XORs with itself, multiplies by second hash constant
final round: right shift by 31 bits and XOR to finalize the password
----------------------------------------------------------------------------------------------------
  if ((BVar4 != 0) && (BVar4 = IsDebuggerPresent(), BVar4 == 0)) {
    uVar9 = (index >> 0x1e ^ index) * -0x40a7b892e31b1a47;
    uVar9 = (uVar9 >> 0x1b ^ uVar9) * -0x6b2fb644ecceee15;
    *password = uVar9 >> 0x1f ^ uVar9;
    FUN_1400015d0(local_10 ^ (ulonglong)auStack_148);
    return;
  }
----------------------------------------------------------------------------------------------------
  debugger_found();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
This is my password generator I created in C++ using the logic in the function above.
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
#include <iostream>
#include <string>
unsigned long long generate_password(const std::string& input_username) {
    std::string username = input_username;
    int username_len = username.length();
    
    // apply all transformations we found above in one loop
    if (username_len > 0) {
        for (int i = 0; i < username_len; i++) {
            username[i] += ((i + 1) ^ 0x30);
            username[i] += (i & 0x10); 
            username[i] += '~';
        }
        
        for (int i = 0; i < username_len; i++) {
            username += (char)(username[i] * 5);
        }
    }
    
    unsigned long long hash = 0;
    int final_len = username.length();

    // go through the modified username and put into hash var
    for (int i = 0; i < final_len; i++) {
        hash += username[i] + (i * i);
    }

    // apply magic number hash calculations
    unsigned long long result = hash;
    result = ((result >> 30) ^ result) * 0xbf58476d1ce4e5b9ULL;
    result = ((result >> 27) ^ result) * 0x94d049bb133111ebULL;
    result = (result >> 31) ^ result;
    
    // return the final password
    return result;
}

int main() {
    std::string input_username;
    
    std::cout << "Password Generator" << std::endl;
    std::cout << "Enter username: ";
    
    if (std::getline(std::cin, input_username)) {
        unsigned long long password = generate_password(input_username);
        
        std::cout << "Generated Password: " << password << std::endl;
        std::cout << "Generated Password (hex): 0x" << std::hex << password << std::endl;
    } else {
        std::cerr << "Error reading input" << std::endl;
        return 1;
    }
    
    return 0;
}


