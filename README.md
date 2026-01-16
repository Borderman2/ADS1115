How to use this class

```cpp

//Include the "ADS1115Lib.h" file
#include "ADS1115Lib.h"

//Create the Class
ADS1115 ads;
```
```cpp
//U can also create it with pins specified
//if you have it not connected to the default gpio pins (GP4/GP5)
ADS1115 ads(pins[x],size);
```
```cpp
//To use this class there are two functions you need to use
ads.ReadRaw(ch)
ads.RawToVoltage();

//ch is the channel you want to read from it is a (int)
// 0 = AIN0
// 1 = AIN1
// 2 = AIN2
// 3 = AIN3 
float v = ads.RawToVoltage(ads.ReadRaw(ch));
```
```cpp
//if you have multiple ads1115 you can change the address of them by doing this
ads.m_Settings.Address = ADS_ADDR_VDD;
//These are the other options
    //ADS_ADDR_DEFAULT = 0x48,
    //ADS_ADDR_GND = 0x48,
    //ADS_ADDR_VDD = 0x49,
    //ADS_ADDR_SDA = 0x4A,
    //ADS_ADDR_SCL = 0x4B

//These are all the settings you can change with ads.m_Settings
    ADS_ADDRESSES_ENUMS Address = ADS_ADDR_DEFAULT;
    ADS_DR_SPS_ENUMS DataRate = ADS_DR_DEFAULT_SPS;
    ADS_PGA_ENUMS PGA = ADS_PGA_DEFAULT;
    ADS_MODES_ENUMS Mode = ADS_MODE_SINGLESHOT;
    ADS_OS_ENUMS OS = ADS_OS_START_CONVERSION;
    ADS_COMP_ENUMS Comparator = ADS_COMP_DISABLE;

/*Her is the rest of the settings you can change*/
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

    ADS_DR_DEFAULT_SPS = (0x4 << 5),
    ADS_DR_8SPS = (0x0 << 5),
    ADS_DR_16SPS = (0x1 << 5),
    ADS_DR_32SPS = (0x2 << 5),
    ADS_DR_64SPS = (0x3 << 5),
    ADS_DR_128SPS = (0x4 << 5), 
    ADS_DR_250SPS = (0x5 << 5),
    ADS_DR_475SPS = (0x6 << 5),
    ADS_DR_860SPS = (0x7 << 5)

    ADS_MODE_SINGLESHOT = (1 << 8),
    ADS_MODE_CONTINUOUS = (0 << 8)

#define ADS_PGA_SHIFT 9

    ADS_PGA_DEFAULT = (0x1 << ADS_PGA_SHIFT),
    ADS_PGA_6_144V = (0x0 << ADS_PGA_SHIFT),
    ADS_PGA_4_096V = (0x1 << ADS_PGA_SHIFT),
    ADS_PGA_2_048V = (0x2 << ADS_PGA_SHIFT),
    ADS_PGA_1_024V = (0x3 << ADS_PGA_SHIFT),
    ADS_PGA_0_512V = (0x4 << ADS_PGA_SHIFT),
    ADS_PGA_0_256V = (0x5 << ADS_PGA_SHIFT)

    ADS_OS_START_CONVERSION = (1 << 15),
    ADS_OS_NOEFFECT = (0 << 15)

```
