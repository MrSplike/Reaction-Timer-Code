/*
 * File:   newmain.c
 * Author: student
 *
 * Created on September 26, 2019, 12:52 PM
 */

#pragma config FOSC = INTRCCLK  // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)

#include <xc.h>
#define _XTAL_FREQ 1000000

void displayPattern();

int pattern = 0b00000001;

void main() {
    OSCCON = 0b01000000;
    TRISA = 1;
    TRISC = 0;
    ANSEL = 0x00;
    ANSELH = 0x00;
    OPTION_REGbits.nRABPU = 0;
    WPUBbits.WPUB4 = 1;
    
    while (1) {
        for (int a = 0; a < 7; a++) {
            pattern = pattern * 2 + 1;
            displayPattern();
        }
        for (int b = 0; b < 7; b++) {
            pattern = (pattern - 1) / 2;
            displayPattern();
        }
    }
}

void displayPattern() {
    for (int c = 0; c < 25; c++) {
        if (PORTAbits.RA0 == 0) {
            for (int d = 0; d < 3; d++) {
                PORTC = pattern;
                __delay_ms(500);
                PORTC = 0;
                __delay_ms(500);
            }
        }
        __delay_ms(1);
    }
    PORTC = pattern;
}
