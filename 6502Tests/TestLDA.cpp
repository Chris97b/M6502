#include "pch.h"
#include "../M6502/M6502.h"



TEST(LDA, LDA_IMM) { //LDA can load an immediate to the A register

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.WriteRAM(0x8000, 0xA9);
 CPU.WriteRAM(0x8001, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.A, 0x45) << "A: " << hex << uppercase << (int)CPU.A;
 EXPECT_FALSE(CPU.Status.Z);
 EXPECT_FALSE(CPU.Status.N);
 }

TEST(LDA, LDA_ZERO) { //LDA sets Zero flag

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.WriteRAM(0x8000, 0xA9);
 CPU.WriteRAM(0x8001, 0x00);
 CPU.Execute(2);
 EXPECT_EQ(CPU.A, 0x00) << "A: " << hex << uppercase << (int)CPU.A;
 EXPECT_TRUE(CPU.Status.Z);
 EXPECT_FALSE(CPU.Status.N);
 }

TEST(LDA, LDA_NEG) { //LDA sets Negative flag

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.WriteRAM(0x8000, 0xA9);
 CPU.WriteRAM(0x8001, 0xFF);
 CPU.Execute(2);
 EXPECT_EQ(CPU.A, 0xFF) << "A: " << hex << uppercase << (int)CPU.A;
 EXPECT_FALSE(CPU.Status.Z);
 EXPECT_TRUE(CPU.Status.N);
 }

TEST(LDA, LDA_ABS) { 

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.WriteRAM(0x8000, 0xAD);
 CPU.WriteRAM(0x8001, 0x34);
 CPU.WriteRAM(0x8002, 0x12);
 CPU.WriteRAM(0x1234, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.A, 0x45) << "A: " << hex << uppercase << (int)CPU.A;
 }

TEST(LDA, LDA_ABSX) { 

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.X = 0x10;
 CPU.WriteRAM(0x8000, 0xBD);
 CPU.WriteRAM(0x8001, 0x34);
 CPU.WriteRAM(0x8002, 0x12);
 CPU.WriteRAM(0x1244, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.A, 0x45) << "A: " << hex << uppercase << (int)CPU.A;
 }

TEST(LDA, LDA_ABSY) {

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.Y = 0x10;
 CPU.WriteRAM(0x8000, 0xB9);
 CPU.WriteRAM(0x8001, 0x34);
 CPU.WriteRAM(0x8002, 0x12);
 CPU.WriteRAM(0x1244, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.A, 0x45) << "A: " << hex << uppercase << (int)CPU.A;
 }

TEST(LDA, LDA_ZP) {

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.WriteRAM(0x8000, 0xA5);
 CPU.WriteRAM(0x8001, 0x34);
 CPU.WriteRAM(0x34, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.A, 0x45) << "A: " << hex << uppercase << (int)CPU.A;
 }

TEST(LDA, LDA_ZPX) {

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.X = 0x10;
 CPU.WriteRAM(0x8000, 0xB5);
 CPU.WriteRAM(0x8001, 0x34);
 CPU.WriteRAM(0x44, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.A, 0x45) << "A: " << hex << uppercase << (int)CPU.A;
 }

TEST(LDA, LDA_ZPX_OVF) { //LDA ZPX overflows to stay in zero page

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.X = 0x10;
 CPU.WriteRAM(0x8000, 0xB5);
 CPU.WriteRAM(0x8001, 0xFA);
 CPU.WriteRAM(0x0A, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.A, 0x45) << "A: " << hex << uppercase << (int)CPU.A;
 }

TEST(LDA, LDA_INDX) { 

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.X = 0x04;
 CPU.WriteRAM(0x8000, 0xA1);
 CPU.WriteRAM(0x8001, 0x20);
 CPU.WriteRAM(0x24, 0x74);
 CPU.WriteRAM(0x25, 0x20);
 CPU.WriteRAM(0x2074, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.A, 0x45) << "A: " << hex << uppercase << (int)CPU.A;
 }

TEST(LDA, LDA_INDY) {

 M6502 CPU;
 CPU.WriteRAM(0xFFFC, 0x00);
 CPU.WriteRAM(0xFFFD, 0x80);
 CPU.Reset();
 CPU.Y = 0x10;
 CPU.WriteRAM(0x8000, 0xB1);
 CPU.WriteRAM(0x8001, 0x86);
 CPU.WriteRAM(0x86, 0x28);
 CPU.WriteRAM(0x87, 0x40);
 CPU.WriteRAM(0x4038, 0x45);
 CPU.Execute(2);
 EXPECT_EQ(CPU.A, 0x45) << "A: " << hex << uppercase << (int)CPU.A;
 }