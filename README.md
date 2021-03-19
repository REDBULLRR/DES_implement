# DES_implement
DES (Data Encryption Standard) encryption and decryption implement.

## Input format
An ordered pair of keys and plaintexts in characters, such as “12345678 Advanced”. 

Each character is interpreted as its ASCII code, e.g., ‘A’= 41 (Hex)
## Output format
16 hex characters, such as AE184796707E59FB,which is the ciphertext of the above key and plaintext.


### test sample for correctness
(key-plaintext-ciphertext):

12345678 Advanced AE184796707E59FB

**Language**: 
Use C or C++ to write your code.

1. The source code file with name: `DES.c` or `DES.cpp`.

i. The output file `out.txt` that contains **5 lines of ciphertexts** for the ordered pairs of key and plaintext (**one pair per line**) from the file `DES-Key-Plaintext.txt`.

ii. One line of time (in milliseconds) for the running time of each DES encryption.


2. You can use the following code to compute the running time of a function
```c
#include <time.h>
clock_t start, end;
double cpu_time_used;
start = clock();
... /* Do the work. */
end = clock();

cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
```
