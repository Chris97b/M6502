#pragma once
#ifndef M6502_H
#define M6502_H

#include "OpcodeLookup.h"
#include <map>

using namespace std;
using byte = uint8_t;
using word = uint16_t;

struct StatusFlags
 {
 byte N : 1;
 byte V : 1;
 byte B : 1;
 byte D : 1;
 byte I : 1;
 byte Z : 1;
 byte C : 1;
 };


class M6502
 {
 public:

  byte A, X, Y, SP;
  word PC;
  StatusFlags Status;
  byte RAM[65536];
  OpcodeLookup OL;
  bool EnableBCDMode=false;
  bool EnableUndocumentedInstructions = false;
  int Cycles = 0;
  bool InstructionComplete = false;
  bool CPUHalt = false;

  M6502();

  void WriteRAM(word addr, byte value);
  byte ReadRAM(word addr);
  void Push(byte Data);
  byte Pop();
  void Reset();
  byte FetchIns();
  word ResolveAddress(byte Opcode, word AdditionalBytes, bool Undoc=false);
  void Execute();
  void NMI();
  void IRQ();
  map <word, string> Disassemble(word StartAddr, word StopAddr);
  string ToHex(word Num, byte Dec);
  

 };




#endif