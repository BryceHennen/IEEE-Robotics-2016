#ifndef L3G_h
#define L3G_h

#include <Arduino.h> // for byte data type

#define L3GD20H_ID	0xD7
#define L3GD20_ADDRESS 0x6B

class L3G
{
public:

  // register addresses
	enum regAddr
	{
		WHO_AM_I = 0x0F,

		CTRL1 = 0x20, // D20H
		CTRL_REG1 = 0x20, // D20, 4200D
		CTRL2 = 0x21, // D20H
		CTRL_REG2 = 0x21, // D20, 4200D
		CTRL3 = 0x22, // D20H
		CTRL_REG3 = 0x22, // D20, 4200D
		CTRL4 = 0x23, // D20H
		CTRL_REG4 = 0x23, // D20, 4200D
		CTRL5 = 0x24, // D20H
		CTRL_REG5 = 0x24, // D20, 4200D
		REFERENCE = 0x25,
		OUT_TEMP = 0x26,
		STATUS = 0x27, // D20H
		STATUS_REG = 0x27, // D20, 4200D

		OUT_X_L = 0x28,
		OUT_X_H = 0x29,
		OUT_Y_L = 0x2A,
		OUT_Y_H = 0x2B,
		OUT_Z_L = 0x2C,
		OUT_Z_H = 0x2D,

		FIFO_CTRL = 0x2E, // D20H
		FIFO_CTRL_REG = 0x2E, // D20, 4200D
		FIFO_SRC = 0x2F, // D20H
		FIFO_SRC_REG = 0x2F, // D20, 4200D

		IG_CFG = 0x30, // D20H
		INT1_CFG = 0x30, // D20, 4200D
		IG_SRC = 0x31, // D20H
		INT1_SRC = 0x31, // D20, 4200D
		IG_THS_XH = 0x32, // D20H
		INT1_THS_XH = 0x32, // D20, 4200D
		IG_THS_XL = 0x33, // D20H
		INT1_THS_XL = 0x33, // D20, 4200D
		IG_THS_YH = 0x34, // D20H
		INT1_THS_YH = 0x34, // D20, 4200D
		IG_THS_YL = 0x35, // D20H
		INT1_THS_YL = 0x35, // D20, 4200D
		IG_THS_ZH = 0x36, // D20H
		INT1_THS_ZH = 0x36, // D20, 4200D
		IG_THS_ZL = 0x37, // D20H
		INT1_THS_ZL = 0x37, // D20, 4200D
		IG_DURATION = 0x38, // D20H
		INT1_DURATION = 0x38, // D20, 4200D

		LOW_ODR = 0x39  // D20H
	};

	float z; // gyro angular velocity readings for z
	volatile bool fresh_data = false;

	L3G();
	bool init(byte threshold_size, byte cs, byte sdo, byte sda, byte scl);

	void writeReg(byte reg, byte value);
	byte readReg(byte reg);

	bool read(void);

private:
	byte address;

	byte _cs;
	byte _miso;
	byte _mosi;
	byte _clk;

	uint8_t SPIxfer(uint8_t x);
};

#endif



