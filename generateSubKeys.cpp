#include<bitset>
#include<iostream>
using namespace std;

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