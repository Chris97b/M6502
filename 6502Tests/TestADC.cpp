#include "pch.h"
#include "../M6502/M6502.h"


TEST(ADC, ADC_Basic) { //1+1 = 2; C=0, N=0, V=0

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.A = 0x01;
 CPU.WriteRAM(0x8000, 0x69);
 CPU.WriteRAM(0x8001, 0x01);
 CPU.Execute(2);
 EXPECT_EQ(CPU.A, 0x02) << "A: " << hex << uppercase << (int)CPU.A;
 EXPECT_FALSE(CPU.Status.Z);
 EXPECT_FALSE(CPU.Status.N);
 EXPECT_FALSE(CPU.Status.V);
 }

TEST(ADC, ADC_NEG) { //1+(-1) = 0; C=0, N=1, V=0

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.A = 0x01;
 CPU.WriteRAM(0x8000, 0x69);
 CPU.WriteRAM(0x8001, 0xFF);
 CPU.Execute(2);
 EXPECT_EQ(CPU.A, 0x00) << "A: " << hex << uppercase << (int)CPU.A;
 EXPECT_TRUE(CPU.Status.Z);
 EXPECT_FALSE(CPU.Status.N);
 EXPECT_FALSE(CPU.Status.V);
 }

TEST(ADC, ADC_OVF1) { //127+1 = 128; C=0, N=1, V=1

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.A = 0x01;
 CPU.WriteRAM(0x8000, 0x69);
 CPU.WriteRAM(0x8001, 0x7F);
 CPU.Execute(2);
 EXPECT_EQ(CPU.A, 0x80) << "A: " << hex << uppercase << (int)CPU.A;
 EXPECT_FALSE(CPU.Status.Z);
 EXPECT_TRUE(CPU.Status.N);
 EXPECT_TRUE(CPU.Status.V);
 }

TEST(ADC, ADC_OVF2) { //(-128)+(-1) = -129 (127 + Carry, Overflow); C=1, N=0, V=1

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.A = 0x80;
 CPU.WriteRAM(0x8000, 0x69);
 CPU.WriteRAM(0x8001, 0xFF);
 CPU.Execute(2);
 EXPECT_EQ(CPU.A, 0x7F) << "A: " << hex << uppercase << (int)CPU.A;
 EXPECT_TRUE(CPU.Status.C);
 EXPECT_FALSE(CPU.Status.N);
 EXPECT_TRUE(CPU.Status.V);
 }