#include "pch.h"
#include "../M6502/M6502.h"



TEST(LDX, LDX_IMM) { //LDX can load an immediate to the X register

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.WriteRAM(0x8000, 0xA2);
 CPU.WriteRAM(0x8001, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.X, 0x45) << "X: " << hex << uppercase << (int)CPU.X;
 EXPECT_FALSE(CPU.Status.Z);
 EXPECT_FALSE(CPU.Status.N);
 }

TEST(LDX, LDX_ZERO) { //LDX sets Zero flag

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.WriteRAM(0x8000, 0xA2);
 CPU.WriteRAM(0x8001, 0x00);
 CPU.Execute(2);
 EXPECT_EQ(CPU.X, 0x00) << "X: " << hex << uppercase << (int)CPU.X;
 EXPECT_TRUE(CPU.Status.Z);
 EXPECT_FALSE(CPU.Status.N);
 }

TEST(LDX, LDX_NEG) { //LDX sets Negative flag

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.WriteRAM(0x8000, 0xA2);
 CPU.WriteRAM(0x8001, 0xFF);
 CPU.Execute(2);
 EXPECT_EQ(CPU.X, 0xFF) << "X: " << hex << uppercase << (int)CPU.X;
 EXPECT_FALSE(CPU.Status.Z);
 EXPECT_TRUE(CPU.Status.N);
 }

TEST(LDX, LDX_ABS) { 

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.WriteRAM(0x8000, 0xAE);
 CPU.WriteRAM(0x8001, 0x34);
 CPU.WriteRAM(0x8002, 0x12);
 CPU.WriteRAM(0x1234, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.X, 0x45) << "X: " << hex << uppercase << (int)CPU.X;
 }

TEST(LDX, LDX_ABSY) {

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.Y = 0x10;
 CPU.WriteRAM(0x8000, 0xBE);
 CPU.WriteRAM(0x8001, 0x34);
 CPU.WriteRAM(0x8002, 0x12);
 CPU.WriteRAM(0x1244, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.X, 0x45) << "X: " << hex << uppercase << (int)CPU.X;
 }

TEST(LDX, LDX_ZP) {

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.WriteRAM(0x8000, 0xA6);
 CPU.WriteRAM(0x8001, 0x34);
 CPU.WriteRAM(0x34, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.X, 0x45) << "X: " << hex << uppercase << (int)CPU.X;
 }

TEST(LDX, LDX_ZPY) { 

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.Y = 0x10;
 CPU.WriteRAM(0x8000, 0xB6);
 CPU.WriteRAM(0x8001, 0xFA);
 CPU.WriteRAM(0x010A, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.X, 0x45) << "X: " << hex << uppercase << (int)CPU.X;
 }
