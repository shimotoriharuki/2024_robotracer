/*
 * IMU.cpp
 *
 *  Created on: Jun 21, 2023
 *      Author: SHIMOTORI Haruki
 */


#include "IMU.hpp"
#include "MPU6500.h"
#include "globalDefine.h"
#include <cmath>

float mon_zg, mon_theta;
float mon_robot_angle_acc;
float mon_omega_x, mon_omega_y, mon_omega_z;

IMU::IMU() : xa_(0), ya_(0), za_(0), xg_(0), yg_(0), zg_(0),
		omega_x_(0), omega_y_(0), omega_z_(0), offset_x_(0), offset_y_(0), offset_z_(0),
		theta_(0), theta_10mm_(0), robot_angle_from_acc_(0), robot_angle_from_gyro_(0)
{

}

uint8_t IMU::init()
{
	uint8_t who_i_am;
	who_i_am = IMU_init();

	return who_i_am;

}

void IMU::updateValues()
{
	read_gyro_data();
	read_accel_data();

	static int16_t pre_zg;
	zg_ = int((R_IMU)*(zg) + (1.0 - (R_IMU))* (pre_zg)); // lowpath filter

	pre_zg = zg_;
	mon_zg= zg_;

	float corrected_xg = float(xg_) - offset_x_;
	float corrected_yg = float(yg_) - offset_y_;
	float corrected_zg = float(zg_) - offset_z_;
	omega_x_ = -(corrected_xg / 16.4) * PI / 180;
	omega_y_ = -(corrected_yg / 16.4) * PI / 180;
	omega_z_ = -(corrected_zg / 16.4) * PI / 180;
	mon_omega_x= omega_x_;
	mon_omega_y= omega_y_;
	mon_omega_z= omega_z_;

	theta_ += omega_z_ * DELTA_T;
	theta_10mm_ += omega_z_ * DELTA_T;
	mon_theta = theta_;

	if(ya == 0) ya = 1e-3;
	robot_angle_from_acc_ = std::atan2(ya, -za) + M_PI / 2;
	mon_robot_angle_acc = robot_angle_from_acc_;
}

float IMU::getOmegaX()
{
	return omega_x_;
}

float IMU::getOmegaY()
{
	return omega_y_;
}

float IMU::getOmegaZ()
{
	return omega_z_;
}

void IMU::calibration()
{
	int16_t num = 2000;
	float xg_sum;
	float yg_sum;
	float zg_sum;
	for(uint16_t i = 0; i < num; i++){
		xg_sum += float(xg_);
		yg_sum += float(yg_);
		zg_sum += float(zg_);
		HAL_Delay(1);
	}

	offset_x_ = xg_sum / num;
	offset_y_ = yg_sum / num;
	offset_z_ = zg_sum / num;
}

float IMU::getOffsetVal()
{
	return offset_z_;
}

float IMU::getTheta()
{
	return theta_;
}

void IMU::correctionTheta(float theta)
{
	theta_ = theta;
}

void IMU::clearTheta()
{
	theta_ = 0;
}
float IMU::getTheta10mm()
{
	return theta_10mm_;
}

void IMU::clearTheta10mm()
{
	theta_10mm_ = 0;
}

float IMU::getRobotAngleFromAcc()
{
	return robot_angle_from_acc_;
}

void IMU::clearRobotAngleFromAcc()
{
	robot_angle_from_acc_ = 0;
}

float IMU::getRobotAngleFromGyro()
{
	return robot_angle_from_gyro_;
}

void IMU::clearRobotAngleFromGyro()
{
	robot_angle_from_gyro_ = 0;
}
