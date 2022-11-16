
#include "OpcodeLookup.h"
#include <string>

using namespace std;


		OpcodeLookup::OpcodeLookup()
			{

			for (int i = 0; i < 256; i++)
				{
				OpcodeMatrix[i].mnemonic = "ILL";
				OpcodeMatrix[i].addressing = "IMP";
				OpcodeMatrix[i].bytes = 1;
				OpcodeMatrix[i].cycles = 1;
				OpcodeMatrix[i].flags = "czidbvn";
				}

			OpcodeMatrix[0x0].mnemonic = "ILL";
			OpcodeMatrix[0x0].addressing = "IMP";
			OpcodeMatrix[0x0].bytes = 1;
			OpcodeMatrix[0x0].cycles = 1;
			OpcodeMatrix[0x0].flags = "czidbvn";
			

			OpcodeMatrix[0x69].mnemonic = "ADC";
			OpcodeMatrix[0x69].addressing = "IMM";
			OpcodeMatrix[0x69].bytes = 2;
			OpcodeMatrix[0x69].cycles = 2;
			OpcodeMatrix[0x69].flags = "CZidbVN";

			OpcodeMatrix[0x65].mnemonic = "ADC";
			OpcodeMatrix[0x65].addressing = "ZP";
			OpcodeMatrix[0x65].bytes = 2;
			OpcodeMatrix[0x65].cycles = 3;
			OpcodeMatrix[0x65].flags = "CZidbVN";

			OpcodeMatrix[0x75].mnemonic = "ADC";
			OpcodeMatrix[0x75].addressing = "ZPX";
			OpcodeMatrix[0x75].bytes = 2;
			OpcodeMatrix[0x75].cycles = 4;
			OpcodeMatrix[0x75].flags = "CZidbVN";

			OpcodeMatrix[0x6D].mnemonic = "ADC";
			OpcodeMatrix[0x6D].addressing = "ABS";
			OpcodeMatrix[0x6D].bytes = 3;
			OpcodeMatrix[0x6D].cycles = 4;
			OpcodeMatrix[0x6D].flags = "CZidbVN";

			OpcodeMatrix[0x7D].mnemonic = "ADC";
			OpcodeMatrix[0x7D].addressing = "ABSX";
			OpcodeMatrix[0x7D].bytes = 3;
			OpcodeMatrix[0x7D].cycles = 4;
			OpcodeMatrix[0x7D].flags = "CZidbVN";

			OpcodeMatrix[0x79].mnemonic = "ADC";
			OpcodeMatrix[0x79].addressing = "ABSY";
			OpcodeMatrix[0x79].bytes = 3;
			OpcodeMatrix[0x79].cycles = 4;
			OpcodeMatrix[0x79].flags = "CZidbVN";

			OpcodeMatrix[0x61].mnemonic = "ADC";
			OpcodeMatrix[0x61].addressing = "INDX";
			OpcodeMatrix[0x61].bytes = 2;
			OpcodeMatrix[0x61].cycles = 6;
			OpcodeMatrix[0x61].flags = "CZidbVN";

			OpcodeMatrix[0x71].mnemonic = "ADC";
			OpcodeMatrix[0x71].addressing = "INDY";
			OpcodeMatrix[0x71].bytes = 2;
			OpcodeMatrix[0x71].cycles = 5;
			OpcodeMatrix[0x71].flags = "CZidbVN";

			OpcodeMatrix[0x29].mnemonic = "AND";
			OpcodeMatrix[0x29].addressing = "IMM";
			OpcodeMatrix[0x29].bytes = 2;
			OpcodeMatrix[0x29].cycles = 2;
			OpcodeMatrix[0x29].flags = "cZidbvN";

			OpcodeMatrix[0x25].mnemonic = "AND";
			OpcodeMatrix[0x25].addressing = "ZP";
			OpcodeMatrix[0x25].bytes = 2;
			OpcodeMatrix[0x25].cycles = 3;
			OpcodeMatrix[0x25].flags = "cZidbvN";

			OpcodeMatrix[0x35].mnemonic = "AND";
			OpcodeMatrix[0x35].addressing = "ZPX";
			OpcodeMatrix[0x35].bytes = 2;
			OpcodeMatrix[0x35].cycles = 4;
			OpcodeMatrix[0x35].flags = "cZidbvN";

			OpcodeMatrix[0x2D].mnemonic = "AND";
			OpcodeMatrix[0x2D].addressing = "ABS";
			OpcodeMatrix[0x2D].bytes = 3;
			OpcodeMatrix[0x2D].cycles = 4;
			OpcodeMatrix[0x2D].flags = "cZidbvN";

			OpcodeMatrix[0x3D].mnemonic = "AND";
			OpcodeMatrix[0x3D].addressing = "ABSX";
			OpcodeMatrix[0x3D].bytes = 3;
			OpcodeMatrix[0x3D].cycles = 4;
			OpcodeMatrix[0x3D].flags = "cZidbvN";

			OpcodeMatrix[0x39].mnemonic = "AND";
			OpcodeMatrix[0x39].addressing = "ABSY";
			OpcodeMatrix[0x39].bytes = 3;
			OpcodeMatrix[0x39].cycles = 4;
			OpcodeMatrix[0x39].flags = "cZidbvN";

			OpcodeMatrix[0x21].mnemonic = "AND";
			OpcodeMatrix[0x21].addressing = "INDX";
			OpcodeMatrix[0x21].bytes = 2;
			OpcodeMatrix[0x21].cycles = 6;
			OpcodeMatrix[0x21].flags = "cZidbvN";

			OpcodeMatrix[0x31].mnemonic = "AND";
			OpcodeMatrix[0x31].addressing = "INDY";
			OpcodeMatrix[0x31].bytes = 2;
			OpcodeMatrix[0x31].cycles = 5;
			OpcodeMatrix[0x31].flags = "cZidbvN";

			OpcodeMatrix[0x0A].mnemonic = "ASL";
			OpcodeMatrix[0x0A].addressing = "ACC";
			OpcodeMatrix[0x0A].bytes = 1;
			OpcodeMatrix[0x0A].cycles = 2;
			OpcodeMatrix[0x0A].flags = "CZidbvN";

			OpcodeMatrix[0x06].mnemonic = "ASL";
			OpcodeMatrix[0x06].addressing = "ZP";
			OpcodeMatrix[0x06].bytes = 2;
			OpcodeMatrix[0x06].cycles = 5;
			OpcodeMatrix[0x06].flags = "CZidbvN";

			OpcodeMatrix[0x16].mnemonic = "ASL";
			OpcodeMatrix[0x16].addressing = "ZPX";
			OpcodeMatrix[0x16].bytes = 2;
			OpcodeMatrix[0x16].cycles = 6;
			OpcodeMatrix[0x16].flags = "CZidbvN";

			OpcodeMatrix[0x0E].mnemonic = "ASL";
			OpcodeMatrix[0x0E].addressing = "ABS";
			OpcodeMatrix[0x0E].bytes = 3;
			OpcodeMatrix[0x0E].cycles = 6;
			OpcodeMatrix[0x0E].flags = "CZidbvN";

			OpcodeMatrix[0x1E].mnemonic = "ASL";
			OpcodeMatrix[0x1E].addressing = "ABSX";
			OpcodeMatrix[0x1E].bytes = 3;
			OpcodeMatrix[0x1E].cycles = 7;
			OpcodeMatrix[0x1E].flags = "CZidbvN";

			OpcodeMatrix[0x90].mnemonic = "BCC";
			OpcodeMatrix[0x90].addressing = "REL";
			OpcodeMatrix[0x90].bytes = 2;
			OpcodeMatrix[0x90].cycles = 2;
			OpcodeMatrix[0x90].flags = "czidbvn";

			OpcodeMatrix[0xB0].mnemonic = "BCS";
			OpcodeMatrix[0xB0].addressing = "REL";
			OpcodeMatrix[0xB0].bytes = 2;
			OpcodeMatrix[0xB0].cycles = 2;
			OpcodeMatrix[0xB0].flags = "czidbvn";

			OpcodeMatrix[0xF0].mnemonic = "BEQ";
			OpcodeMatrix[0xF0].addressing = "REL";
			OpcodeMatrix[0xF0].bytes = 2;
			OpcodeMatrix[0xF0].cycles = 2;
			OpcodeMatrix[0xF0].flags = "czidbvn";

			OpcodeMatrix[0x30].mnemonic = "BMI";
			OpcodeMatrix[0x30].addressing = "REL";
			OpcodeMatrix[0x30].bytes = 2;
			OpcodeMatrix[0x30].cycles = 2;
			OpcodeMatrix[0x30].flags = "czidbvn";

			OpcodeMatrix[0xD0].mnemonic = "BNE";
			OpcodeMatrix[0xD0].addressing = "REL";
			OpcodeMatrix[0xD0].bytes = 2;
			OpcodeMatrix[0xD0].cycles = 2;
			OpcodeMatrix[0xD0].flags = "czidbvn";

			OpcodeMatrix[0x10].mnemonic = "BPL";
			OpcodeMatrix[0x10].addressing = "REL";
			OpcodeMatrix[0x10].bytes = 2;
			OpcodeMatrix[0x10].cycles = 2;
			OpcodeMatrix[0x10].flags = "czidbvn";

			OpcodeMatrix[0x50].mnemonic = "BVC";
			OpcodeMatrix[0x50].addressing = "REL";
			OpcodeMatrix[0x50].bytes = 2;
			OpcodeMatrix[0x50].cycles = 2;
			OpcodeMatrix[0x50].flags = "czidbvn";

			OpcodeMatrix[0x70].mnemonic = "BVS";
			OpcodeMatrix[0x70].addressing = "REL";
			OpcodeMatrix[0x70].bytes = 2;
			OpcodeMatrix[0x70].cycles = 2;
			OpcodeMatrix[0x70].flags = "czidbvn";

			OpcodeMatrix[0x24].mnemonic = "BIT";
			OpcodeMatrix[0x24].addressing = "ZP";
			OpcodeMatrix[0x24].bytes = 2;
			OpcodeMatrix[0x24].cycles = 3;
			OpcodeMatrix[0x24].flags = "cZidbVN";

			OpcodeMatrix[0x2C].mnemonic = "BIT";
			OpcodeMatrix[0x2C].addressing = "ABS";
			OpcodeMatrix[0x2C].bytes = 3;
			OpcodeMatrix[0x2C].cycles = 4;
			OpcodeMatrix[0x2C].flags = "cZidbVN";

			OpcodeMatrix[0x00].mnemonic = "BRK";
			OpcodeMatrix[0x00].addressing = "IMP";
			OpcodeMatrix[0x00].bytes = 2;
			OpcodeMatrix[0x00].cycles = 7;
			OpcodeMatrix[0x00].flags = "czidbvn";

			OpcodeMatrix[0x18].mnemonic = "CLC";
			OpcodeMatrix[0x18].addressing = "IMP";
			OpcodeMatrix[0x18].bytes = 1;
			OpcodeMatrix[0x18].cycles = 2;
			OpcodeMatrix[0x18].flags = "Czidbvn";

			OpcodeMatrix[0xD8].mnemonic = "CLD";
			OpcodeMatrix[0xD8].addressing = "IMP";
			OpcodeMatrix[0xD8].bytes = 1;
			OpcodeMatrix[0xD8].cycles = 2;
			OpcodeMatrix[0xD8].flags = "cziDbvn";

			OpcodeMatrix[0x58].mnemonic = "CLI";
			OpcodeMatrix[0x58].addressing = "IMP";
			OpcodeMatrix[0x58].bytes = 1;
			OpcodeMatrix[0x58].cycles = 2;
			OpcodeMatrix[0x58].flags = "czIdbvn";

			OpcodeMatrix[0xB8].mnemonic = "CLV";
			OpcodeMatrix[0xB8].addressing = "IMP";
			OpcodeMatrix[0xB8].bytes = 1;
			OpcodeMatrix[0xB8].cycles = 2;
			OpcodeMatrix[0xB8].flags = "czidbVn";

			OpcodeMatrix[0xEA].mnemonic = "NOP";
			OpcodeMatrix[0xEA].addressing = "IMP";
			OpcodeMatrix[0xEA].bytes = 1;
			OpcodeMatrix[0xEA].cycles = 2;
			OpcodeMatrix[0xEA].flags = "czidbvn";

			OpcodeMatrix[0x48].mnemonic = "PHA";
			OpcodeMatrix[0x48].addressing = "IMP";
			OpcodeMatrix[0x48].bytes = 1;
			OpcodeMatrix[0x48].cycles = 3;
			OpcodeMatrix[0x48].flags = "czidbvn";

			OpcodeMatrix[0x68].mnemonic = "PLA";
			OpcodeMatrix[0x68].addressing = "IMP";
			OpcodeMatrix[0x68].bytes = 1;
			OpcodeMatrix[0x68].cycles = 4;
			OpcodeMatrix[0x68].flags = "cZidbvN";

			OpcodeMatrix[0x08].mnemonic = "PHP";
			OpcodeMatrix[0x08].addressing = "IMP";
			OpcodeMatrix[0x08].bytes = 1;
			OpcodeMatrix[0x08].cycles = 3;
			OpcodeMatrix[0x08].flags = "czidbvn";

			OpcodeMatrix[0x28].mnemonic = "PLP";
			OpcodeMatrix[0x28].addressing = "IMP";
			OpcodeMatrix[0x28].bytes = 1;
			OpcodeMatrix[0x28].cycles = 4;
			OpcodeMatrix[0x28].flags = "CZIDBVN";

			OpcodeMatrix[0x40].mnemonic = "RTI";
			OpcodeMatrix[0x40].addressing = "IMP";
			OpcodeMatrix[0x40].bytes = 1;
			OpcodeMatrix[0x40].cycles = 6;
			OpcodeMatrix[0x40].flags = "czidbvn";

			OpcodeMatrix[0x60].mnemonic = "RTS";
			OpcodeMatrix[0x60].addressing = "IMP";
			OpcodeMatrix[0x60].bytes = 1;
			OpcodeMatrix[0x60].cycles = 6;
			OpcodeMatrix[0x60].flags = "czidbvn";

			OpcodeMatrix[0x38].mnemonic = "SEC";
			OpcodeMatrix[0x38].addressing = "IMP";
			OpcodeMatrix[0x38].bytes = 1;
			OpcodeMatrix[0x38].cycles = 2;
			OpcodeMatrix[0x38].flags = "Czidbvn";

			OpcodeMatrix[0xF8].mnemonic = "SED";
			OpcodeMatrix[0xF8].addressing = "IMP";
			OpcodeMatrix[0xF8].bytes = 1;
			OpcodeMatrix[0xF8].cycles = 2;
			OpcodeMatrix[0xF8].flags = "cziDbvn";

			OpcodeMatrix[0x78].mnemonic = "SEI";
			OpcodeMatrix[0x78].addressing = "IMP";
			OpcodeMatrix[0x78].bytes = 1;
			OpcodeMatrix[0x78].cycles = 2;
			OpcodeMatrix[0x78].flags = "czIdbvn";

			OpcodeMatrix[0xAA].mnemonic = "TAX";
			OpcodeMatrix[0xAA].addressing = "IMP";
			OpcodeMatrix[0xAA].bytes = 1;
			OpcodeMatrix[0xAA].cycles = 2;
			OpcodeMatrix[0xAA].flags = "cZidbvN";

			OpcodeMatrix[0x8A].mnemonic = "TXA";
			OpcodeMatrix[0x8A].addressing = "IMP";
			OpcodeMatrix[0x8A].bytes = 1;
			OpcodeMatrix[0x8A].cycles = 2;
			OpcodeMatrix[0x8A].flags = "cZidbvN";

			OpcodeMatrix[0xA8].mnemonic = "TAY";
			OpcodeMatrix[0xA8].addressing = "IMP";
			OpcodeMatrix[0xA8].bytes = 1;
			OpcodeMatrix[0xA8].cycles = 2;
			OpcodeMatrix[0xA8].flags = "cZidbvN";

			OpcodeMatrix[0x98].mnemonic = "TYA";
			OpcodeMatrix[0x98].addressing = "IMP";
			OpcodeMatrix[0x98].bytes = 1;
			OpcodeMatrix[0x98].cycles = 2;
			OpcodeMatrix[0x98].flags = "cZidbvN";

			OpcodeMatrix[0xBA].mnemonic = "TSX";
			OpcodeMatrix[0xBA].addressing = "IMP";
			OpcodeMatrix[0xBA].bytes = 1;
			OpcodeMatrix[0xBA].cycles = 2;
			OpcodeMatrix[0xBA].flags = "cZidbvN";

			OpcodeMatrix[0x9A].mnemonic = "TXS";
			OpcodeMatrix[0x9A].addressing = "IMP";
			OpcodeMatrix[0x9A].bytes = 1;
			OpcodeMatrix[0x9A].cycles = 2;
			OpcodeMatrix[0x9A].flags = "czidbvn";

			OpcodeMatrix[0xC9].mnemonic = "CMP";
			OpcodeMatrix[0xC9].addressing = "IMM";
			OpcodeMatrix[0xC9].bytes = 2;
			OpcodeMatrix[0xC9].cycles = 2;
			OpcodeMatrix[0xC9].flags = "CZidbvN";

			OpcodeMatrix[0xC5].mnemonic = "CMP";
			OpcodeMatrix[0xC5].addressing = "ZP";
			OpcodeMatrix[0xC5].bytes = 2;
			OpcodeMatrix[0xC5].cycles = 3;
			OpcodeMatrix[0xC5].flags = "CZidbvN";

			OpcodeMatrix[0xD5].mnemonic = "CMP";
			OpcodeMatrix[0xD5].addressing = "ZPX";
			OpcodeMatrix[0xD5].bytes = 2;
			OpcodeMatrix[0xD5].cycles = 4;
			OpcodeMatrix[0xD5].flags = "CZidbvN";

			OpcodeMatrix[0xCD].mnemonic = "CMP";
			OpcodeMatrix[0xCD].addressing = "ABS";
			OpcodeMatrix[0xCD].bytes = 3;
			OpcodeMatrix[0xCD].cycles = 4;
			OpcodeMatrix[0xCD].flags = "CZidbvN";

			OpcodeMatrix[0xDD].mnemonic = "CMP";
			OpcodeMatrix[0xDD].addressing = "ABSX";
			OpcodeMatrix[0xDD].bytes = 3;
			OpcodeMatrix[0xDD].cycles = 4;
			OpcodeMatrix[0xDD].flags = "CZidbvN";

			OpcodeMatrix[0xD9].mnemonic = "CMP";
			OpcodeMatrix[0xD9].addressing = "ABSY";
			OpcodeMatrix[0xD9].bytes = 3;
			OpcodeMatrix[0xD9].cycles = 4;
			OpcodeMatrix[0xD9].flags = "CZidbvN";

			OpcodeMatrix[0xC1].mnemonic = "CMP";
			OpcodeMatrix[0xC1].addressing = "INDX";
			OpcodeMatrix[0xC1].bytes = 2;
			OpcodeMatrix[0xC1].cycles = 6;
			OpcodeMatrix[0xC1].flags = "CZidbvN";

			OpcodeMatrix[0xD1].mnemonic = "CMP";
			OpcodeMatrix[0xD1].addressing = "INDY";
			OpcodeMatrix[0xD1].bytes = 2;
			OpcodeMatrix[0xD1].cycles = 5;
			OpcodeMatrix[0xD1].flags = "CZidbvN";

			OpcodeMatrix[0xE0].mnemonic = "CPX";
			OpcodeMatrix[0xE0].addressing = "IMM";
			OpcodeMatrix[0xE0].bytes = 2;
			OpcodeMatrix[0xE0].cycles = 2;
			OpcodeMatrix[0xE0].flags = "CZidbvN";

			OpcodeMatrix[0xE4].mnemonic = "CPX";
			OpcodeMatrix[0xE4].addressing = "ZP";
			OpcodeMatrix[0xE4].bytes = 2;
			OpcodeMatrix[0xE4].cycles = 3;
			OpcodeMatrix[0xE4].flags = "CZidbvN";

			OpcodeMatrix[0xEC].mnemonic = "CPX";
			OpcodeMatrix[0xEC].addressing = "ABS";
			OpcodeMatrix[0xEC].bytes = 3;
			OpcodeMatrix[0xEC].cycles = 4;
			OpcodeMatrix[0xEC].flags = "CZidbvN";

			OpcodeMatrix[0xC0].mnemonic = "CPY";
			OpcodeMatrix[0xC0].addressing = "IMM";
			OpcodeMatrix[0xC0].bytes = 2;
			OpcodeMatrix[0xC0].cycles = 2;
			OpcodeMatrix[0xC0].flags = "CZidbvN";

			OpcodeMatrix[0xC4].mnemonic = "CPY";
			OpcodeMatrix[0xC4].addressing = "ZP";
			OpcodeMatrix[0xC4].bytes = 2;
			OpcodeMatrix[0xC4].cycles = 3;
			OpcodeMatrix[0xC4].flags = "CZidbvN";

			OpcodeMatrix[0xCC].mnemonic = "CPY";
			OpcodeMatrix[0xCC].addressing = "ABS";
			OpcodeMatrix[0xCC].bytes = 3;
			OpcodeMatrix[0xCC].cycles = 4;
			OpcodeMatrix[0xCC].flags = "CZidbvN";

			OpcodeMatrix[0xC6].mnemonic = "DEC";
			OpcodeMatrix[0xC6].addressing = "ZP";
			OpcodeMatrix[0xC6].bytes = 2;
			OpcodeMatrix[0xC6].cycles = 5;
			OpcodeMatrix[0xC6].flags = "cZidbvN";

			OpcodeMatrix[0xD6].mnemonic = "DEC";
			OpcodeMatrix[0xD6].addressing = "ZPX";
			OpcodeMatrix[0xD6].bytes = 2;
			OpcodeMatrix[0xD6].cycles = 6;
			OpcodeMatrix[0xD6].flags = "cZidbvN";

			OpcodeMatrix[0xCE].mnemonic = "DEC";
			OpcodeMatrix[0xCE].addressing = "ABS";
			OpcodeMatrix[0xCE].bytes = 3;
			OpcodeMatrix[0xCE].cycles = 6;
			OpcodeMatrix[0xCE].flags = "cZidbvN";

			OpcodeMatrix[0xDE].mnemonic = "DEC";
			OpcodeMatrix[0xDE].addressing = "ABSX";
			OpcodeMatrix[0xDE].bytes = 3;
			OpcodeMatrix[0xDE].cycles = 7;
			OpcodeMatrix[0xDE].flags = "cZidbvN";

			OpcodeMatrix[0xCA].mnemonic = "DEX";
			OpcodeMatrix[0xCA].addressing = "IMP";
			OpcodeMatrix[0xCA].bytes = 1;
			OpcodeMatrix[0xCA].cycles = 2;
			OpcodeMatrix[0xCA].flags = "cZidbvN";

			OpcodeMatrix[0x88].mnemonic = "DEY";
			OpcodeMatrix[0x88].addressing = "IMP";
			OpcodeMatrix[0x88].bytes = 1;
			OpcodeMatrix[0x88].cycles = 2;
			OpcodeMatrix[0x88].flags = "cZidbvN";

			OpcodeMatrix[0xE8].mnemonic = "INX";
			OpcodeMatrix[0xE8].addressing = "IMP";
			OpcodeMatrix[0xE8].bytes = 1;
			OpcodeMatrix[0xE8].cycles = 2;
			OpcodeMatrix[0xE8].flags = "cZidbvN";

			OpcodeMatrix[0xC8].mnemonic = "INY";
			OpcodeMatrix[0xC8].addressing = "IMP";
			OpcodeMatrix[0xC8].bytes = 1;
			OpcodeMatrix[0xC8].cycles = 2;
			OpcodeMatrix[0xC8].flags = "cZidbvN";

			OpcodeMatrix[0x49].mnemonic = "EOR";
			OpcodeMatrix[0x49].addressing = "IMM";
			OpcodeMatrix[0x49].bytes = 2;
			OpcodeMatrix[0x49].cycles = 2;
			OpcodeMatrix[0x49].flags = "cZidbvN";

			OpcodeMatrix[0x45].mnemonic = "EOR";
			OpcodeMatrix[0x45].addressing = "ZP";
			OpcodeMatrix[0x45].bytes = 2;
			OpcodeMatrix[0x45].cycles = 3;
			OpcodeMatrix[0x45].flags = "cZidbvN";

			OpcodeMatrix[0x55].mnemonic = "EOR";
			OpcodeMatrix[0x55].addressing = "ZPX";
			OpcodeMatrix[0x55].bytes = 2;
			OpcodeMatrix[0x55].cycles = 4;
			OpcodeMatrix[0x55].flags = "cZidbvN";

			OpcodeMatrix[0x4D].mnemonic = "EOR";
			OpcodeMatrix[0x4D].addressing = "ABS";
			OpcodeMatrix[0x4D].bytes = 3;
			OpcodeMatrix[0x4D].cycles = 4;
			OpcodeMatrix[0x4D].flags = "cZidbvN";

			OpcodeMatrix[0x5D].mnemonic = "EOR";
			OpcodeMatrix[0x5D].addressing = "ABSX";
			OpcodeMatrix[0x5D].bytes = 3;
			OpcodeMatrix[0x5D].cycles = 4;
			OpcodeMatrix[0x5D].flags = "cZidbvN";

			OpcodeMatrix[0x59].mnemonic = "EOR";
			OpcodeMatrix[0x59].addressing = "ABSY";
			OpcodeMatrix[0x59].bytes = 3;
			OpcodeMatrix[0x59].cycles = 4;
			OpcodeMatrix[0x59].flags = "cZidbvN";

			OpcodeMatrix[0x41].mnemonic = "EOR";
			OpcodeMatrix[0x41].addressing = "INDX";
			OpcodeMatrix[0x41].bytes = 2;
			OpcodeMatrix[0x41].cycles = 6;
			OpcodeMatrix[0x41].flags = "cZidbvN";

			OpcodeMatrix[0x51].mnemonic = "EOR";
			OpcodeMatrix[0x51].addressing = "INDY";
			OpcodeMatrix[0x51].bytes = 2;
			OpcodeMatrix[0x51].cycles = 5;
			OpcodeMatrix[0x51].flags = "cZidbvN";

			OpcodeMatrix[0xE6].mnemonic = "INC";
			OpcodeMatrix[0xE6].addressing = "ZP";
			OpcodeMatrix[0xE6].bytes = 2;
			OpcodeMatrix[0xE6].cycles = 5;
			OpcodeMatrix[0xE6].flags = "cZidbvN";

			OpcodeMatrix[0xF6].mnemonic = "INC";
			OpcodeMatrix[0xF6].addressing = "ZPX";
			OpcodeMatrix[0xF6].bytes = 2;
			OpcodeMatrix[0xF6].cycles = 6;
			OpcodeMatrix[0xF6].flags = "cZidbvN";

			OpcodeMatrix[0xEE].mnemonic = "INC";
			OpcodeMatrix[0xEE].addressing = "ABS";
			OpcodeMatrix[0xEE].bytes = 3;
			OpcodeMatrix[0xEE].cycles = 6;
			OpcodeMatrix[0xEE].flags = "cZidbvN";

			OpcodeMatrix[0xFE].mnemonic = "INC";
			OpcodeMatrix[0xFE].addressing = "ABSX";
			OpcodeMatrix[0xFE].bytes = 3;
			OpcodeMatrix[0xFE].cycles = 7;
			OpcodeMatrix[0xFE].flags = "cZidbvN";

			OpcodeMatrix[0x4C].mnemonic = "JMP";
			OpcodeMatrix[0x4C].addressing = "ABS";
			OpcodeMatrix[0x4C].bytes = 3;
			OpcodeMatrix[0x4C].cycles = 3;
			OpcodeMatrix[0x4C].flags = "czidbvn";

			OpcodeMatrix[0x6C].mnemonic = "JMP";
			OpcodeMatrix[0x6C].addressing = "IND";
			OpcodeMatrix[0x6C].bytes = 3;
			OpcodeMatrix[0x6C].cycles = 5;
			OpcodeMatrix[0x6C].flags = "czidbvn";

			OpcodeMatrix[0x20].mnemonic = "JSR";
			OpcodeMatrix[0x20].addressing = "ABS";
			OpcodeMatrix[0x20].bytes = 3;
			OpcodeMatrix[0x20].cycles = 6;
			OpcodeMatrix[0x20].flags = "czidbvn";

			OpcodeMatrix[0xA9].mnemonic = "LDA";
			OpcodeMatrix[0xA9].addressing = "IMM";
			OpcodeMatrix[0xA9].bytes = 2;
			OpcodeMatrix[0xA9].cycles = 2;
			OpcodeMatrix[0xA9].flags = "cZidbvN";

			OpcodeMatrix[0xA5].mnemonic = "LDA";
			OpcodeMatrix[0xA5].addressing = "ZP";
			OpcodeMatrix[0xA5].bytes = 2;
			OpcodeMatrix[0xA5].cycles = 3;
			OpcodeMatrix[0xA5].flags = "cZidbvN";

			OpcodeMatrix[0xB5].mnemonic = "LDA";
			OpcodeMatrix[0xB5].addressing = "ZPX";
			OpcodeMatrix[0xB5].bytes = 2;
			OpcodeMatrix[0xB5].cycles = 4;
			OpcodeMatrix[0xB5].flags = "cZidbvN";

			OpcodeMatrix[0xAD].mnemonic = "LDA";
			OpcodeMatrix[0xAD].addressing = "ABS";
			OpcodeMatrix[0xAD].bytes = 3;
			OpcodeMatrix[0xAD].cycles = 4;
			OpcodeMatrix[0xAD].flags = "cZidbvN";

			OpcodeMatrix[0xBD].mnemonic = "LDA";
			OpcodeMatrix[0xBD].addressing = "ABSX";
			OpcodeMatrix[0xBD].bytes = 3;
			OpcodeMatrix[0xBD].cycles = 4;
			OpcodeMatrix[0xBD].flags = "cZidbvN";

			OpcodeMatrix[0xB9].mnemonic = "LDA";
			OpcodeMatrix[0xB9].addressing = "ABSY";
			OpcodeMatrix[0xB9].bytes = 3;
			OpcodeMatrix[0xB9].cycles = 4;
			OpcodeMatrix[0xB9].flags = "cZidbvN";

			OpcodeMatrix[0xA1].mnemonic = "LDA";
			OpcodeMatrix[0xA1].addressing = "INDX";
			OpcodeMatrix[0xA1].bytes = 2;
			OpcodeMatrix[0xA1].cycles = 6;
			OpcodeMatrix[0xA1].flags = "cZidbvN";

			OpcodeMatrix[0xB1].mnemonic = "LDA";
			OpcodeMatrix[0xB1].addressing = "INDY";
			OpcodeMatrix[0xB1].bytes = 2;
			OpcodeMatrix[0xB1].cycles = 5;
			OpcodeMatrix[0xB1].flags = "cZidbvN";

			OpcodeMatrix[0xA2].mnemonic = "LDX";
			OpcodeMatrix[0xA2].addressing = "IMM";
			OpcodeMatrix[0xA2].bytes = 2;
			OpcodeMatrix[0xA2].cycles = 2;
			OpcodeMatrix[0xA2].flags = "cZidbvN";

			OpcodeMatrix[0xA6].mnemonic = "LDX";
			OpcodeMatrix[0xA6].addressing = "ZP";
			OpcodeMatrix[0xA6].bytes = 2;
			OpcodeMatrix[0xA6].cycles = 3;
			OpcodeMatrix[0xA6].flags = "cZidbvN";

			OpcodeMatrix[0xB6].mnemonic = "LDX";
			OpcodeMatrix[0xB6].addressing = "ZPY";
			OpcodeMatrix[0xB6].bytes = 2;
			OpcodeMatrix[0xB6].cycles = 4;
			OpcodeMatrix[0xB6].flags = "cZidbvN";

			OpcodeMatrix[0xAE].mnemonic = "LDX";
			OpcodeMatrix[0xAE].addressing = "ABS";
			OpcodeMatrix[0xAE].bytes = 3;
			OpcodeMatrix[0xAE].cycles = 4;
			OpcodeMatrix[0xAE].flags = "cZidbvN";

			OpcodeMatrix[0xBE].mnemonic = "LDX";
			OpcodeMatrix[0xBE].addressing = "ABSY";
			OpcodeMatrix[0xBE].bytes = 3;
			OpcodeMatrix[0xBE].cycles = 4;
			OpcodeMatrix[0xBE].flags = "cZidbvN";

			OpcodeMatrix[0xA0].mnemonic = "LDY";
			OpcodeMatrix[0xA0].addressing = "IMM";
			OpcodeMatrix[0xA0].bytes = 2;
			OpcodeMatrix[0xA0].cycles = 2;
			OpcodeMatrix[0xA0].flags = "cZidbvN";

			OpcodeMatrix[0xA4].mnemonic = "LDY";
			OpcodeMatrix[0xA4].addressing = "ZP";
			OpcodeMatrix[0xA4].bytes = 2;
			OpcodeMatrix[0xA4].cycles = 3;
			OpcodeMatrix[0xA4].flags = "cZidbvN";

			OpcodeMatrix[0xB4].mnemonic = "LDY";
			OpcodeMatrix[0xB4].addressing = "ZPX";
			OpcodeMatrix[0xB4].bytes = 2;
			OpcodeMatrix[0xB4].cycles = 4;
			OpcodeMatrix[0xB4].flags = "cZidbvN";

			OpcodeMatrix[0xAC].mnemonic = "LDY";
			OpcodeMatrix[0xAC].addressing = "ABS";
			OpcodeMatrix[0xAC].bytes = 3;
			OpcodeMatrix[0xAC].cycles = 4;
			OpcodeMatrix[0xAC].flags = "cZidbvN";

			OpcodeMatrix[0xBC].mnemonic = "LDY";
			OpcodeMatrix[0xBC].addressing = "ABSX";
			OpcodeMatrix[0xBC].bytes = 3;
			OpcodeMatrix[0xBC].cycles = 4;
			OpcodeMatrix[0xBC].flags = "cZidbvN";

			OpcodeMatrix[0x4A].mnemonic = "LSR";
			OpcodeMatrix[0x4A].addressing = "ACC";
			OpcodeMatrix[0x4A].bytes = 1;
			OpcodeMatrix[0x4A].cycles = 2;
			OpcodeMatrix[0x4A].flags = "CZidbvN";

			OpcodeMatrix[0x46].mnemonic = "LSR";
			OpcodeMatrix[0x46].addressing = "ZP";
			OpcodeMatrix[0x46].bytes = 2;
			OpcodeMatrix[0x46].cycles = 5;
			OpcodeMatrix[0x46].flags = "CZidbvN";

			OpcodeMatrix[0x56].mnemonic = "LSR";
			OpcodeMatrix[0x56].addressing = "ZPX";
			OpcodeMatrix[0x56].bytes = 2;
			OpcodeMatrix[0x56].cycles = 6;
			OpcodeMatrix[0x56].flags = "CZidbvN";

			OpcodeMatrix[0x4E].mnemonic = "LSR";
			OpcodeMatrix[0x4E].addressing = "ABS";
			OpcodeMatrix[0x4E].bytes = 3;
			OpcodeMatrix[0x4E].cycles = 6;
			OpcodeMatrix[0x4E].flags = "CZidbvN";

			OpcodeMatrix[0x5E].mnemonic = "LSR";
			OpcodeMatrix[0x5E].addressing = "ABSX";
			OpcodeMatrix[0x5E].bytes = 3;
			OpcodeMatrix[0x5E].cycles = 7;
			OpcodeMatrix[0x5E].flags = "CZidbvN";

			OpcodeMatrix[0x09].mnemonic = "ORA";
			OpcodeMatrix[0x09].addressing = "IMM";
			OpcodeMatrix[0x09].bytes = 2;
			OpcodeMatrix[0x09].cycles = 2;
			OpcodeMatrix[0x09].flags = "cZidbvN";

			OpcodeMatrix[0x05].mnemonic = "ORA";
			OpcodeMatrix[0x05].addressing = "ZP";
			OpcodeMatrix[0x05].bytes = 2;
			OpcodeMatrix[0x05].cycles = 3;
			OpcodeMatrix[0x05].flags = "cZidbvN";

			OpcodeMatrix[0x15].mnemonic = "ORA";
			OpcodeMatrix[0x15].addressing = "ZPX";
			OpcodeMatrix[0x15].bytes = 2;
			OpcodeMatrix[0x15].cycles = 4;
			OpcodeMatrix[0x15].flags = "cZidbvN";

			OpcodeMatrix[0x0D].mnemonic = "ORA";
			OpcodeMatrix[0x0D].addressing = "ABS";
			OpcodeMatrix[0x0D].bytes = 3;
			OpcodeMatrix[0x0D].cycles = 4;
			OpcodeMatrix[0x0D].flags = "cZidbvN";

			OpcodeMatrix[0x1D].mnemonic = "ORA";
			OpcodeMatrix[0x1D].addressing = "ABSX";
			OpcodeMatrix[0x1D].bytes = 3;
			OpcodeMatrix[0x1D].cycles = 4;
			OpcodeMatrix[0x1D].flags = "cZidbvN";

			OpcodeMatrix[0x19].mnemonic = "ORA";
			OpcodeMatrix[0x19].addressing = "ABSY";
			OpcodeMatrix[0x19].bytes = 3;
			OpcodeMatrix[0x19].cycles = 4;
			OpcodeMatrix[0x19].flags = "cZidbvN";

			OpcodeMatrix[0x01].mnemonic = "ORA";
			OpcodeMatrix[0x01].addressing = "INDX";
			OpcodeMatrix[0x01].bytes = 2;
			OpcodeMatrix[0x01].cycles = 6;
			OpcodeMatrix[0x01].flags = "cZidbvN";

			OpcodeMatrix[0x11].mnemonic = "ORA";
			OpcodeMatrix[0x11].addressing = "INDY";
			OpcodeMatrix[0x11].bytes = 2;
			OpcodeMatrix[0x11].cycles = 5;
			OpcodeMatrix[0x11].flags = "cZidbvN";

			OpcodeMatrix[0x2A].mnemonic = "ROL";
			OpcodeMatrix[0x2A].addressing = "ACC";
			OpcodeMatrix[0x2A].bytes = 1;
			OpcodeMatrix[0x2A].cycles = 2;
			OpcodeMatrix[0x2A].flags = "CZidbvN";

			OpcodeMatrix[0x26].mnemonic = "ROL";
			OpcodeMatrix[0x26].addressing = "ZP";
			OpcodeMatrix[0x26].bytes = 2;
			OpcodeMatrix[0x26].cycles = 5;
			OpcodeMatrix[0x26].flags = "CZidbvN";

			OpcodeMatrix[0x36].mnemonic = "ROL";
			OpcodeMatrix[0x36].addressing = "ZPX";
			OpcodeMatrix[0x36].bytes = 2;
			OpcodeMatrix[0x36].cycles = 6;
			OpcodeMatrix[0x36].flags = "CZidbvN";

			OpcodeMatrix[0x2E].mnemonic = "ROL";
			OpcodeMatrix[0x2E].addressing = "ABS";
			OpcodeMatrix[0x2E].bytes = 3;
			OpcodeMatrix[0x2E].cycles = 6;
			OpcodeMatrix[0x2E].flags = "CZidbvN";

			OpcodeMatrix[0x3E].mnemonic = "ROL";
			OpcodeMatrix[0x3E].addressing = "ABSX";
			OpcodeMatrix[0x3E].bytes = 3;
			OpcodeMatrix[0x3E].cycles = 7;
			OpcodeMatrix[0x3E].flags = "CZidbvN";

			OpcodeMatrix[0x6A].mnemonic = "ROR";
			OpcodeMatrix[0x6A].addressing = "ACC";
			OpcodeMatrix[0x6A].bytes = 1;
			OpcodeMatrix[0x6A].cycles = 2;
			OpcodeMatrix[0x6A].flags = "CZidbvN";

			OpcodeMatrix[0x66].mnemonic = "ROR";
			OpcodeMatrix[0x66].addressing = "ZP";
			OpcodeMatrix[0x66].bytes = 2;
			OpcodeMatrix[0x66].cycles = 5;
			OpcodeMatrix[0x66].flags = "CZidbvN";

			OpcodeMatrix[0x76].mnemonic = "ROR";
			OpcodeMatrix[0x76].addressing = "ZPX";
			OpcodeMatrix[0x76].bytes = 2;
			OpcodeMatrix[0x76].cycles = 6;
			OpcodeMatrix[0x76].flags = "CZidbvN";

			OpcodeMatrix[0x6E].mnemonic = "ROR";
			OpcodeMatrix[0x6E].addressing = "ABS";
			OpcodeMatrix[0x6E].bytes = 3;
			OpcodeMatrix[0x6E].cycles = 6;
			OpcodeMatrix[0x6E].flags = "CZidbvN";

			OpcodeMatrix[0x7E].mnemonic = "ROR";
			OpcodeMatrix[0x7E].addressing = "ABSX";
			OpcodeMatrix[0x7E].bytes = 3;
			OpcodeMatrix[0x7E].cycles = 7;
			OpcodeMatrix[0x7E].flags = "CZidbvN";

			OpcodeMatrix[0xE9].mnemonic = "SBC";
			OpcodeMatrix[0xE9].addressing = "IMM";
			OpcodeMatrix[0xE9].bytes = 2;
			OpcodeMatrix[0xE9].cycles = 2;
			OpcodeMatrix[0xE9].flags = "CZidbVN";

			OpcodeMatrix[0xE5].mnemonic = "SBC";
			OpcodeMatrix[0xE5].addressing = "ZP";
			OpcodeMatrix[0xE5].bytes = 2;
			OpcodeMatrix[0xE5].cycles = 3;
			OpcodeMatrix[0xE5].flags = "CZidbVN";

			OpcodeMatrix[0xF5].mnemonic = "SBC";
			OpcodeMatrix[0xF5].addressing = "ZPX";
			OpcodeMatrix[0xF5].bytes = 2;
			OpcodeMatrix[0xF5].cycles = 4;
			OpcodeMatrix[0xF5].flags = "CZidbVN";

			OpcodeMatrix[0xED].mnemonic = "SBC";
			OpcodeMatrix[0xED].addressing = "ABS";
			OpcodeMatrix[0xED].bytes = 3;
			OpcodeMatrix[0xED].cycles = 4;
			OpcodeMatrix[0xED].flags = "CZidbVN";

			OpcodeMatrix[0xFD].mnemonic = "SBC";
			OpcodeMatrix[0xFD].addressing = "ABSX";
			OpcodeMatrix[0xFD].bytes = 3;
			OpcodeMatrix[0xFD].cycles = 4;
			OpcodeMatrix[0xFD].flags = "CZidbVN";

			OpcodeMatrix[0xF9].mnemonic = "SBC";
			OpcodeMatrix[0xF9].addressing = "ABSY";
			OpcodeMatrix[0xF9].bytes = 3;
			OpcodeMatrix[0xF9].cycles = 4;
			OpcodeMatrix[0xF9].flags = "CZidbVN";

			OpcodeMatrix[0xE1].mnemonic = "SBC";
			OpcodeMatrix[0xE1].addressing = "INDX";
			OpcodeMatrix[0xE1].bytes = 2;
			OpcodeMatrix[0xE1].cycles = 6;
			OpcodeMatrix[0xE1].flags = "CZidbVN";

			OpcodeMatrix[0xF1].mnemonic = "SBC";
			OpcodeMatrix[0xF1].addressing = "INDY";
			OpcodeMatrix[0xF1].bytes = 2;
			OpcodeMatrix[0xF1].cycles = 5;
			OpcodeMatrix[0xF1].flags = "CZidbVN";

			OpcodeMatrix[0x85].mnemonic = "STA";
			OpcodeMatrix[0x85].addressing = "ZP";
			OpcodeMatrix[0x85].bytes = 2;
			OpcodeMatrix[0x85].cycles = 3;
			OpcodeMatrix[0x85].flags = "czidbvn";

			OpcodeMatrix[0x95].mnemonic = "STA";
			OpcodeMatrix[0x95].addressing = "ZPX";
			OpcodeMatrix[0x95].bytes = 2;
			OpcodeMatrix[0x95].cycles = 4;
			OpcodeMatrix[0x95].flags = "czidbvn";

			OpcodeMatrix[0x8D].mnemonic = "STA";
			OpcodeMatrix[0x8D].addressing = "ABS";
			OpcodeMatrix[0x8D].bytes = 3;
			OpcodeMatrix[0x8D].cycles = 4;
			OpcodeMatrix[0x8D].flags = "czidbvn";

			OpcodeMatrix[0x9D].mnemonic = "STA";
			OpcodeMatrix[0x9D].addressing = "ABSX";
			OpcodeMatrix[0x9D].bytes = 3;
			OpcodeMatrix[0x9D].cycles = 5;
			OpcodeMatrix[0x9D].flags = "czidbvn";

			OpcodeMatrix[0x99].mnemonic = "STA";
			OpcodeMatrix[0x99].addressing = "ABSY";
			OpcodeMatrix[0x99].bytes = 3;
			OpcodeMatrix[0x99].cycles = 5;
			OpcodeMatrix[0x99].flags = "czidbvn";

			OpcodeMatrix[0x81].mnemonic = "STA";
			OpcodeMatrix[0x81].addressing = "INDX";
			OpcodeMatrix[0x81].bytes = 2;
			OpcodeMatrix[0x81].cycles = 6;
			OpcodeMatrix[0x81].flags = "czidbvn";

			OpcodeMatrix[0x91].mnemonic = "STA";
			OpcodeMatrix[0x91].addressing = "INDY";
			OpcodeMatrix[0x91].bytes = 2;
			OpcodeMatrix[0x91].cycles = 6;
			OpcodeMatrix[0x91].flags = "czidbvn";

			OpcodeMatrix[0x86].mnemonic = "STX";
			OpcodeMatrix[0x86].addressing = "ZP";
			OpcodeMatrix[0x86].bytes = 2;
			OpcodeMatrix[0x86].cycles = 3;
			OpcodeMatrix[0x86].flags = "czidbvn";

			OpcodeMatrix[0x96].mnemonic = "STX";
			OpcodeMatrix[0x96].addressing = "ZPY";
			OpcodeMatrix[0x96].bytes = 2;
			OpcodeMatrix[0x96].cycles = 4;
			OpcodeMatrix[0x96].flags = "czidbvn";

			OpcodeMatrix[0x8E].mnemonic = "STX";
			OpcodeMatrix[0x8E].addressing = "ABS";
			OpcodeMatrix[0x8E].bytes = 3;
			OpcodeMatrix[0x8E].cycles = 4;
			OpcodeMatrix[0x8E].flags = "czidbvn";

			OpcodeMatrix[0x84].mnemonic = "STY";
			OpcodeMatrix[0x84].addressing = "ZP";
			OpcodeMatrix[0x84].bytes = 2;
			OpcodeMatrix[0x84].cycles = 3;
			OpcodeMatrix[0x84].flags = "czidbvn";

			OpcodeMatrix[0x94].mnemonic = "STY";
			OpcodeMatrix[0x94].addressing = "ZPX";
			OpcodeMatrix[0x94].bytes = 2;
			OpcodeMatrix[0x94].cycles = 4;
			OpcodeMatrix[0x94].flags = "czidbvn";

			OpcodeMatrix[0x8C].mnemonic = "STY";
			OpcodeMatrix[0x8C].addressing = "ABS";
			OpcodeMatrix[0x8C].bytes = 3;
			OpcodeMatrix[0x8C].cycles = 4;
			OpcodeMatrix[0x8C].flags = "czidbvn";

			//Undocumented Instructions

			UndocMatrix[0x80].mnemonic = "NOP";
			UndocMatrix[0x80].addressing = "IMM";
			UndocMatrix[0x80].bytes = 2;
			UndocMatrix[0x80].cycles = 2;

			UndocMatrix[0x1A].mnemonic = "NOP";
			UndocMatrix[0x1A].addressing = "IMP";
			UndocMatrix[0x1A].bytes = 1;
			UndocMatrix[0x1A].cycles = 2;

			UndocMatrix[0x3A].mnemonic = "NOP";
			UndocMatrix[0x3A].addressing = "IMP";
			UndocMatrix[0x3A].bytes = 1;
			UndocMatrix[0x3A].cycles = 2;

			UndocMatrix[0x5A].mnemonic = "NOP";
			UndocMatrix[0x5A].addressing = "IMP";
			UndocMatrix[0x5A].bytes = 1;
			UndocMatrix[0x5A].cycles = 2;

			UndocMatrix[0x7A].mnemonic = "NOP";
			UndocMatrix[0x7A].addressing = "IMP";
			UndocMatrix[0x7A].bytes = 1;
			UndocMatrix[0x7A].cycles = 2;

			UndocMatrix[0xDA].mnemonic = "NOP";
			UndocMatrix[0xDA].addressing = "IMP";
			UndocMatrix[0xDA].bytes = 1;
			UndocMatrix[0xDA].cycles = 2;

			UndocMatrix[0xFA].mnemonic = "NOP";
			UndocMatrix[0xFA].addressing = "IMP";
			UndocMatrix[0xFA].bytes = 1;
			UndocMatrix[0xFA].cycles = 2;

			UndocMatrix[0x82].mnemonic = "NOP";
			UndocMatrix[0x82].addressing = "IMM";
			UndocMatrix[0x82].bytes = 2;
			UndocMatrix[0x82].cycles = 2;

			UndocMatrix[0x89].mnemonic = "NOP";
			UndocMatrix[0x89].addressing = "IMM";
			UndocMatrix[0x89].bytes = 2;
			UndocMatrix[0x89].cycles = 2;

			UndocMatrix[0xC2].mnemonic = "NOP";
			UndocMatrix[0xC2].addressing = "IMM";
			UndocMatrix[0xC2].bytes = 2;
			UndocMatrix[0xC2].cycles = 2;

			UndocMatrix[0xE2].mnemonic = "NOP";
			UndocMatrix[0xE2].addressing = "IMM";
			UndocMatrix[0xE2].bytes = 2;
			UndocMatrix[0xE2].cycles = 2;

			UndocMatrix[0x04].mnemonic = "NOP";
			UndocMatrix[0x04].addressing = "ZP";
			UndocMatrix[0x04].bytes = 2;
			UndocMatrix[0x04].cycles = 3;

			UndocMatrix[0x44].mnemonic = "NOP";
			UndocMatrix[0x44].addressing = "ZP";
			UndocMatrix[0x44].bytes = 2;
			UndocMatrix[0x44].cycles = 3;

			UndocMatrix[0x64].mnemonic = "NOP";
			UndocMatrix[0x64].addressing = "ZP";
			UndocMatrix[0x64].bytes = 2;
			UndocMatrix[0x64].cycles = 3;

			UndocMatrix[0x14].mnemonic = "NOP";
			UndocMatrix[0x14].addressing = "ZPX";
			UndocMatrix[0x14].bytes = 2;
			UndocMatrix[0x14].cycles = 4;

			UndocMatrix[0x34].mnemonic = "NOP";
			UndocMatrix[0x34].addressing = "ZPX";
			UndocMatrix[0x34].bytes = 2;
			UndocMatrix[0x34].cycles = 4;

			UndocMatrix[0x54].mnemonic = "NOP";
			UndocMatrix[0x54].addressing = "ZPX";
			UndocMatrix[0x54].bytes = 2;
			UndocMatrix[0x54].cycles = 4;

			UndocMatrix[0x74].mnemonic = "NOP";
			UndocMatrix[0x74].addressing = "ZPX";
			UndocMatrix[0x74].bytes = 2;
			UndocMatrix[0x74].cycles = 4;

			UndocMatrix[0xD4].mnemonic = "NOP";
			UndocMatrix[0xD4].addressing = "ZPX";
			UndocMatrix[0xD4].bytes = 2;
			UndocMatrix[0xD4].cycles = 4;

			UndocMatrix[0xF4].mnemonic = "NOP";
			UndocMatrix[0xF4].addressing = "ZPX";
			UndocMatrix[0xF4].bytes = 2;
			UndocMatrix[0xF4].cycles = 4;

			UndocMatrix[0x0C].mnemonic = "NOP";
			UndocMatrix[0x0C].addressing = "ABS";
			UndocMatrix[0x0C].bytes = 3;
			UndocMatrix[0x0C].cycles = 4;

			UndocMatrix[0x1C].mnemonic = "NOP";
			UndocMatrix[0x1C].addressing = "ABSX";
			UndocMatrix[0x1C].bytes = 3;
			UndocMatrix[0x1C].cycles = 4;

			UndocMatrix[0x3C].mnemonic = "NOP";
			UndocMatrix[0x3C].addressing = "ABSX";
			UndocMatrix[0x3C].bytes = 3;
			UndocMatrix[0x3C].cycles = 4;

			UndocMatrix[0x5C].mnemonic = "NOP";
			UndocMatrix[0x5C].addressing = "ABSX";
			UndocMatrix[0x5C].bytes = 3;
			UndocMatrix[0x5C].cycles = 4;

			UndocMatrix[0x7C].mnemonic = "NOP";
			UndocMatrix[0x7C].addressing = "ABSX";
			UndocMatrix[0x7C].bytes = 3;
			UndocMatrix[0x7C].cycles = 4;

			UndocMatrix[0xDC].mnemonic = "NOP";
			UndocMatrix[0xDC].addressing = "ABSX";
			UndocMatrix[0xDC].bytes = 3;
			UndocMatrix[0xDC].cycles = 4;

			UndocMatrix[0xFC].mnemonic = "NOP";
			UndocMatrix[0xFC].addressing = "ABSX";
			UndocMatrix[0xFC].bytes = 3;
			UndocMatrix[0xFC].cycles = 4;

			UndocMatrix[0x48].mnemonic = "ALR";
			UndocMatrix[0x48].addressing = "IMM";
			UndocMatrix[0x48].bytes = 2;
			UndocMatrix[0x48].cycles = 2;

			UndocMatrix[0x0B].mnemonic = "ANC";
			UndocMatrix[0x0B].addressing = "IMM";
			UndocMatrix[0x0B].bytes = 2;
			UndocMatrix[0x0B].cycles = 2;

			UndocMatrix[0x2B].mnemonic = "ANC2";
			UndocMatrix[0x2B].addressing = "IMM";
			UndocMatrix[0x2B].bytes = 2;
			UndocMatrix[0x2B].cycles = 2;

			UndocMatrix[0x8B].mnemonic = "ANE";
			UndocMatrix[0x8B].addressing = "IMM";
			UndocMatrix[0x8B].bytes = 2;
			UndocMatrix[0x8B].cycles = 2;

			UndocMatrix[0x6B].mnemonic = "ARR";
			UndocMatrix[0x6B].addressing = "IMM";
			UndocMatrix[0x6B].bytes = 2;
			UndocMatrix[0x6B].cycles = 2;

			UndocMatrix[0xC7].mnemonic = "DCP";
			UndocMatrix[0xC7].addressing = "ZP";
			UndocMatrix[0xC7].bytes = 2;
			UndocMatrix[0xC7].cycles = 5;

			UndocMatrix[0xD7].mnemonic = "DCP";
			UndocMatrix[0xD7].addressing = "ZPX";
			UndocMatrix[0xD7].bytes = 2;
			UndocMatrix[0xD7].cycles = 6;

			UndocMatrix[0xCF].mnemonic = "DCP";
			UndocMatrix[0xCF].addressing = "ABS";
			UndocMatrix[0xCF].bytes = 3;
			UndocMatrix[0xCF].cycles = 6;

			UndocMatrix[0xDF].mnemonic = "DCP";
			UndocMatrix[0xDF].addressing = "ABSX";
			UndocMatrix[0xDF].bytes = 3;
			UndocMatrix[0xDF].cycles = 7;

			UndocMatrix[0xD8].mnemonic = "DCP";
			UndocMatrix[0xD8].addressing = "ABSY";
			UndocMatrix[0xD8].bytes = 3;
			UndocMatrix[0xD8].cycles = 7;

			UndocMatrix[0xC3].mnemonic = "DCP";
			UndocMatrix[0xC3].addressing = "INDX";
			UndocMatrix[0xC3].bytes = 2;
			UndocMatrix[0xC3].cycles = 8;

			UndocMatrix[0xD3].mnemonic = "DCP";
			UndocMatrix[0xD3].addressing = "INDY";
			UndocMatrix[0xD3].bytes = 2;
			UndocMatrix[0xD3].cycles = 8;

			UndocMatrix[0xE7].mnemonic = "ISC";
			UndocMatrix[0xE7].addressing = "ZP";
			UndocMatrix[0xE7].bytes = 2;
			UndocMatrix[0xE7].cycles = 5;

			UndocMatrix[0xF7].mnemonic = "ISC";
			UndocMatrix[0xF7].addressing = "ZPX";
			UndocMatrix[0xF7].bytes = 2;
			UndocMatrix[0xF7].cycles = 6;

			UndocMatrix[0xEF].mnemonic = "ISC";
			UndocMatrix[0xEF].addressing = "ABS";
			UndocMatrix[0xEF].bytes = 3;
			UndocMatrix[0xEF].cycles = 6;

			UndocMatrix[0xFF].mnemonic = "ISC";
			UndocMatrix[0xFF].addressing = "ABSX";
			UndocMatrix[0xFF].bytes = 3;
			UndocMatrix[0xFF].cycles = 7;

			UndocMatrix[0xFB].mnemonic = "ISC";
			UndocMatrix[0xFB].addressing = "ABSY";
			UndocMatrix[0xFB].bytes = 3;
			UndocMatrix[0xFB].cycles = 7;

			UndocMatrix[0xE3].mnemonic = "ISC";
			UndocMatrix[0xE3].addressing = "INDX";
			UndocMatrix[0xE3].bytes = 2;
			UndocMatrix[0xE3].cycles = 8;

			UndocMatrix[0xF3].mnemonic = "ISC";
			UndocMatrix[0xF3].addressing = "INDY";
			UndocMatrix[0xF3].bytes = 2;
			UndocMatrix[0xF3].cycles = 8;

			UndocMatrix[0xBB].mnemonic = "LAS";
			UndocMatrix[0xBB].addressing = "ABSY";
			UndocMatrix[0xBB].bytes = 3;
			UndocMatrix[0xBB].cycles = 4;

			UndocMatrix[0xA7].mnemonic = "LAX";
			UndocMatrix[0xA7].addressing = "ZP";
			UndocMatrix[0xA7].bytes = 2;
			UndocMatrix[0xA7].cycles = 3;

			UndocMatrix[0xB7].mnemonic = "LAX";
			UndocMatrix[0xB7].addressing = "ZPY";
			UndocMatrix[0xB7].bytes = 2;
			UndocMatrix[0xB7].cycles = 4;

			UndocMatrix[0xAF].mnemonic = "LAX";
			UndocMatrix[0xAF].addressing = "ABS";
			UndocMatrix[0xAF].bytes = 3;
			UndocMatrix[0xAF].cycles = 4;

			UndocMatrix[0xBF].mnemonic = "LAX";
			UndocMatrix[0xBF].addressing = "ABSY";
			UndocMatrix[0xBF].bytes = 3;
			UndocMatrix[0xBF].cycles = 4;

			UndocMatrix[0xA3].mnemonic = "LAX";
			UndocMatrix[0xA3].addressing = "INDX";
			UndocMatrix[0xA3].bytes = 2;
			UndocMatrix[0xA3].cycles = 6;

			UndocMatrix[0xB3].mnemonic = "LAX";
			UndocMatrix[0xB3].addressing = "INDY";
			UndocMatrix[0xB3].bytes = 2;
			UndocMatrix[0xB3].cycles = 5;

			UndocMatrix[0xAB].mnemonic = "LXA";
			UndocMatrix[0xAB].addressing = "IMM";
			UndocMatrix[0xAB].bytes = 2;
			UndocMatrix[0xAB].cycles = 2;

			UndocMatrix[0x27].mnemonic = "RLA";
			UndocMatrix[0x27].addressing = "ZP";
			UndocMatrix[0x27].bytes = 2;
			UndocMatrix[0x27].cycles = 5;

			UndocMatrix[0x37].mnemonic = "RLA";
			UndocMatrix[0x37].addressing = "ZPX";
			UndocMatrix[0x37].bytes = 2;
			UndocMatrix[0x37].cycles = 6;

			UndocMatrix[0x2F].mnemonic = "RLA";
			UndocMatrix[0x2F].addressing = "ABS";
			UndocMatrix[0x2F].bytes = 3;
			UndocMatrix[0x2F].cycles = 6;

			UndocMatrix[0x3F].mnemonic = "RLA";
			UndocMatrix[0x3F].addressing = "ABSX";
			UndocMatrix[0x3F].bytes = 3;
			UndocMatrix[0x3F].cycles = 7;

			UndocMatrix[0x3B].mnemonic = "RLA";
			UndocMatrix[0x3B].addressing = "ABSY";
			UndocMatrix[0x3B].bytes = 3;
			UndocMatrix[0x3B].cycles = 7;

			UndocMatrix[0x23].mnemonic = "RLA";
			UndocMatrix[0x23].addressing = "INDX";
			UndocMatrix[0x23].bytes = 2;
			UndocMatrix[0x23].cycles = 8;

			UndocMatrix[0x33].mnemonic = "RLA";
			UndocMatrix[0x33].addressing = "INDY";
			UndocMatrix[0x33].bytes = 2;
			UndocMatrix[0x33].cycles = 8;

			UndocMatrix[0x67].mnemonic = "RRA";
			UndocMatrix[0x67].addressing = "ZP";
			UndocMatrix[0x67].bytes = 2;
			UndocMatrix[0x67].cycles = 5;

			UndocMatrix[0x77].mnemonic = "RRA";
			UndocMatrix[0x77].addressing = "ZPX";
			UndocMatrix[0x77].bytes = 2;
			UndocMatrix[0x77].cycles = 6;

			UndocMatrix[0x6F].mnemonic = "RRA";
			UndocMatrix[0x6F].addressing = "ABS";
			UndocMatrix[0x6F].bytes = 3;
			UndocMatrix[0x6F].cycles = 6;

			UndocMatrix[0x7F].mnemonic = "RRA";
			UndocMatrix[0x7F].addressing = "ABSX";
			UndocMatrix[0x7F].bytes = 3;
			UndocMatrix[0x7F].cycles = 7;

			UndocMatrix[0x7B].mnemonic = "RRA";
			UndocMatrix[0x7B].addressing = "ABSY";
			UndocMatrix[0x7B].bytes = 3;
			UndocMatrix[0x7B].cycles = 7;

			UndocMatrix[0x63].mnemonic = "RRA";
			UndocMatrix[0x63].addressing = "INDX";
			UndocMatrix[0x63].bytes = 2;
			UndocMatrix[0x63].cycles = 8;

			UndocMatrix[0x73].mnemonic = "RRA";
			UndocMatrix[0x73].addressing = "INDY";
			UndocMatrix[0x73].bytes = 2;
			UndocMatrix[0x73].cycles = 8;

			UndocMatrix[0x87].mnemonic = "SAX";
			UndocMatrix[0x87].addressing = "ZP";
			UndocMatrix[0x87].bytes = 2;
			UndocMatrix[0x87].cycles = 3;

			UndocMatrix[0x97].mnemonic = "SAX";
			UndocMatrix[0x97].addressing = "ZPY";
			UndocMatrix[0x97].bytes = 2;
			UndocMatrix[0x97].cycles = 4;

			UndocMatrix[0x8F].mnemonic = "SAX";
			UndocMatrix[0x8F].addressing = "ABS";
			UndocMatrix[0x8F].bytes = 3;
			UndocMatrix[0x8F].cycles = 4;

			UndocMatrix[0x83].mnemonic = "SAX";
			UndocMatrix[0x83].addressing = "INDX";
			UndocMatrix[0x83].bytes = 2;
			UndocMatrix[0x83].cycles = 6;

			UndocMatrix[0xCB].mnemonic = "SBX";
			UndocMatrix[0xCB].addressing = "IMM";
			UndocMatrix[0xCB].bytes = 2;
			UndocMatrix[0xCB].cycles = 2;

			UndocMatrix[0x9F].mnemonic = "SHA";
			UndocMatrix[0x9F].addressing = "ABSY";
			UndocMatrix[0x9F].bytes = 3;
			UndocMatrix[0x9F].cycles = 5;

			UndocMatrix[0x93].mnemonic = "SHA";
			UndocMatrix[0x93].addressing = "INDY";
			UndocMatrix[0x93].bytes = 2;
			UndocMatrix[0x93].cycles = 6;

			UndocMatrix[0x9E].mnemonic = "SHX";
			UndocMatrix[0x9E].addressing = "ABSY";
			UndocMatrix[0x9E].bytes = 3;
			UndocMatrix[0x9E].cycles = 5;

			UndocMatrix[0x9C].mnemonic = "SHY";
			UndocMatrix[0x9C].addressing = "ABSX";
			UndocMatrix[0x9C].bytes = 3;
			UndocMatrix[0x9C].cycles = 5;

			UndocMatrix[0x07].mnemonic = "SLO";
			UndocMatrix[0x07].addressing = "ZP";
			UndocMatrix[0x07].bytes = 2;
			UndocMatrix[0x07].cycles = 5;

			UndocMatrix[0x17].mnemonic = "SLO";
			UndocMatrix[0x17].addressing = "ZPX";
			UndocMatrix[0x17].bytes = 2;
			UndocMatrix[0x17].cycles = 6;

			UndocMatrix[0x0F].mnemonic = "SLO";
			UndocMatrix[0x0F].addressing = "ABS";
			UndocMatrix[0x0F].bytes = 3;
			UndocMatrix[0x0F].cycles = 6;

			UndocMatrix[0x1F].mnemonic = "SLO";
			UndocMatrix[0x1F].addressing = "ABSX";
			UndocMatrix[0x1F].bytes = 3;
			UndocMatrix[0x1F].cycles = 7;

			UndocMatrix[0x1B].mnemonic = "SLO";
			UndocMatrix[0x1B].addressing = "ABSY";
			UndocMatrix[0x1B].bytes = 3;
			UndocMatrix[0x1B].cycles = 7;

			UndocMatrix[0x03].mnemonic = "SLO";
			UndocMatrix[0x03].addressing = "INDX";
			UndocMatrix[0x03].bytes = 2;
			UndocMatrix[0x03].cycles = 8;

			UndocMatrix[0x13].mnemonic = "SLO";
			UndocMatrix[0x13].addressing = "INDY";
			UndocMatrix[0x13].bytes = 2;
			UndocMatrix[0x13].cycles = 8;

			UndocMatrix[0x47].mnemonic = "SRE";
			UndocMatrix[0x47].addressing = "ZP";
			UndocMatrix[0x47].bytes = 2;
			UndocMatrix[0x47].cycles = 5;

			UndocMatrix[0x57].mnemonic = "SRE";
			UndocMatrix[0x57].addressing = "ZPX";
			UndocMatrix[0x57].bytes = 2;
			UndocMatrix[0x57].cycles = 6;

			UndocMatrix[0x4F].mnemonic = "SRE";
			UndocMatrix[0x4F].addressing = "ABS";
			UndocMatrix[0x4F].bytes = 3;
			UndocMatrix[0x4F].cycles = 6;

			UndocMatrix[0x5F].mnemonic = "SRE";
			UndocMatrix[0x5F].addressing = "ABSX";
			UndocMatrix[0x5F].bytes = 3;
			UndocMatrix[0x5F].cycles = 7;

			UndocMatrix[0x5B].mnemonic = "SRE";
			UndocMatrix[0x5B].addressing = "ABSY";
			UndocMatrix[0x5B].bytes = 3;
			UndocMatrix[0x5B].cycles = 7;

			UndocMatrix[0x43].mnemonic = "SRE";
			UndocMatrix[0x43].addressing = "INDX";
			UndocMatrix[0x43].bytes = 2;
			UndocMatrix[0x43].cycles = 8;

			UndocMatrix[0x53].mnemonic = "SRE";
			UndocMatrix[0x53].addressing = "INDY";
			UndocMatrix[0x53].bytes = 2;
			UndocMatrix[0x53].cycles = 8;

			UndocMatrix[0x9B].mnemonic = "TAS";
			UndocMatrix[0x9B].addressing = "ABSY";
			UndocMatrix[0x9B].bytes = 3;
			UndocMatrix[0x9B].cycles = 5;

			UndocMatrix[0xEB].mnemonic = "USBC";
			UndocMatrix[0xEB].addressing = "IMM";
			UndocMatrix[0xEB].bytes = 2;
			UndocMatrix[0xEB].cycles = 2;

			UndocMatrix[0x02].mnemonic = "HLT";
			UndocMatrix[0x02].addressing = "IMM";
			UndocMatrix[0x02].bytes = 1;
			UndocMatrix[0x02].cycles = 1;

			UndocMatrix[0x12].mnemonic = "HLT";
			UndocMatrix[0x12].addressing = "IMM";
			UndocMatrix[0x12].bytes = 1;
			UndocMatrix[0x12].cycles = 1;

			UndocMatrix[0x22].mnemonic = "HLT";
			UndocMatrix[0x22].addressing = "IMM";
			UndocMatrix[0x22].bytes = 1;
			UndocMatrix[0x22].cycles = 1;

			UndocMatrix[0x32].mnemonic = "HLT";
			UndocMatrix[0x32].addressing = "IMM";
			UndocMatrix[0x32].bytes = 1;
			UndocMatrix[0x32].cycles = 1;

			UndocMatrix[0x42].mnemonic = "HLT";
			UndocMatrix[0x42].addressing = "IMM";
			UndocMatrix[0x42].bytes = 1;
			UndocMatrix[0x42].cycles = 1;

			UndocMatrix[0x52].mnemonic = "HLT";
			UndocMatrix[0x52].addressing = "IMM";
			UndocMatrix[0x52].bytes = 1;
			UndocMatrix[0x52].cycles = 1;

			UndocMatrix[0x62].mnemonic = "HLT";
			UndocMatrix[0x62].addressing = "IMM";
			UndocMatrix[0x62].bytes = 1;
			UndocMatrix[0x62].cycles = 1;

			UndocMatrix[0x72].mnemonic = "HLT";
			UndocMatrix[0x72].addressing = "IMM";
			UndocMatrix[0x72].bytes = 1;
			UndocMatrix[0x72].cycles = 1;

			UndocMatrix[0x92].mnemonic = "HLT";
			UndocMatrix[0x92].addressing = "IMM";
			UndocMatrix[0x92].bytes = 1;
			UndocMatrix[0x92].cycles = 1;

			UndocMatrix[0xB2].mnemonic = "HLT";
			UndocMatrix[0xB2].addressing = "IMM";
			UndocMatrix[0xB2].bytes = 1;
			UndocMatrix[0xB2].cycles = 1;

			UndocMatrix[0xD2].mnemonic = "HLT";
			UndocMatrix[0xD2].addressing = "IMM";
			UndocMatrix[0xD2].bytes = 1;
			UndocMatrix[0xD2].cycles = 1;

			UndocMatrix[0xF2].mnemonic = "HLT";
			UndocMatrix[0xF2].addressing = "IMM";
			UndocMatrix[0xF2].bytes = 1;
			UndocMatrix[0xF2].cycles = 1;


			}


		string OpcodeLookup::Mnemonic(int Opcode, bool Undoc)
			{
			if (Opcode == 0x0) //Weird VS bug returning string from idx 0. *shrug*
				return "BRK";
			else if (OpcodeMatrix[Opcode].mnemonic == "ILL" && Undoc == true)
				{
				return UndocMatrix[Opcode].mnemonic;
				}
			else
				return OpcodeMatrix[Opcode].mnemonic;
			}

		string OpcodeLookup::Addressing(int Opcode, bool Undoc)
			{
			if (Opcode == 0x0)
				return "IMP";
			else if (OpcodeMatrix[Opcode].mnemonic == "ILL" && Undoc == true)
				{
				return UndocMatrix[Opcode].addressing;
				}
			else
				return OpcodeMatrix[Opcode].addressing;
			}

		int OpcodeLookup::Bytes(int Opcode, bool Undoc)
			{
			if (Opcode == 0x0)
				return 2;
			else if (OpcodeMatrix[Opcode].mnemonic == "ILL" && Undoc == true)
				{
				return UndocMatrix[Opcode].bytes;
				}
			else
				return OpcodeMatrix[Opcode].bytes;
			}

		int OpcodeLookup::Cycles(int Opcode, bool Undoc)
			{
			if (Opcode == 0x0)
				return 7;
			else if (OpcodeMatrix[Opcode].mnemonic == "ILL" && Undoc == true)
				{
				return UndocMatrix[Opcode].cycles;
				}
			else
				return OpcodeMatrix[Opcode].cycles;
			}
