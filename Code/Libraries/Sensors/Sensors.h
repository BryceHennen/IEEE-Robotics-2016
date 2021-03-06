#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <EEPROM.h>
#include <SPI.h>
#include <PixySPI_SS.h>
#include <Wire.h>
#include <L3G.h>

struct VisualSensorConfig
{
	byte pixy_ss;
	int center; //Where the robot aims for in PID control. Also affects score of blocks
	float block_score_consts[2]; //These values are the weights used to determine a blocks score
	float min_block_score;
	float min_block_size;

	//victim scanning
	unsigned int min_good_bad_ratio; //ratio needed for the pixy to successfully confirm a victim is present in its view
	unsigned long pixy_scan_time; //how long to scan for victim

	byte victim_sensor_pin; //IR receiver
	byte victim_emitter_pin; //IR LED
	word victim_sensor_frequency;
	unsigned long ir_scan_time;
};

/**
 * Class that contains sensors and functions to be used to visually locate and detect a block in front of the robot.
 */
class VisualSensor
{
public:
	/**
	* Variables
	*/

	VisualSensorConfig config;
	//Variable that is a "bad block", used when we find no good blocks
	const Block BAD_BLOCK = {-1, -1, -1, -1, -1, -1};

	/**
	 * Functions
	 */

	//Constructor
	VisualSensor(VisualSensorConfig config);

	//Destructor
	~VisualSensor();

	//Check if the target block is valid.
	bool IsGoodBlock(Block target_block);

	/**
	* Determines the score of a block. Bigger, lower blocks that are close to the center will get the highest score
	*/
	float GetBlockScore(Block block, boolean print);

	/**
	 * Find the correct block to go to. Returns BAD_BLOCK if no good blocks to go to.
	 */
	Block GetBlock();

	/**
	* Returns the count of the block signature that the GetBlock method saw most often,
	* and resets the counts back to 0 if desired
	*/
	byte GetBlockSignature(boolean resetCounts);

	//Scans (using the Pixy) for a victim in front of the robot and returns a number depending on situation:
	//0: Scan completed and no victim
	//1: Scan completed and victim
	//2: Scan uncompleted
	byte ScanForVictim();

	//Return whether or not there is a victim in the cutout of the robot
	bool HasVictim();

	//return center value 
	int GetCenter();

private:
	/**
	* Variables
	*/

	/* Pixy Variables */
	PixySPI_SS* pixy_; //Variable for pixy camera
	int blockCounts_[2]; //Record how many times we've seen each block signature
	int center_; //Where the robot aims for in PID control. Also affects score of blocks
	float center_const_;
	float bottom_line_const_;
	float min_block_score_;
	float min_block_size_;

	unsigned long timer_ = 0UL;

	//variables for scanning
	unsigned int num_good_scanned_ = 0;
	unsigned int num_bad_scanned_ = 0;
	unsigned int min_good_bad_ratio_;
	unsigned long pixy_scan_time_;

	byte victim_sensor_pin_;
	byte victim_emitter_pin_;
	word victim_sensor_frequency_;
	unsigned long ir_scan_time_;
	/**
	* Functions
	*/

	/**
	* Increments how many times we've seen the given block
	*/
	void IncrementBlocks(Block block);
};

/**
 * Struct for the Calibration Data for the gyro_.
 */
struct CalibrationData
{
	float averageBiasZ;
	float sigmaZ;
	float scaleFactorZ;
};

struct GyroConfig
{
	byte threshold_size; //2<x<31

	//Gyro pins
	byte cs;
	byte sdo;
	byte sda;
	byte scl;
};

/**
 * The gyro_ allows you to get the current heading of the robot in degrees.
 */
class Gyro
{
public:
	//Constructor
	Gyro(GyroConfig config);

	//Destructor
	~Gyro();

	/**
	 * Returns the current heading of the robot in degrees, based on the initial heading of the robot. (0 <= degrees < 360)
	 */
	float GetDegrees();

	/**
	 * Updates the current angle read by the l3g_gyro_. Should be called every loop. Takes in the current time of the loop in millis().
	 */
	inline void Update()
	{
		l3g_gyro_.fresh_data = true;
	};

	bool Calibrate();

	float offset_angle; //Angle how much the gyro_ is offset

	L3G l3g_gyro_;
	CalibrationData calibration;
private:
	float angleZ_;
	unsigned long previous_time;
	unsigned long sample_time;

	void TransformData();
};

struct WallSensorsConfig
{
	byte front_left_sensor_pin;
	byte front_right_sensor_pin;
	byte rear_left_sensor_pin;
	byte rear_right_sensor_pin;
	byte forward_sensor_pin;
};

enum SensorPosition
{
	FRONT_LEFT,
	FRONT_RIGHT,
	REAR_LEFT,
	REAR_RIGHT,
	FORWARD
};

class WallSensors
{
public:
	// Variables ///////////////////////////

	WallSensorsConfig config;

	// Functions ///////////////////////////

	//Constructor
	WallSensors(WallSensorsConfig wall_sensors_config);

	//Destructor
	~WallSensors();

	//Read value from one of the IR sensors and convert it to cm.
	float ReadSensor(SensorPosition pos);

private:
	// Variables ///////////////////////////

	// Functions ///////////////////////////

};

#endif