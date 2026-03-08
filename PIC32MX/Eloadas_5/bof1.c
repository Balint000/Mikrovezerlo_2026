#include <xc.h>
#include "string.h"

void masol(char* valami)
{
    char tomb[5];
    strcpy(tomb, valami);
}

main()
{
    char hetfo[10] = {'1', '2','3','4','5','6','7','8','9','0'};
    TRISD = 0x0000;
    
    masol(hetfo);
    while(1);
}
