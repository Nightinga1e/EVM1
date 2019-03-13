#pragma once

#define SC_MEM_SIZE 100
#define REG_SIZE 32

#define MEM_OUT       0b00000001
#define INVALID_REG   0b00000010
#define WRONG_COMMAND 0b00000100


int sc_memoryInit();

int sc_memorySet(int address, int value);

int sc_memoryGet(int address, int *value);

int sc_memorySave(char filename[]);

int sc_memoryLoad(char filename[]);

int sc_regInit();

int sc_regSet(int reg, int value);

int sc_regGet(int reg, int *value);

int sc_commandEncode(int command, int operand, int *value);

int sc_commandDecode(int value, int *command, int *operand);
