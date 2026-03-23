#include <xc.h>

#define SCL1       LATAbits.LATA14
#define SDA1Out    LATAbits.LATA15

void i2cMasterIdle()
{
    while(I2C1CON & 0x1F);
    while(I2C1STATbits.TRSTAT);
}

void i2cMasterStart()
{
    i2cMasterIdle();
    I2C1CONbits.SEN = 1;
    while(I2C1CONbits.SEN);
}

void i2cMasterStop()
{
    i2cMasterIdle();
    I2C1CONbits.PEN = 1;
    while(I2C1CONbits.PEN);
}

void i2cMasterSend(unsigned char byte)
{
    I2C1TRN = byte;
    while(I2C1STATbits.TRSTAT);
}

void i2cMasterConfig()
{
    I2C1BRG = 0x01E7;
    I2C1CONbits.A10M = 0;
    I2C1CONbits.ON = 1;
}

main()
{
    TRISAbits.TRISA14 = 0;
    TRISAbits.TRISA15 = 0;
    
    i2cMasterConfig();
    
    while(1)
    {
        i2cMasterStart();
        i2cMasterSend(0xA2);
        i2cMasterStop();
    }
}
