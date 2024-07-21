/*
 * IMU.hpp
 *
 *  Created on: Jun 21, 2023
 *      Author: SHIMOTORI Haruki
 */

#ifndef INC_IMU_HPP_
#define INC_IMU_HPP_

#include "stm32f4xx_hal.h"

#define R_IMU 0.1 //0.03 Lowpath filter constant. The smaller it is, the more effective/

class IMU{
private:
	int16_t xa_, ya_, za_, xg_, yg_, zg_;
	float omega_x_;
	float omega_y_;
	float omega_z_;
	float offset_x_;
	float offset_y_;
	float offset_z_;
	float theta_;
	float theta_10mm_;
	float robot_angle_from_acc_;
	float robot_angle_from_gyro_;

public:
	IMU();
	uint8_t init();
	void updateValues();
	float getOmegaX();
	float getOmegaY();
	float getOmegaZ();
	void calibration();

	float getOffsetVal();

	float getTheta();

	void correctionTheta(float);
	void clearTheta();

	float getTheta10mm();
	void clearTheta10mm();

	float getRobotAngleFromAcc();
	void resetRobotAngleFromAcc();

	float getRobotAngleFromGyro();
	void resetRobotAngleFromGyro();

	float getOmegaXOffset();


};




#endif /* INC_IMU_HPP_ */
