#include<bitset>
#include<iostream>
#include<string>
using namespace std;

void Test()
{
  bitset<4> test(string("1111"));
  

  cout << hex << uppercase << test.to_ullong()<<endl;
  int t = static_cast<int>(test.to_ulong());
  cout << dec << nouppercase << t <<endl;

  
}