/*
 * IdleStateController.hpp
 *
 *  Created on: Jun 25, 2023
 *      Author: SHIMOTORI Haruki
 */

#ifndef INC_IDLESTATECONTROLLER_HPP_
#define INC_IDLESTATECONTROLLER_HPP_

#include "Motor.hpp"
#include "LineFollowing.hpp"
#include "FollowingSensor.hpp"
#include "VelocityControl.hpp"
#include "Encoder.hpp"
#include "IMU.hpp"
#include "UI.hpp"
#include "sdCard.hpp"
#include "Logger.hpp"
#include "RunningStateController.hpp"
#include "InvertedControl.hpp"

class IdleStateController{
private:
	bool break_flag_;
	int8_t state_;
	int8_t parameter_state_;
	bool fall_down_flag_;

	DriveMotor *drive_motor_;
	FanMotor *fan_motor_;
	LineFollowing *line_following_;
	FollowingSensor *following_sensor_;
	VelocityControl *velocity_control_;
	Encoder *encoder_;
	IMU *imu_;
	WheelDial *wheel_dial_;
	sdCard *sd_card_;
	RunningStateController *running_state_controller_;
	InvertedControl *inverted_control_;

	Logger *logger_;
	Switch *push_switch_;
	LED led_;

	Logger *acc_data_logger_;
	Logger *gyro_data_logger_;

	Logger *x1_logger_;
	Logger *x2_logger_;
	Logger *x3_logger_;
	Logger *x4_logger_;
	Logger *x5_logger_;


	void parameterAdjustmentMode();
	void initializeRobotAngle();

public:
	IdleStateController(DriveMotor *, FanMotor *, LineFollowing *, FollowingSensor *, VelocityControl *, Encoder *, IMU *, WheelDial *, sdCard *, RunningStateController *, InvertedControl *);
	void loop();
	void flip();
};


#endif /* INC_IDLESTATECONTROLLER_HPP_ */
