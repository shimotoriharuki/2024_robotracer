/*
 * IdleStateController.cpp
 *
 *  Created on: Jun 25, 2023
 *      Author: SHIMOTORI Haruki
 */
#include "UI.hpp"

#include "IdleStateController.hpp"

int8_t mon_state, mon_param_state;
//-------------------------//
//---------private---------//
//-------------------------//
void IdleStateController::parameterAdjustmentMode()
{
	bool break_flag = false;

	while(break_flag == false){
		//メニュー切り替えの制御
		if(wheel_dial_->isCW(RIGHT) == true) parameter_state_++;
		else if(wheel_dial_->isCCW(RIGHT) == true) parameter_state_--;

		if(parameter_state_ > 7) parameter_state_ = 0;
		else if(parameter_state_ < 0) parameter_state_ = 7;

		mon_param_state = parameter_state_;
		led_.set(parameter_state_);

		//条件分岐
		switch(parameter_state_){
		case 0: //速度制御確認
			if(push_switch_->getStatus() == true){
				HAL_Delay(500);

				HAL_Delay(1000);

				velocity_control_->enableAngularVelocityPIDControl();
				velocity_control_->setTargetVelocity(0.0, 0.0);
				velocity_control_->start();

				HAL_Delay(3000);

				velocity_control_->stop();

				HAL_Delay(500);
			}
			break;

		case 1: //ライン追従制御確認
			if(push_switch_->getStatus() == true){
				HAL_Delay(500);

				HAL_Delay(1000);

				line_following_->resetInvertedMode();
				line_following_->setTargetVelocity(0.5);
				line_following_->start();

				HAL_Delay(3000);

				line_following_->stop();

				HAL_Delay(500);
			}

			break;

		case 2: // 倒立テスト
			if(push_switch_->getStatus() == true){
				HAL_Delay(500);

				initializeRobotAngle();

				//imu_->resetRobotAngleFromGyro();
				inverted_control_->resetEstimatedTheta();
				encoder_->clearTheta();
				inverted_control_->setTargetOmega(1);
				inverted_control_->setDebugMode();
				inverted_control_->setStopFeedbackGain();

				//x1_logger_->start();
				//x2_logger_->start();
				//x3_logger_->start();
				//x4_logger_->start();
				//x5_logger_->start();

				inverted_control_->start();

				while(inverted_control_->fallDown() == false){}
				//HAL_Delay(10000);

				inverted_control_->stop();
				inverted_control_->resetDebugMode();

				//x1_logger_->stop();
				//x2_logger_->stop();
				//x3_logger_->stop();
				//x4_logger_->stop();
				//x5_logger_->stop();

				//x1_logger_->saveLogs("debug", "theta_p");
				//x2_logger_->saveLogs("debug", "dtheta_p");
				//x3_logger_->saveLogs("debug", "theta_w");
				//x4_logger_->saveLogs("debug", "dtheta_w");
				//x5_logger_->saveLogs("debug", "z");

			}
			break;

		case 3: //倒立ライントレーステスト
			if(push_switch_->getStatus() == true){
				HAL_Delay(500);

				initializeRobotAngle();

				line_following_->setInvertedMode();
				//imu_->resetRobotAngleFromGyro();
				encoder_->clearTheta();
				line_following_->setInvertedMode();
				line_following_->setTargetVelocity(0.0);

				x1_logger_->start();
				x2_logger_->start();
				x3_logger_->start();
				x4_logger_->start();
				x5_logger_->start();

				line_following_->start();

				fall_down_flag_ = false;

				uint16_t cnt = 0;
				double omega= 0;
				double max_omega = PI/2;
				inverted_control_->setRunFeedbackGain();
				while(fall_down_flag_ == false){
					if(cnt >= 2000){
						break;
					}

					inverted_control_->setTargetOmega(0);

					HAL_Delay(1);
					cnt++;

					omega += max_omega * 0.001;
					if(omega >= max_omega){
						omega = max_omega;
					}

				}

				cnt = 0;
				inverted_control_->setStopFeedbackGain();
				while(fall_down_flag_ == false){
					if(cnt >= 10000){
						break;
					}

					inverted_control_->setTargetOmega(0);

					HAL_Delay(1);
					cnt++;

					omega += max_omega * 0.001;
					if(omega >= max_omega){
						omega = max_omega;
					}

				}

				line_following_->stop();

				x1_logger_->stop();
				x2_logger_->stop();
				x3_logger_->stop();
				x4_logger_->stop();
				x5_logger_->stop();

				x1_logger_->saveLogs("debug", "theta_p");
				x2_logger_->saveLogs("debug", "dtheta_p");
				x3_logger_->saveLogs("debug", "theta_w");
				x4_logger_->saveLogs("debug", "dtheta_w");
				x5_logger_->saveLogs("debug", "z");
				HAL_Delay(500);

				//imu_->resetRobotAngleFromGyro();
				//inverted_control_->start();

				//HAL_Delay(3000);

				//inverted_control_->stop();
			}

			HAL_Delay(100);
			break;

		case 4: //傾斜計テスト
			if(push_switch_->getStatus() == true){
				HAL_Delay(2000);
				acc_data_logger_->start();
				gyro_data_logger_->start();

				HAL_Delay(2000);

				acc_data_logger_->stop();
				gyro_data_logger_->stop();

				acc_data_logger_->saveLogs("debug", "robot_theta_from_acc");
				gyro_data_logger_->saveLogs("debug", "robot_omega_x");
			}

			HAL_Delay(100);
			break;

		case 5: //モータテスト
			if(push_switch_->getStatus() == true){
				HAL_Delay(500);
				drive_motor_->setDuty(300, 300);

				HAL_Delay(2000);

				drive_motor_->setDuty(0, 0);
			}
			break;

		case 6: //SD書き込みテスト
			if(push_switch_->getStatus() == true){
				HAL_Delay(500);
				logger_->start();

				logger_->storeLogs(0);
				logger_->storeLogs(1);
				logger_->storeLogs(2);
				logger_->storeLogs(3);

				logger_->stop();

				logger_->saveLogs("TEST", "test");
			}
			break;

		case 7: //パラメータ調整モードを抜ける
			if(push_switch_->getStatus() == true){
				HAL_Delay(500);
				break_flag = true;
			}
			HAL_Delay(100);
			break;

		}
	}

}

void IdleStateController::initializeRobotAngle()
{
	uint16_t initial_angle_cnt = 0;
	bool initializing_flag = true;

	led_.set(0x07);
	while(initializing_flag == true){
		float robot_angle_acc = imu_->getRobotAngleFromAcc();

		if(INITIAL_ANGLE - 0.002 <= robot_angle_acc && robot_angle_acc <= INITIAL_ANGLE + 0.002){
			initial_angle_cnt++;
		}
		else{
			initial_angle_cnt = 0;
		}

		if(initial_angle_cnt >= 1000){
			imu_->resetRobotAngleFromGyro();
			initializing_flag = false;
		}
	}
	led_.set(0x00);

}

//-------------------------//
//---------public----------//
//-------------------------//
IdleStateController::IdleStateController(DriveMotor *drive_motor, FanMotor *fan_motor, LineFollowing *line_following, FollowingSensor *following_sensor,
		VelocityControl *velocity_control, Encoder *encoder, IMU *imu, WheelDial *wheel_dial, sdCard *sd_card, RunningStateController *running_state_controller, InvertedControl *inverted_control) :
		break_flag_(false), state_(0), parameter_state_(0), fall_down_flag_(false)
{
	drive_motor_ = drive_motor;
	fan_motor_ = fan_motor;
	line_following_ = line_following;
	following_sensor_ = following_sensor;
	velocity_control_ = velocity_control;
	encoder_ = encoder;
	imu_ = imu;
	wheel_dial_ = wheel_dial;
	sd_card_ = sd_card;
	running_state_controller_ = running_state_controller;
	inverted_control_ = inverted_control;

	logger_ = new Logger(sd_card, 10);
	push_switch_ = new Switch(GPIOA, GPIO_PIN_12);

	acc_data_logger_ = new Logger(sd_card, 1); //2000
	gyro_data_logger_ = new Logger(sd_card, 1);

	x1_logger_ = new Logger(sd_card, 1000);
	x2_logger_ = new Logger(sd_card, 1000);
	x3_logger_ = new Logger(sd_card, 1000);
	x4_logger_ = new Logger(sd_card, 1000);
	x5_logger_ = new Logger(sd_card, 1000);

}

void IdleStateController::loop()
{
	break_flag_ = false; //もう一度この関数に帰ってきたときのためにfalseにしておく

	while(break_flag_ == false){

		//メニュー切り替えの制御
		if(wheel_dial_->isCW(RIGHT) == true) state_++;
		else if(wheel_dial_->isCCW(RIGHT) == true) state_--;

		if(state_ > 7) state_ = 0;
		else if(state_ < 0) state_ = 7;

		mon_state = state_;
		led_.set(state_);

		//条件分岐
		switch(state_){
		case 0:
			if(push_switch_->getStatus() == true){
				HAL_Delay(500);

				initializeRobotAngle();

				running_state_controller_->setInvertedMode();//倒立モード
				running_state_controller_->setRunMode(1);
				running_state_controller_->setMinVelocity(0.5); //0.6:OK, 0.7:OK, 0.8:NG

				running_state_controller_->loop(); //走行状態ループ．
				line_following_->stop();
			}
			break;

		case 1:
			if(push_switch_->getStatus() == true){
				HAL_Delay(500);

				initializeRobotAngle();

				running_state_controller_->setInvertedMode();//倒立モード
				running_state_controller_->setRunMode(2);
				running_state_controller_->setMinVelocity(0.5); //0.6:OK, 0.7:OK, 0.8:NG

				running_state_controller_->loop(); //走行状態ループ．
				line_following_->stop();
			}
			break;

		case 2:
			if(push_switch_->getStatus() == true){
				HAL_Delay(500);

				initializeRobotAngle();

				running_state_controller_->setInvertedMode();//倒立モード
				running_state_controller_->setRunMode(3);
				running_state_controller_->setMinVelocity(0.5); //0.6:OK, 0.7:OK, 0.8:NG

				running_state_controller_->loop(); //走行状態ループ．
				line_following_->stop();
			}
			break;

		case 3:
			if(push_switch_->getStatus() == true){
				HAL_Delay(500);

				initializeRobotAngle();

				running_state_controller_->setInvertedMode();//倒立モード
				running_state_controller_->setRunMode(4);
				running_state_controller_->setMinVelocity(0.5); //0.6:OK, 0.7:OK, 0.8:NG

				running_state_controller_->loop(); //走行状態ループ．
				line_following_->stop();
			}
			break;

		case 4: //オートスタートモード
			if(push_switch_->getStatus() == true){
				HAL_Delay(500);

				int8_t ret = 0;

				//1走目
				initializeRobotAngle();

				running_state_controller_->setInvertedMode();//倒立モード
				running_state_controller_->setRunMode(1);
				running_state_controller_->setMinVelocity(0.5); //0.6:OK, 0.7:OK, 0.8:NG

				ret = running_state_controller_->loop(); //走行状態ループ．
				//if(ret != 0) return; //正常終了じゃなかったらreturn

				//2走目
				running_state_controller_->setInvertedMode();//倒立モード
				running_state_controller_->setRunMode(2);
				running_state_controller_->setMinVelocity(0.5);
				running_state_controller_->setMaxVelocity(0.7);
				running_state_controller_->setAccDec(1.0, 0.5); //8.0, 8.0
				running_state_controller_->setStraightRadius(1000);

				ret = running_state_controller_->loop(); //走行状態ループ．
				//if(ret != 0) return; //正常終了じゃなかったらreturn

				//3走目
				running_state_controller_->setInvertedMode();//倒立モード
				running_state_controller_->setRunMode(3);
				running_state_controller_->setMinVelocity(0.5);
				running_state_controller_->setMaxVelocity(0.7);
				running_state_controller_->setAccDec(1.0, 0.5); //8.0, 8.0
				running_state_controller_->setStraightRadius(1000);

				ret = running_state_controller_->loop(); //走行状態ループ．
				//if(ret != 0) return; //正常終了じゃなかったらreturn

				//4走目
				running_state_controller_->setInvertedMode();//倒立モード
				running_state_controller_->setRunMode(4);
				running_state_controller_->setMinVelocity(0.5);
				running_state_controller_->setMaxVelocity(0.8);
				running_state_controller_->setAccDec(1.0, 0.5); //8.0, 8.0
				running_state_controller_->setStraightRadius(1000);

				ret = running_state_controller_->loop(); //走行状態ループ．
				//if(ret != 0) return; //正常終了じゃなかったらreturn

				//5走目
				running_state_controller_->setInvertedMode();//倒立モード
				running_state_controller_->setRunMode(5);
				running_state_controller_->setMinVelocity(0.6);
				running_state_controller_->setMaxVelocity(0.9);
				running_state_controller_->setAccDec(1.0, 0.5); //8.0, 8.0
				running_state_controller_->setStraightRadius(1000);

				ret = running_state_controller_->loop(); //走行状態ループ．
				//if(ret != 0) return; //正常終了じゃなかったらreturn
				line_following_->stop();

			}
			break;

		case 5: //超安全モード
			if(push_switch_->getStatus() == true){
				HAL_Delay(500);

				running_state_controller_->resetInvertedMode();//寝そべりモード
				running_state_controller_->setRunMode(1);
				running_state_controller_->setMinVelocity(0.3);

				running_state_controller_->loop(); //走行状態ループ．
			}
			break;

		case 6: //最新の記録したコースをロード
			if(push_switch_->getStatus() == true){
				HAL_Delay(500);
				running_state_controller_->loadSearchinRunLog();
			}

			break;

		case 7:
			HAL_Delay(100);
			if(push_switch_->getStatus() == true){
				HAL_Delay(500);
				parameterAdjustmentMode();
			}

			break;

		}
	}

}

void IdleStateController::flip()
{
	//acc_data_logger_->storeLogs(imu_->getRobotAngleFromAcc());
	//gyro_data_logger_->storeLogs(imu_->getOmegaX());

	double theta_p, dtheta_p, theta_w, dtheta_w, z;
	inverted_control_->getStateVariables(&theta_p, &dtheta_p, &theta_w, &dtheta_w, &z);

	x1_logger_->storeLogs(theta_p);
	x2_logger_->storeLogs(dtheta_p);
	x3_logger_->storeLogs(theta_w);
	x4_logger_->storeLogs(dtheta_w);
	x5_logger_->storeLogs(z);

	if(inverted_control_->fallDown() == true){
		fall_down_flag_ = true;
	}

}

