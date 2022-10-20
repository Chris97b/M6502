#include "pch.h"
#include "../M6502/M6502.h"



TEST(LDY, LDY_IMM) { //LDY can load an immediate to the Y register

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.WriteRAM(0x8000, 0xA0);
 CPU.WriteRAM(0x8001, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.Y, 0x45) << "A: " << hex << uppercase << (int)CPU.Y;
 EXPECT_FALSE(CPU.Status.Z);
 EXPECT_FALSE(CPU.Status.N);
 }

TEST(LDY, LDY_ZERO) { //LDY sets Zero flag

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.WriteRAM(0x8000, 0xA0);
 CPU.WriteRAM(0x8001, 0x00);
 CPU.Execute(2);
 EXPECT_EQ(CPU.Y, 0x00) << "A: " << hex << uppercase << (int)CPU.Y;
 EXPECT_TRUE(CPU.Status.Z);
 EXPECT_FALSE(CPU.Status.N);
 }

TEST(LDY, LDY_NEG) { //LDY sets Negative flag

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.WriteRAM(0x8000, 0xA0);
 CPU.WriteRAM(0x8001, 0xFF);
 CPU.Execute(2);
 EXPECT_EQ(CPU.Y, 0xFF) << "A: " << hex << uppercase << (int)CPU.Y;
 EXPECT_FALSE(CPU.Status.Z);
 EXPECT_TRUE(CPU.Status.N);
 }

TEST(LDY, LDY_ABS) { 

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.WriteRAM(0x8000, 0xAC);
 CPU.WriteRAM(0x8001, 0x34);
 CPU.WriteRAM(0x8002, 0x12);
 CPU.WriteRAM(0x1234, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.Y, 0x45) << "A: " << hex << uppercase << (int)CPU.Y;
 }

TEST(LDY, LDY_ABSX) { 

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.X = 0x10;
 CPU.WriteRAM(0x8000, 0xBC);
 CPU.WriteRAM(0x8001, 0x34);
 CPU.WriteRAM(0x8002, 0x12);
 CPU.WriteRAM(0x1244, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.Y, 0x45) << "A: " << hex << uppercase << (int)CPU.Y;
 }

TEST(LDY, LDY_ZP) {

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.WriteRAM(0x8000, 0xA4);
 CPU.WriteRAM(0x8001, 0x34);
 CPU.WriteRAM(0x34, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.Y, 0x45) << "A: " << hex << uppercase << (int)CPU.Y;
 }

TEST(LDY, LDY_ZPX) {

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.X = 0x10;
 CPU.WriteRAM(0x8000, 0xB4);
 CPU.WriteRAM(0x8001, 0x34);
 CPU.WriteRAM(0x44, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.Y, 0x45) << "A: " << hex << uppercase << (int)CPU.Y;
 }

TEST(LDY, LDY_ZPX_OVF) { //LDA ZPX overflows to stay in zero page

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.X = 0x10;
 CPU.WriteRAM(0x8000, 0xB4);
 CPU.WriteRAM(0x8001, 0xFA);
 CPU.WriteRAM(0x0A, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.Y, 0x45) << "A: " << hex << uppercase << (int)CPU.Y;
 }
 