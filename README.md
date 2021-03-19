# DES_implement
DES (Data Encryption Standard) encryption and decryption implement.


## Input format
An ordered pair of keys and plaintexts in characters, such as “12345678 Advanced”. 

Each character is interpreted as its ASCII code, e.g., ‘A’= 41 (Hex)
## Output format
16 hex characters, such as AE184796707E59FB,which is the ciphertext of the above key and plaintext.


## Test sample for correctness
(key-plaintext-ciphertext):

12345678 Advanced AE184796707E59FB

> Test sample Reference: [The DES Algorithm Illustrated - by J. Orlin Grabbe](http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm?fbclid=IwAR1q6qC4QxhGxUqaT1eFXldFMpauoQMuCbMm3E1RLsXxNTvi4PiE_evVA9A)

## Other Request
**Language**: 
Use C or C++.


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

## Implement
### Data Type
`#include<bitset>`
> Refer: [bitset 整理](https://edisonx.pixnet.net/blog/post/34045379)

### 步驟

1. 
2. 
3. 
4. 
5. 
6. 
7. 
8. 
