/*
 * InvertedControl.cpp
 *
 *  Created on: 2024/07/20
 *      Author: SHIMOTORi HARUKI
 */

#include "InvertedControl.hpp"
#include "kalmanFilter.h"
#include <cmath>
#include "getEquationOfStateParameters.h"
#include "servoStateFeedback.h"

float mon_angle_diff;
double mon_estimated_robot_theta;

InvertedControl::InvertedControl(DriveMotor *motor, Encoder *encoder, IMU *imu): kp_(0), ki_(0), kd_(0), i_reset_flag_(0),
		pre_P_{0.1*M_PI/180, 0, 0, 6.3e-06}, pre_theta_(0), U_(6.3e-06), W_(2.2e-05), estimated_robot_theta_(0), //U: 角速度の分散, W: 角度の分散
		pre_xb_{0, 0, 0, 0}, xb_{0, 0, 0, 0}, dt_(1e-3), input_(0), target_theta_(0), z_(0), current_voltage_(8.4), target_omega_(0),
		pre_target_theta_(0), pre_z_(0), pre_input_(0), disturbance_{0, 0, 0, 0}, f_{-2.6052e+03, -388.0362, -55.6586, -71.1086}, k_(-100)
{
	motor_ = motor;
	encoder_ = encoder;
	imu_ = imu;

	getEquationOfStateParameters(m_w_,  m_p_,  r_w_, r_p_,  J_w_,  J_p_, J_m_,  g_,  n_,  kt_, kn_,  R_,  Ab_, Bb_,  C_);
}

//--------------------------------private----------------//

float InvertedControl::calcError()
{
	//float diff = imu_->getRobotAngleFromGyro() - 0;
	float diff = estimated_robot_theta_ - 0;
	mon_angle_diff = diff;

	return diff;
}

void InvertedControl::pid()
{
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

void InvertedControl::estimateRobotAngle(double dt, double omega_offset, const double pre_P[4],
		double pre_theta, double U, double W, double omega,
		double theta, double *estimated_robot_theta,
		double P[4])
{
	kalmanFilter(dt, omega_offset, pre_P, pre_theta, U, W, omega, theta, estimated_robot_theta, P);

}

//--------------------------------public----------------//
void InvertedControl::flip()
{
	if(processing_flag_ == true){
		double P[4];

		estimateRobotAngle(1e-3, double(imu_->getOmegaXOffset()), pre_P_, pre_theta_, U_, W_, double(imu_->getOmegaX()), double(imu_->getRobotAngleFromAcc()), &estimated_robot_theta_, P);
		mon_estimated_robot_theta = estimated_robot_theta_;

		for(uint8_t i = 0; i < 4; i++){
			pre_P_[i] = P[i];
		}
		pre_theta_ = estimated_robot_theta_;

		//pid();
	}
}

void InvertedControl::stateFeedbackControl()
{
	servoStateFeedback(dt_, target_omega_, Ab_, Bb_, pre_target_theta_, pre_xb_, pre_z_, pre_input_, disturbance_, f_, k_, &input_, &target_theta_, xb_, &z_);
	pre_input_ = input_;
	pre_target_theta_ = target_theta_;
	for(uint8_t i = 0; i < 4; i++){
		pre_xb_[i] = xb_[i];
	}
	pre_z_ = z_;

	motor_->setDuty((input_/current_voltage_) * 1000, (input_/current_voltage_) * 1000);
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

void InvertedControl::resetEstimatedTheta()
{
	estimated_robot_theta_ = 0;
}



