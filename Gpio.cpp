
#include "Gpio.h"

void GpioRPi::begin() {
    gpio.address = GPIO_ADDRESS;
    Bcm2835::mapPeripheral(&gpio);
}

void GpioRPi::stop() {
    Bcm2835::unmapPeripheral(&gpio);
}

void GpioRPi::digitalWrite(unsigned char pin, bool value) {
    volatile unsigned int* address = (unsigned int*)gpio.mem + ((value) ? BCM2835_GPSET0 : BCM2835_GPCLR0) / 4 + pin / 32;
    unsigned char shift = pin % 32;
    safeWrite(address, 0x000001 << shift);
}

bool GpioRPi::digitalRead(unsigned char pin) {
    volatile unsigned int* address = (unsigned int*)gpio.mem + BCM2835_GPLEV0 / 4 + pin / 32;
    unsigned char shift = pin % 32;
    unsigned int v = safeRead(address);
    return (v & (1 << shift)) ? HIGH : LOW;
}
    
void GpioRPi::setPin(unsigned char pin) {
    digitalWrite(pin, HIGH)
}

void GpioRPi::clearPin(unsigned char pin) {
    digitalWrite(pin, LOW)
}

void GpioRPi::pinMode(unsigned char pin, bool mode) {
    volatile unsigned int* address = (unsigned int*)gpio.mem + BCM2835_GPFSEL0 / 4 + (pin / 10);
    unsigned char shift = (pin % 10) * 3;
    unsigned int mask = BCM2835_FSEL_MASK << shift;
    unsigned int value = (mode) ? (0x000001 << shift) : 0x000000;
    configureBits(address, value, mask);
}

void GpioRPi::configureBits(volatile unsigned int* address, unsigned int value, unsigned int mask) {
    unsigned int v = safeRead(address);
    v = (v & ~mask) | (value & mask);
    safeWrite(address, v);
}

unsigned int GpioRPi::safeRead(volatile unsigned int* address) {
    unsigned int i = *address;
#if USE_RW_BARRIER == 1
    unsigned int dummy = *address;
#endif
    return i;
}

void GpioRPi::safeWrite(volatile unsigned int* address, unsigned int value) {
#if USE_RW_BARRIER == 1
    *address = value;
#endif
    *address = value;
}

GpioRPi Gpio;
