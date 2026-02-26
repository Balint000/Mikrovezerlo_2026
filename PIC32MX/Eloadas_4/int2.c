// Két belső és egy külső (INT3) megszakításkérés lehetséges.
// Az INT3/RA14-es lábon történő állapotváltás külső megszakításkérést idéz elő.
// Más nem single, hanem multi mód kerül alkalmazásra, tehát minden megszakításkérő 
// perifériának saját függvénye van.

#include <xc.h>
#include "sys/attribs.h"

// INT3/RA14

#define     T1ON()      { T1CONbits.ON = 1; }
#define     T2ON()      { T2CONbits.ON = 1; }
#define     LEDT1       LATDbits.LATD0
#define     LEDT2       LATDbits.LATD1
#define     LEDT1TG()     { LEDT1 = ~LEDT1; }
#define     LEDT2TG()     { LEDT2 = ~LEDT2; }

void __ISR(_TIMER_1_VECTOR, IPL1SRS) T1INTM()
{
    IFS0bits.T1IF = 0;
    LEDT1TG();
}

void __ISR(_TIMER_2_VECTOR, IPL1SRS) T2INTM()
{
    IFS0bits.T2IF = 0;
    LEDT2TG();
}

void __ISR(_EXTERNAL_3_VECTOR, IPL1SRS) INT3INTM()
{
    IFS0bits.INT3IF = 0;
    LATB++;
}

void T1Config(unsigned int pr1, unsigned char oszto);

main()
{
    // konfig
    TRISAbits.TRISA14 = 1;
    TRISB = 0x0000;
    LATB = 0x0000;
    TRISD = 0x0000;
    LATD = 0x0000;
    
    // Timer1 konfig
    // időzítő mód
    T1Config(0x1234, 0x02);
    
    // Timer2 konfig, irdőzítő, 1:32
    T2CON = 0x0040;
    PR2 = 0x1234;
    
    // T1 INT konfig
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    IPC1bits.T1IP = 1;
    
    // T2 INT konfig
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;
    IPC2bits.T2IP = 1;
    
    // INT3 INT konfig
    IFS0bits.INT3IF = 0;
    IEC0bits.INT3IE = 1;
    IPC3bits.INT3IP = 1;
    
    // INT konfig, multi
    INTCONbits.MVEC = 1;
    
    // INT engedélyezése
    asm volatile("ei");
    
    // T1, T2 engedélyezése
    T1ON();
    T2ON();
    
    while(1)
    {
       // itt van a vezérlés 
    }
}

void T1Config(unsigned int pr1, unsigned char oszto)
{
    T1CONbits.TGATE = 0;
    T1CONbits.TCS = 0;
    T1CONbits.TCKPS = oszto;
    TMR1 = 0x0000;
    PR1 = pr1;
}
