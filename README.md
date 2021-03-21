# DES_implement
DES (Data Encryption Standard) encryption and decryption implement.

線上編譯站：[Replit - DES](https://replit.com/@REDBULLRR/DES#DES.cpp)

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
* Note: 注意  `#include<bitset>` 內建的 `<<` shift 不會把最左的 1 移到最右。
    * Ex: 0110  ==[shift 2]==> 1000 

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
* 表 IP 會把明文 rearrange: 第一個 bit 變成原本的第 58 個 bit，以此類推。

##### 3-2. 把 `plaintext_IPed` 切成兩半：`L_0`,`R_0` (各 32 bits）

#### 4. 製作 F function
* **Expansion P-box**


                      E BIT-SELECTION TABLE

                 32     1    2     3     4    5
                  4     5    6     7     8    9
                  8     9   10    11    12   13
                 12    13   14    15    16   17
                 16    17   18    19    20   21
                 20    21   22    23    24   25
                 24    25   26    27    28   29
                 28    29   30    31    32    1
* **S-Boxes（共 8 個)**
    * input 是 48-bits ，令依序每六個 bits 為一組，共有八組（B1~B8）
    * 映射規則：
        *  1st, 6th bits: row number (binary)
        *  2nd, 3rd, 4th, 5th: column number (binary)
    *  Bi 用 Si 表去對應得到一個十進位整數，此數再轉為 4-bits 形式的二進位數，即為對應結果
    *  不知道行不行得通：寫一個 pointer array，size=8，裡面 8 個 element 分別指到 S1~S8 的頭。這樣我就可以 loop i=0~7 來抓 Si 用了，也不用寫 `switch`。

                             S1
      14  4  13  1   2 15  11  8   3 10   6 12   5  9   0  7
       0 15   7  4  14  2  13  1  10  6  12 11   9  5   3  8
       4  1  14  8  13  6   2 11  15 12   9  7   3 10   5  0
      15 12   8  2   4  9   1  7   5 11   3 14  10  0   6 13


                             S2
      15  1   8 14   6 11   3  4   9  7   2 13  12  0   5 10
       3 13   4  7  15  2   8 14  12  0   1 10   6  9  11  5
       0 14   7 11  10  4  13  1   5  8  12  6   9  3   2 15
      13  8  10  1   3 15   4  2  11  6   7 12   0  5  14  9


                             S3
       10  0   9 14   6  3  15  5   1 13  12  7  11  4   2  8
       13  7   0  9   3  4   6 10   2  8   5 14  12 11  15  1
       13  6   4  9   8 15   3  0  11  1   2 12   5 10  14  7
        1 10  13  0   6  9   8  7   4 15  14  3  11  5   2 12


                             S4
       7  13  14  3   0  6   9 10   1  2   8  5  11 12   4 15
      13   8  11  5   6 15   0  3   4  7   2 12   1 10  14  9
      10   6   9  0  12 11   7 13  15  1   3 14   5  2   8  4
       3  15   0  6  10  1  13  8   9  4   5 11  12  7   2 14


                             S5
       2  12   4   1   7  10   11   6   8   5   3   15   13  0  14  9
      14  11   2  12   4   7   13   1   5   0  15   10    3  9   8  6
       4   2   1  11  10  13    7   8  15   9  12   5     6  3   0 14
      11   8   12  7   1  14    2  13   6  15   0   9    10  4   5  3


                             S6
      12   1  10 15   9  2   6  8   0 13   3  4  14  7   5 11
      10  15   4  2   7 12   9  5   6  1  13 14   0 11   3  8
       9  14  15  5   2  8  12  3   7  0   4 10   1 13  11  6
       4   3   2 12   9  5  15 10  11 14   1  7   6  0   8 13


                             S7
      4  11   2 14  15  0   8 13   3 12   9  7   5 10   6  1
      13  0  11  7   4  9   1 10  14  3   5 12   2 15   8  6
      1   4  11 13  12  3   7 14  10 15   6  8   0  5   9  2
      6  11  13  8   1  4  10  7   9  5   0 15  14  2   3 12


                             S8
      13   2    8   4   6  15  11  1  10  9   3 14   5  0  12  7
       1  15   13   8  10   3   7  4  12  5   6 11   0 14   9  2
       7  11    4   1   9  12  14  2   0  6  10 13  15  3   5  8
       2   1   14   7   4  10   8 13  15 12   9  0   3  5   6 11

* **Straight P-box**

                           P

                    16   7  20  21
                    29  12  28  17
                     1  15  23  26
                     5  18  31  10
                     2   8  24  14
                    32  27   3   9
                    19  13  30   6
                    22  11   4  25
                    


#### 5. 依序算出 `L_1`, `R_1` ~ `L_16`, `R_16`
* `L_n = R_{n-1}`
* `R_n = L_{n-1} + f(R_{n-1},Kn)`，其中 f()是 F function
* 此處 `+` 表示 ＸＯＲ運算
* 不必留存每一個 L 和 R，只要能得到 `L_16` 和 `R_16` 就萬萬歲了

#### 6. 算出密文
##### 6-1. 對 `R_16 L_16` 做 Inverse Initial Permutation
* 64-bits  --> 64-bits

           Inverse Initial Permutation
    40     8   48    16    56   24    64   32
    39     7   47    15    55   23    63   31
    38     6   46    14    54   22    62   30
    37     5   45    13    53   21    61   29
    36     4   44    12    52   20    60   28
    35     3   43    11    51   19    59   27
    34     2   42    10    50   18    58   26
    33     1   41     9    49   17    57   25           

* 可以得到一個 64-bits 的二進位 ciphertext
* 把 ciphertext 按 bytes 轉為 10 進位，變換回字元型態
* 搞定。


> Steps Reference: [The DES Algorithm Illustrated - by J. Orlin Grabbe](http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm?fbclid=IwAR1q6qC4QxhGxUqaT1eFXldFMpauoQMuCbMm3E1RLsXxNTvi4PiE_evVA9A)
> Coding Reference:
> [StackOverflow - convert bitset to int in c++](https://stackoverflow.com/questions/19583720/convert-bitset-to-int-in-c)
