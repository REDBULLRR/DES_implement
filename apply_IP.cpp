#include<iostream>
#include<bitset>
using namespace std;

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