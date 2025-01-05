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
float mon_robot_angle_acc, mon_robot_angle_gyro;
float mon_omega_x, mon_omega_y, mon_omega_z;
float mon_offset_x, mon_offset_y, mon_offset_z;

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

	xg_ = xg;
	yg_ = yg;

	static int16_t pre_zg;
	zg_ = int((R_IMU)*(zg) + (1.0 - (R_IMU))* (pre_zg)); // lowpath filter

	pre_zg = zg_;
	mon_zg= zg_;

	//各速度に変換
	float omega_x_raw_ = -(xg_ / 16.4) * PI / 180;
	float omega_y_raw_ = -(yg_ / 16.4) * PI / 180;
	float omega_z_raw_ = -(zg_ / 16.4) * PI / 180;

	//オフセットを考慮
	omega_x_ = omega_x_raw_; //カルマンフィルタの中でオフセットを考慮しているのここではオフセットを引かない
	omega_y_ = omega_y_raw_ - offset_y_;
	omega_z_ = omega_z_raw_ - offset_z_;

	mon_omega_x= omega_x_;
	mon_omega_y= omega_y_;
	mon_omega_z= omega_z_;

	theta_ += omega_z_ * DELTA_T;
	theta_10mm_ += omega_z_ * DELTA_T;
	mon_theta = theta_;

	robot_angle_from_gyro_ += (omega_x_ - offset_x_) * DELTA_T;
	mon_robot_angle_gyro = robot_angle_from_gyro_;

	if(ya == 0) ya = 1e-9;
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
	float omega_x_sum;
	float omega_y_sum;
	float omega_z_sum;

	for(uint16_t i = 0; i < num; i++){
		omega_x_sum += omega_x_;
		omega_y_sum += omega_y_;
		omega_z_sum += omega_z_;
		HAL_Delay(1);
	}

	offset_x_ = omega_x_sum / num;
	offset_y_ = omega_y_sum / num;
	offset_z_ = omega_z_sum / num;

	mon_offset_x = offset_x_;
	mon_offset_y = offset_y_;
	mon_offset_z = offset_z_;
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

void IMU::resetRobotAngleFromAcc()
{
	robot_angle_from_acc_ = 0;
}

float IMU::getRobotAngleFromGyro()
{
	return robot_angle_from_gyro_;
}

void IMU::resetRobotAngleFromGyro()
{
	robot_angle_from_gyro_ = 0;
}

float IMU::getOmegaXOffset()
{
	return offset_x_;
}
