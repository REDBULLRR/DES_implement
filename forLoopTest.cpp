#include<iostream>
#include<bitset>
using namespace std;


void forLoopTest()
{
  cout <<"Test for  Loop:"<<endl;

  bitset<64> test, test2(string("1110111011101110111011101110111011101110111011101110111011101110"));
  
  for (int i=63; i>=32; i--)
  {
    test[i]=test2[i];
    cout <<"test["<<i<<"]="<<test[i]<<endl<<"test="<<test<<endl;
  }
}
