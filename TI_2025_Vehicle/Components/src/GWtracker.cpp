#include "GWtracker.h"

GWtracker::GWtracker(I2C_Regs* I2C_PORT) : I2C_PORT_(I2C_PORT) {}

bool GWtracker::readBytes(uint8_t slaveAddress, uint8_t regAddress, uint8_t* result, uint8_t len) {
    uint8_t temp[1] = {regAddress};
    
    // Write register address
    DL_I2C_fillControllerTXFIFO(I2C_PORT_, temp, 1);
    while (!(DL_I2C_getControllerStatus(I2C_PORT_) & DL_I2C_CONTROLLER_STATUS_IDLE));
    DL_I2C_startControllerTransfer(I2C_PORT_, slaveAddress, DL_I2C_CONTROLLER_DIRECTION_TX, 1);
    while (DL_I2C_getControllerStatus(I2C_PORT_) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
    while (!(DL_I2C_getControllerStatus(I2C_PORT_) & DL_I2C_CONTROLLER_STATUS_IDLE));
    DL_I2C_flushControllerTXFIFO(I2C_PORT_);

    // Read data
    DL_I2C_startControllerTransfer(I2C_PORT_, slaveAddress, DL_I2C_CONTROLLER_DIRECTION_RX, len);
    while (DL_I2C_getControllerStatus(I2C_PORT_) & DL_I2C_CONTROLLER_STATUS_BUSY_BUS);
    while (!(DL_I2C_getControllerStatus(I2C_PORT_) & DL_I2C_CONTROLLER_STATUS_IDLE));
    
    for (uint8_t i = 0; i < len; i++) {
        result[i] = DL_I2C_receiveControllerData(I2C_PORT_);
    }
    
    return true;
}

bool GWtracker::ping() {
    uint8_t dat;
    readBytes(GW_GRAY_ADDR_DEF << 1, GW_GRAY_PING, &dat, 1);
	if (dat==GW_GRAY_PING_OK){
		return 0;
    } else {
        return 1;
    }
}

uint8_t GWtracker::getDigital() {
    uint8_t dat;
    readBytes(GW_GRAY_ADDR_DEF << 1, GW_GRAY_DIGITAL_MODE, &dat, 1);
    return dat;
}
