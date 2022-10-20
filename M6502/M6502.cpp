// M6502.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <cstdint>
#include <iomanip>
#include <bitset>
#include "OpcodeLookup.h";
#include "M6502.h"
#include <fstream>


int main()
{
 M6502 CPU;
 //CPU.WriteRAM(0xFFFC, 0x00);
 //CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 //CPU.WriteRAM(0x8000, 0xA1);
 //CPU.WriteRAM(0x8001, 0xFA);
 //CPU.WriteRAM(0x05, 0x74);
 //CPU.WriteRAM(0x06, 0x20);
 //cout << "0b" << bitset<8>((CPU.Status.N << 7) | (CPU.Status.V << 6) | (1 << 5) | (1 << 4) | (CPU.Status.D << 3) | (CPU.Status.I << 2) | (CPU.Status.Z << 1) | CPU.Status.C) << endl;
 //CPU.X = 0x0A;

 streampos size;
 ifstream file("6502_functional_test.bin", ios::in|ios::binary|ios::ate);
 if (file.is_open())
  {
  size = file.tellg();
  char junk = 0;
  char* buf = &junk;
  //65526
  for (int i = 0; i < 64500; i++)
   {
   
   file.seekg(i, ios::beg);
   file.read(buf, 1);

   CPU.RAM[0x0400 + i] = *buf;
   }
  
  //file.seekg(0, ios::beg);
  }
 file.close();

 CPU.PC = 0x0400;
 CPU.Execute(5);
 

 

 
}

