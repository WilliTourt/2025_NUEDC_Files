#pragma once

#include "ti_msp_dl_config.h"

#define GW_GRAY_ADDR_DEF      0x4C
#define GW_GRAY_PING          0xAA
#define GW_GRAY_DIGITAL_MODE  0xDD

#define GW_GRAY_PING_OK       0x66

class GWtracker {
    public:
        enum class GW_Turning_Info {
            ninty_left,
            straight
        };

        GWtracker(I2C_Regs* I2C_PORT);

        bool ping();
        uint8_t getDigital();

    private:
        I2C_Regs* I2C_PORT_;
        bool readBytes(uint8_t slaveAddress, uint8_t regAddress, uint8_t* result, uint8_t len);
};
