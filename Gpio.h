
/**
 * 
 */
 
#ifndef __RASPBERRY_GPIO_H__
#define __RASPBERRY_GPIO_H__ 1

#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

#include <Bcm2835.h>

#define GPIO_ADDRESS                        0x200000

#define INPUT                               0
#define OUTPUT                              1
#define LOW                                 0
#define HIGH                                1

#define USE_RW_BARRIER                      0

/* FSEL */
#define BCM2835_FSEL_MASK                    0x000007 // Function select bits mask
#define BCM2835_GPFSEL0                      0x000000 // GPIO Function Select 0
#define BCM2835_GPFSEL1                      0x000004 // GPIO Function Select 1
#define BCM2835_GPFSEL2                      0x000008 // GPIO Function Select 2
#define BCM2835_GPFSEL3                      0x00000c // GPIO Function Select 3
#define BCM2835_GPFSEL4                      0x000010 // GPIO Function Select 4
#define BCM2835_GPFSEL5                      0x000014 // GPIO Function Select 5
#define BCM2835_GPSET0                       0x00001c // GPIO Pin Output Set 0
#define BCM2835_GPSET1                       0x000020 // GPIO Pin Output Set 1
#define BCM2835_GPCLR0                       0x000028 // GPIO Pin Output Clear 0
#define BCM2835_GPCLR1                       0x00002c // GPIO Pin Output Clear 1
#define BCM2835_GPLEV0                       0x000034 // GPIO Pin Level 0
#define BCM2835_GPLEV1                       0x000038 // GPIO Pin Level 1
#define BCM2835_GPEDS0                       0x000040 // GPIO Pin Event Detect Status 0
#define BCM2835_GPEDS1                       0x000044 // GPIO Pin Event Detect Status 1
#define BCM2835_GPREN0                       0x00004c // GPIO Pin Rising Edge Detect Enable 0
#define BCM2835_GPREN1                       0x000050 // GPIO Pin Rising Edge Detect Enable 1
#define BCM2835_GPFEN0                       0x000048 // GPIO Pin Falling Edge Detect Enable 0
#define BCM2835_GPFEN1                       0x00005c // GPIO Pin Falling Edge Detect Enable 1
#define BCM2835_GPHEN0                       0x000064 // GPIO Pin High Detect Enable 0
#define BCM2835_GPHEN1                       0x000068 // GPIO Pin High Detect Enable 1
#define BCM2835_GPLEN0                       0x000070 // GPIO Pin Low Detect Enable 0
#define BCM2835_GPLEN1                       0x000074 // GPIO Pin Low Detect Enable 1
#define BCM2835_GPAREN0                      0x00007c // GPIO Pin Async. Rising Edge Detect 0
#define BCM2835_GPAREN1                      0x000080 // GPIO Pin Async. Rising Edge Detect 1
#define BCM2835_GPAFEN0                      0x000088 // GPIO Pin Async. Falling Edge Detect 0
#define BCM2835_GPAFEN1                      0x00008c // GPIO Pin Async. Falling Edge Detect 1
#define BCM2835_GPPUD                        0x000094 // GPIO Pin Pull-up/down Enable
#define BCM2835_GPPUDCLK0                    0x000098 // GPIO Pin Pull-up/down Enable Clock 0
#define BCM2835_GPPUDCLK1                    0x00009c // GPIO Pin Pull-up/down Enable Clock 1

class GpioRPi {
    
    Bcm2835::Peripheral gpio;
    
public:

    void begin();

    void stop();
    
    void pinMode(unsigned char pin, bool mode);
    
    void digitalWrite(unsigned char pin, bool value);
    
    bool digitalRead(unsigned char pin);
    
    void setPin(unsigned char pin);
    
    void clearPin(unsigned char pin);
    
private:

    void configureBits(volatile unsigned int* address, unsigned int value, unsigned int mask);

    unsigned int safeRead(volatile unsigned int* address);
    
    void safeWrite(volatile unsigned int* address, unsigned int value);
};

extern GpioRPi Gpio;

#endif /* __RASPBERRY_GPIO_H__ */
