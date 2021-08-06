#include "lcd.h"

void printf(char txt[12]) {
    int i;
    for (i = 0; i < 11; i++) {
        if (txt[i] == '\0'){
            return;
        }
        if (txt[i] == '\n'){
            lcdCommand(0xC0);
            continue;
        }
        lcdData(txt[i]);
    }
}