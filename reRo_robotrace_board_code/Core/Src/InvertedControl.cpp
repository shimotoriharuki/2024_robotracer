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

//f_{-36.4462, -3.6192, -0.1414, -0.2448}

//		pre_target_theta_(0), pre_z_(0), pre_input_(0), disturbance_{0, 0, 0, 0}, f_{-24.5217, -1.9125, -0.00, -0.0871}, k_(0),

InvertedControl::InvertedControl(DriveMotor *motor, Encoder *encoder, IMU *imu): kp_(0), ki_(0), kd_(0), i_reset_flag_(0),
		pre_P_{0.1*M_PI/180, 0, 0, 6.3e-06}, pre_theta_(0), U_(6.3e-06), W_(2.2e-05), estimated_robot_theta_(0), //U: 角速度の分散, W: 角度の分散
		pre_xb_{0, 0, 0, 0}, xb_{0, 0, 0, 0}, dt_(1e-3), input_(0), target_theta_(0), z_(0), current_voltage_(8.4), target_omega_(0),
		pre_target_theta_(0), pre_z_(0), pre_input_(0), disturbance_{0, 0, 0, 0}, f_{F1_STOP, F2_STOP, F3_STOP, F4_STOP}, k_(0),
		debug_flag_(false)
{
	motor_ = motor;
	encoder_ = encoder;
	imu_ = imu;

	getServoEquationOfStateParameters(m_w_,  m_p_,  r_w_, r_p_,  J_w_,  J_p_, J_m_,  g_,  n_,  kt_, kn_,  R_,  Ab_, Bb_,  C_);
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

		pre_theta_ = estimated_robot_theta_;

		stateFeedbackControl(estimated_robot_theta_, imu_->getOmegaX(), encoder_->getTheta(), encoder_->getDTheta(), target_theta_);
		mon_theta_p = estimated_robot_theta_;
		mon_dtheta_p = imu_->getOmegaX();
		mon_theta_w = encoder_->getTheta();
		mon_dtheta_w = encoder_->getDTheta();
		mon_target_theta = target_theta_;
		mon_target_omega = target_omega_;


		if(debug_flag_ == true){
			motor_->setDuty(inverted_left_duty_, inverted_right_duty_);
		}
	}
}

void InvertedControl::stateFeedbackControl(double theta_p, double dtheta_p, double theta_w, double dtheta_w, double target_theta)
{
	double x[4] = {theta_p, dtheta_p, theta_w, dtheta_w};

	input_ = servoStateFeedback(x, z_, f_, k_, target_omega_);
	//input_ = stateFeedback(x, f_);

	double dz = -x[0] - x[1] - x[2] - x[3] + target_theta;
	z_ = z_ + dz * DELTA_T;
	mon_z = z_;

	double k = 162; //162: 8.4v

	inverted_left_duty_ = input_ * k;
	inverted_right_duty_ = input_ * k;

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
	pre_theta_ = 0;
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

void InvertedControl::getStateVariables(double *theta_p, double *dtheta_p, double *theta_w, double *dtheta_w, double *z)
{
	*theta_p = estimated_robot_theta_;
	*dtheta_p = imu_->getOmegaX();
	*theta_w = encoder_->getTheta();
	*dtheta_w = encoder_->getDTheta();
	*z= z_;
}

void InvertedControl::setRunFeedbackGain()
{
	resetAllState();
	f_[0] = F1_RUN;
	f_[1] = F2_RUN;
	f_[2] = F3_RUN;
	f_[3] = F4_RUN;
}

void InvertedControl::setStopFeedbackGain()
{
	resetAllState();
	f_[0] = F1_STOP;
	f_[1] = F2_STOP;
	f_[2] = F3_STOP;
	f_[3] = F4_STOP;
}


void InvertedControl::resetAllState()
{
	estimated_robot_theta_ = 0;
	imu_->resetOmegaX();
	encoder_->clearTheta();
	encoder_->clearDTheta();

	for(uint8_t i = 0; i < 4; i++){
		pre_P_[i] = 0;
	}

	pre_theta_ = 0;
	z_ = 0;


}
