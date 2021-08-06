/*
 * File:   Main.c
 * Author: Flávio
 *
 * Created on 15 de Julho de 2021, 14:37
 */

#include "config.h"
#include "lcd.h"
#include "keypad.h"
#include "ssd.h"
#include "bits.h"
// inclusão da blibiotecas

void main(void) {
    int pnts = 1, time, trava;
    int crgpnts = -1;
    unsigned int flag = 0;
    unsigned long int pntsj1 = 0, pntsj2 = 0;
    // criação das variaveis utilizadas

    ssdInit();
    // inicializa o display de 7 segmentos

    lcdInit();
    //inicializa o lcd

    kpInit();

    for (;;) {

        lcdData('J');
        lcdData('1');
        lcdPosition(0, 7);
        lcdData('V');
        lcdData('S');
        lcdPosition(0, 14);
        lcdData('J');
        lcdData('2');
        lcdPosition(1, 7);
        lcdData('/');
        lcdData('/');

        if (pnts == 1) {
            ssdDigit(0, 0);
            ssdDigit(0, 1);
            ssdDigit(0, 2);
            ssdDigit(1, 3);
        }
        if (pnts == 3) {
            ssdDigit(0, 0);
            ssdDigit(0, 1);
            ssdDigit(0, 2);
            ssdDigit(3, 3);
        }

        if (pnts == 6) {
            ssdDigit(0, 0);
            ssdDigit(0, 1);
            ssdDigit(0, 2);
            ssdDigit(6, 3);
        }

        if (pnts == 9) {
            ssdDigit(0, 0);
            ssdDigit(0, 1);
            ssdDigit(0, 2);
            ssdDigit(9, 3);
        }
        if (pnts == 12) {
            ssdDigit(0, 0);
            ssdDigit(0, 1);
            ssdDigit(1, 2);
            ssdDigit(2, 3);
        }
        
        kpDebounce();

        if (kpRead() != flag) {
            flag = kpRead();

            if (bitTst(flag, 6)) {
                switch (pnts) {

                    case 1:
                        pnts = 3;
                        crgpnts = -3;
                        break;

                    case 3:
                        pnts = 6;
                        crgpnts = -6;
                        break;

                    case 6:
                        pnts = 9;
                        crgpnts = -9;
                        break;

                    case 9:
                        pnts = 12;
                        crgpnts = -12;
                        break;

                    default:
                        break;
                }
            }
            if (bitTst(flag, 2)) {
                pntsj1 += pnts;
                pnts = 1;
            }
            if (bitTst(flag, 10)) {
                pntsj2 += pnts;
                pnts = 1;
            }
            if (bitTst(flag, 5)) {
                pnts = crgpnts;
                crgpnts = -1;
            }
            if (bitTst(flag, 7)) {
                pnts = 1;
                pntsj1 = 0;
                pntsj2 = 0;
            }
        }

        for (time = 0; time < 10; time++);
        ssdUpdate();

        lcdPosition(1, 0);
        lcdData(((pntsj1 / 10) % 10) + 48);
        lcdData(((pntsj1 / 1) % 10) + 48);

        lcdPosition(1, 14);
        lcdData(((pntsj2 / 10) % 10) + 48);
        lcdData(((pntsj2 / 1) % 10) + 48);

        if (pntsj1 >= 12) {
            pntsj1 = 12;
            trava = pntsj2;
            if (pntsj2 > trava) {
                pntsj2 = trava;
            }
        }

        if (pntsj2 >= 12) {
            pntsj2 = 12;
            trava = pntsj1;
            if (pntsj1 > trava) {
                pntsj1 = trava;
            }
        }
    }
}
