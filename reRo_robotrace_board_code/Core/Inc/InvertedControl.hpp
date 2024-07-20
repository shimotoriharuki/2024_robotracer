/*
 * InvertedControl.hpp
 *
 *  Created on: 2024/07/20
 *      Author: SHIMOTORI Haruki
 */

#ifndef INC_INVERTEDCONTROL_HPP_
#define INC_INVERTEDCONTROL_HPP_

#include "Motor.hpp"
#include "Encoder.hpp"
#include "IMU.hpp"
#include "globalDefine.h"

class InvertedControl{
private:
	float kp_, ki_, kd_;
	bool i_reset_flag_;
	bool processing_flag_;
	float ratio_;
	DriveMotor *motor_;
	Encoder *encoder_;
	IMU *imu_;

	float calcError();
	void pid();

public:
	InvertedControl(DriveMotor *, Encoder *, IMU *);
	void flip();
	void setPIDGain(float, float, float);
	void start();
	void stop();


};




#endif /* INC_INVERTEDCONTROL_HPP_ */
