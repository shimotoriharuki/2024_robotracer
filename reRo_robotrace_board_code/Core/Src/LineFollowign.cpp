/*
 * LineFollowign.cpp
 *
 *  Created on: Jun 21, 2023
 *      Author: SHIMOTORI Haruki
 */
#include "LineFollowing.hpp"

float mon_diff;
float _mon_left_duty;
float _mon_right_duty;
float mon_rotation_duty;

LineFollowing::LineFollowing(VelocityControl *velocity_control, FollowingSensor *following_sensor, InvertedControl *inverted_control, DriveMotor *drive_motor) : i_reset_flag_(false), kp_(0), ki_(0), kd_(0), target_velocity_(0),
		processing_flag_(false)
{
	velocity_control_ = velocity_control;
	following_sensor_ = following_sensor;
	inverted_control_ = inverted_control;
	drive_motor_ = drive_motor;

}

float LineFollowing::calcError()
{
	float average_left = 0, average_right = 0;

	average_left = (following_sensor_->sensor[0] * 3.0 + following_sensor_->sensor[1] * 2.6 + following_sensor_->sensor[2] * 2.2 + following_sensor_->sensor[3] * 1.8
			+ following_sensor_->sensor[4] * 1.4 + following_sensor_->sensor[5] * 1.0) / 6;

	average_right= (following_sensor_->sensor[6] * 1.0 + following_sensor_->sensor[7] * 1.4 + following_sensor_->sensor[8] * 1.8 + following_sensor_->sensor[9] * 2.2
			+ following_sensor_->sensor[10] * 2.6 + following_sensor_->sensor[11] * 3.0) / 6;


	float diff = average_left- average_right;
	mon_diff = diff;

	return diff;

}

void LineFollowing::setTargetVelocity(float velocity)
{
	target_velocity_ = velocity;
}

float LineFollowing::getTargetVelocity()
{
	return target_velocity_;
}

void LineFollowing::pidFlip()
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

		rotation_ratio_ = p + i + d;
		mon_rotation_duty = rotation_ratio_;

		//velocity_control_->setTargetTranslationVelocityOnly(target_velocity_, rotation_ratio_);
		double left_duty, right_duty;
		inverted_control_->getDytu(&left_duty, &right_duty);
		_mon_right_duty = right_duty;
		_mon_left_duty = left_duty;

		drive_motor_->setDuty(left_duty + rotation_ratio_, right_duty - rotation_ratio_);
		//drive_motor_->setDuty(rotation_ratio_, -rotation_ratio_);

		pre_diff = diff;
	}
}

void LineFollowing::setGain(float kp, float ki, float kd)
{
	kp_ = kp;
	ki_ = ki;
	kd_ = kd;
}

void LineFollowing::start()
{
	i_reset_flag_ = true;

	processing_flag_ = true;

	//velocity_control_->disableAngularVelocityPIDControl();
	//velocity_control_->start();

	inverted_control_->resetEstimatedTheta();
	inverted_control_->start();
	inverted_control_->setTargetOmega(0);

}

void LineFollowing::stop()
{
	setTargetVelocity(0.0);
	HAL_Delay(1000);

	processing_flag_ = false;

	velocity_control_->stop();

	inverted_control_-> stop();


}

void LineFollowing::emergencyStop()
{
	processing_flag_ = false;

	velocity_control_->setTargetTranslationVelocityOnly(0.0, 0.0);
	HAL_Delay(1000);
	velocity_control_->stop();


}
