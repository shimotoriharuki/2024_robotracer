/*
 * InvertedControl.cpp
 *
 *  Created on: 2024/07/20
 *      Author: SHIMOTORi HARUKI
 */

#include "InvertedControl.hpp"

float mon_angle_diff;

InvertedControl::InvertedControl(DriveMotor *motor, Encoder *encoder, IMU *imu): kp_(0), ki_(0), kd_(0), i_reset_flag_(0)
{
	motor_ = motor;
	encoder_ = encoder;
	imu_ = imu;
}

//--------------------------------private----------------//

float InvertedControl::calcError()
{
	float diff = imu_->getRobotAngleFromGyro() - 0;
	mon_angle_diff = diff;

	return diff;
}

void InvertedControl::pid()
{
	if(processing_flag_ == true){
		float diff = calcError();
		static float pre_diff = 0;
		float p, d;
		static float i;

		if(i_reset_flag_ == true){
			i = 0;
			pre_diff = 0;
			i_reset_flag_ = false;
		}

		p = kp_ * diff;
		i += ki_ * diff * DELTA_T;
		d = kd_ * (diff - pre_diff) / DELTA_T;

		ratio_ = p + i + d;
		motor_->setDuty(ratio_, ratio_);
		pre_diff = diff;
	}
}

//--------------------------------public----------------//
void InvertedControl::flip(){
	pid();
}

void InvertedControl::setPIDGain(float kp, float ki, float kd)
{
	kp_ = kp;
	ki_ = ki;
	kd_ = kd;
}

void InvertedControl::start()
{
	processing_flag_ = true;
	i_reset_flag_ = true;
}

void InvertedControl::stop()
{
	processing_flag_ = false;
	motor_->setDuty(0, 0);
}




