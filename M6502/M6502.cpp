// M6502.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdint>
#include "OpcodeLookup.h";
#include "M6502.h"
#include <fstream>


int main()
{
 M6502 CPU;
 CPU.Reset();
 ifstream file("6502_functional_test.bin", ios::in | ios::binary);
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
 

 

 
}

