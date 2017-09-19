#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <algorithm>
#include <unordered_map>
#include<fstream>
#define RAM_MAXSIZE 1001000
using namespace std;

////Define Area////
ifstream fin;
class Ram;
class operand;
class instruction;
class REGI;
void HASH_INITIALIZE();
void operate(instruction & INS, int & nowline);
void EX_SYSCALL(int k);
int REG_INT(string tmp);
void Build_Inst();
string Input_Temp;
int line = 0;
int sequence[25000100];
int seqpos = 0;
bool exited = false;

std::unordered_map<string, int> ADDR_HASH;
std::unordered_map<string, int> LABEL_HASH;
std::unordered_map<string, int> INST_HASH;
std::unordered_map<string, int> REG_HASH;

////Text Area////

enum INST_TYPE
{
	DATA, ALIGN, ASCII, ASCIIZ, BYTE, HALF, SPACE, WORD, TEXT,
	ADD, ADDU, DIV, MUL, NEG, REM, SUB, SUBU, XOR,
	LI,
	SEQ, SGE, SGT, SLE, SLT, SNE,
	B, BEQ, BEQZ, BGE, BGEZ, BGT, BGTZ, BLE, BLEZ, BLT, BLTZ, BNE, BNEZ,
	J, JAL, JALR, JR,
	LA, LB, LW, SB, SW,
	MOVE, MFHI, MFLO, NOP, SYSCALL,
	LABEL,
	EMPTY
};
string INSTLIB[] =
{
	".data", ".align", ".ascii", ".asciiz", ".byte", ".half", ".space", ".word", ".text",
	"add", "addu", "div", "mul", "neg", "rem", "sub", "subu", "xor",
	"li",
	"seq", "sge", "sgt", "sle", "slt", "sne",
	"b", "beq", "beqz", "bge", "bgez", "bgt", "bgtz", "ble", "blez", "blt", "bltz", "bne", "bnez",
	"j", "jal", "jalr", "jr",
	"la", "lb", "lw", "sb", "sw",
	"move", "mfhi", "mflo", "nop", "syscall",
	"LABEL",
	"EMPTY"
};
enum REG_TYPE
{
	Zero, at, v0, v1, a0, a1, a2, a3,
	t0, t1, t2, t3, t4, t5, t6, t7,
	s0, s1, s2, s3, s4, s5, s6, s7,
	t8, t9,
	k0, k1,
	gp, sp, s8, fp,
	ra
};
string REGLIB[] =
{
	"zero", "at", "v0", "v1", "a0", "a1","a2", "a3",
	"t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
	"s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
	"t8",  "t9",
	"k0",  "k1",
	"gp",  "sp",  "s8",  "fp",
	"ra",
	"0","1", "2", "3", "4", "5", "6", "7", "8", "9", "10",
	"11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
	"21", "22", "23", "24", "25", "26", "27", "28", "29", "30",
	"31"
};
enum OPD_TYPE { REGISTER, INTEGER, STRING, ADDRESS, NONE };
class Ram
{
public:
	char data[RAM_MAXSIZE];
	int processaddress;

	Ram() :processaddress(0) {
		memset(data, '\0', sizeof(data));
	};

	void align(int k)
	{
		while ((processaddress % (int)pow(2, k)) != 0)
		{
			processaddress++;
		}
	}

	void in_word(int value)
	{
		data[processaddress++] = (char)((value >> 24) & 0xFF);
		data[processaddress++] = (char)((value >> 16) & 0xFF);
		data[processaddress++] = (char)((value >> 8) & 0xFF);
		data[processaddress++] = (char)(value & 0xFF);
	}

	int out_word(int address)
	{
		int value = 0;
		value = (int)(((data[address] & 0xFF) << 24)
			| ((data[address + 1] & 0xFF) << 16)
			| ((data[address + 2] & 0xFF) << 8)
			| (data[address + 3] & 0xFF));
		return value;
	}

	void in_byte(int value)
	{
		data[processaddress++] = value;
	}

	char out_byte(int address)
	{
		return data[address];
	}

	void in_half(int value)
	{
		data[processaddress++] = (char)((value & 0xFF00) >> 8);
		data[processaddress++] = (char)(value & 0xFF);
	}

	int out_half(int address)
	{
		int value = 0;
		value = (char)(((data[address] & 0xFF) << 8) | (data[address] & 0xFF));
		return value;
	}

	void space(int n)
	{
		processaddress += n;
	}

	void ascii(string value)
	{
		int len = value.length();
		for (int i = 0; i < len; i++)
		{
			data[processaddress++] = value[i];
		}
	}

	void asciiz(string value)
	{
		int len = value.length();
		for (int i = 0; i < len; i++)
		{
			data[processaddress++] = value[i];
		}
		data[processaddress++] = '\0';
	}

};

Ram SIMU_RAM;
class REGI
{
public:
	int Regist[34];
	Ram* LinkRAM;
	REGI(Ram* inilink)
	{
		memset(Regist, 0, sizeof(Regist));
		LinkRAM = inilink;
	}
	void envalue(int dist, int value)
	{
		Regist[dist] = value;
	}
	void encopy(int dist, int from)
	{
		Regist[dist] = Regist[from];
	}
	void enmove(int dist, int from)
	{
		Regist[dist] = Regist[from];
		Regist[from] = 0;
	}
	void R_RAM_BYTE(int dist, int address)
	{
		Regist[dist] = LinkRAM->out_byte(address);
	}
	void R_RAM_INT(int dist, int address)
	{
		Regist[dist] = LinkRAM->out_word(address);
	}
	void W_RAM_BYTE(int pos, int address)
	{
		LinkRAM->data[address++] = Regist[pos];
	}
	void W_RAM_INT(int pos, int address)
	{
		int value = Regist[pos];
		LinkRAM->data[address++] = (char)((value >> 24) & 0xFF);
		LinkRAM->data[address++] = (char)((value >> 16) & 0xFF);
		LinkRAM->data[address++] = (char)((value >> 8) & 0xFF);
		LinkRAM->data[address++] = (char)(value & 0xFF);
	}
	int value(operand & opdtmp);
};REGI Register(&SIMU_RAM);

class operand
{
public:
	OPD_TYPE Type;
	int reg_;
	int int_;
	string str_;
	operand(OPD_TYPE _type = NONE, int _reg = 0, int _int = 0, string _str = "\0")
		:Type(_type), reg_(_reg), int_(_int), str_(_str) {}
	int addr()
	{
		if (reg_ == -1 && int_)
			return int_;
		if (reg_ != -1 && !int_)
			return Register.Regist[reg_];
		if (reg_ != -1 && int_)
			return Register.Regist[reg_] + int_;
		return ADDR_HASH[str_];
	}
};

int REGI::value(operand & opdtmp)
{
	if (opdtmp.Type == REGISTER)
		return Regist[opdtmp.reg_];
	return opdtmp.int_;
}

class instruction
{
public:
	INST_TYPE Type;
	int k;
	operand opd[10];
	int ramaddress;
	instruction()
	{
		k = 0;
		ramaddress = 0;
		Type = DATA;
	}
	void inserttype(INST_TYPE _type)
	{
		Type = _type;
	}
	void insertopd(OPD_TYPE _type, int _reg = -1, int _int = 0, const char _str[] = NULL)
	{
		if (_type == REGISTER)
		{
			opd[k].Type = REGISTER;
			opd[k].reg_ = _reg;
			opd[k].int_ = _int;
		}
		else if (_type == INTEGER)
		{
			opd[k].Type = INTEGER;
			opd[k].reg_ = _reg;
			opd[k].int_ = _int;
		}
		else if (_type == STRING)
		{
			opd[k].Type = STRING;
			opd[k].str_ = _str;
			opd[k].reg_ = _reg;
			opd[k].int_ = _int;
		}
		else if (_type == ADDRESS)
		{
			opd[k].Type = ADDRESS;
			opd[k].reg_ = _reg;
			opd[k].int_ = _int;
		}
		k++;
	}
};instruction INST[100000];

void HASH_INITIALIZE()
{
	for (int i = 0; i <= 51; i++)
	{
		INST_HASH[INSTLIB[i]] = i;
	}
	for (int i = 0; i < 30; i++)
	{
		REG_HASH[REGLIB[i]] = i;
	}
	REG_HASH[REGLIB[30]] = 30;
	REG_HASH[REGLIB[31]] = 30;
	REG_HASH[REGLIB[32]] = 31;
	for (int i = 33; i <= 64; i++)
	{
		REG_HASH[REGLIB[i]] = i - 33;
	}

}
void operate(instruction & INS, int & nowline)
{
	nowline++;
	switch (INS.Type)
	{
	case DATA:case TEXT:case NOP:
		return;
	case ALIGN:
		SIMU_RAM.align(INS.opd[0].int_);
		return;
	case ASCII:
		SIMU_RAM.ascii(INS.opd[0].str_);
		return;
	case ASCIIZ:
		SIMU_RAM.asciiz(INS.opd[0].str_);
		return;
	case BYTE:
		SIMU_RAM.in_byte(INS.opd[0].int_);
		return;
	case HALF:
		SIMU_RAM.in_half(INS.opd[0].int_);
		return;
	case SPACE:
		SIMU_RAM.space(INS.opd[0].int_);
		return;
	case WORD:
		SIMU_RAM.in_word(INS.opd[0].int_);
		return;
	case NEG:
		Register.envalue(INS.opd[0].reg_, -Register.value(INS.opd[1]));
		return;
	case ADD: case ADDU:
		Register.envalue(INS.opd[0].reg_, Register.value(INS.opd[1]) + Register.value(INS.opd[2]));
		return;
	case REM:
		Register.envalue(INS.opd[0].reg_, Register.value(INS.opd[1]) % Register.value(INS.opd[2]));
		return;
	case SUB: case SUBU:
		Register.envalue(INS.opd[0].reg_, Register.value(INS.opd[1]) - Register.value(INS.opd[2]));
		return;
	case XOR:
		Register.envalue(INS.opd[0].reg_, Register.value(INS.opd[1]) ^ Register.value(INS.opd[2]));
		return;
	case DIV:
		if (INS.k == 2)
		{
			Register.envalue(33, Register.value(INS.opd[0]) / Register.value(INS.opd[1]));
			Register.envalue(32, Register.value(INS.opd[0]) % Register.value(INS.opd[1]));
		}
		else
		{
			Register.envalue(INS.opd[0].reg_, Register.value(INS.opd[1]) / Register.value(INS.opd[2]));
		}
		return;
	case MUL:
		Register.envalue(INS.opd[0].reg_, Register.value(INS.opd[1]) * Register.value(INS.opd[2]));
		return;
	case J:
		nowline = LABEL_HASH[INS.opd[0].str_];
		return;
	case JAL:
		Register.envalue(31, nowline);
		nowline = LABEL_HASH[INS.opd[0].str_];
		return;
	case JALR:
		Register.envalue(31, nowline);
		nowline = Register.value(INS.opd[0]);
		return;
	case JR:
		nowline = Register.value(INS.opd[0]);
		return;
	case LI:
		Register.envalue(INS.opd[0].reg_, INS.opd[1].int_);
		return;
	case LA:
		Register.envalue(INS.opd[0].reg_, INS.opd[1].addr());
		return;
	case LB:
		Register.R_RAM_BYTE(INS.opd[0].reg_, INS.opd[1].addr());
		return;
	case LW:
		Register.R_RAM_INT(INS.opd[0].reg_, INS.opd[1].addr());
		return;
	case SB:
		Register.W_RAM_BYTE(INS.opd[0].reg_, INS.opd[1].addr());
		return;
	case SW:
		Register.W_RAM_INT(INS.opd[0].reg_, INS.opd[1].addr());
		return;
	case SEQ:
		if (Register.value(INS.opd[1]) == Register.value(INS.opd[2]))
			Register.Regist[INS.opd[0].reg_] = 1;
		else Register.Regist[INS.opd[0].reg_] = 0;
		return;
	case SGE:
		if (Register.value(INS.opd[1]) >= Register.value(INS.opd[2]))
			Register.Regist[INS.opd[0].reg_] = 1;
		else Register.Regist[INS.opd[0].reg_] = 0;
		return;
	case SGT:
		if (Register.value(INS.opd[1]) > Register.value(INS.opd[2]))
			Register.Regist[INS.opd[0].reg_] = 1;
		else Register.Regist[INS.opd[0].reg_] = 0;
		return;
	case SLE:
		if (Register.value(INS.opd[1]) <= Register.value(INS.opd[2]))
			Register.Regist[INS.opd[0].reg_] = 1;
		else Register.Regist[INS.opd[0].reg_] = 0;
		return;
	case SLT:
		if (Register.value(INS.opd[1]) < Register.value(INS.opd[2]))
			Register.Regist[INS.opd[0].reg_] = 1;
		else Register.Regist[INS.opd[0].reg_] = 0;
		return;
	case SNE:
		if (Register.value(INS.opd[1]) != Register.value(INS.opd[2]))
			Register.Regist[INS.opd[0].reg_] = 1;
		else Register.Regist[INS.opd[0].reg_] = 0;
		return;
	case B:
		nowline = LABEL_HASH[INS.opd[0].str_] + 1;
		return;
	case BEQ:
		if (Register.value(INS.opd[0]) == Register.value(INS.opd[1]))
		{
			nowline = LABEL_HASH[INS.opd[2].str_] + 1;
		}
		return;
	case BEQZ:
		if (!Register.value(INS.opd[0]))
		{
			nowline = LABEL_HASH[INS.opd[1].str_] + 1;
		}
		return;
	case BGT:
		if (Register.value(INS.opd[0]) > Register.value(INS.opd[1]))
		{
			nowline = LABEL_HASH[INS.opd[2].str_] + 1;
		}
		return;
	case BGTZ:
		if (Register.value(INS.opd[0])>0)
		{
			nowline = LABEL_HASH[INS.opd[1].str_] + 1;
		}
		return;
	case BGE:
		if (Register.value(INS.opd[0]) >= Register.value(INS.opd[1]))
		{
			nowline = LABEL_HASH[INS.opd[2].str_] + 1;
		}
		return;
	case  BGEZ:
		if (Register.value(INS.opd[0]) >= 0)
		{
			nowline = LABEL_HASH[INS.opd[1].str_] + 1;
		}
		return;
	case BLE:
		if (Register.value(INS.opd[0]) <= Register.value(INS.opd[1]))
		{
			nowline = LABEL_HASH[INS.opd[2].str_] + 1;
		}
		return;
	case BLEZ:
		if (Register.value(INS.opd[0]) <= 0)
		{
			nowline = LABEL_HASH[INS.opd[1].str_] + 1;
		}
		return;
	case BLT:
		if (Register.value(INS.opd[0]) < Register.value(INS.opd[1]))
		{
			nowline = LABEL_HASH[INS.opd[2].str_] + 1;
		}
		return;
	case BLTZ:
		if (Register.value(INS.opd[0]) < 0)
		{
			nowline = LABEL_HASH[INS.opd[1].str_] + 1;
		}
		return;
	case BNE:
		if (Register.value(INS.opd[0]) != Register.value(INS.opd[1]))
		{
			nowline = LABEL_HASH[INS.opd[2].str_] + 1;
		}
		return;
	case BNEZ:
		if (Register.value(INS.opd[0]) != 0)
		{
			nowline = LABEL_HASH[INS.opd[1].str_] + 1;
		}
		return;
	case MOVE:
		Register.encopy(INS.opd[0].reg_, INS.opd[1].reg_);
		return;
	case MFHI:
		Register.encopy(INS.opd[0].reg_, 32);
		return;
	case MFLO:
		Register.encopy(INS.opd[0].reg_, 33);
		return;
	case SYSCALL:
		INS.opd[0].int_ = Register.Regist[2];
		EX_SYSCALL(Register.Regist[2]);
		return;
	default:
		break;
	}
}

void EX_SYSCALL(int k)
{
	char tmp[10000];
	memset(tmp, '\0', sizeof(tmp));
	int len = 0;
	int x = 0;
	switch (k)
	{
	case 1:
		printf("%d", Register.Regist[4]);
		break;
	case 4:
		printf("%s", SIMU_RAM.data + Register.Regist[4]);
		break;
	case 5:
		scanf("%d", &Register.Regist[2]);
		break;
	case 8:
		scanf("%s", tmp);
		len = strlen(tmp);
		x = Register.Regist[4];
		for (int i = 0; i <= len; i++)
		{
			SIMU_RAM.data[x++] = tmp[i];
		}
		break;
	case 9:
		len = SIMU_RAM.processaddress;
		SIMU_RAM.processaddress += Register.Regist[4];
		Register.Regist[2] = len;
		break;
	case 10:case 17:
		exited = true;
		break;
	default:
		break;
	}
}
int REG_INT(string tmp)
{
	return REG_HASH[tmp];
}

void CH_INITIALIZE(char data[])
{
	int len = strlen(data);
	for (int i = 0; i < len - 1; i++)
	{
		if (data[i] == '\\')
		{
			if (data[i + 1] == 'n')
			{
				data[i] = '\n';
				for (int j = i + 1; j <= len - 1; j++)
				{
					data[j] = data[j + 1];
				}
			}
			else
				if (data[i + 1] == 't')
				{
					data[i] = '\t';
					for (int j = i + 1; j <= len - 1; j++)
					{
						data[j] = data[j + 1];
					}
				}
		}
	}

}

void Build_Inst()
{
	++line;
	char Temp[1000];
	if (sscanf(Input_Temp.c_str(), "%s", Temp) == EOF)
	{
		INST[line].inserttype(EMPTY);
		return;
	}
	string Str_Temp = Temp;
	if (Temp[strlen(Temp) - 1] == ':')
	{
		Temp[strlen(Temp) - 1] = '\0';
		INST[line].inserttype(LABEL);
		INST[line].insertopd(STRING, -1, 0, Temp);
		LABEL_HASH[Temp] = line;
		return;
	}
	int flag = INST_HASH[Str_Temp];
	INST[line].inserttype((INST_TYPE)flag);
	int k = Input_Temp.find_first_of(Temp[strlen(Temp) - 1]);
	int ktmp = 0;
	int inttmp = 0;
	switch (flag)
	{
	case 0:case 8:case 50:case 51:
		return;
	case 2:case 3:
	{
		while (Input_Temp[k] != '\"') k++;
		k++;
		int m = 0;
		while (Input_Temp[k] != '\"')
		{
			Temp[m++] = Input_Temp[k];
			k++;
		}
		Temp[m++] = '\0';
		CH_INITIALIZE(Temp);
		INST[line].insertopd(STRING, -1, 0, Temp);
		return;
	}
	break;
	case 42:case 43:case 44:case 45: case 46:

		k = Input_Temp.find_first_of('$', k + 1);
		sscanf(Input_Temp.c_str() + k, "$%s", Temp);
		if (Temp[strlen(Temp) - 1] == ',')
			Temp[strlen(Temp) - 1] = '\0';
		INST[line].insertopd(REGISTER, REG_INT(Temp));

		k = Input_Temp.find_first_of(' ', k + 1);
		if (k != -1)
			while (Input_Temp[k + 1] == ' ' || Input_Temp[k + 1] == '\t')
				k++;
		if (Input_Temp[k + 1] == '(')
		{
			sscanf(Input_Temp.c_str() + k, "$%s", Temp);
			if (Temp[strlen(Temp) - 1] == ',')
				Temp[strlen(Temp) - 1] = '\0';
			INST[line].insertopd(ADDRESS, REG_INT(Temp));
			return;
		}
		else if ((Input_Temp[k + 1] >= '0'&& Input_Temp[k + 1] <= '9') || Input_Temp[k + 1] == '-')
		{
			int dollarpos = Input_Temp.find_first_of('$', k + 1);
			if (dollarpos == -1)
			{
				inttmp = 0;
				sscanf(Input_Temp.c_str() + k, "%d", &inttmp);
				INST[line].insertopd(ADDRESS, -1, inttmp);
				return;
			}
			else
			{
				inttmp = 0;
				sscanf(Input_Temp.c_str() + dollarpos, "$%s", Temp);
				if (Temp[strlen(Temp) - 1] == ')')
					Temp[strlen(Temp) - 1] = '\0';
				Input_Temp[dollarpos - 1] = ' ';
				sscanf(Input_Temp.c_str() + k, "%d", &inttmp);
				INST[line].insertopd(ADDRESS, REG_INT(Temp), inttmp);
				return;
			}
		}
		else
		{
			sscanf(Input_Temp.c_str() + k, "%s", Temp);
			CH_INITIALIZE(Temp);
			INST[line].insertopd(STRING, -1, 0, Temp);
			return;
		}
		break;
	default:
		while (1)
		{
			ktmp = k;
			k = Input_Temp.find_first_of('$', k + 1);
			if (k != -1)
			{
				sscanf(Input_Temp.c_str() + k, "$%s", Temp);
				if (Temp[strlen(Temp) - 1] == ',')
					Temp[strlen(Temp) - 1] = '\0';
				INST[line].insertopd(REGISTER, REG_INT(Temp));
				continue;
			}
			else
			{
				inttmp = 0;
				k = Input_Temp.find_first_of(' ', ktmp + 1);
				if (k != -1)
					while (Input_Temp[k + 1] == ' ' || Input_Temp[k + 1] == '\t')
						k++;
				if (k != -1 && ((Input_Temp[k + 1] >= '0'&&Input_Temp[k + 1] <= '9') || Input_Temp[k + 1] == '-'))
				{
					sscanf(Input_Temp.c_str() + k, "%d", &inttmp);
					INST[line].insertopd(INTEGER, -1, inttmp);
					continue;
				}
				else
				{
					if (k != -1 && Input_Temp[k + 1] != '\0')
					{
						sscanf(Input_Temp.c_str() + k, "%s", Temp);
						CH_INITIALIZE(Temp);
						INST[line].insertopd(STRING, -1, 0, Temp);
						return;
					}
					else
					{
						return;
					}
				}

			}

		}
		break;
	}
}

void RAM_INITIALIZE()
{
	bool flag = false;
	for (int i = 1; i <= line; i++)
	{
		int k = i;
		if (INST[i].Type == DATA) { flag = true; continue; }
		if (INST[i].Type == TEXT) { flag = false; continue; }
		if (flag&&INST[i].Type == LABEL)
			ADDR_HASH[INST[i].opd[0].str_] = SIMU_RAM.processaddress;
		if (flag&&INST[i].Type >= 1 && INST[i].Type <= 7)
			operate(INST[i], k);
	}
	Register.Regist[29] = RAM_MAXSIZE - 100;
}

class ProgressCount
{
public:
	int* data;
	int now;
	int tot;
	int counter[7];
	bool RAMLOCK;
	int RAMPOS;
	bool JUMPLOCK;
	int JUMPPOS;
	bool REGILOCK[35];
	int REGIPOS[35];
	long long cnt;
	void locknlock(instruction & INS, int counternum)
	{
		switch (INS.Type)
		{
		case SYSCALL:
			if (counternum == 2)
			{
				JUMPPOS = counternum;
				JUMPLOCK = true;
			}
			if (counternum == 2)
			{
				if (INS.opd[0].int_ == 5 || INS.opd[0].int_ == 9)
				{
					REGIPOS[2] = counternum;
					REGILOCK[2] = true;
				}
			}
			if (counternum == 5)
			{
				JUMPPOS = 6;
				JUMPLOCK = false;
				if (INS.opd[0].int_ == 5 || INS.opd[0].int_ == 9)
				{
					REGIPOS[2] = 6;
					REGILOCK[2] = false;
				}
			}
			if (INS.opd[0].int_ == 2)
			{
				if (counternum == 4)
				{
					RAMPOS = counternum;
					RAMLOCK = true;
				}
				if (counternum == 5)
				{
					RAMPOS = 6;
					RAMLOCK = false;
				}
			}
			break;
		case LA:case LB:case LW:
			if (counternum == 2)
			{
				REGILOCK[INS.opd[0].reg_] = true;
				REGIPOS[INS.opd[0].reg_] = counternum;
			}
			if (counternum == 5)
			{
				REGILOCK[INS.opd[0].reg_] = false;
				REGIPOS[INS.opd[0].reg_] = 6;
			}
			if (counternum == 4)
			{
				RAMPOS = counternum;
				RAMLOCK = true;
			}
			if (counternum == 5)
			{
				RAMPOS = 6;
				RAMLOCK = false;
			}
			break;
		case SB:case SW:
			if (counternum == 4)
			{
				RAMPOS = counternum;
				RAMLOCK = true;
			}
			if (counternum == 5)
			{
				RAMPOS = 6;
				RAMLOCK = false;
			}
			break;
		case JALR:	case JAL:
			if (counternum == 2)
			{
				REGILOCK[31] = true;
				REGIPOS[31] = counternum;
			}
			if (counternum == 5)
			{
				REGILOCK[31] = false;
				REGIPOS[31] = 6;
			}
			if (counternum == 2)
			{
				JUMPPOS = counternum;
				JUMPLOCK = true;
			}
			if (counternum == 5)
			{
				JUMPPOS = 6;
				JUMPLOCK = false;
			}
			break;
		case J: case JR:
			if (counternum == 2)
			{
				JUMPPOS = counternum;
				JUMPLOCK = true;
			}
			if (counternum == 5)
			{
				JUMPPOS = 6;
				JUMPLOCK = false;
			}
			break;
		case BEQ: case BEQZ: case BGE: case BGEZ: case BGT: case BGTZ:
		case BLE: case BLEZ: case BLT: case BLTZ: case BNE: case BNEZ:
		case B:
			if (counternum == 2)
			{
				JUMPPOS = counternum;
				JUMPLOCK = true;
			}
			if (counternum == 5)
			{
				JUMPPOS = 6;
				JUMPLOCK = false;
			}
			break;
		case NOP:
			break;
		case DIV:
			if (INS.k == 2)
			{
				if (counternum == 2)
				{
					REGILOCK[32] = true;REGIPOS[32] = counternum;
					REGILOCK[33] = true;REGIPOS[33] = counternum;
				}
				if (counternum == 5)
				{
					REGILOCK[32] = false;REGIPOS[32] = 6;
					REGILOCK[33] = false;REGIPOS[33] = 6;
				}
			}
			else
			{
				if (counternum == 2)
				{
					REGILOCK[INS.opd[0].reg_] = true;
					REGIPOS[INS.opd[0].reg_] = counternum;
				}
				if (counternum == 5)
				{
					REGILOCK[INS.opd[0].reg_] = false;
					REGIPOS[INS.opd[0].reg_] = 6;
				}
			}
			break;
		default:
			if (counternum == 2)
			{
				REGILOCK[INS.opd[0].reg_] = true;
				REGIPOS[INS.opd[0].reg_] = counternum;
			}
			if (counternum == 5)
			{
				REGILOCK[INS.opd[0].reg_] = false;
				REGIPOS[INS.opd[0].reg_] = 6;
			}
			break;
		}
	}
	ProgressCount(int _data[], int _tot)
	{
		JUMPPOS = 6;
		RAMPOS = 6;
		memset(REGIPOS, 6, sizeof(REGIPOS));
		cnt = 0;
		data = _data;
		tot = _tot;
		now = 1;
		memset(counter, 0, sizeof(counter));
		memset(REGILOCK, 0, sizeof(REGILOCK));
		RAMLOCK = false;
		JUMPLOCK = false;
		counter[1] = sequence[now++];
	}

	bool valid(instruction& INS, int pos)
	{

		if (JUMPLOCK && pos <= JUMPPOS)
			return false;
		if (pos == 1)
		{
			if (RAMLOCK)
				return false;
			else
				return true;
		}
		switch (INS.Type)
		{
		case SYSCALL:
			if (REGILOCK[2] && pos <= REGIPOS[2])
				return false;
			switch (INS.opd[0].int_)
			{
			case 1: case 4: case 17:
				if (REGILOCK[4] && pos <= REGIPOS[4])
					return false;
				else return true;
			case 5:
				//if (RAMLOCK && pos <= RAMPOS)
					//return false;
				return true;
			case 8:
				//if (RAMLOCK&& pos <= RAMPOS)
				//	return false;
				if ((REGILOCK[4] && pos <= REGIPOS[4]) || (REGILOCK[5] && pos <= REGIPOS[5]))
					return false;
				else return true;
			case 9:
				if (REGILOCK[4] && pos <= REGIPOS[4])
					return false;
				else return true;
			default:
				break;
			}
			break;
		case DIV:
			if (INS.k == 2)
			{
				if (INS.opd[0].Type == REGISTER&&REGILOCK[INS.opd[0].reg_] && pos <= REGIPOS[INS.opd[0].reg_])
					return false;
				if (INS.opd[1].Type == REGISTER&&REGILOCK[INS.opd[1].reg_] && pos <= REGIPOS[INS.opd[1].reg_])
					return false;
			}
			else
			{
				for (int i = 1; i <= INS.k; i++)
				{
					if (INS.opd[i].Type == REGISTER)
						if (REGILOCK[INS.opd[i].reg_] && pos <= REGIPOS[INS.opd[i].reg_])
							return false;
				}
			}
			break;
		case LA:case LB:case LW:
		//	if (RAMLOCK&& pos <= RAMPOS)
			//	return false;
			if (INS.opd[1].reg_ != -1&&REGILOCK[INS.opd[1].reg_] && pos <= REGIPOS[INS.opd[1].reg_])
			{
				return false;
			}
			break;
		case SB:case SW:
			//if (RAMLOCK&& pos <= RAMPOS)
			//	return false;
			if (REGILOCK[INS.opd[0].reg_] && pos <= REGIPOS[INS.opd[0].reg_])
			{
				return false;
			}
			if (INS.opd[1].reg_ != -1 && REGILOCK[INS.opd[1].reg_] && pos <= REGIPOS[INS.opd[1].reg_])
			{
				return false;
			}
			break;
		case J: case JAL:
			if (INS.opd[0].reg_ != -1 && REGILOCK[INS.opd[0].reg_] && pos <= REGIPOS[INS.opd[0].reg_])
				return false;
			break;
		case JR:case JALR:
			if (INS.opd[0].Type == REGISTER&&REGILOCK[INS.opd[0].reg_] && pos <= REGIPOS[INS.opd[0].reg_])
				return false;
			break;
		case MFHI:
			if (REGILOCK[32] && pos <= REGIPOS[32])
				return false;
			break;
		case MFLO:
			if (REGILOCK[33] && pos <= REGIPOS[33])
				return false;
			break;
		case B:case BEQ:case BEQZ: case BGE: case BGEZ: case BGT: case BGTZ:
		case BLE: case BLEZ: case BLT: case BLTZ: case BNE: case BNEZ:
			for (int i = 0; i <= INS.k; i++)
			{
				if (INS.opd[i].Type == REGISTER)
					if (REGILOCK[INS.opd[i].reg_] && pos <= REGIPOS[INS.opd[i].reg_])
						return false;
				if (INS.opd[i].Type == ADDRESS)
					if (INS.opd[i].reg_ != -1 && REGILOCK[INS.opd[i].reg_] && pos <= REGIPOS[INS.opd[i].reg_])
						return false;
			}
			break;
		default:
			for (int i = 1; i <= INS.k; i++)
			{
				if (INS.opd[i].Type == REGISTER)
					if (REGILOCK[INS.opd[i].reg_] && pos <= REGIPOS[INS.opd[i].reg_])
						return false;
				if (INS.opd[i].Type == ADDRESS)
					if (INS.opd[i].reg_ != -1 && REGILOCK[INS.opd[i].reg_] && pos <= REGIPOS[INS.opd[i].reg_])
						return false;
			}
			break;
		}
		return true;
	}

	void displace()
	{
		cnt++;
		if (counter[5] != 0)
		{
			locknlock(INST[counter[5]], 5);
			counter[5] = 0;
		}
		for (int i = 4; i >= 1; i--)
		{
			if (counter[i] != 0 && valid(INST[counter[i]], i) && counter[i + 1] == 0)
			{
				counter[i + 1] = counter[i];
				if (counter[i] != 0)
					locknlock(INST[counter[i]], i);
				counter[i] = 0;
			}
		}
		if (counter[1] == 0)
		{
			counter[1] = data[now++];
		}
	}

	void work()
	{
		while (1)
		{
			if (now > tot)
			{
				bool allclear = true;
				for (int i = 1; i <= 5; i++)
				{
					if (counter[i])
						allclear = false;
				}
				if (allclear)
					break;
			}
			displace();
			//print();
			//if (now >= 500) break;
			//printf("%d\n", now);
			//if (now == 7)
			//cout << endl;
		}
	}
	void print()
	{
		string tmp;
		for (int i = 0; i <= 33; i++)
		{
			printf("%d ", REGILOCK[i]);
		}
		printf("%d ", JUMPLOCK);
		if (RAMLOCK)
			printf("true\n");
		else printf("false\n");
		getline(fin, tmp);
		cout << tmp << endl;
		cout << "------------------------------------------------------------------" << endl;
	}
};


int main(int argc, char* argv[])
{
	fin.open(argv[1]);
	HASH_INITIALIZE();
	while (getline(fin, Input_Temp))
	{
		Build_Inst();
	}
	RAM_INITIALIZE();
	fin.close();
	int nowline = LABEL_HASH["main"] + 1;
	while (1)
	{
		if (INST[nowline].Type<52 && INST[nowline].Type>8 && INST[nowline].Type != LABEL)
			sequence[++seqpos] = nowline;
		while (INST[nowline].Type >= 0 && INST[nowline].Type <= 7) nowline++;
		operate(INST[nowline], nowline);
		if (exited)
			break;
	}
	ProgressCount PCNT(sequence, seqpos);
	PCNT.work();
	printf("\n");
	printf("%d\n", PCNT.cnt);
	printf("%d\n", PCNT.tot);
	return 0;
}