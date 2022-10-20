#include "pch.h"
#include "../M6502/M6502.h"


 TEST(AddressResolution, ZP) //Zero page addressing returns 0x00XX given $XX
  {
  M6502 CPU;
  int Cycles = 3;
  EXPECT_EQ(CPU.ResolveAddress(0xA5, 0xB6, &Cycles), 0x00B6);
  }

 TEST(AddressResolution, ZPX) //Zero page X addressing returns operand + contents of X register
  {
  M6502 CPU;
  CPU.X = 0x0F;
  int Cycles = 4;
  EXPECT_EQ(CPU.ResolveAddress(0xB5, 0x80, &Cycles), 0x8F);
  }

 TEST(AddressResolution, ZPX_OVF) //Zero page X addressing overflows to stay in Zero Page
  {
  M6502 CPU;
  CPU.X = 0xFF;
  int Cycles = 4;
  EXPECT_EQ(CPU.ResolveAddress(0xB5, 0x80, &Cycles), 0x7F);
  }

 TEST(AddressResolution, ZPY) //Zero page Y addressing returns operand + contents of X register
  {
  M6502 CPU;
  CPU.Y = 0x0F;
  int Cycles = 4;
  EXPECT_EQ(CPU.ResolveAddress(0xB6, 0x80, &Cycles), 0x8F);
  }

 TEST(AddressResolution, ZPY_OVF) //Zero page Y does not wrap in ZP
  {
  M6502 CPU;
  CPU.Y = 0xFF;
  int Cycles = 4;
  EXPECT_EQ(CPU.ResolveAddress(0xB6, 0x80, &Cycles), 0x017F);
  }

 TEST(AddressResolution, REL) //Relative addressing returns PC + Offset
  {
  M6502 CPU;
  CPU.PC = 0x0100;
  int Cycles = 4;
  EXPECT_EQ(CPU.ResolveAddress(0xF0, 0x0F, &Cycles), 0x010F);
  }

 TEST(AddressResolution, REL_OVF) //Relative addressing Overflows to following page
  {
  M6502 CPU;
  CPU.PC = 0x01FA;
  int Cycles = 4;
  EXPECT_EQ(CPU.ResolveAddress(0xF0, 0x0A, &Cycles), 0x0204);
  }

 TEST(AddressResolution, REL_UNF) //Relative addressing Underflows to previous page
  {
  M6502 CPU;
  CPU.PC = 0x0100;
  int Cycles = 4;
  EXPECT_EQ(CPU.ResolveAddress(0xF0, 0xF6, &Cycles), 0x00F6);
  }

 TEST(AddressResolution, REL_NEG) //Relative addressing returns PC - Offset if Offset is negative (signed byte)
  {
  M6502 CPU;
  CPU.PC = 0x0105;
  int Cycles = 4;
  EXPECT_EQ(CPU.ResolveAddress(0xF0, 0xFF, &Cycles), 0x0104);
  }

 TEST(AddressResolution, ABS) //Absolute addressing
  {
  M6502 CPU;
  int Cycles = 4;
  EXPECT_EQ(CPU.ResolveAddress(0xAD, 0x0123, &Cycles), 0x0123);
  }

 TEST(AddressResolution, ABSX) //Absolute addressing
  {
  M6502 CPU;
  int Cycles = 4;
  CPU.X = 0x92;
  EXPECT_EQ(CPU.ResolveAddress(0xBD, 0x2000, &Cycles), 0x2092);
  }

 TEST(AddressResolution, ABSX_OVF) //Absolute addressing overflows to following page
  {
  M6502 CPU;
  int Cycles = 4;
  CPU.X = 0x92;
  EXPECT_EQ(CPU.ResolveAddress(0xBD, 0x01FF, &Cycles), 0x0291);
  EXPECT_EQ(Cycles, 3); //Consumes an additional cycle if page crossed
  }

 TEST(AddressResolution, ABSY) //Absolute addressing
  {
  M6502 CPU;
  int Cycles = 4;
  CPU.Y = 0x92;
  EXPECT_EQ(CPU.ResolveAddress(0xB9, 0x2000, &Cycles), 0x2092);
  }

 TEST(AddressResolution, ABSY_OVF) //Absolute addressing overflows to following page
  {
  M6502 CPU;
  int Cycles = 4;
  CPU.Y = 0x92;
  EXPECT_EQ(CPU.ResolveAddress(0xB9, 0x01FF, &Cycles), 0x0291);
  EXPECT_EQ(Cycles, 3); //Consumes an additional cycle if page crossed
  }

 TEST(AddressResolution, IND) 
  {
  M6502 CPU;
  int Cycles = 5;
  CPU.WriteRAM(0x0120, 0xFC);
  CPU.WriteRAM(0x0121, 0xBA);
  EXPECT_EQ(CPU.ResolveAddress(0x6C, 0x0120, &Cycles), 0xBAFC);
  }
 
 TEST(AddressResolution, INDX) 
  {
  M6502 CPU;
  int Cycles = 5;
  CPU.X = 0x04;
  CPU.WriteRAM(0x24, 0x74);
  CPU.WriteRAM(0x25, 0x20);
  EXPECT_EQ(CPU.ResolveAddress(0xA1, 0x20, &Cycles), 0x2074);
  }

 TEST(AddressResolution, INDX_OVF) //INDX stays in zero page if overflow
  {
  M6502 CPU;
  int Cycles = 5;
  CPU.X = 0x0A;
  CPU.WriteRAM(0x04, 0x74);
  CPU.WriteRAM(0x05, 0x20);
  EXPECT_EQ(CPU.ResolveAddress(0xA1, 0xFA, &Cycles), 0x2074);
  }

 TEST(AddressResolution, INDY) 
  {
  M6502 CPU;
  int Cycles = 5;
  CPU.Y = 0x10;
  CPU.WriteRAM(0x86, 0x28);
  CPU.WriteRAM(0x87, 0x40);
  EXPECT_EQ(CPU.ResolveAddress(0xB1, 0x86, &Cycles), 0x4038);
  }







