#pragma once
#ifndef M6502_H
#define M6502_H

#include "OpcodeLookup.h"

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
  byte RAM[65535];
  OpcodeLookup OL;

  M6502()
   {
   //Do Stuff
   A = Y = X = PC = 0;
   Status.N = Status.V = Status.B = Status.D = Status.I = Status.Z = Status.C = 0;
   SP = 0xFF;
   for (int i = 0; i < 65535; i++)
    {
    RAM[i] = 0x00;
    }
   }

  void WriteRAM(byte addr, byte value)
   {
   RAM[addr] = value;
   }

  byte ReadRAM(byte addr)
   {
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
    return ReadRAM(Addr);
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
    return AdditionalBytes + Y; //See ZPX - Note ZPY does *not* wrap in the ZP, result can be outside 0x00
    }
   if (AddressingMode == "REL")
    {
    int8_t Offset = AdditionalBytes; //Typecast to signed int to handle negative offset
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
    if (AdditionalBytes >> 8 != (AdditionalBytes + X) >> 8)
     (*Cycles)--; //Additional cycle if crossing a page boundary
    return AdditionalBytes + X;
    }
   if (AddressingMode == "ABSY")
    {
    if (AdditionalBytes >> 8 != (AdditionalBytes + Y) >> 8)
     (*Cycles)--; //Additional cycle if crossing a page boundary
    return AdditionalBytes + Y;
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


  void Execute(int Cycles)
   {
   //while (Cycles > 0)
   while(true) //testing
    {
    byte Opcode = FetchIns();
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
     //cout << "AReg: 0x" << hex << uppercase << (int)AReg << " -- " << dec << (int)AReg << endl;
     if (OL.Addressing(Opcode) == "IMM")
      Operand = ExtraBytes;
     else
      Operand = ReadRAM(Address);
     //cout << "Operand: 0x" << hex << uppercase << (int)Operand << " -- " << dec << (int)Operand << endl;
     word Result = AReg + Operand + Status.C;
     if (Result == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Result >> 8)
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

    if (Instruction == "AND")
     {
     if (OL.Addressing(Opcode) == "IMM")
      A = A & ExtraBytes;
     else
     A = A & ReadRAM(Address);
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
     PC++;
     Push(PC >> 8);
     Push(PC & 0xFF);
     Status.B = 1;
     Status.I = 1;
     byte FlagsByte = (Status.N << 7) | (Status.V << 6) | (1<<5) | (1<<4) | (Status.D << 3) | (Status.I << 2) | (Status.Z << 1) | Status.C;
     Push(FlagsByte);
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
     byte Result = 0;
     if (OL.Addressing(Opcode) == "IMM")
      Result = A - (int8_t)ExtraBytes;
     else
      Result = A - ReadRAM(Address);
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
     byte Result = 0;
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
     byte Result = 0;
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
     PC = ReadRAM(Address);
     }

    if (Instruction == "JSR") //memory issues - read 1 byte vs 2? Check earlier work
     {
     word RetPC = PC++;
     Push(RetPC >> 8);
     Push(RetPC & 0xFF);
     PC = ReadRAM(Address) + (ReadRAM(Address + 1) << 8);
     }

    if (Instruction == "LDA")
     {
     if (OL.Addressing(Opcode) == "IMM")
      A = ExtraBytes;
     else
      A = ReadRAM(Address);
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
     A = A >> 1;
     if (A == 0)
      Status.Z == 1;
     else
      Status.Z == 0;
     Status.N = 0;
     }

    if (Instruction == "LSR" && OL.Addressing(Opcode) != "ACC")
     {
     byte Data = ReadRAM(Address);
     Status.C = (Data & 0x01);
     Data = Data >> 1;
     if (Data == 0)
      Status.Z == 1;
     else
      Status.Z == 0;
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
     Push(A);
     }

    if (Instruction == "PHP")
     {
     byte FlagsByte = (Status.N << 7) | (Status.V << 6) | (1 << 5) | (1 << 4) | (Status.D << 3) | (Status.I << 2) | (Status.Z << 1) | Status.C;
     Push(FlagsByte);
     }

    if (Instruction == "PLA")
     {
     A = Pop();
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
     Status.N = FlagsByte & 0b10000000;
     Status.V = FlagsByte & 0b01000000;
     Status.D = FlagsByte & 0b00001000;
     Status.I = FlagsByte & 0b00000100;
     Status.Z = FlagsByte & 0b00000010;
     Status.C = FlagsByte & 0b00000001;
     Status.B = 0;
     }

    if (Instruction == "ROL" && OL.Addressing(Opcode) == "ACC")
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

    if (Instruction == "ROL" && OL.Addressing(Opcode) != "ACC")
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

    if (Instruction == "ROR" && OL.Addressing(Opcode) == "ACC")
     {
     Status.C = A & 0x01;
     A = A >> 1;
     if (A == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (A >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "ROR" && OL.Addressing(Opcode) != "ACC")
     {
     byte Data = ReadRAM(Address);
     Status.C = Data & 0x1;
     Data = Data >> 1;
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

    if (Instruction == "RTI")
     {
     byte FlagsByte = Pop();
     Status.N = FlagsByte & 0b10000000;
     Status.V = FlagsByte & 0b01000000;
     Status.D = FlagsByte & 0b00001000;
     Status.I = FlagsByte & 0b00000100;
     Status.Z = FlagsByte & 0b00000010;
     Status.C = FlagsByte & 0b00000001;
     Status.B = 0;
     byte LSB = Pop();
     byte MSB = (Pop() << 8);
     PC = LSB + MSB;
     }

    if (Instruction == "RTS")
     {
     byte LSB = Pop();
     byte MSB = (Pop() << 8);
     PC = LSB + MSB;
     PC++;
     }

    if (Instruction == "SBC")
     {
     bool ANeg = A >> 7;
     int8_t Operand = 0;
     int8_t AReg = A;
     if (OL.Addressing(Opcode) == "IMM")
      Operand = ExtraBytes;
     else
      Operand = ReadRAM(Address);
     Operand = ~Operand;
     word Result = AReg + Operand + Status.C;
     if (Result == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Result >> 8)
      Status.C = 0;
     else
      Status.C = 1;
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




    Cycles -= OL.Cycles(Opcode);
    }
   }


 };




#endif