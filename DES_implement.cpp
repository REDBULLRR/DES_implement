#include<bitset>
#include<iostream>
#include<string>
using namespace std;
const int ROUND_N=16; // round 數

bitset<64> str_to_binary(string aStr);
bitset<56> apply_PC_1(bitset<64> originKey);
bitset<64> apply_IP(bitset<64> origin_plaintext);
bitset<32> F_function(bitset<32> input, bitset<48> subKey);
void generateSubKeys(bitset<56> K_0, bitset<48> subKeys[]); 
bitset<64> apply_IIP(bitset<64> input);
string bitsToHexString(bitset<64> bits);

// 對輸入的明文和金鑰執行 DES 加密，回傳密文
void DES(string plaintext, string key)
{
  bitset<64> cipherText;

  // Step1: 將 plaintext 和 key 轉換為 64-bits binary form
  bitset<64> plaintext_bin, key_bin; 
  plaintext_bin = str_to_binary(plaintext);
  //cout <<"plaintext_bin="<<plaintext_bin<<endl;
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
  //cout <<"R16="<<R_i<<endl<<"L16="<<L_i<<endl;

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
  cout <<hex<<uppercase << cipherText.to_ullong()<<" ";
  cout <<dec<<nouppercase<< key <<" "<<plaintext<<endl;

}