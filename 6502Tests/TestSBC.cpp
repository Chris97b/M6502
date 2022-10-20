#include "pch.h"
#include "../M6502/M6502.h"


TEST(SBC, SBC_Basic) { //0-1 = -1; C=0, N=1, V=0, Z=0

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.A = 0x00;
 CPU.Status.C = 1;
 CPU.WriteRAM(0x8000, 0xE9);
 CPU.WriteRAM(0x8001, 0x01);
 CPU.Execute(2);
 EXPECT_EQ(CPU.A, 0xFF);
 EXPECT_FALSE(CPU.Status.Z);
 EXPECT_FALSE(CPU.Status.C); //I give up
 EXPECT_TRUE(CPU.Status.N);
 EXPECT_FALSE(CPU.Status.V);
 }

