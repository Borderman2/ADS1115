#pragma once


#include <stdio.h>
#include "pico/stdlib.h"

//Die ADS Addresse
typedef enum {
    ADS_ADDR_DEFAULT = 0x48,
    ADS_ADDR_GND = 0x48,
    ADS_ADDR_VDD = 0x49,
    ADS_ADDR_SDA = 0x4A,
    ADS_ADDR_SCL = 0x4B
} ADS_ADDRESSES_ENUMS;

typedef enum {
    
    // COMP_QUE (Bits 1–0)
    ADS_COMP_ASSERT_1 = (0x0),
    ADS_COMP_ASSERT_2 = (0x1),
    ADS_COMP_ASSERT_4 = (0x2),
    ADS_COMP_DISABLE = (0x3),

    // COMP_LAT (Bit 2)
    ADS_COMP_NON_LATCHING = (0 << 2),
    ADS_COMP_LATCHING = (1 << 2),
    
    // COMP_POL (Bit 3)
    ADS_COMP_ACTIVE_LOW = (0 << 3),
    ADS_COMP_ACTIVE_HIGH = (1 << 3),

    // COMP_MODE (Bit 4)
    ADS_COMP_TRADITIONAL = (0 << 4),
    ADS_COMP_WINDOW = (1 << 4)




}   ADS_COMP_ENUMS;

/*
000b : 8SPS
001b : 16SPS
010b : 32SPS
011b : 64SPS
100b : 128SPS (default)
101b : 250SPS
110b : 475SPS
111b : 860SPS
*/

//Der 5 - 7 bit
typedef enum {
    ADS_DR_DEFAULT_SPS = (0x4 << 5),
    ADS_DR_8SPS = (0x0 << 5),
    ADS_DR_16SPS = (0x1 << 5),
    ADS_DR_32SPS = (0x2 << 5),
    ADS_DR_64SPS = (0x3 << 5),
    ADS_DR_128SPS = (0x4 << 5), 
    ADS_DR_250SPS = (0x5 << 5),
    ADS_DR_475SPS = (0x6 << 5),
    ADS_DR_860SPS = (0x7 << 5)
} ADS_DR_SPS_ENUMS;

//Welcher Modus
//Der 8 bit
typedef enum {
    ADS_MODE_SINGLESHOT = (1 << 8),
    ADS_MODE_CONTINUOUS = (0 << 8)
} ADS_MODES_ENUMS;

#define ADS_PGA_SHIFT 9

// mögliche Gains
//Der 9 - 11 bit
typedef enum {
    ADS_PGA_DEFAULT = (0x1 << ADS_PGA_SHIFT),
    ADS_PGA_6_144V = (0x0 << ADS_PGA_SHIFT),
    ADS_PGA_4_096V = (0x1 << ADS_PGA_SHIFT),
    ADS_PGA_2_048V = (0x2 << ADS_PGA_SHIFT),
    ADS_PGA_1_024V = (0x3 << ADS_PGA_SHIFT),
    ADS_PGA_0_512V = (0x4 << ADS_PGA_SHIFT),
    ADS_PGA_0_256V = (0x5 << ADS_PGA_SHIFT)
} ADS_PGA_ENUMS;

/*Operational status or single-shot conversion start
This bit determines the operational status of the device. OS can only be written
when in power-down state and has no effect when a conversion is ongoing.
When writing:
0b : No effect
1b : Start a single conversion (when in power-down state)
When reading:
0b : Device is currently performing a conversion.
1b : Device is not currently performing a conversion.*/
//Der 15 bit
typedef enum {
    ADS_OS_START_CONVERSION = (1 << 15),
    ADS_OS_NOEFFECT = (0 << 15)
} ADS_OS_ENUMS;


//Settings for the ads
struct ADS1115Settings {
    ADS_ADDRESSES_ENUMS Address = ADS_ADDR_DEFAULT;
    ADS_DR_SPS_ENUMS DataRate = ADS_DR_DEFAULT_SPS;
    ADS_PGA_ENUMS PGA = ADS_PGA_DEFAULT;
    ADS_MODES_ENUMS Mode = ADS_MODE_SINGLESHOT;
    ADS_OS_ENUMS OS = ADS_OS_START_CONVERSION;
    ADS_COMP_ENUMS Comparator = ADS_COMP_DISABLE;
};

class ADS1115 {
public:
ADS1115();
ADS1115(int pins[],uint16_t size);
~ADS1115();

int16_t ReadRaw(uint8_t channel);
float RawToVoltage(int16_t raw);

public:
ADS1115Settings m_Settings;

};