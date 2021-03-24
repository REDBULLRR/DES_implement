#include<bitset>
#include<iostream>
#include<string>
using namespace std;
const int ROUND_N=16;

// ====subfunc=====
bitset<56> apply_PC_1(bitset<64> originKey);
bitset<64> apply_IP(bitset<64> origin_plaintext);
bitset<64> str_to_binary(string aStr);
void DES(string plaintext, string key);
bitset<32> F_function(bitset<32> input, bitset<48> subKey);
void generateSubKeys(bitset<56> K_0, bitset<48> subKeys[]); 
void Test();
bitset<64> apply_IIP(bitset<64> input);

//test subfunc
void forLoopTest();

int main() {
  cout << "Test:\n";
  string plaintext="Advanced", key="12345678";

  DES(plaintext, key);

  return 0;
}
