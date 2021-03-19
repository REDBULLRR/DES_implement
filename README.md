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

1. Input

假設： plaintext, key 皆為 size=16 的 string。

**PlainText**: size ８ 的字串 --> (decimal ASCII) --> Hex ASCII <string>[16] -->  bitset<64> (define by <bitset>) 

**Key**: size 8 的字串 --> （同上）--> bitset<64>

> 可能要考慮的防呆：Plaintext 和 Key 的 Hex 字串長不及 16 或大於 16。
> 若有這樣的 Case，考慮取 plaintext repeat ，補至 16 的倍數。 


2. **Step 1: Create 16 subkeys, each of which is 48-bits long**

2-1. 根據下表，把 Key (**64** bits) 置換為 Key+ (**56** bits)

* 規則：第一個 bit 替換為第 57 個 bit

** PC-1**

              57   49    41   33    25    17    9
               1   58    50   42    34    26   18
              10    2    59   51    43    35   27
              19   11     3   60    52    44   36
              63   55    47   39    31    23   15
               7   62    54   46    38    30   22
              14    6    61   53    45    37   29
              21   13     5   28    20    12    4
2-2. 把 K+ 從正中間切成左右兩半：C_0, D_0

2-3. 
```note
Loop: n=1~16 

C_n = nleftShift( C_{n-1} , IterationNum) 
D_n = nleftShift( D_{n-1} , IterationNum) 
```
參照下表做 shifts:


                     Iteration     Number of
                      Number      Left Shifts

                          1          1
                          2          1
                          3          2
                          4          2
                          5          2
                          6          2
                          7          2
                          8          2
                          9          1
                         10          2
                         11          2
                         12          2
                         13          2
                         14          2
                         15          2 // C_14 (D_14) --Do 2 Left shift--> C_15 (D_15)
                         16          1 // C_15 (D_15) --Do 1 Left shift--> C_16 (D_16)
4. 
5. 
6. 
7. 
8. 
9. 
10. 
