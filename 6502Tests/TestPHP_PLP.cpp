#include "pch.h"
#include "../M6502/M6502.h"


TEST(PHPPLP, PHPPLPFlags) { //0-1 = -1; C=0, N=1, V=0, Z=0

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
  CPU.Status.C = 1;
  CPU.Status.Z = 1;
  CPU.Status.V = 0;
  CPU.Status.N = 0;
 CPU.WriteRAM(0x8000, 0x08);
 CPU.WriteRAM(0x8001, 0x28);
 CPU.Execute(5);
 EXPECT_TRUE(CPU.Status.C);
 EXPECT_TRUE(CPU.Status.Z);
 EXPECT_FALSE(CPU.Status.V);
 EXPECT_FALSE(CPU.Status.N);
 
 }

