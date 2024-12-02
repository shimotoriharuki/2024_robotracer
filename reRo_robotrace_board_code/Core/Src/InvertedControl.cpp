/*
 * InvertedControl.cpp
 *
 *  Created on: 2024/07/20
 *      Author: SHIMOTORi HARUKI
 */

#include "InvertedControl.hpp"
#include "kalmanFilter.h"
#include <cmath>
#include "getEquationOfStateParameters2.h"
#include "getServoEquationOfStateParameters.h"
#include "stateFeedback.h"
#include "servoStateFeedback.h"
#include <cmath>

float mon_angle_diff;
double mon_estimated_robot_theta;
double mon_inverted_left_duty, mon_inverted_right_dity;
double mon_input;
double mon_theta_p, mon_dtheta_p, mon_theta_w, mon_dtheta_w;
double mon_z;
double mon_target_theta, mon_target_omega;
bool mon_fall_down;
double mon_estimate_theta;

//f_{-22.2690, -2.5254, -0.1171, -0.3624}
//-26.5862, -3.2078, -0.2540, -0.4977


InvertedControl::InvertedControl(DriveMotor *motor, Encoder *encoder, IMU *imu): kp_(0), ki_(0), kd_(0), i_reset_flag_(0),
		pre_P_{0.1*M_PI/180, 0, 0, 6.3e-06}, pre_theta_(0), U_(6.3e-06), W_(2.2e-05), estimated_robot_theta_(0), //U: 角速度の分散, W: 角度の分散
		pre_xb_{0, 0, 0, 0}, xb_{0, 0, 0, 0}, dt_(1e-3), input_(0), target_theta_(0), z_(0), current_voltage_(8.4), target_omega_(0), target_velocity_(0),
		pre_target_theta_(0), pre_z_(0), pre_input_(0), disturbance_{0, 0, 0, 0}, f_{-50, -5.2}, k_(-0.2500),
		debug_flag_(false)
{
	motor_ = motor;
	encoder_ = encoder;
	imu_ = imu;

	getEquationOfStateParameters2(m_w_,  m_p_,  r_w_, r_p_,  J_w_,  J_p_, J_m_,  g_,  n_,  kt_, kn_,  R_,  Ab_, Bb_,  C_);
}

//--------------------------------private----------------//

float InvertedControl::calcError()
{
	//float diff = imu_->getRobotAngleFromGyro() - 0;
	float diff = estimated_robot_theta_ - 0;
	mon_angle_diff = diff;

	return diff;
}

//void InvertedControl::pid()
//{
//	float diff = calcError();
//	static float pre_diff = 0;
//	float p, d;
//	static float i;
//
//	if(i_reset_flag_ == true){
//		i = 0;
//		pre_diff = 0;
//		i_reset_flag_ = false;
//	}
//
//	p = kp_ * diff;
//	i += ki_ * diff * DELTA_T;
//	d = kd_ * (diff - pre_diff) / DELTA_T;
//
//	linefollowing_ratio_ = p + i + d;
//	//motor_->setDuty(ratio_, ratio_);
//	pre_diff = diff;
//}

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
		//倒立制御
		double P[4];
		estimateRobotAngle(1e-3, double(imu_->getOmegaXOffset()), pre_P_, pre_theta_, U_, W_, double(imu_->getOmegaX()), double(imu_->getRobotAngleFromAcc()), &estimated_robot_theta_, P);
		mon_estimated_robot_theta = estimated_robot_theta_;

		for(uint8_t i = 0; i < 4; i++){
			pre_P_[i] = P[i];
		}

		stateFeedbackControl(estimated_robot_theta_, imu_->getOmegaX(), encoder_->getTheta(), encoder_->getDTheta());
		mon_theta_p = estimated_robot_theta_;
		mon_dtheta_p = imu_->getOmegaX();
		mon_theta_w = encoder_->getTheta();
		mon_dtheta_w = encoder_->getDTheta();
		mon_target_theta = target_theta_;
		mon_target_omega = target_omega_;


		if(debug_flag_ == true){
			motor_->setDuty(inverted_left_duty_ + target_velocity_, inverted_right_duty_ + target_velocity_);
		}
	}
}

void InvertedControl::stateFeedbackControl(double theta_p, double dtheta_p, double theta_w, double dtheta_w)
{
	//double x[4] = {theta_p, dtheta_p, theta_w, dtheta_w};
	double x[2] = {theta_p, dtheta_p};

	//input_ = servoStateFeedback(x, z_, f_, k_);
	input_ = stateFeedback(x, f_);

	//double dz = -x[0] - x[1] - x[2] - x[3] + target_theta;
	//z_ = z_ + dz * DELTA_T;
	//mon_z = z_;

	//pre_input_ = input_;
	//pre_target_theta_ = target_theta_;
	//for(uint8_t i = 0; i < 4; i++){
	//	pre_xb_[i] = xb_[i];
	//}
	//pre_z_ = z_;

	inverted_left_duty_ = (input_/current_voltage_) * 1000;
	inverted_right_duty_ = (input_/current_voltage_) * 1000;

	//double offset_v = 0.0; //0.5
	//if(inverted_left_duty_ > 0) inverted_left_duty_ += (offset_v / current_voltage_) * 1000;
	//else if(inverted_left_duty_ < 0) inverted_left_duty_ -= (offset_v / current_voltage_) * 1000;
	//if(inverted_right_duty_ > 0) inverted_right_duty_ += (offset_v / current_voltage_) * 1000;
	//else if(inverted_right_duty_ < 0) inverted_right_duty_ -= (offset_v / current_voltage_) * 1000;

	mon_input = input_;
	mon_inverted_left_duty = inverted_left_duty_;
	mon_inverted_right_dity = inverted_right_duty_;

	//motor_->setDuty(left_duty_, right_duty_);
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
	z_ = 0;
	target_theta_ = 0;
	target_omega_ = 0;
	//pre_theta_ = 0;
	input_ = 0;
	estimated_robot_theta_ = 0;

	encoder_->clearTheta();
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

void InvertedControl::setTargetOmega(double target_omega)
{
	target_omega_ = target_omega;
}

void InvertedControl::setTargetVelocity(double target_velocity)
{
	target_velocity_ = target_velocity;
}


bool InvertedControl::fallDown()
{
	bool fall_down = false;

	if(estimated_robot_theta_ >= FALL_DOWN_THETA || -FALL_DOWN_THETA >= estimated_robot_theta_){
		fall_down = true;
	}

	mon_fall_down = fall_down;

	return fall_down;
}

void InvertedControl::getDytu(double *left, double *right)
{
	*left = inverted_left_duty_;
	*right = inverted_right_duty_;

}

void InvertedControl::setDebugMode()
{
	debug_flag_ = true;
}

void InvertedControl::resetDebugMode()
{
	debug_flag_ = false;
}

void InvertedControl::getStateVariables(double *theta_p, double *dtheta_p, double *theta_w, double *dtheta_w)
{
	*theta_p = estimated_robot_theta_;
	*dtheta_p = imu_->getOmegaX();
	*theta_w = encoder_->getTheta();
	*dtheta_w = encoder_->getDTheta();
}
