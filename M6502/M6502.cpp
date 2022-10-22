// M6502.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdint>
#include "OpcodeLookup.h";
#include "M6502.h"
#include <fstream>


int main()
{

 byte Op1 = 0x41;
 byte Op2 = 0x01;


 //BCD Testing
 /*
 int Op1Split = (((Op1 >>4)*10) + (Op1 & 0x0F));
 cout << "Op1: " << Op1Split << endl;
 int Op2Split = (((Op2 >>4)*10) + (Op2 & 0x0F));
 cout << "Op2: " << Op2Split << endl;
 int Result = Op1Split + Op2Split;
 int Ones = Result % 10;
 cout << "Ones: " << Ones << endl;
 cout << "Tens: " << ((Result - Ones) % 100)/10 << endl;
 cout << "result: " << Result << endl;
 */

 /*
 int ToHex = 42;
 int Ones = ToHex % 10;
 int Tens = ((ToHex - Ones)) % 100 / 10;
 int BCDHex = (Tens << 4) | Ones;
 cout << "Hex: 0x" << hex << uppercase << BCDHex << endl;

 exit(EXIT_SUCCESS);
 */



 M6502 CPU;
 CPU.Reset();
 CPU.EnableDec = 1;
 ifstream file("6502_functional_test_incdec.bin", ios::in | ios::binary);
 char junk = 0;
 char* buf = &junk;
 for (int i = 0; i < 65527; i++)
  {
   file.seekg(i);
   file.read(buf, 1);
   CPU.RAM[0x0a + i] = *buf;
  }
 CPU.PC = 0x0400;
 CPU.Execute(5);
 

 

 return 0;
}

