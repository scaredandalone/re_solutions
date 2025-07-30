/*
      _ _,---._
   ,-','       `-.___
  /-;'               `._
 /\/          ._   _,'o \
( /\       _,--'\,','"`. )
 |\      ,'o     \'    //\
 |      \        /   ,--'""`-.
 :       \_    _/ ,-'         `-._
  \        `--'  /                )
   `.  \`._    ,'     ________,','
     .--`     ,'  ,--` __\___,;'
      \`.,-- ,' ,`_)--'  /`.,'
       \( ;  | | )      (`-/
         `--'| |)       |-/
           | | |        | |
           | | |,.,-.   | |_
           | `./ /   )---`  )
          _|  /    ,',   ,-'
         ,'|_(    /-<._,' |--,
         |    `--'---.     \/ \
         |          / \    /\  \
       ,-^---._     |  \  /  \  \
    ,-'        \----'   \/    \--`.
   /            \              \   \
   written by scaredandalone
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
link to the picoctf page: https://play.picoctf.org/practice/challenge/458?category=3&page=1&search=perplex
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

 Original Code from Ghidra diassembler:
 This is the main function of the challenge, it runs a check on the user_input length and then begins the validation steps.
 It executes some bitwise operations to seperate individual bits from both the user_input and the secret array of bytes and compares them in order to test for validity.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool check_input(char *input)

{
  bool bVar1;
  size_t input_len;
  byte secret [36];
  int secret_bit_idx;
  uint secret_byte_idx;
  int input_bit_idx;
  int input_byte_idx;
  
  input_len = strlen(input);
  if (input_len == 27) {
    secret[0] = 0xe1;
    secret[1] = 0xa7;
    secret[2] = 0x1e;
    secret[3] = 0xf8;
    secret[4] = 0x75;
    secret[5] = 0x23;
    secret[6] = 0x7b;
    secret[7] = 0x61;
    secret[8] = 0xb9;
    secret[9] = 0x9d;
    secret[10] = 0xfc;
    secret[0xb] = 0x5a;
    secret[0xc] = 0x5b;
    secret[0xd] = 0xdf;
    secret[0xe] = 0x69;
    secret[0xf] = 0xd2;
    secret[0x10] = 0xfe;
    secret[0x11] = 0x1b;
    secret[0x12] = 0xed;
    secret[0x13] = 0xf4;
    secret[0x14] = 0xed;
    secret[0x15] = 0x67;
    secret[0x16] = 0xf4;
    input_byte_idx = 0;
    input_bit_idx = 0;
    for (secret_byte_idx = 0; secret_byte_idx < 23; secret_byte_idx = secret_byte_idx + 1) {
      for (secret_bit_idx = 0; secret_bit_idx < 8; secret_bit_idx = secret_bit_idx + 1) {
        if (input_bit_idx == 0) {
                    
          input_bit_idx = 1;
        }
        if (0 < ((int)input[input_byte_idx] & 1 << (7U - (char)input_bit_idx & 31)) !=
            0 < ((int)(char)secret[(int)secret_byte_idx] & 1 << (7U - (char)secret_bit_idx & 31))) {
          return true;
        }
        input_bit_idx = input_bit_idx + 1;
        if (input_bit_idx == 8) {
          input_bit_idx = 0;
          input_byte_idx = input_byte_idx + 1;
        }
        input_len = strlen(input);
        if ((long)input_byte_idx == input_len) {
          return false;
        }
      }
    }
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  return bVar1;
}

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
This is the cpp script I wrote to decode the "expected" or "secret" bytes in the array.
As mentioned in my walkthrough, the ASCII chars of the flag are packed into the array of bytes.
Since ASCII chars are 7 bytes (with the first byte ALWAYS being 0), we need to extract the contents 
of the bytes, and add a 0 in front of every 7 bits, in order to create readable ASCII text.
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/


#include <iostream>

int main() {
    unsigned char expected_bytes[23] = {
        0xe1, 0xa7, 0x1e, 0xf8, 0x75, 0x23, 0x7b, 0x61,
        0xb9, 0x9d, 0xfc, 0x5a, 0x5b, 0xdf, 0x69, 0xd2,
        0xfe, 0x1b, 0xed, 0xf4, 0xed, 0x67, 0xf4
    };
    
    unsigned char reconstructed[27] = {0};  
    
    int input_bit = 0;        // bit we are reading (0-183)
    int output_char = 0;      // char we are on (0-26)
    int char_bit = 1;         // current bit in the char (1-7, skips bit 0)
    
    // Loop through all 184 bits in the input data (23 bytes * 8 bits)
    for (int i = 0; i < 23 * 8; i++) {
        
        // STEP 1: Extract current bit from input data
        int byte_idx = input_bit / 8;          
        int bit_idx = 7 - (input_bit % 8);  // MSB first 
        bool bit_is_set = (expected_bytes[byte_idx] & (1 << bit_idx)) != 0;
        
        // STEP 2: If bit is set, place it in the output character (right to left)
        if (output_char < 27 && bit_is_set) {
            reconstructed[output_char] |= (1 << (7 - char_bit));
        }
        
        // STEP 3: Move to next positions
        input_bit++;     
        char_bit++;     
        
        // STEP 4: When we've used 7 bits for current char, move to next char
        if (char_bit == 8) {
            char_bit = 1;        // skip bit 0
            output_char++;      
        }
    }
    
    for (int i = 0; i < 27; i++) {
        std::cout << (char)(reconstructed[i]);
    }
    
    return 0;
}