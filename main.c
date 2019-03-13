#include "mySimpleComputer.h"

#include <stdio.h>

int main() {
    sc_regInit();
    sc_memoryInit();
    sc_memorySet(10, 50);
    int cell;
    sc_memoryGet(10, &cell);
    printf("cell - %d\n", cell);
    sc_memorySave("save.bin");
    sc_memoryLoad("save.bin");

    sc_regSet(MEM_OUT, 1);
    int val;
    sc_regGet(1, &val);
    printf("val - %d\n", val);
    sc_commandEncode(0x55, 0x59, &val);
    int command;
    int oper;
    sc_commandDecode(val, &command, &oper);
    printf("%x %x\n", command, oper);
}
