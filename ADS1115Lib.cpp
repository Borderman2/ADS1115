#include "ADS1115Lib.h"
#include "hardware/i2c.h"



float ADS1115::RawToVoltage(int16_t raw)
{
    switch (m_Settings.PGA)
    {
    case 0:
        return raw * (6.144f / 32768.0f);
    case 512:
        return raw * (4.096f / 32768.0f);
    case 1024:
        return raw * (2.048f / 32768.0f);
    case 1536:
        return raw * (1.024f / 32768.0f);
    case 2048:
        return raw * (0.512f / 32768.0f);
    case 2560:
        return raw * (0.256f / 32768.0f);
    default:
        return 0;
    }
}

ADS1115::ADS1115(){
    i2c_init(i2c0, 100000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);
}

ADS1115::ADS1115(int pins[],uint16_t size){

    i2c_init(i2c0, 100000);

    for (int i = 0; i < size; ++i) {
        gpio_set_function(pins[i], GPIO_FUNC_I2C);
        gpio_pull_up(pins[i]);
    }
}

ADS1115::~ADS1115(){

}

int16_t ADS1115::ReadRaw(uint8_t channel)
{
    uint16_t config = 0;

    // Start conversion Single-Shot
    config |= m_Settings.OS;

    // Wähle Kanal AIN
    config |= ((0x4 + channel) << 12);

    // PGA = ±4.096V
    config |= m_Settings.PGA;

    // Single-Shot
    config |= m_Settings.Mode;

    // Data Rate 128 SPS
    config |= m_Settings.DataRate;

    // Comparator off
    config |= m_Settings.Comparator;  // Beispiel

    // 2. Config ins ADS schreiben
    uint8_t cfg[3];
    cfg[0] = 0x01;                 // Config-Register
    cfg[1] = config >> 8;          // High Byte
    cfg[2] = config & 0xFF;        // Low Byte

    i2c_write_blocking(i2c0, m_Settings.Address, cfg, 3, false);

    if (m_Settings.Mode == ADS_MODE_SINGLESHOT)
    {

        switch (m_Settings.DataRate)
        {
            case ADS_DR_8SPS:   sleep_ms(125); break;
            case ADS_DR_16SPS:  sleep_ms(63);  break;
            case ADS_DR_32SPS:  sleep_ms(32);  break;
            case ADS_DR_64SPS:  sleep_ms(16);  break;
            case ADS_DR_128SPS: sleep_ms(8);   break;
            case ADS_DR_250SPS: sleep_ms(4);   break;
            case ADS_DR_475SPS: sleep_ms(3);   break;
            case ADS_DR_860SPS: sleep_ms(2);   break;
            default:            sleep_ms(125); break;
        }
    }   

    //printf("DATA RATE : %d",m_Settings.DataRate);
    // 4. Messwert lesen
    uint8_t reg = 0x00;            // Conversion-Register
    uint8_t data[2];

    i2c_write_blocking(i2c0, m_Settings.Address, &reg, 1, true);
    i2c_read_blocking(i2c0, m_Settings.Address, data, 2, false);

    // 5. Signed 16-bit zurückgeben
    return (int16_t)((data[0] << 8) | data[1]);
}
