#pragma once
#ifndef M6502_H
#define M6502_H

#include "OpcodeLookup.h"
#include <bitset>
#include <chrono>

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

  M6502()
   {
   //Do Stuff
   A = Y = X = PC = 0;
   Status.N = Status.V = Status.B = Status.D = Status.I = Status.Z = Status.C = 0;
   SP = 0xFF;
   for (int i = 0; i < 65535; i++)
    {
    //RAM[i] = 0x00;
    //RAM[i] = 0xFF;
    RAM[i] = 0xEA;
    }
   }

  void WriteRAM(word addr, byte value)
   {
   RAM[addr] = value;
   }

  byte ReadRAM(word addr)
   {
   //cout << "Reading address: " << hex << uppercase << (int)addr << endl;
   byte Value = RAM[addr];
   //cout << "Returning: " << hex << uppercase << (int)Value << endl;
   return RAM[addr];
   }

  void Push(byte Data)
   {
   word Addr = 0x0100 + SP;
   WriteRAM(Addr, Data);
   SP--;
   }

  byte Pop()
   {
    SP++;
    word Addr = 0x0100 + SP;
    byte Data = ReadRAM(Addr);
    //WriteRAM(Addr, 0x00);
    return Data;

   }

  void Reset()
   {
   A = Y = X = 0x00;
   Status.N = Status.V = Status.B = Status.D = Status.I = Status.Z = Status.C = 0;
   SP = 0xFF;
   //cout << "0xFFFD: " << hex << uppercase << (int)ReadRAM(0xFFFD) << " -- 0xFFFC: " << (int)ReadRAM(0xFFFC) << endl;
   //cout << "Bitshift - " << (int)ReadRAM(0xFFFD) << 8 << endl;
   PC = ReadRAM(0xFFFD) << 8 | ReadRAM(0xFFFC);
   }

  byte FetchIns()
   {
   byte opcode = ReadRAM(PC);
   PC++;
   return opcode;
   }


  word ResolveAddress(byte Opcode, word AdditionalBytes, int* Cycles)
   {
   string AddressingMode = OL.Addressing(Opcode);
   if (AddressingMode == "IMP")
    return 0; //Implied - No operand required
   if (AddressingMode == "IMM")
    return 0; //Immediate - No address to locate
   if (AddressingMode == "ZP")
    return AdditionalBytes; //Zero Page - 0x00XX
   if (AddressingMode == "ZPX")
    {
    byte temp = AdditionalBytes + X; //Use a single byte to ensure wraparound (ie: 0x80 + 0xFF -> 0x7F
    return temp;
    }
   if (AddressingMode == "ZPY")
    {
    //return AdditionalBytes + Y; //See ZPX - Note ZPY does *not* wrap in the ZP, result can be outside 0x00
    byte temp = AdditionalBytes + Y; //Ugh Apparently ZPY does wrap? Fucking conflicting documentation
    return temp;
    }
   if (AddressingMode == "REL")
    {
    int8_t Offset = AdditionalBytes; //Typecast to signed int to handle negative offset - int8 is OK since REL offset is limited to -128/+127
    if (PC >> 8 != (PC + Offset) >> 8)
     (*Cycles)--; //Crossing page boundary consumes an extra cycle
    return PC + Offset;
    }
   if (AddressingMode == "ABS")
    return AdditionalBytes;
   if (AddressingMode == "ACC")
    return A;
   if (AddressingMode == "ABSX")
    {
    word Addr = AdditionalBytes + X;
    //cout << "ABSX Returned 0x" << hex << uppercase << (int)AdditionalBytes << " + 0x" << (int)X << " = 0x" << (int)Addr << endl;
    if (AdditionalBytes >> 8 != (AdditionalBytes + X) >> 8)
     (*Cycles)--; //Additional cycle if crossing a page boundary
    return Addr;
    }
   if (AddressingMode == "ABSY")
    {
    word Addr = AdditionalBytes + Y;
    //cout << "ABSY Returned 0x" << hex << uppercase << (int)AdditionalBytes << " + 0x" << (int)Y << " = 0x" << (int)Addr << endl;
    if (AdditionalBytes >> 8 != (AdditionalBytes + Y) >> 8)
     (*Cycles)--; //Additional cycle if crossing a page boundary
    return Addr;
    }
   if (AddressingMode == "IND")
    return (ReadRAM(AdditionalBytes + 1) << 8) | ReadRAM(AdditionalBytes); //Indirect - additional bytes contain the absolute address of the LSB of the target (used only by JMP)
   if (AddressingMode == "INDX")
    {
    //cout << "INDX called" << endl;
    byte LSB = AdditionalBytes + X; //Ugh additional bytes + X point to an address which contains the LSB of the target
    //cout << "LSB: 0x" << hex << uppercase << (int)LSB << endl;
    return(ReadRAM(LSB) | (ReadRAM(LSB + 1) << 8));
    }
   if (AddressingMode == "INDY")
    {
    word Ref = (ReadRAM(AdditionalBytes) | (ReadRAM(AdditionalBytes + 1) << 8)) + Y; //See INDX - similar
    if (Ref >> 8 != 0)
     (*Cycles)--; //Result crossed a page boundary - is not on 0 page
    return Ref;

    }

   }

  template <
   class result_t = std::chrono::milliseconds,
   class clock_t = std::chrono::steady_clock,
   class duration_t = std::chrono::milliseconds
  >
  auto since(std::chrono::time_point<clock_t, duration_t> const& start)
   {
   return std::chrono::duration_cast<result_t>(clock_t::now() - start);
   }

  void Execute(int Cycles)
   {
   auto start = chrono::steady_clock::now();
   word OldPC = 0;
   int FailCount = 0;
   long ticks = 0;
   long trigger = LONG_MAX;
   //while (Cycles > 0)
   while(true) //testing
    {
    ticks++;
    //if (ticks % 10000 == 0)
     //cout << "Executed " << ticks << " Instructions" << endl;
    if (FailCount >= 10)
     {
     cout << "Looping at PC:" << hex << uppercase << (int) PC << endl;
     cout << "Executed " << dec<<ticks << " Instructions ("<<abs(Cycles)<<" Cycles)" << endl;
     cout << "Execution took " << since(start).count() << "msec"<<endl;
     cout << "Effective clock: " << abs(Cycles) / since(start).count()  << "kHz" << endl;

     exit(EXIT_FAILURE);
     }
    //cout << "Executing PC: " <<hex<<uppercase<<(int)PC << endl;
    //cout << "Old PC: " << hex << uppercase << (int)OldPC << endl;
    OldPC = PC;

    byte Opcode = FetchIns();
    //if (PC == OldPC)
    // FailCount++;
    string Instruction = OL.Mnemonic(Opcode);
    word ExtraBytes = 0;
    
    if (OL.Bytes(Opcode) > 1)
     ExtraBytes = FetchIns();
    if (OL.Bytes(Opcode) == 3)
     ExtraBytes |= (FetchIns() << 8);
    word Address = ResolveAddress(Opcode, ExtraBytes, &Cycles);
    //cout << "Resolved Address: " << hex << uppercase << (int)Address << endl;
    //cout << "Opcode: " << hex << uppercase << setw(2)<<(int)Instruction << endl;
    //if (Instruction == "ILL") //Illegal Opcode - Do nothing -- Note to self, consume cycle? -- Removed for testing
    // return;
    
    if (Instruction == "ADC") 
     {
     bool ANeg = A >> 7;
     int8_t Operand = 0; //Typecast operands to int8_t to handle signed-ness
     int8_t AReg = A;
     if (ticks >= trigger)
     cout << "ADC Adding AReg: 0x" << hex << uppercase << (int)AReg << " -- " << dec << (int)AReg << " -- 0b"<<bitset<8>(AReg)<<endl;
     if (OL.Addressing(Opcode) == "IMM")
      Operand = ExtraBytes;
     else
      Operand = ReadRAM(Address);
     if (ticks >= trigger)
     cout << "ADC Adding Operand: 0x" << hex << uppercase << (int)Operand << " -- " << dec << (int)Operand << " -- 0b"<<bitset<8>(Operand)<< endl;
     //word Result = AReg + Operand + Status.C;
     if (ticks >= trigger)
      {
      if (Status.C)
       cout << "ADC Adding incoming Carry" << endl;
      }
     int Result = AReg + Operand + Status.C;
     if (ticks >= trigger)
     cout << "ADC Result: 0x" << hex << uppercase << Result << " -- " << dec << Result << " -- 0b"<<bitset<8>(Result)<<endl;
     if ((int8_t)Result == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     //if (Result >> 8) //Doesn't work because negative. eg: 0+(-128)=-128. Fits in 8 bits neatly - 0x80 (no carry) but (word)-128 = FF80 (Note bit 8 set in negative representation)
     //if(Result>255 || Result<-128) //Ugh. Binary math sucks. Cheap hack? - Nope doesn't work either... 0b11111111 (-1) + 1 *should* carry (0x0100), even though result=0
     uint16_t CarryTest = (uint8_t)AReg + (uint8_t)Operand + Status.C;//Forget positves and negatives. Carry is just a matter of is bit 8 fucking set. Use unsigned types to ignore pos/neg traps
     if(CarryTest>>8)
      {
      Status.C = 1;
      if (ticks >= trigger)
      cout << "Carry set" << endl;
      }
     else
      {
      Status.C = 0;
      if (ticks >= trigger)
      cout << "Carry cleared" << endl;
      }
     A = Result;
     if (A >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     Status.V = 0;
     if (ANeg && Operand >> 7 && !(A >> 7))
      Status.V = 1;
     if (!ANeg && Operand >> 7 == 0 && A >> 7)
      Status.V = 1;
     }

    if (Instruction == "AND")
     {
     if (OL.Addressing(Opcode) == "IMM")
      {
      //cout << "AND: A=0x" << hex << uppercase << (int)A << " - 0b" << bitset<8>(A) << " & 0x" << (int)ExtraBytes << " - 0b" << bitset<8>(ExtraBytes) << endl;
      A = A & ExtraBytes;
      }
     else
      {
      byte Operand = ReadRAM(Address);
      //cout << "AND: A=0x" << hex << uppercase << (int)A << " - 0b" << bitset<8>(A) << " & 0x" << (int)Operand << " - 0b" << bitset<8>(Operand) << endl;
      A = A & Operand;
      }
     if (A == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (A >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "ASL" && OL.Addressing(Opcode)=="ACC")
     {
     Status.C = A >> 7;
     A = A << 1;
     if (A == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (A >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "ASL" && OL.Addressing(Opcode) != "ACC")
     {
     byte Data = ReadRAM(Address);
     Status.C = Data >> 7;
     Data = Data << 1;
     if (Data == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Data >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     WriteRAM(Address, Data);
     }
 
    if (Instruction == "BCC")
     {
     word OldPC = PC;
     if (!Status.C)
      {
      PC = Address;
      Cycles--; //Consume cycle if branch taken
      if ((OldPC >> 8) != (PC >> 8))
       Cycles-=2; //Consume 2 extra cycles if page bounardy was crossed
      }
     }

    if (Instruction == "BCS")
     {
     word OldPC = PC;
     if (Status.C)
      {
      PC = Address;
      Cycles--; //Consume cycle if branch taken
      if ((OldPC >> 8) != (PC >> 8))
       Cycles -= 2; //Consume 2 extra cycles if page bounardy was crossed
      }
     }

    if (Instruction == "BEQ")
     {
     word OldPC = PC;
     if (Status.Z)
      {
      PC = Address;
      Cycles--; //Consume cycle if branch taken
      if ((OldPC >> 8) != (PC >> 8))
       Cycles -= 2; //Consume 2 extra cycles if page bounardy was crossed
      }
     }

    if (Instruction == "BIT")
     {
     byte Mask = ReadRAM(Address);
     if ((A & Mask) == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Mask >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     if (Mask & 0b01000000)
      Status.V = 1;
     else
      Status.V = 0;
     }

    if (Instruction == "BMI")
     {
     word OldPC = PC;
     if (Status.N)
      {
      PC = Address;
      Cycles--; //Consume cycle if branch taken
      if ((OldPC >> 8) != (PC >> 8))
       Cycles -= 2; //Consume 2 extra cycles if page bounardy was crossed
      }
     }

    if (Instruction == "BNE")
     {
     word OldPC = PC;
     if (!Status.Z)
      {
      PC = Address;
      Cycles--; //Consume cycle if branch taken
      if ((OldPC >> 8) != (PC >> 8))
       Cycles -= 2; //Consume 2 extra cycles if page bounardy was crossed
      }
     }

    if (Instruction == "BPL")
     {
     word OldPC = PC;
     if (!Status.N)
      {
      PC = Address;
      Cycles--; //Consume cycle if branch taken
      if ((OldPC >> 8) != (PC >> 8))
       Cycles -= 2; //Consume 2 extra cycles if page bounardy was crossed
      }
     }

    if (Instruction == "BRK")
     {
     //cout << "BRK Called" << endl;
     //PC++; //right? Wasn't this just to handle break being implemented as a single byte instruction?
     Push(PC >> 8);
     //cout << "Pushed 0x" << hex << uppercase << (int)(PC >> 8) << endl;
     Push(PC & 0xFF);
     //cout << "Pushed 0x" << hex << uppercase << (int)(PC & 0xFF) << endl;
     //Status.B = 1;
     byte FlagsByte = (Status.N << 7) | (Status.V << 6) | (1<<5) | (1<<4) | (Status.D << 3) | (Status.I<<2) | (Status.Z << 1) | Status.C;
     Push(FlagsByte);
     //cout << "BRK Pushed Flags 0b" << bitset<8>(FlagsByte) << endl;
     Status.I = 1; //Set interrupt disable on break 
     //cout << "1: " << bitset<8>(ReadRAM(0xFFFE)) << " - 2:" << bitset<8>(ReadRAM(0xFFFF)) << endl;
     //cout << "1: " << bitset<8>(RAM[0xFFFE]) << " - 2:" << bitset<8>(RAM[0xFFFF]) << endl;
     //cout << "Jumping to 0x" << hex << uppercase << (int)(ReadRAM(0xFFFE) | (ReadRAM(0xFFFF)<<8)) << endl;
     PC = (ReadRAM(0xFFFE) | (ReadRAM(0xFFFF) << 8));
     }

    if (Instruction == "BVC")
     {
     word OldPC = PC;
     if (!Status.V)
      {
      PC = Address;
      Cycles--; //Consume cycle if branch taken
      if ((OldPC >> 8) != (PC >> 8))
       Cycles -= 2; //Consume 2 extra cycles if page bounardy was crossed
      }
     }

    if (Instruction == "BVS")
     {
     word OldPC = PC;
     if (Status.V)
      {
      PC = Address;
      Cycles--; //Consume cycle if branch taken
      if ((OldPC >> 8) != (PC >> 8))
       Cycles -= 2; //Consume 2 extra cycles if page bounardy was crossed
      }
     }

    if (Instruction == "CLC")
     {
     Status.C = 0;
     }

    if (Instruction == "CLD")
     {
     Status.D = 0;
     }

    if (Instruction == "CLI")
     {
     Status.I = 0;
     }

    if (Instruction == "CLV")
     {
     Status.V = 0;
     }

    if (Instruction == "CMP")
     {
     int8_t Result = 0;
     if (OL.Addressing(Opcode) == "IMM")
      {
      if(ticks>=trigger)
      cout << "Comparing A=0x" << hex << uppercase << (int)A << " - 0b" << bitset<8>(A) << "  with 0x" << (int)ExtraBytes << " - 0b" << bitset<8>(ExtraBytes) << endl;
      Result = A - (int8_t)ExtraBytes;
      }
     else
      {
      byte Operand = ReadRAM(Address);
      Result = A - Operand;
      if (ticks >= trigger)
      cout << "Comparing A=0x" << hex << uppercase << (int)A << " - 0b" << bitset<8>(A) << "  with 0x" << (int)Operand << " - 0b" << bitset<8>(Operand) << endl;
      }
     if (Result == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Result >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     if (Result >= 0)
      Status.C = 1;
     else
      Status.C = 0;
     }

    if (Instruction == "CPX")
     {
     int8_t Result = 0;
     if (OL.Addressing(Opcode) == "IMM")
      Result = X - (int8_t)ExtraBytes;
     else
      Result = X - ReadRAM(Address);
     if (Result == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Result >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     if (Result >= 0)
      Status.C = 1;
     else
      Status.C = 0;
     }

    if (Instruction == "CPY")
     {
     int8_t Result = 0;
     if (OL.Addressing(Opcode) == "IMM")
      Result = Y - (int8_t)ExtraBytes;
     else
      Result = Y - ReadRAM(Address);
     if (Result == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Result >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     if (Result >= 0)
      Status.C = 1;
     else
      Status.C = 0;
     }

    if (Instruction == "DEC")
     {
     byte Value = ReadRAM(Address)-1;
     if (Value == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Value >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     WriteRAM(Address, Value);
     }

    if (Instruction == "DEX")
     {
     X--;
     if (X == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (X >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "DEY")
     {
     Y--;
     if (Y == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Y >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "EOR")
     {
     byte Operand = 0;
     if (OL.Addressing(Opcode) == "IMM")
      Operand = ExtraBytes;
     else
      Operand = ReadRAM(Address);
     //cout << "EOR 0b" << bitset<8>(A) << " ^ 0b" << bitset<8>(Operand) << " = 0b" << bitset<8>(A ^ Operand) << endl;
     A = A ^ Operand;
     if (A == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (A >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "INC")
     {
     byte Value = ReadRAM(Address) + 1;
     if (Value == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Value >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     WriteRAM(Address, Value);
     }

    if (Instruction == "INX")
     {
     X++;
     if (X == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (X >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "INY")
     {
     Y++;
     if (Y == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Y >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "JMP")
     {
     //PC = ReadRAM(Address);
     PC = Address;
     }

    if (Instruction == "JSR") //memory issues - read 1 byte vs 2? Check earlier work
     {
     word RetPC = PC-1;
     //cout << "JSR Return Address: " << hex << uppercase << (int)RetPC << endl;
     Push(RetPC >> 8);
     Push(RetPC & 0xFF);
     //PC = ReadRAM(Address) + (ReadRAM(Address + 1) << 8);
     PC = ExtraBytes;
     }

    if (Instruction == "LDA")
     {
     if (OL.Addressing(Opcode) == "IMM")
      A = ExtraBytes;
     else
      A = ReadRAM(Address);
     //cout << "Loaded A=" << hex << uppercase << (int)A << " - 0b" << bitset<8>(A) << endl;
     if (A == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (A & 0x80)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "LDX")
     {
     if (OL.Addressing(Opcode) == "IMM")
      X = ExtraBytes;
     else
      X = ReadRAM(Address);
     if (X == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (X & 0x80)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "LDY")
     {
     if (OL.Addressing(Opcode) == "IMM")
      Y = ExtraBytes;
     else
      Y = ReadRAM(Address);
     if (Y == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Y & 0x80)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "LSR" && OL.Addressing(Opcode)=="ACC")
     {
     Status.C = (A & 0x01);
     //cout << "LSR 0b" << bitset<8>(A) << " >> 1 = 0b" << bitset<8>(A >> 1) << "Carry: "<<(int)Status.C<<endl;
     A = A >> 1;
     if (A == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     Status.N = 0;
     }

    if (Instruction == "LSR" && OL.Addressing(Opcode) != "ACC")
     {
     byte Data = ReadRAM(Address);
     Status.C = (Data & 0x01);
     //cout << "LSR 0b" << bitset<8>(Data) << " >> 1 = 0b" << bitset<8>(Data >> 1) << "Carry: " << (int)Status.C << endl;
     Data = Data >> 1;
     if (Data == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     Status.N = 0;
     WriteRAM(Address, Data);
     }

    if (Instruction == "NOP")
     {
      //NOP - Do nothing - Here as a placeholder
     }

    if (Instruction == "ORA")
     {
     byte Operand = 0;
     if (OL.Addressing(Opcode) == "IMM")
      Operand = ExtraBytes;
     else
      Operand = ReadRAM(Address);
     A = A | Operand;
     if (A == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (A >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "PHA")
     {
     //cout << "Pushed A=" << hex << uppercase << (int)A << endl;
     Push(A);
     }

    if (Instruction == "PHP")
     {
     //cout << "Bitshift: " << bitset<8>(Status.Z << 1) << endl;
     byte FlagsByte = (Status.N << 7) | (Status.V << 6) | (1 << 5) | (1 << 4) | (Status.D << 3) | (Status.I << 2) | (Status.Z << 1) | Status.C;
     //cout << "PHP Flags Pushed: 0b" << bitset<8>((int)FlagsByte) << endl;
     Push(FlagsByte);
     }

    if (Instruction == "PLA")
     {
     A = Pop();
     //cout << "Pulled A=" << hex << uppercase << (int)A << endl;
     if (A == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (A >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "PLP")
     {
     byte FlagsByte = Pop();
     //cout << "Flags Popped: 0x" << hex << uppercase << (int)FlagsByte <<" -- 0b"<<bitset<8>((int)FlagsByte) << endl;
     //cout << "and check: " << bitset<8>(FlagsByte & 0b00000010) << endl;
     Status.N = (bool)(FlagsByte & 0b10000000);
     Status.V = (bool)(FlagsByte & 0b01000000);
     Status.D = (bool)(FlagsByte & 0b00001000);
     Status.I = (bool)(FlagsByte & 0b00000100);
     Status.Z = (bool)(FlagsByte & 0b00000010);
     Status.C = (bool)(FlagsByte & 0b00000001);
     Status.B = 0;
     }

    if (Instruction == "ROL" && OL.Addressing(Opcode) == "ACC")
     {
     bool CarryIn = Status.C;
     //cout << "ROL on A=0b" << bitset<8>(A) << endl;
     Status.C = A >> 7;
     //cout << "ROL Set Carry=" <<(int)Status.C << endl;
     A = A << 1;
     if (CarryIn)
      A++;
     //cout << "ROL Result=0b" << bitset<8>(A) << endl;
     if (A == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (A >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "ROL" && OL.Addressing(Opcode) != "ACC")
     {
     bool CarryIn = Status.C;
     byte Data = ReadRAM(Address);
     Status.C = Data >> 7;
     Data = Data << 1;
     if (CarryIn)
      Data++;
     if (Data == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Data >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     WriteRAM(Address, Data);
     }

    if (Instruction == "ROR" && OL.Addressing(Opcode) == "ACC")
     {
     bool CarryIn = Status.C;
     Status.C = A & 0x01;
     //cout << "ROR 0b" << bitset<8>(A) << " > 0b" << bitset<8>(A >> 1) << endl;
     A = A >> 1;
     if (CarryIn)
      A = A | 0x80;
     if (A == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (CarryIn)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "ROR" && OL.Addressing(Opcode) != "ACC")
     {
     
     bool CarryIn = Status.C;
     byte Data = ReadRAM(Address);
     Status.C = Data & 0x1;
     //cout << "ROR 0b" << bitset<8>(Data) << " > 0b" << bitset<8>(Data >> 1) << endl;
     Data = Data >> 1;
     if (CarryIn)
      Data = Data | 0x80;
     if (Data == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (CarryIn)
      Status.N = 1;
     else
      Status.N = 0;
     WriteRAM(Address, Data);
     }

    if (Instruction == "RTI")
     {
     byte FlagsByte = Pop();
     //cout << "RTI Flags Byte: 0x" << hex << uppercase << (int)FlagsByte << " - 0b" << bitset<8>((int)FlagsByte) << endl;
     Status.N = ((FlagsByte & 0b10000000)>>7);
     Status.V = ((FlagsByte & 0b01000000)>>6);
     Status.D = ((FlagsByte & 0b00001000)>>3);
     Status.I = ((FlagsByte & 0b00000100)>>2);
     //Status.I = 0; //RTI Clears interrupt flag? - Nope
     Status.Z = ((FlagsByte & 0b00000010))>>1;
     Status.C = FlagsByte & 0b00000001;
     //Status.B = 0; //Ignores break flag apparently
     //cout << "RTI Flags: N=" << (int)Status.N << " V=" << (int)Status.V << " D=" << (int)Status.D << " I=" << (int)Status.I << " Z=" << (int)Status.Z << " C=" << (int)Status.C << " B=" << (int)Status.B << endl;
     byte LSB = Pop();
     word MSB = (Pop() << 8);
     PC = LSB + MSB;
     }

    if (Instruction == "RTS")
     {
     byte LSB = Pop();
     //cout << "RTS LSB: " << hex << uppercase << (int)LSB << endl;
     word MSB = (Pop() << 8);
     //cout << "RTS MSB: " << hex << uppercase << (int)MSB << endl;
     PC = LSB + MSB;
     //cout << "RTS Returning to: " << hex << uppercase << (int)PC << endl;
     PC++;
     }

    if (Instruction == "SBC")
     {
     bool ANeg = A >> 7;
     int8_t Operand = 0;
     int8_t AReg = A;
     if (ticks >= trigger)
     cout << "SBC Subtracting AReg: 0x" << hex << uppercase << (int)AReg << " -- " << dec << (int)AReg << endl;
     if (OL.Addressing(Opcode) == "IMM")
      Operand = ExtraBytes;
     else
      Operand = ReadRAM(Address);
     if (ticks >= trigger)
     cout << "SBC Subtracting Operand: 0x" << hex << uppercase << (int)Operand << " -- " << dec << (int)Operand << endl;
     Operand = ~Operand;
     if (ticks >= trigger)
     cout << "SBC Negated Operand: 0x" << hex << uppercase << (int)Operand << " -- " << dec << (int)Operand << endl;
     int Result = AReg + Operand + Status.C;
     if (ticks >= trigger)
     cout << "SBC Result: 0x" << hex << uppercase << (int)Result << " -- " << dec << (int)Result << endl;
     if ((int8_t)Result == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     /*if (Result >> 8)
      Status.C = 0;
     else
      Status.C = 1;
     */
     //if (Result >> 8) //Carry flag behavior backwards or no? Conflicting docs
     uint16_t CarryTest = (uint8_t)AReg + (uint8_t)Operand + Status.C;
     if (CarryTest >> 8) //See ADC hack, same problem
      Status.C = 1;
     else
      Status.C = 0;
     A = Result;
     if (A >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     Status.V = 0;
     if (ANeg && Operand >> 7 && !(A >> 7))
      Status.V = 1;
     if (!ANeg && Operand >> 7 == 0 && A >> 7)
      Status.V = 1;
     }

    if (Instruction == "SEC")
     {
     Status.C = 1;
     }

    if (Instruction == "SED")
     {
     Status.D = 1;
     }

    if (Instruction == "SEI")
     {
     Status.I = 1;
     }

    if (Instruction == "STA")
     {
     WriteRAM(Address, A);
     }

    if (Instruction == "STX")
     {
     WriteRAM(Address, X);
     }

    if (Instruction == "STY")
     {
     WriteRAM(Address, Y);
     }

    if (Instruction == "TAX")
     {
     X = A;
     if (X == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (X >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "TAY")
     {
     Y = A;
     if (Y == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Y >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     }
    
    if (Instruction == "TSX")
     {
     X = SP;
     if (X == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (X >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "TXA")
     {
     A=X ;
     if (A == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (A >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "TXS")
     {
     SP = X;
     }

    if (Instruction == "TYA")
     {
     A = Y;
     if (A == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (A >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     }



    if (OldPC == PC)
     FailCount++;

    Cycles -= OL.Cycles(Opcode);
    }
   }


 };




#endif