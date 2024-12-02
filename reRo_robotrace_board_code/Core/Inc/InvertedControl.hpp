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
#include <cmath>
#include "Logger.hpp"

#define FALL_DOWN_THETA 0.5

class InvertedControl{
private:
	float kp_, ki_, kd_;
	bool i_reset_flag_;
	bool processing_flag_;
	float linefollowing_ratio_;
	double pre_P_[4];
	double pre_theta_, U_, W_;
	double estimated_robot_theta_;

	double m_w_ = 33e-3; // ホイールの重さ [kg]
	double m_p_ = 193e-3; // 振子の重さ [kg]
	double r_w_ = 33e-3; // ホイールの半径 [m]
	double r_p_ = 70e-3; // 振子の重心までの距離 [m]
	double J_w_ = 0.477e-4; // ホイールのイナーシャ
	double J_p_ = 6.498e-4; // 振子のイナーシャ ??
	double J_m_ = 0.151e-7; // モータの回転子のイナーシャ
	double g_ = 9.8; // 重力加速度 [m/s^2]
	double n_ = 4; // 減速比
	double kt_ = 3.52e-3; //トルク定数 [Nm/A]
	double kn_ = 2710; // 回転数定数[rpm/V]
	double ke_ = 1 / (kn_ * 2*M_PI / 60); //起電力定数 [V/(rad/s)]
	double R_ = 2.9; //内部抵抗 [Ω]
	double Ab_[25];
	double Bb_[5];
	double C_[4];

	double pre_xb_[4]; //
	double xb_[4];
	double dt_;
	double input_;
	double target_theta_;
	double z_;

	double current_voltage_;
	double target_omega_;
	double target_velocity_;
	double pre_target_theta_;
	double pre_z_;
	double pre_input_;
	double disturbance_[4];
	double f_[4];
	double k_;

	double inverted_left_duty_, inverted_right_duty_;

	bool debug_flag_;

	DriveMotor *motor_;
	Encoder *encoder_;
	IMU *imu_;

	float calcError();
	void pid();
	void estimateRobotAngle(double dt, double omega_offset, const double pre_P[4],
                         double pre_theta, double U, double W, double omega,
                         double theta, double *estimated_robot_theta,
                         double P[4]);
	void stateFeedbackControl(double, double, double, double);

public:
	InvertedControl(DriveMotor *, Encoder *, IMU *);
	void flip();
	void setPIDGain(float, float, float);
	void start();
	void stop();
	void resetEstimatedTheta();
	void setTargetOmega(double);
	void setTargetVelocity(double);

	bool fallDown();
	void getDytu(double *, double *);

	void setDebugMode();
	void resetDebugMode();

	void getStateVariables(double *, double *, double *, double *);

};




#endif /* INC_INVERTEDCONTROL_HPP_ */
