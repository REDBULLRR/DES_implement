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

> **Debugging**:
> 
> 1. 檢查 binary 有沒有轉換正確。
> ```python
> >>> int('01100001', 2)
> 97
> ```
> 
> 2. 批量檢查 
> ```python
> binStr = '0110000101100010011000110110010001100101011001100110011101101000'
> originInt = [int(bin, 2) for bin in [binStr[x:x+8] for x in range(0,len(binStr), 8)]]
> 
> >>> originInt
> [97, 98, 99, 100, 101, 102, 103, 104]
> ```
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

#### 1. 讀入 plaintext, key，將它倆轉換為二進位
> 假設： `plaintext`, `key` 皆為 size=16 的 string。
> 

* 每個字元用 8 個 bits 表示，空位數補 0
* **`plainText`**: size ８ 的字串 --> (decimal ASCII) --> Hex ASCII <string>[16] -->  bitset<64> (define by <bitset>) 
* **`key`**: size 8 的字串 --> （同上）--> bitset<64>

 
> 可能要考慮的防呆：`plaintext` 和 `key` 的 Hex 字串長不及 16 或大於 16。
> 若有這樣的 Case，考慮取 `plaintext` repeat ，補至 16 的倍數。 


#### 2. Create 16 subkeys, each of which is 48-bits long

##### 2-1. 根據下表，把 `Key` (**64** bits) 置換為 `Key+` (**56** bits)
* `Key+ = applying_PC_1(Key)`
* 規則：第一個 bit 替換為第 57 個 bit

                  PC-1

        57   49    41   33    25    17    9
         1   58    50   42    34    26   18
        10    2    59   51    43    35   27
        19   11     3   60    52    44   36
        63   55    47   39    31    23   15
         7   62    54   46    38    30   22
        14    6    61   53    45    37   29
        21   13     5   28    20    12    4


##### 2-2. 把 `Key+` 從正中間切成左右兩半：`C_0`, `D_0` (各 28 bits）

##### 2-3. 計算 `C_1`, `D_1` ~ `C_16`, `D_16` (56 bits)
```note
Loop: n=1~16 

C_n = nleftShift( C_{n-1} , IterationNum) 
D_n = nleftShift( D_{n-1} , IterationNum) 
```
* 參照下表做 shifts:


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

##### 2-4. 計算 `K_1`~`K16` (48 bits)

* `K_n = applying_PC_2( C_n D_n )`

                          PC-2

             14    17   11    24     1    5
              3    28   15     6    21   10
             23    19   12     4    26    8
             16     7   27    20    13    2
             41    52   31    37    47   55
             30    40   51    45    33   48
             44    49   39    56    34   53
             46    42   50    36    29   32


#### 3. Encode each 64-bit block of data.
##### 3-1. Applying **initial permutation IP**:

                           IP
          58    50   42    34    26   18    10    2
          60    52   44    36    28   20    12    4
          62    54   46    38    30   22    14    6
          64    56   48    40    32   24    16    8
          57    49   41    33    25   17     9    1
          59    51   43    35    27   19    11    3
          61    53   45    37    29   21    13    5
          63    55   47    39    31   23    15    7
 
 to the `plaintext`, s.t.
* `plaintext_IPed = apply_IP(plaintext)`

##### 3-2. 把 `plaintext_IPed` 切成兩半：`L_0`,`R_0` (各 32 bits）
##### 3-3. 執行 F function
* `L_n = R_{n-1}`
* `R_n = L_{n-1} + f(R_{n-1},Kn)`
* 此處 `+` 表示 ＸＯＲ運算

#### 4. 
#### 5. 
#### 6. 
#### 7. 
#### 8. 
#### 9. 

> Steps Reference: [The DES Algorithm Illustrated - by J. Orlin Grabbe](http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm?fbclid=IwAR1q6qC4QxhGxUqaT1eFXldFMpauoQMuCbMm3E1RLsXxNTvi4PiE_evVA9A)
