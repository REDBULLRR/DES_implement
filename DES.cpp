#include<bitset>    // bits operation and memory saving
#include<iostream>  // std::cout
#include<fstream>   // file I/O
#include<string>    // std::string
#include<iomanip>   // std::hex
//#include<algorithm> // std::reverse
using namespace std;

const int N_TEST = 5;       // 測資數
const int BYTE_SIZE = 8;    // 單個 byte 擁有的 bit 數
const int MAX_STR_SIZE = 8; // str_to_binary(string) 一次能轉換的最大 string 長度


// ======== Sub Functions ===========

string DES(string plaintext, string key);
// 對輸入的明文（size:8）和金鑰（size：8）執行 DES 加密，回傳密文

bitset<64> apply_IP(bitset<64> origin_plaintext);
// 對原始 plaintext (64-bits）套用 IP 的轉換，得 IP_plaintext（64 bits）

bitset<56> apply_PC_1(bitset<64> originKey);
// 對原始 Key (64-bits）套用 PC-1 的轉換，得 Key+（56 bits）

bitset<64> str_to_binary(string aStr);
// 將輸入字串（長度最大為 8 個字元）的 ASCII 轉換為 binary string （每個字元轉換為 8 個 bit）
// aStr: maximum to 8 characters (expect exactly 8 charcters)
// Every character will be converted to bitset<8> type.
// Ex: "A" -(ASCII)-> "41"(Hex) --> "0010 1001"(binary); 
// Ex: "0" -(ASCII)-> "30"(Hex) --> "0001 1110"(binary).

// =========== Main Function ============
int main()
{
  // purpose
  cout <<"This program performs DES encryption."<<endl;
  
  // 從 DES-Key-Plaintext.txt 讀入測資
  ifstream inFile;
  ofstream outFile;
  
  inFile.open("DES-Key-Plaintext.txt"); // 開檔
  outFile.open("out.txt");
  
  // Loop though pairs of (key, plaintext)
  for(int i=0; i<N_TEST; i++)
  {
    // 從 DES-Key-Plaintext.txt 依序得到 key 和 plaintext
    string plaintext, key;
    inFile>>key>>plaintext;
    
    // Get the cipher text
    cout <<DES(plaintext, key)<<endl; 
  }
  
  return 0;
}

// =========== Sub Function ============
// 對輸入的明文和金鑰執行 DES 加密，回傳密文
string DES(string plaintext, string key)
{
  bitset<64> plaintext_2, key_2; // plaintext and key in binary
  
  // Step1: 將 plaintext 和 key 轉換為 64-bits binary form
  plaintext_2 = str_to_binary(plaintext);
  key_2 = str_to_binary(key);
  
  // Step2: 產生 Sub keys
  
  
  // Step3: 
  
  // Step4:
  
  // Step5:
  
  return cipherText;
}
 

// 對原始 Key (64-bits）套用 PC-1 的轉換，得 Key+（56 bits）
bitset<56> apply_PC_1(bitset<64> originKey)
{
  //cout <<"originKey="<<originKey<<endl<<endl;

  int PC_1[56]={57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};

  bitset<56> newKey;
  int newIdx;

  // Create the 56-bits newKey 
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
    
  cout <<"newKey="<<newKey<<endl;
  return newKey;
}

// 將輸入字串（長度最大為 8 個字元）的 ASCII 轉換為 binary string （每個字元轉換為 8 個 bit）
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



bitset<64> apply_IP(bitset<64> origin_plaintext)
{
  int IP[64]={58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

  bitset<64> IP_plaintext;
  int newIdx;

  // Create the 56-bits newKey 
  for(int i=63; i>=0; i--)
  {
    //cout <<"i="<<i<<endl;
    newIdx = 64-IP[64-i];
    IP_plaintext[i] = origin_plaintext[newIdx];

    //test
    /*cout <<"newIdx="<<newIdx<<", originKey[newIdx]="<<originKey[newIdx]<<", PC_1[63-i]="<<IP[63-i]<<endl<<IP_plaintext<<endl<<endl;
     if(i==50) break;
     */
  }
    
  cout <<"IP_plaintext="<<IP_plaintext<<endl;
  return IP_plaintext;
}
