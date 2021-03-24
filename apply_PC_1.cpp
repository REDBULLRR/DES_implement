#include<bitset>    // bits operation and memory saving
#include<iostream>  // std::cout
#include<string>    // std::string
using namespace std;


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
