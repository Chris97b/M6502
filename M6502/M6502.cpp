

#include "M6502.h"
#include <iostream>
#include <iomanip>

using namespace std;
using byte = uint8_t;
using word = uint16_t;

M6502::M6502()
   {
   A = Y = X = PC = 0;
   Status.N = Status.V = Status.B = Status.D = Status.I = Status.Z = Status.C = 0;
   SP = 0xFF;
   Cycles = 0;
   InstructionComplete = true;
   for (int i = 0; i < 65535; i++)
    {
    RAM[i] = 0xEA;
    }
   }

  void M6502::WriteRAM(word addr, byte value)
   {
   RAM[addr] = value;
   }

  byte M6502::ReadRAM(word addr)
   {
    return RAM[addr];
   }

  void M6502::Push(byte Data)
   {
   word Addr = 0x0100 + SP;
   WriteRAM(Addr, Data);
   SP--;
   }

  byte M6502::Pop()
   {
   SP++;
   word Addr = 0x0100 + SP;
   byte Data = ReadRAM(Addr);
   return Data;

   }

  void M6502::Reset()
   {
   A = Y = X = 0x00;
   Status.N = Status.V = Status.B = Status.D = Status.I = Status.Z = Status.C = 0;
   Cycles = 0;
   InstructionComplete = true;
   SP = 0xFF;
   PC = ReadRAM(0xFFFD) << 8 | ReadRAM(0xFFFC);
   CPUHalt = false;
   }

  byte M6502::FetchIns()
   {
   byte opcode = ReadRAM(PC);
   PC++;
   return opcode;
   }


  word M6502::ResolveAddress(byte Opcode, word AdditionalBytes, bool Undoc)
   {
   string AddressingMode;
   if (Undoc)
    AddressingMode = OL.Addressing(Opcode, true);
   else
    AddressingMode = OL.Addressing(Opcode);
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
    byte temp = AdditionalBytes + Y; //Ugh Apparently ZPY does wrap? Fucking conflicting documentation
    return temp;
    }
   if (AddressingMode == "REL")
    {
    int8_t Offset = (byte)AdditionalBytes; //Typecast to signed int to handle negative offset - int8 is OK since REL offset is limited to -128/+127
    return PC + Offset;
    }
   if (AddressingMode == "ABS")
    return AdditionalBytes;
   if (AddressingMode == "ACC")
    return A;
   if (AddressingMode == "ABSX")
    {
    word Addr = AdditionalBytes + X;
    if( (AdditionalBytes&0xFF00) != ((AdditionalBytes+X)&0xFF00))
    if (OL.Mnemonic(Opcode) != "ASL" && OL.Mnemonic(Opcode) != "ROL" && OL.Mnemonic(Opcode) != "LSR" && OL.Mnemonic(Opcode) != "ROR" && OL.Mnemonic(Opcode) != "STA" && OL.Mnemonic(Opcode) != "DEC" && OL.Mnemonic(Opcode) != "INC") //ASL/ROL/LSR/ROR/STA/etc/etc don't add the page cross penalty? God only knows why
     {
     Cycles++; //Additional cycle if crossing a page boundary
     }
    return Addr;
    }
   if (AddressingMode == "ABSY")
    {
    word Addr = AdditionalBytes + Y;
    if (AdditionalBytes >> 8 != (AdditionalBytes + Y) >> 8)
     {
      if (OL.Mnemonic(Opcode) != "STA") //STA Doesn't add penalty
       Cycles++; //Additional cycle if crossing a page boundary
     }
    return Addr;
    }
   if (AddressingMode == "IND")
    {
    word Address = ReadRAM(AdditionalBytes);
    if ((AdditionalBytes & 0x00FF) == 0xFF) //JMP IND wraps page (technically a bug in the real hardware, fixed in later revisions, but relied upon by many programs)
     {
     Address |= (ReadRAM((AdditionalBytes & 0xFF00)) << 8);
     }
    else
     {
     Address |= (ReadRAM(AdditionalBytes + 1) << 8);
     }
    return Address;
    }
   if (AddressingMode == "INDX")
    {
    byte LSB = AdditionalBytes + X; //Ugh additional bytes + X point to an address which contains the LSB of the target
    return(ReadRAM(LSB) | (ReadRAM(((LSB + 1)&0xFF)) << 8)); //Zero page wrap
    }
   if (AddressingMode == "INDY")  //Similar to INDX except target is fetched first, then the offset Y added - Note that fetching the target wraps in the 0 page, but adding the offset does not
    {
    bool ExtraCycles = false;
    word Ref = (ReadRAM(AdditionalBytes));
    Ref |= (ReadRAM((AdditionalBytes + 1) & 0x00FF) << 8);
    if ((Ref & 0xFF00) != ((Ref + Y) & 0xFF00))
     {
     if (OL.Mnemonic(Opcode) != "STA") //STA INDY Doesn't add penalty
      ExtraCycles = true;
     }
    Ref += Y;
    if (ExtraCycles)
     Cycles++;
    return Ref;

    }

   }


  void M6502::Execute()
   {
   //while (Cycles > 0)
   //while (true) //testing
   if (Cycles == 0 && !CPUHalt) //Only execute if previous instruction is complete
    {
    //cout << "Executing PC=0x" << ToHex(PC, 4) << endl;
    byte Opcode = FetchIns();
    string Instruction = OL.Mnemonic(Opcode);
    Cycles = OL.Cycles(Opcode);
    InstructionComplete = false;
    word ExtraBytes = 0;
    //cout << "Executing " << OL.Mnemonic(Opcode) << " {" << OL.Addressing(Opcode) << "} " << ToHex(ExtraBytes, 4) << endl;
    int NumBytes = OL.Bytes(Opcode);
    string Addressing = OL.Addressing(Opcode);
    if (Instruction == "ILL" && EnableUndocumentedInstructions == false) //Illegal Opcode - Do nothing -- Note to self, consume cycle?
     {
     //*crickets*
     }
    if (Instruction == "ILL" && EnableUndocumentedInstructions)
     {
     Instruction = OL.Mnemonic(Opcode, true);
     Cycles = OL.Cycles(Opcode, true);
     NumBytes = OL.Bytes(Opcode, true);
     Addressing = OL.Addressing(Opcode, true);
     }

    if (NumBytes > 1)
     ExtraBytes = FetchIns();
    if (NumBytes == 3)
     ExtraBytes |= (FetchIns() << 8);
    word Address;
    if (EnableUndocumentedInstructions)
     Address = ResolveAddress(Opcode, ExtraBytes, true);
    else
     Address = ResolveAddress(Opcode, ExtraBytes);


    if (Instruction == "ADC")
     {
     if (EnableBCDMode == 0 || Status.D == 0)
      {
      bool ANeg = A >> 7;
      int8_t Operand = 0; //Typecast operands to int8_t to handle signed-ness
      int8_t AReg = A;
      if (OL.Addressing(Opcode) == "IMM")
       Operand = (byte)ExtraBytes;
      else
       Operand = ReadRAM(Address);
      int Result = AReg + Operand + Status.C;
      if ((int8_t)Result == 0)
       Status.Z = 1;
      else
       Status.Z = 0;
      uint16_t CarryTest = (uint8_t)AReg + (uint8_t)Operand + Status.C;
      if (CarryTest >> 8)
       {
       Status.C = 1;
       }
      else
       {
       Status.C = 0;
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

     if (EnableBCDMode == 1 && Status.D == 1)
      {
      //Decimal Mode - eg: 0x15 + 0x27 = 0x42   (15+27=42)
      //Flags are technically undocumented/unreliable, but code attempts to replicate real NMOS6502 behavior, bugs and all
      uint8_t Operand = 0;
      if (OL.Addressing(Opcode) == "IMM")
       Operand = (byte)ExtraBytes;
      else
       Operand = ReadRAM(Address);
      int Op1Split = (((A >> 4) * 10) + (A & 0x0F));
      int Op2Split = (((Operand >> 4) * 10) + (Operand & 0x0F));
      int Result = Op1Split + Op2Split;
      if (Status.C)
       {
       Result += 1;
       }
      if (Result > 99)
       {
       Result -= 100; //Overflow 
       Status.C = 1;

       }
      else
       Status.C = 0;
      int Ones = Result % 10;
      int Tens = ((Result - Ones)) % 100 / 10;
      int HResult = (Tens << 4) | Ones;
      if (HResult == 0)
       Status.Z = 1;
      else
       Status.Z = 0;
      if (HResult >> 7)
       Status.N = 1;
      else
       Status.N = 0;
      if (HResult < -128 || HResult>127)
       Status.V = 1;
      else
       Status.V = 0;
      A = HResult;


      }
     }


    if (Instruction == "AND")
     {
     if (OL.Addressing(Opcode) == "IMM")
      {
      A = A & ExtraBytes;
      }
     else
      {
      byte Operand = ReadRAM(Address);
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




    if (Instruction == "ASL" && OL.Addressing(Opcode) == "ACC")
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
      Cycles++; //Consume cycle if branch taken
      if ((OldPC >> 8) != (PC >> 8))
       Cycles++; //Consume 2 extra cycles if page bounardy was crossed
      }
     }

    if (Instruction == "BCS")
     {
     word OldPC = PC;
     if (Status.C)
      {
      PC = Address;
      Cycles++; //Consume cycle if branch taken
      if ((OldPC >> 8) != (PC >> 8))
       Cycles++; //Consume 2 extra cycles if page bounardy was crossed
      }
     }

    if (Instruction == "BEQ")
     {
     word OldPC = PC;
     if (Status.Z)
      {
      PC = Address;
      Cycles++; //Consume cycle if branch taken
      if ((OldPC >> 8) != (PC >> 8))
       Cycles++; //Consume 2 extra cycles if page bounardy was crossed
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
      Cycles++; //Consume cycle if branch taken
      if ((OldPC >> 8) != (PC >> 8))
       Cycles++; //Consume 2 extra cycles if page bounardy was crossed
      }
     }

    if (Instruction == "BNE")
     {
     word OldPC = PC;
     //cout << "BNE";
     if (!Status.Z)
      {
      //cout << "Zero flag clear - Branching" << endl;
      PC = Address;
      Cycles++; //Consume cycle if branch taken
      if ((OldPC >> 8) != (PC >> 8))
       Cycles++; //Consume 2 extra cycles if page bounardy was crossed
      }
     //else
     // cout << "Zero flag set - no branch" << endl;
     }

    if (Instruction == "BPL")
     {
     word OldPC = PC;
     if (!Status.N)
      {
      PC = Address;
      Cycles++; //Consume cycle if branch taken
      if ((OldPC >> 8) != (PC >> 8))
       Cycles++; //Consume 2 extra cycles if page bounardy was crossed
      }
     }

    if (Instruction == "BRK")
     {
     Push(PC >> 8);
     Push(PC & 0xFF);
     byte FlagsByte = (Status.N << 7) | (Status.V << 6) | (1 << 5) | (1 << 4) | (Status.D << 3) | (Status.I << 2) | (Status.Z << 1) | Status.C;
     Push(FlagsByte);
     Status.I = 1; //Set interrupt disable on break 
     PC = (ReadRAM(0xFFFE) | (ReadRAM(0xFFFF) << 8));
     }

    if (Instruction == "BVC")
     {
     word OldPC = PC;
     if (!Status.V)
      {
      PC = Address;
      Cycles++; //Consume cycle if branch taken
      if ((OldPC >> 8) != (PC >> 8))
       Cycles++; //Consume 2 extra cycles if page bounardy was crossed
      }
     }

    if (Instruction == "BVS")
     {
     word OldPC = PC;
     if (Status.V)
      {
      PC = Address;
      Cycles++; //Consume cycle if branch taken
      if ((OldPC >> 8) != (PC >> 8))
       Cycles++; //Consume 2 extra cycles if page bounardy was crossed
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
     //cout << "CMP {" << OL.Addressing(Opcode) << "}" << endl;
     uint16_t Result = 0;
     uint16_t Fetched = 0;
     if (OL.Addressing(Opcode) == "IMM")
      Fetched = (uint16_t)ExtraBytes;
     else
      Fetched = (uint16_t)ReadRAM(Address);
     Result = (uint16_t)A - (uint16_t)Fetched;
     //cout << "A: 0x" << ToHex((int)A, 4) << endl;
     //cout << "Fetched: 0x" << ToHex((int)Fetched, 4) << endl;
     //cout << "Result: 0x" << ToHex((int)Result, 4) << endl;
     if ((Result & 0x00FF) == 0x0000)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Result & 0x0080)
      Status.N = 1;
     else
      Status.N = 0;
     if (A >= Fetched)
      Status.C = 1;
     else
      Status.C = 0;
     }

    if (Instruction == "CPX")
     {
     uint16_t Result = 0;
     uint16_t Fetched = 0;
     if (OL.Addressing(Opcode) == "IMM")
      Fetched = (uint16_t)ExtraBytes;
     else
      Fetched = (uint16_t)ReadRAM(Address);
     Result = (uint16_t)X - (uint16_t)Fetched;
     if ((Result & 0x00FF) == 0x0000)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Result & 0x0080)
      Status.N = 1;
     else
      Status.N = 0;
     if (X >= Fetched)
      Status.C = 1;
     else
      Status.C = 0;
     }

    if (Instruction == "CPY")
     {
     uint16_t Result = 0;
     uint16_t Fetched = 0;
     if (OL.Addressing(Opcode) == "IMM")
      Fetched = (uint16_t)ExtraBytes;
     else
      Fetched = (uint16_t)ReadRAM(Address);
     Result = (uint16_t)Y - (uint16_t)Fetched;
     if ((Result & 0x00FF) == 0x0000)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Result & 0x0080)
      Status.N = 1;
     else
      Status.N = 0;
     if (Y >= Fetched)
      Status.C = 1;
     else
      Status.C = 0;
     }

    if (Instruction == "DEC")
     {
     byte Value = ReadRAM(Address) - 1;
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
      Operand = (byte)ExtraBytes;
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
     PC = Address;
     }

    if (Instruction == "JSR") //memory issues - read 1 byte vs 2? Check earlier work
     {
     word RetPC = PC - 1;
     Push(RetPC >> 8);
     Push(RetPC & 0xFF);
     PC = ExtraBytes;
     }

    if (Instruction == "LDA")
     {
     if (OL.Addressing(Opcode) == "IMM")
      {
      A = (byte)ExtraBytes;
      //cout << "LDA {IMM} 0x" << ToHex(ExtraBytes, 4) << endl;
      }
     else
      {
      A = ReadRAM(Address);
      //cout << "LDA {" << OL.Addressing(Opcode) << "} 0x" << ToHex(Address, 4) << " -- 0x" << ToHex(ReadRAM(Address), 4) << endl;
      }
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
      X = (byte)ExtraBytes;
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
      Y = (byte)ExtraBytes;
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

    if (Instruction == "LSR" && OL.Addressing(Opcode) == "ACC")
     {
     Status.C = (A & 0x01);
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
      Operand = (byte)ExtraBytes;
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
     Status.C = A >> 7;
     A = A << 1;
     if (CarryIn)
      A++;
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
     Status.N = ((FlagsByte & 0b10000000) >> 7);
     Status.V = ((FlagsByte & 0b01000000) >> 6);
     Status.D = ((FlagsByte & 0b00001000) >> 3);
     Status.I = ((FlagsByte & 0b00000100) >> 2);
     Status.Z = ((FlagsByte & 0b00000010)) >> 1;
     Status.C = FlagsByte & 0b00000001;
     byte LSB = Pop();
     word MSB = (Pop() << 8);
     PC = LSB + MSB;
     }

    if (Instruction == "RTS")
     {
     byte LSB = Pop();
     word MSB = (Pop() << 8);
     PC = LSB + MSB;
     PC++;
     }

    if (Instruction == "SBC")
     {
     if (EnableBCDMode == 0 || Status.D == 0)
      {
      bool ANeg = A >> 7;
      int8_t Operand = 0;
      int8_t AReg = A;
      if (OL.Addressing(Opcode) == "IMM")
       Operand = (byte)ExtraBytes;
      else
       Operand = ReadRAM(Address);
      Operand = ~Operand;
      int Result = AReg + Operand + Status.C;
      if ((int8_t)Result == 0)
       Status.Z = 1;
      else
       Status.Z = 0;
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

     if (EnableBCDMode == 1 && Status.D == 1)
      {
      //Decimal Mode - See ADC
      uint8_t Operand = 0;
      if (OL.Addressing(Opcode) == "IMM")
       Operand = (byte)ExtraBytes;
      else
       Operand = ReadRAM(Address);
      int Op1Split = (((A >> 4) * 10) + (A & 0x0F));
      int Op2Split = (((Operand >> 4) * 10) + (Operand & 0x0F));
      int Result = Op1Split - Op2Split;
      if (!Status.C)
       {
       Result -= 1;
       }

      if (Result < 0)
       {
       Result += 100; //Overflow
       Status.C = 0;
       }
      else
       Status.C = 1;
      int Ones = Result % 10;
      int Tens = ((Result - Ones)) % 100 / 10;
      int HResult = (Tens << 4) | Ones;
      if (HResult == 0)
       Status.Z = 1;
      else
       Status.Z = 0;
      if (HResult >> 7)
       Status.N = 1;
      else
       Status.N = 0;
      if (HResult < -128 || HResult>127)
       Status.V = 1;
      else
       Status.V = 0;
      A = HResult;

      }



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
     A = X;
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

    //----------------------Begin Illegal/Undocumented Instructions--------------------

    if (Instruction == "ALR")
     {
     byte Operand = ReadRAM(Address);
     byte Result = A & Operand;
     A = ((A & Operand) >> 1);
     if ((Result & 0x01) == 1)
      Status.C = 1;
     else
      Status.C = 0;
     if (A == 0x00)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (A & 0x80)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if ((Instruction == "ANC" || Instruction=="ANC2"))
     {
     byte Operand = ReadRAM(Address);
     A = A * Operand;
     if (A & 0x80)
      {
      Status.C = 1;
      Status.N = 1;
      }
     else
      {
      Status.C = 0;
      Status.N = 0;
      }
     if (A == 0x00)
      Status.Z = 1;
     else
      Status.Z = 0;
     }

    if (Instruction == "ANE") //Using 0x00 as CONST, may be wrong-ish, apparently CONST depended on thermal properties and other shit
     {
     A = 0;
     Status.Z = 1;
     Status.N = 0;
     Status.C = 0;
     }
    
    if (Instruction == "ARR")
     {
     byte Operand = ReadRAM(Address);
     byte Result = A & Operand;
     byte AccBit6In = A & 0b01000000;
     byte OldA = A;
     Result >>= 1;
     if (Status.C)
      Result = Result | 0x80;
     if (Result == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Status.D == 0 || !EnableBCDMode)
      {
      if (Result & 0x80)
       Status.N = 1;
      else
       Status.N = 0;
      Status.C = Result & 0b01000000; //C Flag is copied from Bit 6
      Status.V = ((Result & 0b01000000) ^ (Result & 0b00100000)); //V Flag is bit 5 XOR bit 6
      }
     else
      {
      Status.N = Status.C;
      if (AccBit6In == (A & 0b01000000))
       Status.V = 0;
      else
       Status.V = 1;
      byte Temp = OldA & Operand;
      byte AL = Temp & 0x0F;
      byte AH = Temp & 0xF0;
      if (AL + (AL & 1) > 5)          
       A = (A & 0xF0) | ((A + 6) & 0xF);
      if (Status.C = AH + (AH & 1) > 5)      
       A = (A + 0x60) & 0xFF;        

      }
     }

    if (Instruction == "DCP")
     {
     uint16_t Result = 0;
     uint16_t Fetched = 0;
     if (OL.Addressing(Opcode) == "IMM")
      Fetched = (uint16_t)ExtraBytes;
     else
      Fetched = (uint16_t)ReadRAM(Address);
     Fetched--;
     Result = (uint16_t)A - (uint16_t)Fetched;
     if ((Result & 0x00FF) == 0x0000)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Result & 0x0080)
      Status.N = 1;
     else
      Status.N = 0;
     if (A >= Fetched)
      Status.C = 1;
     else
      Status.C = 0;
     }

    if (Instruction == "ISC")
     {
     if (EnableBCDMode == 0 || Status.D == 0)
      {
      bool ANeg = A >> 7;
      int8_t Operand = 0;
      int8_t AReg = A;
      if (OL.Addressing(Opcode) == "IMM")
       Operand = (byte)ExtraBytes;
      else
       Operand = ReadRAM(Address);
      Operand++;
      Operand = ~Operand;
      int Result = AReg + Operand + Status.C;
      if ((int8_t)Result == 0)
       Status.Z = 1;
      else
       Status.Z = 0;
      uint16_t CarryTest = (uint8_t)AReg + (uint8_t)Operand + Status.C;
      if (CarryTest >> 8)
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

     if (EnableBCDMode == 1 && Status.D == 1)
      {
      uint8_t Operand = 0;
      if (OL.Addressing(Opcode) == "IMM")
       Operand = (byte)ExtraBytes;
      else
       Operand = ReadRAM(Address);
      Operand++;
      int Op1Split = (((A >> 4) * 10) + (A & 0x0F));
      int Op2Split = (((Operand >> 4) * 10) + (Operand & 0x0F));
      int Result = Op1Split - Op2Split;
      if (!Status.C)
       {
       Result -= 1;
       }

      if (Result < 0)
       {
       Result += 100;
       Status.C = 0;
       }
      else
       Status.C = 1;
      int Ones = Result % 10;
      int Tens = ((Result - Ones)) % 100 / 10;
      int HResult = (Tens << 4) | Ones;
      if (HResult == 0)
       Status.Z = 1;
      else
       Status.Z = 0;
      if (HResult >> 7)
       Status.N = 1;
      else
       Status.N = 0;
      if (HResult < -128 || HResult>127)
       Status.V = 1;
      else
       Status.V = 0;
      A = HResult;
      }
     }

    if (Instruction == "LAS")
     {
     byte Operand = ReadRAM(Address);
     byte Result = Operand & SP;
     A = X = SP = Result;
     if (Result == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Result & 0x80)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "LAX")
     {
     A = ReadRAM(Address);
     X = A;
     if (A == 0)
     Status.Z = 1;
    else
     Status.Z = 0;
    if (A & 0x80)
     Status.N = 1;
    else
     Status.N = 0;
     }

    if (Instruction == "LXA") //Using magic const = 0x00; See above
     {
     A = X = 0;
     Status.Z = 1;
     Status.N = 0;
     }

    if (Instruction == "RLA")
     {
     byte Operand = ReadRAM(Address);
     byte OldC = Status.C;
     Status.C = Operand & 0x80;
     Operand <<= 1;
     if (OldC == 1)
      Operand++;
     A = A & Operand;
     if (A == 0)
      Status.Z == 1;
     else
      Status.Z == 0;
     if (A & 0x80)
      Status.N = 1;
     else
      Status.N = 0;
     }

    if (Instruction == "RRA")
     {
     byte Operand = ReadRAM(Address);
     byte OldC = Status.C;
     Status.C = Operand & 0x01;
     Operand >>= 1;
     if (OldC == 1)
      Operand |= 0x80;
     bool ANeg = A >> 7;
     int8_t SOperand = 0; //Typecast operands to int8_t to handle signed-ness
     int8_t AReg = A;
     int Result = AReg + SOperand + Status.C;
     if ((int8_t)Result == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
     uint16_t CarryTest = (uint8_t)AReg + (uint8_t)SOperand + Status.C;
     if (CarryTest >> 8)
      {
      Status.C = 1;
      }
     else
      {
      Status.C = 0;
      }
     A = Result;
     if (A >> 7)
      Status.N = 1;
     else
      Status.N = 0;
     Status.V = 0;
     if (ANeg && SOperand >> 7 && !(A >> 7))
      Status.V = 1;
     if (!ANeg && SOperand >> 7 == 0 && A >> 7)
      Status.V = 1;
      }
     
    if (Instruction == "SAX")
     {
     byte Result = A & X;
     WriteRAM(Address, Result);
     }

    if (Instruction == "SBX")
     {
     uint16_t Result = 0;
     uint16_t Fetched = 0;
     Fetched = (uint16_t)ExtraBytes;
     uint16_t AX = A & X;
     Result = AX - (uint16_t)Fetched;
     if ((Result & 0x00FF) == 0x0000)
      Status.Z = 1;
     else
      Status.Z = 0;
     if (Result & 0x0080)
      Status.N = 1;
     else
      Status.N = 0;
     if (AX >= Fetched)
      Status.C = 1;
     else
      Status.C = 0;
     }

    if (Instruction == "SHA")
     {
     byte Result = A & X & (((Address & 0xFF00) >> 8) + 1);
     WriteRAM(Address, Result);
     }

    if (Instruction == "SHX")
     {
     byte Result = X & (((Address & 0xFF00) >> 8) + 1);
     WriteRAM(Address, Result);
     }

    if (Instruction == "SHY")
     {
     byte Result = Y & (((Address & 0xFF00) >> 8) + 1);
     WriteRAM(Address, Result);
     }

    if (Instruction == "SLO")
     {
     byte Operand = ReadRAM(Address);
     Status.C = Operand & 0x80;
     Operand <<= 1;
     A = A | Operand;
     }

    if (Instruction == "SRE")
     {
     byte Operand = ReadRAM(Address);
     Status.C = Operand & 0x01;
     Operand >>= 1;
     A = A ^ Operand;
     }

    if (Instruction == "TAS")
     {
     SP = A & X;
     byte Result = A & X & (((Address & 0xFF00) >> 8) + 1);
     WriteRAM(Address, Result);
     }

    if (Instruction == "USBC")
     {
     bool ANeg = A >> 7;
     int8_t Operand = 0;
     int8_t AReg = A;
     Operand = (byte)ExtraBytes;
     Operand = ~Operand;
     int Result = AReg + Operand + Status.C;
     if ((int8_t)Result == 0)
      Status.Z = 1;
     else
      Status.Z = 0;
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

    if (Instruction == "HLT")
     {
     CPUHalt = true;
     }

    }
   /*
   else
   {
   cout << "Waiting on previous instruction, Cycles=" << Cycles << endl;
   }
   */

    if (!CPUHalt)
     {
     Cycles--;
     if (Cycles == 0)
      InstructionComplete = true;
     }
   return;
   }


  void M6502::NMI()
   {
   Push(PC >> 8);
   Push(PC & 0xFF);
   byte FlagsByte = (Status.N << 7) | (Status.V << 6) | (1 << 5) | (0 << 4) | (Status.D << 3) | (Status.I << 2) | (Status.Z << 1) | Status.C;
   Push(FlagsByte);
   Status.I = 1;
   PC = (ReadRAM(0xFFFA) | (ReadRAM(0xFFFB) << 8));
   return;
   }


  void M6502::IRQ()
   {
   if (Status.I == 0)
    {
    Push(PC >> 8);
    Push(PC & 0xFF);
    byte FlagsByte = (Status.N << 7) | (Status.V << 6) | (1 << 5) | (0 << 4) | (Status.D << 3) | (Status.I << 2) | (Status.Z << 1) | Status.C;
    Push(FlagsByte);
    Status.I = 1;
    PC = (ReadRAM(0xFFFE) | (ReadRAM(0xFFFF) << 8));
    }
   return;
   }


  string M6502::ToHex(word Num, byte Dec)
   {
   string s(Dec, '0');
   for (int i = Dec - 1; i >= 0; i--, Num >>= 4)
    {
    s[i] = "0123456789ABCDEF"[Num & 0xF];
    }
   return s;
   }

  map<word, string> M6502::Disassemble(word StartAddr, word StopAddr) //May be broken? Copied over without testing
   {
   uint32_t RealAddr = StartAddr;
   uint32_t CurrentAddr = 0x00;
   byte Value = 0x00, lo = 0x00, hi = 0x00;
   map<word, string> MapLines;
   word LineAddr = 0;
   while (RealAddr <= (uint32_t)StopAddr)
    {
    LineAddr = RealAddr;

    byte Junk = 0x00;
    CurrentAddr = RealAddr;
    byte Opcode = ReadRAM(CurrentAddr);
    string Inst = "$" + ToHex(CurrentAddr, 4) + ": ";
    CurrentAddr++;
    RealAddr++;
    Inst += OL.Mnemonic(Opcode) + " ";
    if (OL.Mnemonic(Opcode) == "ILL")
     Inst += "(0x" + ToHex((int)Opcode, 2) + ") ";
    if (OL.Addressing(Opcode) == "IMP")
     {
     Inst += " {IMP}";
     }
    else if (OL.Addressing(Opcode) == "IMM")
     {
     Value = ReadRAM(CurrentAddr);
     CurrentAddr++;
     RealAddr++;
     Inst += "#$" + ToHex(Value, 2) + " { IMM }";
     }
    else if (OL.Addressing(Opcode) == "ZP")
     {
     lo = ReadRAM(CurrentAddr);
     CurrentAddr++;
     RealAddr++;
     hi = 0x00;
     Inst += "$" + ToHex(lo, 2) + " {ZP}";
     }
    else if (OL.Addressing(Opcode) == "ZPX")
     {
     lo = ReadRAM(CurrentAddr);
     CurrentAddr++;
     RealAddr++;
     hi = 0x00;
     Inst += "$" + ToHex(lo, 2) + ", X {ZPX}";
     }
    else if (OL.Addressing(Opcode) == "ZPY")
     {
     lo = ReadRAM(CurrentAddr);
     CurrentAddr++;
     RealAddr++;
     hi = 0x00;
     Inst += "$" + ToHex(lo, 2) + ", Y {ZPY}";
     }
    else if (OL.Addressing(Opcode) == "INDX")
     {
     lo = ReadRAM(CurrentAddr);
     CurrentAddr++;
     RealAddr++;
     hi = 0x00;
     Inst += "($" + ToHex(lo, 2) + ", X) {INDX}";
     }
    else if (OL.Addressing(Opcode) == "INDY")
     {
     lo = ReadRAM(CurrentAddr);
     CurrentAddr++;
     RealAddr++;
     hi = 0x00;
     Inst += "($" + ToHex(lo, 2) + ", Y) {INDY}";
     }
    else if (OL.Addressing(Opcode) == "ABS")
     {
     lo = ReadRAM(CurrentAddr);
     CurrentAddr++;
     RealAddr++;
     hi = ReadRAM(CurrentAddr);
     CurrentAddr++;
     RealAddr++;
     Inst += "$" + ToHex((word)(hi << 8) | lo, 4) + " {ABS}";
     }
    else if (OL.Addressing(Opcode) == "ABSX")
     {
     lo = ReadRAM(CurrentAddr);
     CurrentAddr++;
     RealAddr++;
     hi = ReadRAM(CurrentAddr);
     CurrentAddr++;
     RealAddr++;
     Inst += "$" + ToHex((word)(hi << 8) | lo, 4) + ", X {ABSX}";
     }
    else if (OL.Addressing(Opcode) == "ABSY")
     {
     lo = ReadRAM(CurrentAddr);
     CurrentAddr++;
     RealAddr++;
     hi = ReadRAM(CurrentAddr);
     CurrentAddr++;
     RealAddr++;
     Inst += "$" + ToHex((word)(hi << 8) | lo, 4) + ", Y {ABSY}";
     }
    else if (OL.Addressing(Opcode) == "IND")
     {
     lo = ReadRAM(CurrentAddr);
     CurrentAddr++;
     RealAddr++;
     hi = ReadRAM(CurrentAddr);
     CurrentAddr++;
     RealAddr++;
     Inst += "($" + ToHex((word)(hi << 8) | lo, 4) + ") {IND}";
     }
    else if (OL.Addressing(Opcode) == "REL")
     {
     Value = ReadRAM(CurrentAddr);
     CurrentAddr++;
     RealAddr++;
     Inst += "$" + ToHex(Value, 2) + " [$" + ToHex(CurrentAddr + (int8_t)Value, 4) + "] {REL}";
     }

    MapLines[LineAddr] = Inst;
    }
   return MapLines;
   }


