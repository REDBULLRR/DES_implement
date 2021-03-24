#include<bitset>
#include<iostream>
using namespace std;
// E table
const int E[48]={32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};

//S-boxes
int S1[64]={14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7, 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8, 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0, 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},

S2[64]={15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10, 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5, 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15, 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},

S3[64]={10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8, 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1, 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7, 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},

S4[64]={7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15, 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9, 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4, 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},

S5[64]={2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9, 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6, 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14, 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},

S6[64]={12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11, 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8, 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6, 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},

S7[64]={4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1, 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6, 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2, 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}, 

S8[64]={13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7, 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2, 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8, 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};

//有需要提升 performance 時可試試。不知管不管用。
//const int* Sboxes[8]={S1, S2, S3, S4, S5, S6, S7, S8};

// Straight P-box
const int P[32]={16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};

bitset<48> apply_E(bitset<32> input);
bitset<32> apply_SBox(bitset<48> input);
bitset<32> apply_straitPBox(bitset<32> input);
bitset<4> intTo4Bits(int input);

bitset<32> F_function(bitset<32> input, bitset<48> subKey)
{
  bitset<48> expan_Pbox_result = apply_E(input);
  return apply_straitPBox(apply_SBox(subKey^expan_Pbox_result));
}

bitset<48> apply_E(bitset<32> input)
{
  //test
  //cout <<"Apply E-table:\n";
  //cout <<"input="<<input<<endl;

  bitset<48> output;
  int newIdx;

  // Create the 56-bits newKey 
  for(int i=47; i>=0; i--)
  {
    //cout <<"i="<<i<<endl;
    newIdx = 32-E[47-i];
    output[i] = input[newIdx];

  }
    
  //cout <<"output="<<output<<endl;
  return output;
}


bitset<32> apply_SBox(bitset<48> input)
{
  //test
  //cout <<"\nApply SBoxes:\n";
  //cout <<"input="<<input<<endl;

  bitset<32> output;
  
  for (int i=47; i>=5; i-=6)
  {
    int *Sbox;
    switch(i)
    {
    case 47:
    //cout <<"Take S1 box\n";
    Sbox = S1;
      break;
    
    case 41:
    //cout <<"Take S2 box\n";
    Sbox=S2;
      break;
    
    case 35:
    //cout <<"Take S3 box\n";
    Sbox=S3;
      break;
    
    case 29:
    //cout <<"Take S4 box\n";
    Sbox=S4;
      break;
    
    case 23:
    //cout <<"Take S5 box\n";
    Sbox=S5;
      break;
    
    case 17:
    //cout <<"Take S6 box\n";
    Sbox=S6;
      break;
    
    case 11:
    //cout <<"Take S7 box\n";
    Sbox=S7;
    break;

    case 5:
    //cout <<"Take S8 box\n";
    Sbox=S8;
    break;

    default:
      cout <<"Error\n";
      break;
    }
    
    bitset<2> row_n_inBits;
    bitset<4> col_n_inBits;

    // separate the row bits
    row_n_inBits[1] = input[i];
    row_n_inBits[0] = input[i-5];

    // separate the column bits
    col_n_inBits[3] =input[i-1];
    col_n_inBits[2] =input[i-2];
    col_n_inBits[1] =input[i-3];
    col_n_inBits[0] =input[i-4];

    // convert the binary number into decimal
    int row_n = static_cast<int>(row_n_inBits.to_ulong()),
        col_n = static_cast<int>(col_n_inBits.to_ulong()),
        targetIdx;

    //test
    //cout <<"row_n="<<row_n<<endl<<"col_n="<<col_n<<endl;

    // compute the target decimal number's index in Sbox and convert it into 4-bits
    targetIdx = row_n*16 + col_n; 
    bitset<4> new4Bits = intTo4Bits(Sbox[targetIdx]);

    // store the converted bits into output 
    output[(i/6+1)*4-1]  = new4Bits[3];
    output[(i/6+1)*4-2]  = new4Bits[2];
    output[(i/6+1)*4-3]  = new4Bits[1];
    output[(i/6+1)*4-4]  = new4Bits[0];

    //test
    //cout <<"For i="<<i<<", output="<<output<<endl;
  }

  //test
  //cout <<"output="<<output<<endl;

  return output;
}


// Ex: 5 --> 0101
bitset<4> intTo4Bits(int input)
{
  //test
  //cout <<"intTo4Bits:\n";
  //cout <<"input="<<input<<endl;

  bitset<4> bin; 
  for(int i=0; i<4 && input>0; i++)
  {
    bin[i]=input%2;
    input/=2;
  }
  //test
  //cout <<"bin="<<bin<<endl;
  return bin;
}

// do permutation with PBox
bitset<32> apply_straitPBox(bitset<32> input)
{
  //test
  //cout <<"\nApply straightPBox:\n";
  //cout <<"input="<<input<<endl;

  bitset<32> output;
  int newIdx;

  // Create the 56-bits newKey 
  for(int i=31; i>=0; i--)
  {
    //cout <<"i="<<i<<endl;
    newIdx = 32-P[31-i];
    output[i] = input[newIdx];

    //test
    /*cout <<"newIdx="<<newIdx<<", originKey[newIdx]="<<originKey[newIdx]<<", PC_1[63-i]="<<IP[63-i]<<endl<<IP_plaintext<<endl<<endl;
     if(i==50) break;
     */
  }
    
  //cout <<"output="<<output<<endl;
  return output;
}