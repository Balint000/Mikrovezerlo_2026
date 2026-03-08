#include <xc.h>

// a byte (unsinged char) "tÝpus˙" vßltozˇk 
// lÚtrehozßsßnßl alkalmazhatˇ a typedef.
// typedef V┴LTOZËT═PUS ˙j vßltozˇnÚv

typedef unsigned char byte;

// a "sze" nem egy ˙j vßltozˇtÝpus, hanem 
// az unsigned int tÝpusnak egy ˙j neve
// termÚszetesen hasznßlhatˇ tovßbbra is
// az "unsigned int", de mßr a "sze" is
typedef unsigned int sze;

union
{
    struct
    {
        unsigned s0:1;
        unsigned s1:1;
        unsigned s2:1;
        unsigned s3:1;
        unsigned s4:1;
        unsigned s5:1;
        unsigned s6:1;
        unsigned s7:1;
    } Bit;
    unsigned char Byte;
} Flags;


main()
{
    TRISD = 0x0000;
    sze egesz = 1;
    unsigned char ch;
    
    byte b;
    
    Flags.Byte = 0x12;
    LATDbits.LATD1 = Flags.Bit.s1;
    
    LATD = Flags.Byte;
    
    
    while(1);
}
