#pragma once
#ifndef OPCODELOOKUP_H
#define OPCODELOOKUP_H

#include <string>

using namespace std;

class OpcodeLookup
	{
	public:
	struct Opcode
		{
		string mnemonic;
		string addressing;
		int bytes;
		int cycles;
		string flags;
		};

	Opcode OpcodeMatrix[256];
	Opcode UndocMatrix[256];

	OpcodeLookup();
	string Mnemonic(int Opcode, bool Undoc=false);
	string Addressing(int Opcode, bool Undoc=false);
	int Bytes(int Opcode, bool Undoc=false);
	int Cycles(int Opcode, bool Undoc=false);
		
	};


#endif