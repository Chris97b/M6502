// M6502.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdint>
#include "OpcodeLookup.h";
#include "M6502.h"
#include <fstream>
#include <iomanip>


int main(int argc, char** argv)
{

 
 M6502 CPU;
 CPU.Reset();
 CPU.EnableBCDMode = 0;
 ifstream file("6502_functional_test_nodec.bin", ios::in | ios::binary);
 //ifstream file("6502_functional_test_incdec.bin", ios::in | ios::binary);
 //ifstream file("65C02_extended_opcodes_test.bin", ios::in | ios::binary); //65C02 tests, not working (by design)
 char junk = 0;
 char* buf = &junk;
 for (int i = 0; i < 65527; i++)
  {
   file.seekg(i);
   file.read(buf, 1);
   CPU.RAM[0x0a + i] = *buf;
   //CPU.RAM[i] = *buf;
  }
 CPU.PC = 0x0400;
 bool PCLooping = false;
 word OldPC = CPU.PC;
 int LoopCount = 0;
 while (!PCLooping)
  {
  //cout << "PC=0x" << CPU.ToHex(CPU.PC, 4) << endl;
  OldPC = CPU.PC;
  CPU.Execute();
  if (OldPC == CPU.PC)
   LoopCount++;
  else
   LoopCount = 0;
  if (LoopCount == 100)
   PCLooping = true;
  }
 cout << "PC Looping at " << CPU.ToHex((int)OldPC, 4) << endl;
 //CPU.Execute(5);


 /* //Testing Disassembly ideas
 OpcodeLookup DisOpcode;
 int Offset = 0x0408;
 for (int i = 0; i < 16; i++)
  {
  byte Ins = CPU.ReadRAM(Offset + i - 7);
  string Mnemonic = DisOpcode.Mnemonic(Ins);
  string Addressing = DisOpcode.Addressing(Ins);

  word ExtraBytes = 0;
  int* Stuff=nullptr;
  if (DisOpcode.Bytes(Ins) > 1)
   {
   ExtraBytes = CPU.ReadRAM(Offset + i + 1 - 7);
   Offset++;
   }
  if (DisOpcode.Bytes(Ins) == 3)
   {
   ExtraBytes |= (CPU.ReadRAM(Offset + i + 1 - 7) << 8);
   Offset++;
   }
  word Address = CPU.ResolveAddress(Ins, ExtraBytes, Stuff);
  cout << Mnemonic << "    0x";
  if (Addressing == "IMM")
   cout << hex << uppercase << (int)ExtraBytes;
  else
   cout << hex << uppercase << (int)CPU.ReadRAM(Address);
  cout << "     - (";
  if (Addressing == "IMM")
   cout << dec << (int)ExtraBytes;
  else
   cout << dec << (int)CPU.ReadRAM(Address);
  cout<< ")     { " << DisOpcode.Addressing(Ins) << " }" << endl;
  }
  */

 return 0;
}

