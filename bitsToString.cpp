#include<bitset>
#include<iostream>
#include<string>
using namespace std;

string bitsToHexString(bitset<64> bits)
{
  //test
  cout <<"bitsToString:\n";

  string cipherText = "";
  
  // byte-by-byte 分割原 64-bits 位元串
  for(int i=63; i>=7; i-=8)
  {
    bitset<8> aCharInBin;

    for(int j=0; j<8; j++)
      aCharInBin[7-j] = bits[i-j];    
      
    // 二進位轉十六進位，並以字串型態儲存（如：12345ABC）
    int aCharInInt= static_cast<int>(aCharInBin.to_ulong());
    string hex="0123456789ABCDE";
    string aCharInHex;
    aCharInHex = hex[aCharInInt/16] + hex[aCharInInt%16];
    cipherText += aCharInHex;
  }
  cout <<"cipherText="<<cipherText<<endl;

  return cipherText;
}
