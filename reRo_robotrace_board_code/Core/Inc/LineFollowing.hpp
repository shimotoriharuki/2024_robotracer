/*
 * LineFollowing.hpp
 *
 *  Created on: Jun 21, 2023
 *      Author: SHIMOTORI Haruki
 */

#ifndef INC_LINEFOLLOWING_HPP_
#define INC_LINEFOLLOWING_HPP_

#include "FollowingSensor.hpp"
#include "VelocityControl.hpp"
#include "InvertedControl.hpp"
#include "Motor.hpp"

class LineFollowing
{
private:
	bool i_reset_flag_;
	float kp_, ki_, kd_;
	float target_velocity_;
	float rotation_ratio_;
	bool processing_flag_;
	bool inverted_mode_flag_;
	bool cross_line_ignore_flag_;


	FollowingSensor *following_sensor_;
	VelocityControl *velocity_control_;
	InvertedControl *inverted_control_;
	DriveMotor *drive_motor_;

	float calcError();

public:
	LineFollowing(VelocityControl *, FollowingSensor *, InvertedControl *, DriveMotor *);

	void setTargetVelocity(float);
	float getTargetVelocity();
	void pid();
	void pidWithInvertedControl();
	void flip();
	void setInvertedMode();
	void resetInvertedMode();

	void setGain(float, float, float);
	void start();
	void stop();
	void emergencyStop();

	void enableCrossLineIgnore();
	void disableCrossLineIgnore();
};



#endif /* INC_LINEFOLLOWING_HPP_ */
