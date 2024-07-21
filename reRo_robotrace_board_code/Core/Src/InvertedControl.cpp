/*
 * InvertedControl.cpp
 *
 *  Created on: 2024/07/20
 *      Author: SHIMOTORi HARUKI
 */

#include "InvertedControl.hpp"
#include "kalmanFilter.h"
#include <cmath>

float mon_angle_diff;
double mon_estimated_robot_theta;

InvertedControl::InvertedControl(DriveMotor *motor, Encoder *encoder, IMU *imu): kp_(0), ki_(0), kd_(0), i_reset_flag_(0), pre_P_{1, 0, 0.1, 0}, pre_theta_(0), U_(1e-3), W_(1e-3), estimated_robot_theta_(0), P_{1e-3, 0, 1e-3, 0}
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

double InvertedControl::estimateRobotAngle(double dt, double omega_offset, const double pre_P[4],
		double pre_theta, double U, double W, double omega,
		double theta, double *estimated_robot_theta,
		double P[4])
{
	kalmanFilter(dt, omega_offset, pre_P, pre_theta, U, W, omega, theta, estimated_robot_theta, P);

	for(uint8_t i = 0; i < 4; i++){
		pre_P_[i] = P[i];
	}
	pre_theta_ = *estimated_robot_theta;

	return *estimated_robot_theta;
}

//--------------------------------public----------------//
void InvertedControl::flip(){
	estimateRobotAngle(1e-3, double(imu_->getOmegaXOffset()), pre_P_, pre_theta_, U_, W_, double(imu_->getOmegaX()), double(imu_->getRobotAngleFromAcc()), &estimated_robot_theta_, P_);
	mon_estimated_robot_theta = estimated_robot_theta_;

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




