// Create by 0812249 2021.3.24
#include<bitset>    // for bit operation
#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
using namespace std;
// 此程式在我的 Xcode 上總是會在 run-time 引發 EXC_BAD_ACCESS Error
// ===== 參數與轉換用對應表 =====
// Note: 有些表每次 encryption 只用一次，就不寫成 global const 了
const int ROUND_N = 16;     // DES 中的 round 總數
const int MAX_STR_SIZE = 8; // 每次的最長 encryption 字串長
const int BYTE_SIZE = 8;    // 每個 byte 的 bit 數
const int N=5;              // 執行 encryption 的測資數

// E table
const int E[48]={32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};


//有需要提升 performance 時可試試。不知管不管用。
//const int* Sboxes[8]={S1, S2, S3, S4, S5, S6, S7, S8};

// Straight P-box
const int P[32]={16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};


// ===== Sub Functions =====
void DES(string plaintext, string key, ofstream& outFile);
bitset<56> apply_PC_1(bitset<64> originKey);
bitset<64> apply_IP(bitset<64> origin_plaintext);
bitset<64> apply_IIP(bitset<64> input);
bitset<64> str_to_binary(string aStr);
bitset<32> F_function(bitset<32> input, bitset<48> subKey);
void generateSubKeys(bitset<56> K_0, bitset<48> subKeys[]);

// For F-function()
bitset<48> apply_E(bitset<32> input);
bitset<32> apply_SBox(bitset<48> input);
bitset<32> apply_straitPBox(bitset<32> input);
bitset<4> intTo4Bits(int input);

// ===== Main Function =====
int main()
{
    //ifstream inFile;
    ofstream outFile;
    //inFile.open("in.txt");
    outFile.open("out.txt");

    string plaintext1="Advanced", key1="12345678",
    plaintext2="SK888888", key2="87654321", 
    plaintext3="CSisHard", key3="meowmeow",
    plaintext4="Go_Study", key4="45104711",
    plaintext5="ZaWaRuDO", key5="yeahyeah";

    int n=N;// Encrypt repeating times

    // timing
    clock_t start, end;
    double cpu_time_used;
    start = clock();

        //cout <<"Enter plaintext:";
        //inFile >>plaintext;
        //cout <<"Enter key:";
        //inFile >>key;
        
        DES(plaintext1, key1, outFile);
        DES(plaintext2, key2, outFile);
        DES(plaintext3, key3, outFile);
        DES(plaintext4, key4, outFile);
        DES(plaintext5, key5, outFile);

    end = clock();
    cpu_time_used = static_cast<double>(end-start)*1000/CLOCKS_PER_SEC/N;
    outFile<<"Average CPU time used: "<<cpu_time_used<<" ms"<<endl;

    //inFile.close();
    outFile.close();

    return 0;
}

// ===== Sub Functions ======
// 對輸入的明文和金鑰執行 DES 加密，回傳密文
void DES(string plaintext, string key, ofstream& outFile)
{
  bitset<64> cipherText;

  // Step1: 將 plaintext 和 key 轉換為 64-bits binary form
  bitset<64> plaintext_bin, key_bin;
  plaintext_bin = str_to_binary(plaintext);
  key_bin = str_to_binary(key);

  // Step 2: 對 plaintext 和 key 分別執行 IP 轉換和 PC-1 轉換
  bitset<56> K_0; bitset<64> IP_text;
  K_0 = apply_PC_1(key_bin);
  IP_text = apply_IP(plaintext_bin);
    
  // 把 IP_text 拆分成 L, R 左右兩半，各 32-bits
  bitset<32> L_i, R_i;
  for(int i=31; i>=0; i--)
  {
    L_i[i]=IP_text[i+32];
    R_i[i]=IP_text[i];
  }

  // Step 3: 產生 subKeys
  bitset<48> subKeys[16];
  generateSubKeys(K_0, subKeys);

  // Step 4: 走過 16 個 rounds
  for(int i=0; i<ROUND_N; i++)
  {
    bitset<32> temp=R_i;
    R_i = F_function(R_i, subKeys[i])^L_i;
    L_i = temp;
  }

  // Step5: 把 R_16 L_16 (64-bits) 拿去做 Inverse Initial Permutation
  // 合併 R_16, L_16
  bitset<64> R16_L16;
  for(int i=31; i>=0; i--)
  {
    R16_L16[i+32] = R_i[i];
    R16_L16[i] = L_i[i];
  }
  cipherText = apply_IIP(R16_L16);

  // Last: 把密文轉換回 hex， 並印出來
  //cout <<hex<<uppercase << static_cast<int>(cipherText.to_ullong())<<endl; 怪：當這行輸出 93A21FD7 時，下一行指令輸出的則是 81E3DEE593A21FD7（key:12345678, plaintext: advanced）
  outFile <<hex<<uppercase << cipherText.to_ullong()<<" ";
  outFile <<dec<<nouppercase<< key <<" "<<plaintext<<endl<<endl;
}

bitset<32> F_function(bitset<32> input, bitset<48> subKey)
{
  bitset<48> expan_Pbox_result = apply_E(input);
  return apply_straitPBox(apply_SBox(subKey^expan_Pbox_result));
}

bitset<48> apply_E(bitset<32> input)
{
  //test
  //cout <<"Apply E-table:\n";
  //cout <<"input="<<input<<endl;

  bitset<48> output;
  int newIdx;

  // Create the 56-bits newKey
  for(int i=47; i>=0; i--)
  {
    newIdx = 32-E[47-i];
    output[i] = input[newIdx];
  }
    
  //cout <<"output="<<output<<endl;
  return output;
}


bitset<32> apply_SBox(bitset<48> input)
{
  //S-boxes
  int S1[64]={14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7, 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8, 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0, 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},

  S2[64]={15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10, 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5, 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15, 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},

  S3[64]={10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8, 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1, 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7, 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},

  S4[64]={7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15, 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9, 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4, 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},

  S5[64]={2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9, 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6, 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14, 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},

  S6[64]={12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11, 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8, 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6, 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},

  S7[64]={4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1, 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6, 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2, 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},

  S8[64]={13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7, 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2, 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8, 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};

  bitset<32> output;
  
  for (int i=47; i>=5; i-=6)
  {
    int *Sbox;
    switch(i)
    {
        case 47:
            //cout <<"Take S1 box\n";
            Sbox = S1;
              break;
        
        case 41:
            //cout <<"Take S2 box\n";
            Sbox=S2;
              break;
        
        case 35:
            //cout <<"Take S3 box\n";
            Sbox=S3;
              break;
        
        case 29:
            //cout <<"Take S4 box\n";
            Sbox=S4;
              break;
        
        case 23:
            //cout <<"Take S5 box\n";
            Sbox=S5;
              break;
        
        case 17:
            //cout <<"Take S6 box\n";
            Sbox=S6;
              break;
        
        case 11:
            //cout <<"Take S7 box\n";
            Sbox=S7;
            break;

        case 5:
            //cout <<"Take S8 box\n";
            Sbox=S8;
            break;
            
        default:
            cout <<"Error in SBox switching!"<<endl;
            Sbox=S1;
            break;
    }
    
    bitset<2> row_n_inBits;
    bitset<4> col_n_inBits;

    // separate the row bits
    row_n_inBits[1] = input[i];
    row_n_inBits[0] = input[i-5];

    // separate the column bits
    col_n_inBits[3] =input[i-1];
    col_n_inBits[2] =input[i-2];
    col_n_inBits[1] =input[i-3];
    col_n_inBits[0] =input[i-4];

    // convert the binary number into decimal
    int row_n = static_cast<int>(row_n_inBits.to_ulong()),
        col_n = static_cast<int>(col_n_inBits.to_ulong()),
        targetIdx;

    //test
    //cout <<"row_n="<<row_n<<endl<<"col_n="<<col_n<<endl;

    // compute the target decimal number's index in Sbox and convert it into 4-bits
    targetIdx = row_n*16 + col_n;
    bitset<4> new4Bits = intTo4Bits(Sbox[targetIdx]);

    // store the converted bits into output
    output[(i/6+1)*4-1]  = new4Bits[3];
    output[(i/6+1)*4-2]  = new4Bits[2];
    output[(i/6+1)*4-3]  = new4Bits[1];
    output[(i/6+1)*4-4]  = new4Bits[0];

    //test
    //cout <<"For i="<<i<<", output="<<output<<endl;
  }

  //test
  //cout <<"output="<<output<<endl;

  return output;
}


// Ex: 5 --> 0101
bitset<4> intTo4Bits(int input)
{
  //test
  //cout <<"intTo4Bits:\n";
  //cout <<"input="<<input<<endl;

  bitset<4> bin;
  for(int i=0; i<4 && input>0; i++)
  {
    bin[i]=input%2;
    input/=2;
  }
  //test
  //cout <<"bin="<<bin<<endl;
  return bin;
}

// do permutation with PBox
bitset<32> apply_straitPBox(bitset<32> input)
{
  //test
  //cout <<"\nApply straightPBox:\n";
  //cout <<"input="<<input<<endl;

  bitset<32> output;
  int newIdx;

  // Create the 56-bits newKey
  for(int i=31; i>=0; i--)
  {
    //cout <<"i="<<i<<endl;
    newIdx = 32-P[31-i];
    output[i] = input[newIdx];

    //test
    /*cout <<"newIdx="<<newIdx<<", originKey[newIdx]="<<originKey[newIdx]<<", PC_1[63-i]="<<IP[63-i]<<endl<<IP_plaintext<<endl<<endl;
     if(i==50) break;
     */
  }
    
  //cout <<"output="<<output<<endl;
  return output;
}

bitset<64> apply_IIP(bitset<64> input)
{
  //test
  //cout <<"\nApply IIP:\n";
  
  // Inverse Initial Permutation
  int IIP[64]={40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};

  // Create the 64-bits ciphertext
  bitset<64> ciphertext;
  int newIdx;
  for(int i=63; i>=0; i--)
  {
    //cout <<"i="<<i<<endl;
    newIdx = 64-IIP[63-i];
    ciphertext[i] = input[newIdx];
  }
  
  //test
  //cout <<"ciphertext="<<ciphertext<<endl;
  return ciphertext;

}

bitset<64> apply_IP(bitset<64> origin_plaintext)
{
  // Initial Permutation
  int IP[64]={58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

  // Create the 64-bits IP_plaintext
  bitset<64> IP_plaintext;
  int newIdx;
  for(int i=63; i>=0; i--)
  {
    //cout <<"i="<<i<<endl;
    newIdx = 64-IP[63-i];
    IP_plaintext[i] = origin_plaintext[newIdx];

    //test
    /*cout <<"newIdx="<<newIdx<<", originKey[newIdx]="<<originKey[newIdx]<<", PC_1[63-i]="<<IP[63-i]<<endl<<IP_plaintext<<endl<<endl;
     if(i==50) break;
     */
  }
    
  //cout <<"IP_plaintext="<<IP_plaintext<<endl;
  return IP_plaintext;
}

bitset<56> apply_PC_1(bitset<64> originKey)
{
  //cout <<"originKey="<<originKey<<endl<<endl;

  // Permutation Choice 1
  int PC_1[56]={57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};

  // Create the 56-bits newKey
  bitset<56> newKey;
  int newIdx;
  for(int i=55; i>=0; i--)
  {
    //cout <<"i="<<i<<endl;
    newIdx = 64-PC_1[55-i];
    newKey[i] = originKey[newIdx];

    //test
    /*
    cout <<"newIdx="<<newIdx<<", originKey[newIdx]="<<originKey[newIdx]<<", PC_1[63-i]="<<PC_1[63-i]<<endl<<newKey<<endl<<endl;
  */
  }
    
  //cout <<"newKey="<<newKey<<endl;
  return newKey;
}

void generateSubKeys(bitset<56> K_0, bitset<48> subKeys[])
{
  //test
  //cout <<"\nGenerate Sub Keys:\n";
  //cout <<"K_0="<<K_0<<endl;

  // The shifting rule of Cs and Ds
  int shiftRule[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

  // Permutation Choice 2
  int PC_2[48]={14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

  // 把 K_0 左右切成兩半：C_0 和 D_0
  bitset<28> C_0, D_0;
  for(int i=55; i>27; i--)
    C_0[i-28] = K_0[i];

  for(int i=27; i>=0; i--)
    D_0[i] = K_0[i];
  //test
  //cout <<"C_0="<<C_0<<endl<<"D_0="<<D_0<<endl;

  // 計算 C_1, D_1 ~ C_16, D_16 (56 bits)
  bitset<28> C_i=C_0, D_i=D_0;
  for(int i=0; i<16; i++)
  {
    // shift according to the shifting rule
    bitset<1> C_i1, C_i2, D_i1, D_i2;
    C_i1[0] = C_i[27]; C_i2[0]=C_i[26];
    D_i1[0] = D_i[27]; D_i2[0]=D_i[26];

    C_i = C_i << shiftRule[i];
    D_i = D_i << shiftRule[i];
    
    // 把最左邊被 shift 出去的 bit(s) 補到最右邊（"<<" 不會幫我們做這件事）
    if(shiftRule[i]>1)// shift=2
    {
      C_i[1]=C_i1[0]; C_i[0]=C_i2[0];
      D_i[1]=D_i1[0]; D_i[0]=D_i2[0];
    }
    else// shift=1
    {
      C_i[0]=C_i1[0];
      D_i[0]=D_i1[0];
    }
      
    //test
    //cout <<"C_"<<i+1<<"="<<C_i<<endl<<"D_"<<i+1<<"="<<D_i<<endl;

    // get Ci_Di = (C_i 連接 D_i)
    bitset<56> Ci_Di;
    for(int j=27; j>=0; j--)
    {
      Ci_Di[28+j]  = C_i[j];
      Ci_Di[j]     = D_i[j];
    }
    //test
    //cout <<"C"<<i+1<<" D"<<i+1<<"="<<Ci_Di<<endl;

    // 計算各個 subKey 值：K_i = applying_PC_2( C_i D_i )
    int newIdx;
    for(int j=47; j>=0; j--)
    {
      newIdx = 56 - PC_2[47-j];
      subKeys[i][j] = Ci_Di[newIdx];
    }
    //test
    //cout<<"subKeys["<<i<<"] ="<<subKeys[i]<<endl<<endl;
  }
}

bitset<64> str_to_binary(string aStr)
{
  // 檢查 aStr 大小，超過 MAX_STR_SIZE 為非法，回傳 bitset=0
  if (aStr.size() > MAX_STR_SIZE)
  {
    cout <<"Size Error: aStr size too big:"<<aStr.size()<<endl;
    return bitset<64>(string("0")); // 不確定能否這樣寫
  }
  
  string eightBytes="";
  
  for(int i=0; i<BYTE_SIZE; i++)
  {
    int ascii = aStr[i];
    
    //test
    //cout <<"For aStr[i]="<<aStr[i]<<", ascii="<<ascii<<endl;

    string aByte="";
    
    // 將單一字元轉換為其 ASCII 的二進位表示法
    for(int j=0; j<8; j++)
    {
      // 除以二的餘數是 1 ，則二進位下第 j+1 位數是 1
      if (ascii%2==1)
        aByte += "1";
      
      // 除以二的餘數是 0 ，則二進位下第 j+1 位數是 1
      else
        aByte += "0";
      
      //test
      //cout <<"For j="<<j<<", ascii="<< ascii <<", aByte="<<aByte<<endl;
      
      ascii /=2;
    
    }
    
    // append the 8-bit string of the character aStr[i] to string eightBytes (who is empty in default)
    for(int j=7; j>=0; j--)
      eightBytes+=aByte[j];
    
    //test
    //cout <<"char:"<<aStr[i]<<", eightBytes="<<eightBytes<<endl << endl;
  }
  
  //test
  //cout <<"eightBytes="<<eightBytes<<endl;

  return  bitset<64>(eightBytes);
}
