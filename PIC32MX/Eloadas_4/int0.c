#include <xc.h>

// az INT függvény attribútuma miatt kell
#include "sys/attribs.h"

#define     T1ON()      { T1CONbits.ON = 1; }
#define     LEDT1       LATDbits.LATD0
#define     LEDT1TG()     { LEDT1 = ~LEDT1; }

// INT függvény, szoftveresen nem hívjuk meg!
void __ISR(0, ipl1) szerdaINT()
{
    LEDT1TG();
    IFS0bits.T1IF = 0;
}

// sajátfüggvény prototípusa
// A TImer1-et ezzel a függvénnyel 
// programozzuk fel. Időzítő mód
// A PR1 regiszter és az előosztó értékei
// paraméteresen kerülnek átadásra.
void T1Config(unsigned int pr1, unsigned char oszto);

main()
{
    // konfig
    TRISD = 0x0000;
    LATD = 0x0000;
    
    // Timer1 konfig
    // időzítő mód
    T1Config(0x1234, 0x02);
    
    // T1 INT konfig
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    IPC1bits.T1IP = 1;
    
    // INT konfig, single mód kerül alkalmazásra
    INTCONbits.MVEC = 0;
    
    // INT engedélyezése
    asm volatile("ei");
    
    // T1 engedélyezése
    T1ON();
    
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
