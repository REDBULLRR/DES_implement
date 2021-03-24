#include<iostream>
#include<bitset>
using namespace std;
const int MAX_STR_SIZE = 8;
const int BYTE_SIZE = 8;

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


