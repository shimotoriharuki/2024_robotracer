/*
 * globalDefine.h
 *
 *  Created on: Jun 21, 2023
 *      Author: under
 */

#ifndef INC_GLOBALDEFINE_H_
#define INC_GLOBALDEFINE_H_


#define ADC_DATA_SIZE 4

#define DELTA_T 0.001
#define PI 3.1415926535

#define WHEEL_RADIUS 33 //[mm]
#define ENCODER_RESOLUTION 4096
#define REDUCTION_RATIO 0.167//Gear reduction ratio
#define DISTANCE_PER_CNT (2 * PI * WHEEL_RADIUS * REDUCTION_RATIO / ENCODER_RESOLUTION) //[mm/cnt]=[m/s]
#define RADIAN_PER_CNT (2 * PI * REDUCTION_RATIO / ENCODER_RESOLUTION) //

#define MAX_BATTERY_VOLTAGE 8.4
#define MAX_BATTERY_VOLTAGE_AD_VALUE 3200//MAX_BATTERY_VOLTAGEのときのADCの値（実測）

#define LEFT false
#define RIGHT true

#define SUCTION_DUTY 1000 //700

#define F1_RUN -24.521
#define F2_RUN -1.9125
#define F3_RUN -0.0000
#define F4_RUN -0.0871

#define F1_STOP -30.0
#define F2_STOP -3.5
#define F3_STOP -0.10
#define F4_STOP -0.20
//#define F1_STOP -36.4462
//#define F2_STOP -3.6192
//#define F3_STOP -0.1414
//#define F4_STOP -0.2448



#endif /* INC_GLOBALDEFINE_H_ */
