/*! \file 
 *   Systems-Serial-Headers.h
 *
 * \brief
 *      Headers for communication protocol for Systems Department.
 *
 *      This file contains the Headers (Command Byte)
 *      used in the protocol for the projects developped in the Systems-Department.
 *
 * \author
 *      Ayman Z   \n
 *      Nadim M R \n 
 *		Wissam K  \n  
 *
 * $Revision: 2.0 $
 * Created: 2016-04-22 \n
 * $Revision: 1.0 $
 * Created: 2010-05-17 \n
 *
 *****************************************************************************/


#ifndef SYSTEMS_SERIAL_HEADERS_H
#define SYSTEMS_SERIAL_HEADERS_H

//---------------------------------------------------------------------------
// version 2, 10-October-2015.
// redefine commands according to whom the frame will be sent, "Names" and "IDs".
// add common byte instead of orders which don't need data, so the data become the old command "although we change the IDs".
// add enumeration, acknowledgment, reset.
// use one general silent mode instead of specialized ones. When a specialized one needed use the data bytes.
// using the formula: "TOWHOM_SUBJECT_ORDER" for most cases.
// paging: every page contain 16 byte
//  GENERAL         00--->0F    16/16   Full Page
//  PAN and TILT    10--->1F     9/16
//  PAN and TILT    20--->2F     0/16   Empty Page
//  PAN             30--->3F     6/16
//  PAN             40--->4F     4/16
//  PAN             50--->5F    16/16   Full Page   Pan parameters
//  TILT            60--->6F     6/16
//  TILT            70--->7F     4/16
//  TILT            80--->8F    16/16   Full Page   Tilt parameters
//  PC              90--->9F    16/16   Full Page
//  PC              A0--->AF     2/16
//  LOAD            B0--->BF    10/16
//  LOAD            C0--->CF     0/16   Empty Page
//  LOAD            D0--->DF     0/16   Empty Page
//  INQUIRY         E0--->EF     3/16
//  TEST            F0--->FF     0/16   Empty Page

// total            00--->FF     108/256
//---------------------------------------------------------------------------



// Packet  = | Header | Message | Check |
// Packet  = | Header0 | Header1 | message0 | message1 | message2 |  message3  |  message4  | check |

// Header  = | 0x55 | 0xAA |

// Message = | command0 | data0    | data1 | data2 | data3 |
// Message = | command0 | command1 | data0 | data1 | data2 |

// Check   = XOR_8_bit(Message), initial value is zero.


//------------------------------------ to All "General" ---------------------------------------16/16

#define GEN_EMPTY								0x00 // [ GEN_EMPTY                    | BID_low | BID_high | IID | status ]  // send test purpose.
#define GEN_ERROR_TX_FIFO_OVERFLOW              0x01 // [ GEN_ERROR_TX_FIFO_OVERFLOW   | BID_low | BID_high | IID | status ]  // send TX FIFO overflow Errors.
#define GEN_ERROR_RX_FIFO_OVERFLOW              0x02 // [ GEN_ERROR_RX_FIFO_OVERFLOW   | BID_low | BID_high | IID | status ]  // send RX FIFO overflow Errors.
#define GEN_ERROR_BAD_INTEGRITY                 0x03 // [ GEN_ERROR_BAD_INTEGRITY      | BID_low | BID_high | IID | status ]  // send Bad Integrity Errors.
#define GEN_ERROR_COMMUNICATION_LOST            0x04 // [ GEN_ERROR_COMMUNICATION_LOST | BID_low | BID_high | IID | status ]  // send Communication Lost Errors.
#define GEN_ERROR_SOFTWARE                      0x05 // [ GEN_ERROR_SOFTWARE           | BID_low | BID_high | IID | status ]  // send Software Errors.
#define GEN_ERROR_HARDWARE                      0x06 // [ GEN_ERROR_HARDWARE           | BID_low | BID_high | IID | status ]  // send Hardware Errors.

#define GEN_STATUS                              0x07 // [ GEN_STATUS                   | BID_low | BID_high | IID | status               ] // | H0 | H1 | STAT | BoardID | UnitID |  Parts   |  State   | CHK | // send current status.
#define GEN_ACKNOWLEDGMENT                      0x08 // [ GEN_ACKNOWLEDGMENT           | BID_low | BID_high | IID | acknowledged_command ] // | H0 | H1 | ACKN | BoardID | UnitID |   CMD    |  State   | CHK | // send any command it received.
#define GEN_HELLO_ECHO                          0x09 // [ GEN_HELLO_ECHO               | BID_low | BID_high | IID | peripheral_existence ] // | H0 | H1 | HECH | BoardID | UnitID |  Parts   |    0     | CHK | // send board ID, and instant ID, and parts existence.

#define GEN_HELLO                               0x0A // [ GEN_HELLO                    | BID_low | BID_high | IID | 0      ] // send to one  // | H0 | H1 | HEL  | BoardID | UnitID |  State   |    0     | CHK | // Hello board(s), and wait for echo.
// [ GEN_HELLO                    | 0       | 0        | 0   | 0      ] // send to all

#define GEN_SILENT_MODE                         0x0B // [ GEN_SILENT_MODE              | BID_low | BID_high | IID | status ] // send to one // status = [off, ackn, echo, err, state, enc, 0, 0] // | H0 | H1 | SM   | BoardID | UnitID |  State   |   SPC    | CHK | // Set silent mode.
// [ GEN_SILENT_MODE              | 0       | 0        | 0   | status ] // send to all

#define GEN_STATIC_MODE                         0x0C // [ GEN_STATIC_MODE              | BID_low | BID_high | IID | 0      ] // send to one
// [ GEN_STATIC_MODE              | 0       | 0        | 0   | 0      ] // send to all

#define GEN_RESET                               0x0D // [ GEN_RESET                    | BID_low | BID_high | IID | 0      ] // send to one // | H0 | H1 | RST  | BoardID | UnitID |    0     |    0     | CHK | // Do soft reset.
// [ GEN_RESET                    | 0       | 0        | 0   | 0      ] // send to all

#define GEN_CLEAR                               0x0E // [ GEN_CLEAR                    | BID_low | BID_high | IID | 0      ] // send to one // | H0 | H1 | RST  | BoardID | UnitID |    0     |    0     | CHK | // Do soft reset.
// [ GEN_CLEAR                    | 0       | 0        | 0   | 0      ] // send to all

//#define GEN_BATTERY_VOLTAGE                     0x0F // [ GEN_BATTERY_VOLTAGE          | f32_battery_voltage_mV ]  // | H0 | H1 | Battery  | f32_battery_voltage_mV             | CHK | // Battery Voltage.
#define GEN_SYCRON_MODE                         0x0F // [ GEN_SYCRON_MODE              | BID_low | BID_high | IID | 0      ] // send to one
// [ GEN_SYCRON_MODE              | 0       | 0        | 0   | 0      ] // send to all

//------------------------------------ to PANTILT (Pan and Tilt) from PC --------------------------------------- 9/32

//------------------------------------ to PANTILT from PC

#define PANTILT_COMMON                              0x10     // [ PANTILT_COMMON | command                                 | 0 | 0 | 0 ]
//$ for future compacting use common byte instead of the 7 next lines.
#define PANTILT_DRIVERS_POWER_ON                    0x01 // [ PANTILT_COMMON | PANTILT_DRIVERS_POWER_ON                | 0 | 0 | 0 ] //PC_2_uC_POWER_ON_DRIVERS
#define PANTILT_DRIVERS_POWER_OFF                   0x02 // [ PANTILT_COMMON | PANTILT_DRIVERS_POWER_OFF               | 0 | 0 | 0 ] //PC_2_uC_POWER_OFF_DRIVERS
#define PANTILT_SOFT_START_ACTIVATE                 0x03 // [ PANTILT_COMMON | PANTILT_SOFT_START_ACTIVATE             | 0 | 0 | 0 ] //PC_2_uC_USE_SOFT_START

#define PANTILT_SCANNING_MODE_START                 0x04 // [ PANTILT_COMMON | PANTILT_SCANNING_MODE_START             | 0 | 0 | 0 ] //PC_2_uC_START_SCANNING_MODE
#define PANTILT_SCANNING_MODE_STOP                  0x05 // [ PANTILT_COMMON | PANTILT_SCANNING_MODE_STOP              | 0 | 0 | 0 ] //PC_2_uC_STOP_SCANNING_MODE

#define PANTILT_TRAPEZIODAL_ACTIVATE                0x06 // [ PANTILT_COMMON | PANTILT_TRAPEZIODAL_ACTIVATE            | 0 | 0 | 0 ] //PC_2_uC_USE_TRAPEZIODAL
#define PANTILT_POSITION_TRAPEZIODAL_ACTIVATE	    0x07 // [ PANTILT_COMMON | PANTILT_POSITION_TRAPEZIODAL_ACTIVATE   | 0 | 0 | 0 ] //PC_2_uC_USE_POSITIONTRAPEZIODAL
//end Common

#define PANTILT_POSITION_CONFIGURATION_UPDATE 	    0x08 // [ PANTILT_COMMON | PANTILT_POSITION_CONFIGURATION_UPDATE   | 0 | 0 | 0 ] //PC_2_uC_POSITION_Configueration_UPDATE_E_D


#define PANTILT_PLATFORM_FOLLOW_TELESCOPE_START	    0x09 // [ PANTILT_COMMON | PANTILT_PLATFORM_FOLLOW_TELESCOPE_START | 0 | 0 | 0 ] //START_PLATFORM_FOLLOW_TELESCOPE
#define PANTILT_PLATFORM_FOLLOW_TELESCOPE_STOP	    0x0a // [ PANTILT_COMMON | PANTILT_PLATFORM_FOLLOW_TELESCOPE_STOP  | 0 | 0 | 0 ] //STOP_PLATFORM_FOLLOW_TELESCOPE

#define PANTILT_TRACKING_START                      0x0B // [ PANTILT_COMMON | PANTILT_TRACKING_START                  | 0 | 0 | 0 ] //PC_2_uC_START_TRACKING
#define PANTILT_TRACKING_STOP                       0x0C // [ PANTILT_COMMON | PANTILT_TRACKING_STOP                   | 0 | 0 | 0 ] //PC_2_uC_STOP_TRACKING
#define PANTILT_TRACKING_NO_TARGET                  0x0D // [ PANTILT_COMMON | PANTILT_TRACKING_NO_TARGET              | 0 | 0 | 0 ] //PC_2_uC_NO_TARGET_TRACKING

//------------------------------------ to PANTILT from Load

#define PANTILT_PLATFORM_LASER_DATA             0x11 // [ PANTILT_PLATFORM_LASER_DATA    | f32_duty_cycle ] //PLATFORM_LASER_DATA
#define PANTILT_PLATFORM_POSITION_DATA          0x12 // [ PANTILT_PLATFORM_POSITION_DATA | f32_duty_cycle ] //PLATFORM_POSITIONS_DATA
#define PANTILT_TELESCOPE_DATA                  0x13 // [ PANTILT_TELESCOPE_DATA | f32_data ] //uC_2_PC_TELESCOPE_DATA


// HEADER FOR POSITION TRACKING TARGET
#define PANTILT_POSITION_TRACKER_DX             0x14 // [ PANTILT_POSITION_TRACKER_DX | f32_dx ] //PC_2_uC_POSITION_Dx_Tracker
#define PANTILT_POSITION_TRACKER_DY             0x15 // [ PANTILT_POSITION_TRACKER_DY | f32_dy ] //PC_2_uC_POSITION_Dy_Tracker


// HEADER FOR VELOCITY TRACKING TARGET
#define PANTILT_VELOCITY_TRACKER_DX             0x16 // [ PANTILT_VELOCITY_TRACKER_DX | f32_dx ] //PC_2_uC_VELOCITY_Dx_Tracker
#define PANTILT_VELOCITY_TRACKER_DY             0x17 // [ PANTILT_VELOCITY_TRACKER_DY | f32_dy ] //PC_2_uC_VELOCITY_Dy_Tracker
#define PANTILT_VELOCITY_TRACKER_POSITION_INIT  0x18 // [ PANTILT_VELOCITY_TRACKER_POSITION_INIT | ? ] //PC_2_uC_Position_Init_D_E

//================= Stepper Motor ZKh
#define ACTIVATE_DEACTIVATE_DEMO					0x19
#define DATA_LOGGER									0x1A
#define LOGGER_SETTINGS								0x1B
#define RESET_LOGGER								0x1C
//================= Stepper Motor ZKh


//#define                                       0x19
//#define                                       0x1A
//#define                                       0x1B
//#define                                       0x1C
//#define                                       0x1D
//#define                                       0x1E
//#define                                       0x1F


//#define                                       0x20
//#define                                       0x21
//#define                                       0x22
//#define                                       0x23
//#define                                       0x24
//#define                                       0x25
//#define                                       0x26
//#define                                       0x27
//#define                                       0x28
//#define                                       0x29
//#define                                       0x2A
//#define                                       0x2B
//#define                                       0x2C
//#define                                       0x2D
//#define                                       0x2E
//#define                                       0x2F

//------------------------------------ to Pan --------------------------------------- 6/16 + 4/16 + 16/16

#define PAN_COMMON                                 0x30  // [ PAN_COMMON | command       | data0 | data1 | data2 ]
//$ for future compacting use common byte instead of the 4 next lines.
#define PAN_ACQUISITION                             0x01 // [ PAN_COMMON | PAN_ACQUISITION           | 0 | 0 | 0 ] //PC_2_uC_ACQUISITION_D
#define PAN_HALT                                    0x02 // [ PAN_COMMON | PAN_HALT                  | 0 | 0 | 0 ] //PC_2_uC_HALT_D //uXMega_2_PWR_HALT_D
#define PAN_STOP                                    0x03 // [ PAN_COMMON | PAN_STOP                  | 0 | 0 | 0 ] //PC_2_uC_STOP_D //uXMega_2_PWR_STOP_D
#define PAN_ENCODER_RESET                           0x04 // [ PAN_COMMON | PAN_ENCODER_RESET         | 0 | 0 | 0 ] //PC_2_uC_RESET_ENCODER_D
#define PAN_PWM_DUTY_CYCLE_EXACT                    0x05 // [ PAN_COMMON | PAN_PWM_DUTY_CYCLE_EXACT  | u16_duty_cycle | 0 ] //uXMega_2_PWR_SET_PWM_DUTY_EXACT_D			//not recommended to use, may be deleted in future.
//============================wk=============
#define SHOOT_SINGLE_BULLET							0x06 // [ PAN_COMMON | SHOOT_SINGLE_BULLET
#define SHOOT_MULTI_BULLETS							0x07 // [ PAN_COMMON | SHOOT_SINGLE_BULLET
//=============================BLDC
#define BLDC_ENABLE                                 0x08//0x08
#define BLDC_DISABLE                                0x09//0x09
#define BLDC_PWM_DUTYCYCLE_EXACT                    0x0A//0X0A
#define BLDC_MOTOR_SPEED                            0x0B//0x0B
#define BLDC_MOTOR_CURRENT                          0x0C//0x0C
//=============================BLDC
/*
#define BLDC_ENABLE                             0xF0
#define BLDC_DISABLE                            0xF1
#define BLDC_PWM_DUTYCYCLE_EXACT                0XF2
#define BLDC_MOTOR_SPEED                        0xF3
#define BLDC_MOTOR_CURRENT                      0xF4
*/
//============================wk=============


//============================= Stepper Motor ZKh
#define	PAN_SET_REFERENCE_CURRENT					0x10 // [ PAN_COMMON | PAN_SET_REFERENCE_CURRENT | val_u8(0..7)| 0 | 0 ] //PC_2_uC_SET_REFERENCE_CURRENT
#define PAN_SET_MAXIMUM_FALLING_STEP_TIME			0x12 // [ PAN_COMMON | PAN_SET_MAXIMUM_FALLING_STEP_TIME | val_u8(0..7)| 0 | 0 ] //PC_2_uC_SET_MAXIMUM_FALLING_STEP_TIME
#define PAN_SET_MINIMUM_ON_TIME						0x13 // [ PAN_COMMON | PAN_SET_MINIMUM_ON_TIME | val_u8(0..7)| 0 | 0 ] //PC_2_uC_SET_MINIMUM_ON_TIME
#define PAN_SET_MINIMUM_OFF_TIME					0x14 // [ PAN_COMMON | PAN_SET_MINIMUM_OFF_TIME | val_u8(0..7)| 0 | 0 ] //PC_2_uC_SET_MINIMUM_OFF_TIME
#define PAN_SET_OFF_TIME							0x15 // [ PAN_COMMON | PAN_SET_OFF_TIME | val_u8(0..7)| 0 | 0 ] //PC_2_uC_SET_OFF_TIME
#define PAN_SET_ACCELERATION						0x16 // [ PAN_COMMON | PAN_SET_ACCELERATION | val_u16(0..7)| val_u16(8..15) | 0 ] //PC_2_uC_SET_ACCELERATION
#define PAN_SET_DECELERATION						0x17 // [ PAN_COMMON | PAN_SET_DECELERATION | val_u16(0..7) | val_u16(8..15) | 0 ] //PC_2_uC_SET_DECELERATION
#define PAN_SET_MAXIMUM_SPEED						0x18 // [ PAN_COMMON | PAN_SET_MAXIMUM_SPEED | val_u16(0..7) | val_u16(8..15) | 0 ] //PC_2_uC_SET_MAXIMUM_SPEED
#define PAN_SET_MINIMUM_SPEED						0x19 // [ PAN_COMMON | PAN_SET_MINIMUM_SPEED | val_u16(0..7) | val_u16(8..15)  | 0 ] //PC_2_uC_SET_MINIMUM_SPEED
#define PAN_SET_BASE_SPEED							0x1A // [ PAN_COMMON | PAN_SET_BASE_SPEED | val_u16(0..7) | val_u16(8..15) | 0 ] //PC_2_uC_SET_BASE_SPEED
#define	PAN_GET_REFERENCE_CURRENT					0x20 // [ PAN_COMMON | PAN_GET_REFERENCE_CURRENT | val_u8(0..7)| 0 | 0 ] 
#define PAN_GET_MAXIMUM_FAST_DECAY_TIME				0x21 // [ PAN_COMMON | PAN_GET_MAXIMUM_FAST_DECAY_TIME | val_u8(0..7)| 0 | 0 ] 
#define PAN_GET_MAXIMUM_FALLING_STEP_TIME			0x22 // [ PAN_COMMON | PAN_GET_MAXIMUM_FALLING_STEP_TIME | val_u8(0..7)| 0 | 0 ] 
#define PAN_GET_MINIMUM_ON_TIME						0x23 // [ PAN_COMMON | PAN_GET_MINIMUM_ON_TIME | val_u8(0..7)| 0 | 0 ] 
#define PAN_GET_MINIMUM_OFF_TIME					0x24 // [ PAN_COMMON | PAN_GET_MINIMUM_OFF_TIME | val_u8(0..7)| 0 | 0 ] 
#define PAN_GET_OFF_TIME							0x25 // [ PAN_COMMON | PAN_GET_OFF_TIME | val_u8(0..7)| 0 | 0 ] 
#define PAN_GET_ACCELERATION						0x26 // [ PAN_COMMON | PAN_GET_ACCELERATION | val_u16(0..7)| val_u16(8..15) | 0 ] 
#define PAN_GET_DECELERATION						0x27 // [ PAN_COMMON | PAN_GET_DECELERATION | val_u16(0..7)| val_u16(8..15) | 0 ] 
#define PAN_GET_MAXIMUM_SPEED						0x28 // [ PAN_COMMON | PAN_GET_MAXIMUM_SPEED | val_u16(0..7)| val_u16(8..15) | 0 ] 
#define PAN_GET_MINIMUM_SPEED						0x29 // [ PAN_COMMON | PAN_GET_MINIMUM_SPEED | val_u16(0..7)| val_u16(8..15) | 0 ] 
#define PAN_GET_BASE_SPEED							0x2A // [ PAN_COMMON | PAN_GET_BASE_SPEED | val_u16(0..7)| val_u16(8..15) | 0 ] 
#define PAN_GET_MEMS								0x2B // [ PAN_COMMON | PAN_GET_MEMS | val_u16(0..7)| val_u16(8..15) | 0 ] 
//============================= Stepper Motor ZKh

#define PAN_PWM_DUTY_CYCLE_PERCENT					0x31 // [ PAN_PWM_DUTYCYCLE_PERCENT | f32_duty_cycle ] //PC_2_uC_SET_PWM_DUTY_D //uXMega_2_PWR_SET_PWM_DUTY_PER_CENT_D
#define PAN_STEP_VOLTAGE							0x32 // [ PAN_STEP_VOLTAGE          | f32_step       ] //PC_2_uC_STEP_D //uXMega_2_PWR_SET_VOLT_D

#define PAN_POSITION_INITIAL_ANGLE					0x33 // [ PAN_POSITION_ANGLE_INIT     | f32_initial_angle  ] //PC_2_uC_POSITION_INIT_D
#define PAN_POSITION_SECTOR_ANGLE					0x34 // [ PAN_POSITION_SECTOR_ANGLE   | f32_sector_angle   ] //PC_2_uC_POSITION_SECTOR_ANGLE_D
#define PAN_POSITION_SECTORS_NUMBER					0x35 // [ PAN_POSITION_SECTORS_NUMBER | f32_sectors_number ] //PC_2_uC_POSITION_NUM_SECTOR_D



//-----------WK-----------------------
#define PAN_S_S_PWM_DUTY_CYCLE_PERCENT              0x36 // [ PAN_S_S_PWM_DUTYCYCLE_PERCENT | f32_duty_cycle ] //PC_2_uC_SET_PWM_DUTY_D //uXMega_2_PWR_SET_PWM_DUTY_PER_CENT_D
#define PAN_S_S_STEP_VOLTAGE                        0x37 // [ PAN_S_S_STEP_VOLTAGE          | f32_step       ] //PC_2_uC_STEP_D //uXMega_2_PWR_SET_VOLT_D
#define PAN_SOFT_STEP_VOLTAGE						0x38
#define PAN_SOFT_PWM_DUTY_CYCLE_PERCENT				0x39
#define PAN_DC_MOTOR_DRIVER_CURRENT					0x3A//DC_MotorD_Driver_Current
//-----------WK-----------------------

// removed from headers, because other headers share the same function.
//#define PAN_STEP_RAD_ON_SEC                   0x36 // [ PAN_STEP_RAD_ON_SEC       | f32_step       ] //PC_2_uC_VELOCITY_STEP_DIR					//not recommended to use, may be deleted in future.
//#define PAN_SilentMode						0x37//uXMega_2_PWR_BE_SILENT_D !!!
//#define AMC_2_GUNCONTROL_DIRECTION_ANGLE_RAD	0x38
//#define PAN_DC_MOTOR_DRIVER_CURRENT           0x39//DC_MotorD_Driver_Current
//#define PAN_JOYSTICK_VOLTAGE                  0x3A//JOYSTICK_VOLTAGE_DIRECTION !!!			//not recommended to use, may be deleted in future.
//#define PAN_DC_MOTOR_DRIVER_MILLI_VOLT        0x3B//DC_Motor_Driver_SET_Milli_VOLT_D			//not recommended to use, may be deleted in future.

//#define                                       0x36
//#define                                       0x37
//#define                                       0x38
//#define                                       0x39
//#define                                       0x3A
//#define                                       0x3B
//#define                                       0x3C
//#define                                       0x3D
//#define                                       0x3E
//#define                                       0x3F


// for future use:
// to apply a new control mode:
// 1. set control mode = NULL,
// 2. set parameters (for specified control mode),
// 3. then set reference,
// 4. then set control mode,
// 5. then change the reference.

// if the same reference is wanted for both the new and old control mode, then:
//   just set parameters [if necessary], then set the new control mode.

// Initializes for the first time: Set reference and set control mode parameters, then control mode.
// Initializes in Working time: Cancel control mode, then set reference and set control mode parameters, then control mode.

#define PAN_POSITION_REF								0x40     // [ PAN_POSITION_REF              | f32_position_ref_value                        ]
#define PAN_VELOCITY_REF								0x41     // [ PAN_VELOCITY_REF              | f32_velocity_ref_value                        ]
//======================= Stepper Motor ZKh
#define PAN_STABILIZED_VELOCITY_REF						0x8F     // [ PAN_STABILIZED_VELOCITY_REF              | f32_position_stabilized_ref_value                        ]
//======================= Stepper Motor ZKh

#define PAN_COMMON_CONTROL_PARAMETERS				0x42     // [ PAN_COMMON_CONTROL_PARAMETERS | u8_control_mode                   | 0 | 0 | 0 ] , parameters [ 0x5? ] should be sent before this command, and stored in a buffer.
#define PAN_COMMON_CONTROL_MODE						0x43     // [ PAN_COMMON_CONTROL_MODE       | u8_control_mode                   | 0 | 0 | 0 ]

#define CONTROL_MODE_NULL                           0x00 // [ PAN_COMMON_CONTROL_MODE       | CONTROL_MODE_NULL                 | 0 | 0 | 0 ]

#define CONTROL_MODE_POSITION_PID                   0x01 // [ PAN_COMMON_CONTROL_MODE       | CONTROL_MODE_POSITION_PID         | 0 | 0 | 0 ]
#define CONTROL_MODE_VELOCITY_PID                   0x02 // [ PAN_COMMON_CONTROL_MODE       | CONTROL_MODE_VELOCITY_PID         | 0 | 0 | 0 ]

#define CONTROL_MODE_POSITION_STATE_SPACE           0x03 // [ PAN_COMMON_CONTROL_MODE       | CONTROL_MODE_POSITION_STATE_SPACE | 0 | 0 | 0 ]
#define CONTROL_MODE_VELOCITY_STATE_SPACE           0x04 // [ PAN_COMMON_CONTROL_MODE       | CONTROL_MODE_VELOCITY_STATE_SPACE | 0 | 0 | 0 ]

#define CONTROL_MODE_POSITION_LQR                   0x05 // [ PAN_COMMON_CONTROL_MODE       | CONTROL_MODE_POSITION_LQR         | 0 | 0 | 0 ]
#define CONTROL_MODE_VELOCITY_LQR                   0x06 // [ PAN_COMMON_CONTROL_MODE       | CONTROL_MODE_VELOCITY_LQR         | 0 | 0 | 0 ]

#define CONTROL_MODE_POSITION_SLIDING               0x07 // [ PAN_COMMON_CONTROL_MODE       | CONTROL_MODE_POSITION_SLIDING     | 0 | 0 | 0 ]
#define CONTROL_MODE_VELOCITY_SLIDING               0x08 // [ PAN_COMMON_CONTROL_MODE       | CONTROL_MODE_VELOCITY_SLIDING     | 0 | 0 | 0 ]

#define CONTROL_MODE_POSITION_FUZZY                 0x09 // [ PAN_COMMON_CONTROL_MODE       | CONTROL_MODE_POSITION_FUZZY       | 0 | 0 | 0 ]
#define CONTROL_MODE_VELOCITY_FUZZY                 0x0A // [ PAN_COMMON_CONTROL_MODE       | CONTROL_MODE_VELOCITY_FUZZY       | 0 | 0 | 0 ]

#define CONTROL_MODE_POSITION_PULSE                 0x0B // [ PAN_COMMON_CONTROL_MODE       | CONTROL_MODE_POSITION_PULSE       | 0 | 0 | 0 ]
#define CONTROL_MODE_VELOCITY_PULSE                 0x0C // [ PAN_COMMON_CONTROL_MODE       | CONTROL_MODE_VELOCITY_PULSE       | 0 | 0 | 0 ]


#define PAN_CONTROL_MODE_POSITION_PID				0x44 // [ PAN_CONTROL_MODE_POSITION_PID     | f32_position_ref ]
#define PAN_CONTROL_MODE_VELOCITY_PID				0x45 // [ PAN_CONTROL_MODE_VELOCITY_PID     | f32_velocity_ref ]

#define PAN_CONTROL_MODE_POSITION_SLIDING			0x46 // [ PAN_CONTROL_MODE_POSITION_SLIDING | f32_position_ref ]
#define PAN_CONTROL_MODE_VELOCITY_SLIDING			0x47 // [ PAN_CONTROL_MODE_VELOCITY_SLIDING | f32_velocity_ref ]

// to send a parameter: ex(PID)for position
// 0. by default the parameters buffer should contain default values,
//    because when PAN_COMMON_CONTROL_PARAMETERS is received,
//    all the parameters which stored in a buffer will be copied to the control law parameters.
// for example PI:
// problem: set K_P = 15.5, K_I = 30  , K_D = 0,
// and: position_ref = 10.2, then change it 17, then change it to 25.6.
// and:   reset K_P = 15.5, K_I = 30.2, K_D = 0,
// and: position_ref = 25.7, then change it 29.1, then change it to 40.
// a. define variable for control law:
//   1. pid_t pid;
//   2. uint8_t control_parameters[3];
// b. Initialization:
//   1. control_parameters[0] = 0 // K_P
//   2. control_parameters[1] = 0 // K_I
//   3. control_parameters[2] = 0 // K_D
// c. In receiving data:
//   1. send K_P:            [ PAN_CONTROL_PARAMETER_PID_KP  | 15.5 ]
//   2. send K_I:            [ PAN_CONTROL_PARAMETER_PID_KI  | 30.0 ]
//   3. no need to send K_D, as long as it's not changed, however it could be sent.
//   4. send Set_Parameters: [ PAN_COMMON_CONTROL_PARAMETERS | CONTROL_MODE_POSITION_PID | 0 | 0 | 0 ]
// d. In "tune PID" applying mode:
//   1. pid->K_P = control_parameters[0];
//   2. pid->K_I = control_parameters[1];
//   3. pid->K_D = control_parameters[2];
// e. Send reference and apply control mode:
//   1. Send reference:      [ PAN_POSITION_REF              | 10.2 ]
//   2. Send apply:          [ PAN_COMMON_CONTROL_MODE       | CONTROL_MODE_POSITION_PID | 0 | 0 | 0 ]
// f. Send new reference when it's desired.
//   1. Send reference:      [ PAN_POSITION_REF              | 17.0 ]
//   2. Send reference:      [ PAN_POSITION_REF              | 25.6 ]
// g. re: In receiving data:
//   1. no need to send K_P, as long as it's not changed, however it could be sent.
//   2. send K_I:            [ PAN_CONTROL_PARAMETER_PID_KI  | 30.2 ]
//   3. no need to send K_D, as long as it's not changed, however it could be sent.
//   4. send Set_Parameters: [ PAN_COMMON_CONTROL_PARAMETERS | CONTROL_MODE_POSITION_PID | 0 | 0 | 0 ]
//   5. the previous line will correct position to the last setting reference aka 25.6
//   6. if it's not desired the HALT command should be sent or CONTROL_MODE_NULL.
// h. re: Send new reference when it's desired, because control_mode is already position_pid.
//   1. Send reference:      [ PAN_POSITION_REF              | 25.7 ]
//   2. Send reference:      [ PAN_POSITION_REF              | 29.1 ]
//   3. Send reference:      [ PAN_POSITION_REF              | 40.0 ]

//#define                                       0x44
//#define                                       0x45
//#define                                       0x46
//#define                                       0x47
//#define                                       0x48
//#define                                       0x49
//#define                                       0x4A
//#define                                       0x4B
//#define                                       0x4C
//#define                                       0x4D
//#define                                       0x4E
//#define                                       0x4F

// Those should be reused by all control laws
#define PAN_CONTROL_PARAMETER_0                 0x50 // [ PAN_CONTROL_PARAMETER_0 | ? ]
#define PAN_CONTROL_PARAMETER_1                 0x51 // [ PAN_CONTROL_PARAMETER_1 | ? ]
#define PAN_CONTROL_PARAMETER_2                 0x52 // [ PAN_CONTROL_PARAMETER_2 | ? ]
#define PAN_CONTROL_PARAMETER_3                 0x53 // [ PAN_CONTROL_PARAMETER_3 | ? ]
#define PAN_CONTROL_PARAMETER_4                 0x54 // [ PAN_CONTROL_PARAMETER_4 | ? ]
#define PAN_CONTROL_PARAMETER_5                 0x55 // [ PAN_CONTROL_PARAMETER_5 | ? ]
#define PAN_CONTROL_PARAMETER_6                 0x56 // [ PAN_CONTROL_PARAMETER_6 | ? ]
#define PAN_CONTROL_PARAMETER_7                 0x57 // [ PAN_CONTROL_PARAMETER_7 | ? ]
#define PAN_CONTROL_PARAMETER_8                 0x58 // [ PAN_CONTROL_PARAMETER_8 | ? ]
#define PAN_CONTROL_PARAMETER_9                 0x59 // [ PAN_CONTROL_PARAMETER_9 | ? ]
#define PAN_CONTROL_PARAMETER_A                 0x5A // [ PAN_CONTROL_PARAMETER_A | ? ]
#define PAN_CONTROL_PARAMETER_B                 0x5B // [ PAN_CONTROL_PARAMETER_B | ? ]
#define PAN_CONTROL_PARAMETER_C                 0x5C // [ PAN_CONTROL_PARAMETER_C | ? ]
#define PAN_CONTROL_PARAMETER_D                 0x5D // [ PAN_CONTROL_PARAMETER_D | ? ]
#define PAN_CONTROL_PARAMETER_E                 0x5E // [ PAN_CONTROL_PARAMETER_E | ? ]
#define PAN_CONTROL_PARAMETER_F                 0x5F // [ PAN_CONTROL_PARAMETER_F | ? ]

// For PID
#define PAN_CONTROL_PARAMETER_PID_KP            0x50 // [ PAN_COMMON_CONTROL_MODE | f32_propotional_constan_value       ] //PC_2_uC_POSITION_PID_K_P_DIR
#define PAN_CONTROL_PARAMETER_PID_KI            0x51 // [ PAN_COMMON_CONTROL_MODE | f32_integral_constant_value         ] //PC_2_uC_POSITION_PID_K_I_DIR
#define PAN_CONTROL_PARAMETER_PID_KD            0x52 // [ PAN_COMMON_CONTROL_MODE | f32_derivative_constant_value       ] //PC_2_uC_POSITION_PID_K_D_DIR
#define PAN_CONTROL_PARAMETER_PID_KF            0x53 // [ PAN_COMMON_CONTROL_MODE | f32_forward_constant_value          ]
#define PAN_CONTROL_PARAMETER_PID_KB            0x54 // [ PAN_COMMON_CONTROL_MODE | f32_back_calculation_constant_value ]
#define PAN_CONTROL_PARAMETER_PID_KN            0x55 // [ PAN_COMMON_CONTROL_MODE | f32_derivative_filter_value         ]

// For Project ...
#define PAN_POSITION_MIN                        0x50
#define PAN_POSITION_MAX                        0x51
#define PAN_VELOCITY_MIN                        0x52
#define PAN_VELOCITY_MAX                        0x53
#define PAN_POSITION_KP_ON_RAISING              0x54
#define PAN_POSITION_KP_ON_FALLING              0x55

// Reverse order for sequel purpose



//------------------------------------ to Tilt --------------------------------------- 6/16 + 4/16 + 16/16

#define TILT_COMMON									0x60     // [ TILT_COMMON | command       | data0 | data1 | data2 ]
//$ for future compacting use common byte instead of the 4 next lines.
#define TILT_ACQUISITION                            0x01 // [ TILT_COMMON | TILT_ACQUISITION          | 0 | 0 | 0 ] //PC_2_uC_ACQUISITION_E
#define TILT_HALT                                   0x02 // [ TILT_COMMON | TILT_HALT                 | 0 | 0 | 0 ] //PC_2_uC_HALT_E //uXMega_2_PWR_HALT_E
#define TILT_STOP                                   0x03 // [ TILT_COMMON | TILT_STOP                 | 0 | 0 | 0 ] //PC_2_uC_STOP_E //uXMega_2_PWR_STOP_E
#define TILT_ENCODER_RESET                          0x04 // [ TILT_COMMON | TILT_ENCODER_RESET        | 0 | 0 | 0 ] //PC_2_uC_RESET_ENCODER_E
#define TILT_PWM_DUTY_CYCLE_EXACT                   0x05 // [ TILT_COMMON | TILT_PWM_DUTY_CYCLE_EXACT | u16_duty_cycle | 0 ]  //uXMega_2_PWR_SET_PWM_DUTY_EXACT_E			//not recommended to use, may be deleted in future.

#define TILT_PWM_DUTY_CYCLE_PERCENT					0x61//PC_2_uC_SET_PWM_DUTY_E
#define TILT_STEP_VOLTAGE							0x62//PC_2_uC_STEP_E //uXMega_2_PWR_SET_VOLT_E

#define TILT_POSITION_ITITIAL_ANGLE					0x63//PC_2_uC_POSITION_INIT_E
#define TILT_POSITION_SECTOR_ANGLE					0x64//PC_2_uC_POSITION_SECTOR_ANGLE_E
#define TILT_POSITION_SECTORS_NUMBER					0x65//PC_2_uC_POSITION_NUM_SECTOR_E

//-----------WK-----------------------
#define TILT_S_S_PWM_DUTY_CYCLE_PERCENT             0x66//PC_2_uC_SET_PWM_DUTY_E
#define TILT_S_S_STEP_VOLTAGE                       0x67//PC_2_uC_STEP_E //uXMega_2_PWR_SET_VOLT_E
#define TILT_SOFT_STEP_VOLTAGE						0x68
#define TILT_SOFT_PWM_DUTY_CYCLE_PERCENT				0x69
#define TILT_DC_MOTOR_DRIVER_CURRENT					0x6A//DC_MotorD_Driver_Current

//============================= Stepper Motor ZKh
#define	TILT_SET_REFERENCE_CURRENT					0x10 // [ TILT_COMMON | TILT_SET_REFERENCE_CURRENT | val_u8(0..7)| 0 | 0 ] //PC_2_uC_SET_REFERENCE_CURRENT
#define TILT_SET_MAXIMUM_FALLING_STEP_TIME			0x12 // [ TILT_COMMON | TILT_SET_MAXIMUM_FALLING_STEP_TIME | val_u8(0..7)| 0 | 0 ] //PC_2_uC_SET_MAXIMUM_FALLING_STEP_TIME
#define TILT_SET_MINIMUM_ON_TIME						0x13 // [ TILT_COMMON | TILT_SET_MINIMUM_ON_TIME | val_u8(0..7)| 0 | 0 ] //PC_2_uC_SET_MINIMUM_ON_TIME
#define TILT_SET_MINIMUM_OFF_TIME					0x14 // [ TILT_COMMON | TILT_SET_MINIMUM_OFF_TIME | val_u8(0..7)| 0 | 0 ] //PC_2_uC_SET_MINIMUM_OFF_TIME
#define TILT_SET_OFF_TIME							0x15 // [ TILT_COMMON | TILT_SET_OFF_TIME | val_u8(0..7)| 0 | 0 ] //PC_2_uC_SET_OFF_TIME
#define TILT_SET_ACCELERATION						0x16 // [ TILT_COMMON | TILT_SET_ACCELERATION | val_u16(0..7)| val_u16(8..15) | 0 ] //PC_2_uC_SET_ACCELERATION
#define TILT_SET_DECELERATION						0x17 // [ TILT_COMMON | TILT_SET_DECELERATION | val_u16(0..7) | val_u16(8..15) | 0 ] //PC_2_uC_SET_DECELERATION
#define TILT_SET_MAXIMUM_SPEED						0x18 // [ TILT_COMMON | TILT_SET_MAXIMUM_SPEED | val_u16(0..7) | val_u16(8..15) | 0 ] //PC_2_uC_SET_MAXIMUM_SPEED
#define TILT_SET_MINIMUM_SPEED						0x19 // [ TILT_COMMON | TILT_SET_MINIMUM_SPEED | val_u16(0..7) | val_u16(8..15)  | 0 ] //PC_2_uC_SET_MINIMUM_SPEED
#define TILT_SET_BASE_SPEED							0x1A // [ TILT_COMMON | TILT_SET_BASE_SPEED | val_u16(0..7) | val_u16(8..15) | 0 ] //PC_2_uC_SET_BASE_SPEED
#define	TILT_GET_REFERENCE_CURRENT					0x20 // [ TILT_COMMON | TILT_GET_REFERENCE_CURRENT | val_u8(0..7)| 0 | 0 ] 
#define TILT_GET_MAXIMUM_FAST_DECAY_TIME				0x21 // [ TILT_COMMON | TILT_GET_MAXIMUM_FAST_DECAY_TIME | val_u8(0..7)| 0 | 0 ] 
#define TILT_GET_MAXIMUM_FALLING_STEP_TIME			0x22 // [ TILT_COMMON | TILT_GET_MAXIMUM_FALLING_STEP_TIME | val_u8(0..7)| 0 | 0 ] 
#define TILT_GET_MINIMUM_ON_TIME						0x23 // [ TILT_COMMON | TILT_GET_MINIMUM_ON_TIME | val_u8(0..7)| 0 | 0 ] 
#define TILT_GET_MINIMUM_OFF_TIME					0x24 // [ TILT_COMMON | TILT_GET_MINIMUM_OFF_TIME | val_u8(0..7)| 0 | 0 ] 
#define TILT_GET_OFF_TIME							0x25 // [ TILT_COMMON | TILT_GET_OFF_TIME | val_u8(0..7)| 0 | 0 ] 
#define TILT_GET_ACCELERATION						0x26 // [ TILT_COMMON | TILT_GET_ACCELERATION | val_u16(0..7)| val_u16(8..15) | 0 ] 
#define TILT_GET_DECELERATION						0x27 // [ TILT_COMMON | TILT_GET_DECELERATION | val_u16(0..7)| val_u16(8..15) | 0 ] 
#define TILT_GET_MAXIMUM_SPEED						0x28 // [ TILT_COMMON | TILT_GET_MAXIMUM_SPEED | val_u16(0..7)| val_u16(8..15) | 0 ] 
#define TILT_GET_MINIMUM_SPEED						0x29 // [ TILT_COMMON | TILT_GET_MINIMUM_SPEED | val_u16(0..7)| val_u16(8..15) | 0 ] 
#define TILT_GET_BASE_SPEED							0x2A // [ TILT_COMMON | TILT_GET_BASE_SPEED | val_u16(0..7)| val_u16(8..15) | 0 ] 
#define TILT_GET_MEMS								0x2B // [ TILT_COMMON | TILT_GET_MEMS | val_u16(0..7)| val_u16(8..15) | 0 ] 
//============================= Stepper Motor ZKh


//-----------WK-----------------------

//#define TILT_STEP_RAD_ON_SEC                  0x66//PC_2_uC_VELOCITY_STEP_ELEV	!!!			//not recommended to use, may be deleted in future.
//#define TILT_SilentMode						0x67//uXMega_2_PWR_BE_SILENT_E !!!
//#define AMC_2_GUNCONTROL_DIRECTION_ANGLE_RAD	0x68
//#define TILT_DC_MOTOR_DRIVER_CURRENT          0x69//DC_MotorD_Driver_Current
//#define TILT_JOYSTICK_VOLTAGE					0x6A//JOYSTICK_VOLTAGE_ELEVATION !!!			//not recommended to use, may be deleted in future.
//#define TILT_DC_MOTOR_DRIVER_MILLI_VOLT       0x6B//DC_Motor_Driver_SET_Milli_VOLT_E//		//not recommended to use, may be deleted in future.

//#define                                       0x66
//#define                                       0x67
//#define                                       0x68
//#define                                       0x69
//#define                                       0x6A
//#define                                       0x6B
//#define                                       0x6C
//#define                                       0x6D
//#define                                       0x6E
//#define                                       0x6F

//CURRENT LIMIT, VOLTAGE LIMIT


#define TILT_POSITION_REF                       0x70 // [ TILT_POSITION_REF              | f32_position_ref_value      ]
#define TILT_VELOCITY_REF                       0x71 // [ TILT_VELOCITY_REF              | f32_velocity_ref_value      ]
#define TILT_COMMON_CONTROL_MODE                0x72 // [ TILT_COMMON_CONTROL_MODE       | u8_control_mode | 0 | 0 | 0 ]
#define TILT_COMMON_CONTROL_PARAMETERS          0x73 // [ TILT_COMMON_CONTROL_PARAMETERS | u8_control_mode | 0 | 0 | 0 ] , parameters should be sent before this command, and stored in a buffer.


#define TILT_CONTROL_MODE_POSITION_PID          0x74 // [ TILT_CONTROL_MODE_POSITION_PID | f32_position_ref ]
#define TILT_CONTROL_MODE_VELOCITY_PID          0x75 // [ TILT_CONTROL_MODE_VELOCITY_PID | f32_velocity_ref ]

#define TILT_CONTROL_MODE_POSITION_SLIDING      0x76 // [ TILT_CONTROL_MODE_POSITION_SLIDING | f32_position_ref ]
#define TILT_CONTROL_MODE_VELOCITY_SLIDING      0x77 // [ TILT_CONTROL_MODE_VELOCITY_SLIDING | f32_velocity_ref ]
//======================= Stepper Motor ZKh
#define TILT_STABILIZED_VELOCITY_REF						0x78     // [ TILT_STABILIZED_VELOCITY_REF              | f32_position_stabilized_ref_value                        ]
//======================= Stepper Motor ZKh



//#define                                       0x74
//#define                                       0x75
//#define                                       0x76
//#define                                       0x77
//#define                                       0x78
//#define                                       0x79
//#define                                       0x7A
//#define                                       0x7B
//#define                                       0x7C
//#define                                       0x7D
//#define                                       0x7E
//#define                                       0x7F

// to send a parameter: ex(PID)for position see above note in pan section.

// Those should be reused by all control laws
#define TILT_CONTROL_PARAMETER_0                0x80 // [ TILT_CONTROL_PARAMETER_0 | ? ]
#define TILT_CONTROL_PARAMETER_1                0x81 // [ TILT_CONTROL_PARAMETER_1 | ? ]
#define TILT_CONTROL_PARAMETER_2                0x82 // [ TILT_CONTROL_PARAMETER_2 | ? ]
#define TILT_CONTROL_PARAMETER_3                0x83 // [ TILT_CONTROL_PARAMETER_3 | ? ]
#define TILT_CONTROL_PARAMETER_4                0x84 // [ TILT_CONTROL_PARAMETER_4 | ? ]
#define TILT_CONTROL_PARAMETER_5                0x85 // [ TILT_CONTROL_PARAMETER_5 | ? ]
#define TILT_CONTROL_PARAMETER_6                0x86 // [ TILT_CONTROL_PARAMETER_6 | ? ]
#define TILT_CONTROL_PARAMETER_7                0x87 // [ TILT_CONTROL_PARAMETER_7 | ? ]
#define TILT_CONTROL_PARAMETER_8                0x88 // [ TILT_CONTROL_PARAMETER_8 | ? ]
#define TILT_CONTROL_PARAMETER_9                0x89 // [ TILT_CONTROL_PARAMETER_9 | ? ]
#define TILT_CONTROL_PARAMETER_A                0x8A // [ TILT_CONTROL_PARAMETER_A | ? ]
#define TILT_CONTROL_PARAMETER_B                0x8B // [ TILT_CONTROL_PARAMETER_B | ? ]
#define TILT_CONTROL_PARAMETER_C                0x8C // [ TILT_CONTROL_PARAMETER_C | ? ]
#define TILT_CONTROL_PARAMETER_D                0x8D // [ TILT_CONTROL_PARAMETER_D | ? ]
#define TILT_CONTROL_PARAMETER_E                0x8E // [ TILT_CONTROL_PARAMETER_E | ? ]
#define TILT_CONTROL_PARAMETER_F                0x8F // [ TILT_CONTROL_PARAMETER_F | ? ]

// For PID
#define TILT_CONTROL_PARAMETER_PID_KP           0x80 // [ TILT_COMMON_CONTROL_MODE | f32_propotional_constan_value       ]
#define TILT_CONTROL_PARAMETER_PID_KI           0x81 // [ TILT_COMMON_CONTROL_MODE | f32_integral_constant_value         ]
#define TILT_CONTROL_PARAMETER_PID_KD           0x82 // [ TILT_COMMON_CONTROL_MODE | f32_derivative_constant_value       ]
#define TILT_CONTROL_PARAMETER_PID_KF           0x83 // [ TILT_COMMON_CONTROL_MODE | f32_forward_constant_value          ]
#define TILT_CONTROL_PARAMETER_PID_KB           0x84 // [ TILT_COMMON_CONTROL_MODE | f32_back_calculation_constant_value ]
#define TILT_CONTROL_PARAMETER_PID_KN           0x85 // [ TILT_COMMON_CONTROL_MODE | f32_derivative_filter_value         ]

// For Project ...
#define TILT_POSITION_MIN                       0x80
#define TILT_POSITION_MAX                       0x81
#define TILT_VELOCITY_MIN                       0x82
#define TILT_VELOCITY_MAX                       0x83
#define TILT_POSITION_KP_ON_RAISING             0x84
#define TILT_POSITION_KP_ON_FALLING             0x85

//------------------------------------ to PC --------------------------------------- 18 / 32

#define PC_ADC_VALUES_X_Y                       0x90 // [ PC_ADC_VALUES_X_Y               | u16_pan_voltage      | u16_tilt_voltage      ] //uC_2_PC_ADC_VALUES_X_Y
#define PC_PAN_TILT_ENCODER_DATA                0x91 // [ PC_PAN_TILT_ENCODER_DATA        | u16_pan_encoder_data | u16_tilt_encoder_data ] //uC_2_PC_ENCODER_D_E

#define PC_PAN_ENCODER_DATA_ENDAT22             0x92 // [ PC_PAN_ENCODER_DATA_ENDAT22     | ?                           ] //ENDAT22_ENCODER_D
#define PC_PAN_ENCODER_DATA_SSI                 0x93 // [ PC_PAN_ENCODER_DATA_SSI         | u32_pan_encoder_data        ] //uC_2_PC_ENCODER_D

#define PC_TILT_ENCODER_DATA_ENDAT22            0x94 // [ PC_TILT_ENCODER_DATA_ENDAT22    | ?                           ] //ENDAT22_ENCODER_E
#define PC_TILT_ENCODER_DATA_SSI                0x95 // [ PC_TILT_ENCODER_DATA_SSI        | u32_tilt_encoder_data       ] //uC_2_PC_ENCODER_E

#define PC_PAN_DC_MOTOR_DRIVER_CURRENT          0x96 // [ PC_PAN_DC_MOTOR_DRIVER_CURRENT  | f32_current_value           ] //				//not recommended to use, may be deleted in future.
#define PC_TILT_DC_MOTOR_DRIVER_CURRENT         0x97 // [ PC_TILT_DC_MOTOR_DRIVER_CURRENT | f32_current_value           ] //				//not recommended to use, may be deleted in future.

// from Inclinometer
#define PC_INCLINOMETER_X                       0x98 // [ PC_INCLINOMETER_X               | f32_x                       ] //uC_2_PC_Inclinometer_X
#define PC_INCLINOMETER_Y                       0x99 // [ PC_INCLINOMETER_Y               | f32_y                       ] //uC_2_PC_Inclinometer_Y
#define PC_INCLINOMETER_T                       0x9A // [ PC_INCLINOMETER_T               | f32_z                       ] //uC_2_PC_Inclinometer_T

// from WeatherVaisalaWXT520
#define PC_WeatherVaisalaWXT520_WIND_DIRECTION  0x9B // [ PC_WeatherVaisalaWXT520_WIND_DIRECTION | f32_angle            ] //uC_2_PC_WeatherVaisalaWXT520_Wind_Dir
#define PC_WeatherVaisalaWXT520_WINS_SPEED      0x9C // [ PC_WeatherVaisalaWXT520_WINS_SPEED     | f32_speed            ] //uC_2_PC_WeatherVaisalaWXT520_Wind_Speed
#define PC_WeatherVaisalaWXT520_TEMPRETURE      0x9D // [ PC_WeatherVaisalaWXT520_TEMPRETURE     | f32_tempreture       ] //uC_2_PC_WeatherVaisalaWXT520_Tempreture
#define PC_WeatherVaisalaWXT520_PRESSURE        0x9E // [ PC_WeatherVaisalaWXT520_PRESSURE       | f32_pressure         ] //uC_2_PC_WeatherVaisalaWXT520_Pressure

// from Camera. All commands should have this byte as command, and the wanted command in the next byte.
#define PC_CAMERA_COMMON                        0x9F // [ PC_CAMERA_COMMON | CAMERA_ZOOM_VALUE     | zoom_low_byte   | zoom_high_byte | 0               ] <--ex

// from Laser.
#define PC_LASER_VALUE                          0xA0 // [ PC_LASER_VALUE   | 1st_Target_Low      | 1st_Target_High | 2nd_Target_Low | 2nd_Target_High ]
#define PC_LASER_STATE                          0xA1 // [ PC_LASER_STATE   | State               | 0               | 0              | 0               ]
#define PC_LASER_READY                          0xA2 // [ PC_LASER_READY   | State               | 0               | 1st_Target_Low | 1st_Target_High ]

#define PC_LRF_DATA                             0xA0 // [ PC_LRF_DATA        | u8_target_index    | u8_LRF_status | Target_Distance_Low | Target_Distance_High ]
#define PC_LRF_READY                            0xA2 // [ PC_LASER_READY   | State               | 0               | 1st_Target_Low | 1st_Target_High ]

#define PC_PAN_STATUS                           0xA3 // [ PC_PAN_STATUS      | u8_status | u24_ssiEncoderData]
#define PC_TILT_STATUS                          0xA4 // [ PC_TILT_STATUS     | u8_status | u24_ssiEncoderData]
#define PC_OPTOLOAD_STATUS                      0xA5 // [ PC_OPTOLOAD_STATUS | u8_status | u8_focus_value_high_byte | u16_zoom_value] // u8_focus_value_low_byte is always zero
#define PC_UPS_STATUS                           0xA6 // [ PC_UPS_STATUS      | u8_status | 0 | u16_voltage_millivolt]
#define PC_HUB_STATUS                           0xA7

#define GEN_BATTERY_VOLTAGE                     0xA8 // [ GEN_BATTERY_VOLTAGE          | f32_battery_voltage_mV ]  // | H0 | H1 | Battery  | f32_battery_voltage_mV             | CHK | // Battery Voltage.
#define GEN_BATTERY_CURRENT                     0xA9 // [ GEN_BATTERY_CURRENT          | f32_battery_current_mV ]  // | H0 | H1 | Battery  | f32_battery_current_mV             | CHK | // Battery Current.

#define	BLDC_SPEED_MEASURE						0xAA //to be changed

//======================= Stepper Motor ZKh
#define PAN_MOTOR_STEPS									0xAB  // [ PAN_MOTOR_STEPS      | u8_status | u24_ssiEncoderData]
#define TILT_MOTOR_STEPS								0xAC  // [ TILT_MOTOR_STEPS      | u8_status | u24_ssiEncoderData]

//======================= Stepper Motor ZKh

//#define                                       0xA4
//#define                                       0xA5
//#define                                       0xA6
//#define                                       0xA7
//#define                                       0xA8
//#define                                       0xA9
//#define                                       0xAA
//#define                                       0xAB
//#define                                       0xAC
//#define                                       0xAD
//#define                                       0xAE
//#define                                       0xAF

//------------------------------------ to different Loads --------------------------------------- 10 / 48

//------------------------------------ to Load "Camera" ---------------------------------------
//Header For the Case configuration and definition
#define CAMERA_COMMON								0xB0     // [ CAMERA_COMMON | command                     | 0 | 0 | 0 ]
#define CAMERA_SELECT_TV_CAMERA                     0x01 // [ CAMERA_COMMON | CAMERA_SELECT_TV_CAMERA     | 0 | 0 | 0 ] //uC_2_uC_TV_CAMERA
#define CAMERA_SELECT_IR_CAMERA                     0x02 // [ CAMERA_COMMON | CAMERA_SELECT_IR_CAMERA     | 0 | 0 | 0 ] //uC_2_uC_IR_CAMERA
#define CAMERA_SONY_ON                              0x03 // [ CAMERA_COMMON | CAMERA_SONY_ON              | 0 | 0 | 0 ] //SONY_ON
#define CAMERA_SONY_OFF                             0x04 // [ CAMERA_COMMON | CAMERA_SONY_OFF             | 0 | 0 | 0 ] //SONY_OFF
#define CAMERA_IR_ON                                0x05 // [ CAMERA_COMMON | CAMERA_IR_ON                | 0 | 0 | 0 ] //IR113_ON
#define CAMERA_IR_OFF                               0x06 // [ CAMERA_COMMON | CAMERA_IR_OFF               | 0 | 0 | 0 ] //IR113_OFF

#define CAMERA_SYSTEM_RESET                         0x09 // [ CAMERA_COMMON | CAMERA_SYSTEM_RESET         | 0 | 0 | 0 ]
#define CAMERA_STATUS_INQUIRY                       0x0A // [ CAMERA_COMMON | CAMERA_STATUS_INQUIRY       | 0 | 0 | 0 ]

#define CAMERA_SAVE_CONFIGURATION                   0x0B // [ CAMERA_COMMON | CAMERA_SAVE_CONFIGURATION   | 0 | 0 | 0 ]

// TV and IR Common
#define CAMERA_AUTO                                 0x10 // [ CAMERA_COMMON | CAMERA_AUTO                 | 0 | 0 | 0 ] //uC_2_uC_IR_AUTO
#define CAMERA_SEMIAUTO                             0x11 // [ CAMERA_COMMON | CAMERA_SEMIAUTO             | 0 | 0 | 0 ] //uC_2_uC_IR_SEMIAUTO
#define CAMERA_POLARITY_WHITE                       0x12 // [ CAMERA_COMMON | CAMERA_POLARITY_WHITE       | 0 | 0 | 0 ] //uC_2_uC_IR_POLARITY_White
#define CAMERA_POLARITY_BLACK                       0x13 // [ CAMERA_COMMON | CAMERA_POLARITY_BLACK       | 0 | 0 | 0 ] //uC_2_uC_IR_POLARITY_Black
#define CAMERA_CALIBRATION                          0x14 // [ CAMERA_COMMON | CAMERA_CALIBRATION          | 0 | 0 | 0 ] //uC_2_uC_IR_CALIBRATION
#define CAMERA_MENU                                 0x15 // [ CAMERA_COMMON | CAMERA_MENU                 | 0 | 0 | 0 ] //uC_2_uC_IR_MENU
#define CAMERA_MENU_INCREASE                        0x16 // [ CAMERA_COMMON | CAMERA_MENU_INCREASE        | 0 | 0 | 0 ] //uC_2_uC_IR_MENU_Increase
#define CAMERA_MENU_DECREASE                        0x17 // [ CAMERA_COMMON | CAMERA_MENU_DECREASE        | 0 | 0 | 0 ] //uC_2_uC_IR_MENU_Decreas
#define CAMERA_MENU_SET								0x18 // [ CAMERA_COMMON | CAMERA_MENU_SET			  | 0 | 0 | 0 ] //uC_2_uC_IR_MENU_Decreas
#define CAMERA_BACKGROUND_CALIBRATION				0x19 // [ CAMERA_COMMON | CAMERA_BACKGROUND_CALIBRATION			  | 0 | 0 | 0 ] //

#define CAMERA_BRIGHTNESS_VALUE                     0x20 // [ CAMERA_COMMON | CAMERA_BRIGHTNESS_VALUE     | u16_brightness_value | 0 ]
#define CAMERA_BRIGHTNESS_IN                        0x21 // [ CAMERA_COMMON | CAMERA_BRIGHTNESS_IN        | 0 | 0 | 0 ] //uC_2_uC_BRIGHTNEES_IN
#define CAMERA_BRIGHTNESS_OUT                       0x22 // [ CAMERA_COMMON | CAMERA_BRIGHTNESS_OUT       | 0 | 0 | 0 ] //uC_2_uC_BRIGHTNEES_OUT

//Safir IR
#define CAMERA_HORIZONTAL_INVERT                    0x23 // [ CAMERA_COMMON | CAMERA_HORIZENTAL_INVERT                | 0 | 0 | 0 ] //uC_2_uC_IR_HORIZENTAL_INVERT
#define CAMERA_HORIZONTAL_INVERT_OFF                0x24 // [ CAMERA_COMMON | CAMERA_HORIZENTAL_INVERT_OFF               | 0 | 0 | 0 ] //uC_2_uC_IR_HORIZENTAL_INVERT_OFF
#define CAMERA_VERTICAL_INVERT                      0x25 // [ CAMERA_COMMON | CAMERA_VERTICAL_INVERT                 | 0 | 0 | 0 ] //uC_2_uC_IR_VERTICAL_INVERT
#define CAMERA_VERTICAL_INVERT_OFF                  0x26 // [ CAMERA_COMMON | CAMERA_VERTICAL_INVERT_OFF                 | 0 | 0 | 0 ] //uC_2_uC_IR_VERTICAL_INVERT_OFF
#define CAMERA_ZOOM_WIDE							0x27 // [ CAMERA_COMMON | CAMERA_ZOOM_WIDE                 | 0 | 0 | 0 ] //uC_2_uC_ZOOM_WIDE


#define CAMERA_CONTRAST_VALUE                       0x28 // [ CAMERA_COMMON | CAMERA_CONTRAST_VALUE       | u16_contrast_value | 0 ]
#define CAMERA_CONTRAST_IN                          0x29 // [ CAMERA_COMMON | CAMERA_CONTRAST_IN          | 0 | 0 | 0 ] //uC_2_uC_CONTRAST_IN
#define CAMERA_CONTRAST_OUT                         0x2A // [ CAMERA_COMMON | CAMERA_CONTRAST_OUT         | 0 | 0 | 0 ] //uC_2_uC_CONTRAST_OUT

#define CAMERA_FOCUS_VALUE                          0x30 // [ CAMERA_COMMON | CAMERA_FOCUS_VALUE          | u16_focus_value | 0 ]
#define CAMERA_FOCUS_IN                             0x31 // [ CAMERA_COMMON | CAMERA_FOCUS_IN             | 0 | 0 | 0 ] //uC_2_uC_FOCUS_IN
#define CAMERA_FOCUS_OUT                            0x32 // [ CAMERA_COMMON | CAMERA_FOCUS_OUT            | 0 | 0 | 0 ] //uC_2_uC_FOCUS_OUT
#define CAMERA_FOCUS_STOP                           0x33 // [ CAMERA_COMMON | CAMERA_FOCUS_STOP           | 0 | 0 | 0 ] //uC_2_uC_FOCUS_STOP
#define CAMERA_FOCUS_AUTO                           0x34 // [ CAMERA_COMMON | CAMERA_FOCUS_AUTO           | 0 | 0 | 0 ] //FOCUS_AUTO_CMD
#define CAMERA_FOCUS_MANUAL                         0x35 // [ CAMERA_COMMON | CAMERA_FOCUS_MANUAL         | 0 | 0 | 0 ] //FOCUS_MANUEL_CMD
#define CAMERA_FOCUS_AUTO_ONE_TIME                  0x36 // [ CAMERA_COMMON | CAMERA_FOCUS_AUTO_ONE_TIME  | 0 | 0 | 0 ]  // enable both auto and manual mode

#define CAMERA_DISPLAY_RETICLE						0x37 // [ CAMERA_COMMON | CAMERA_DISPLAY_RETICLE	  | u8_reticle_number | 0 | 0 ]  // display reticle
#define CAMERA_HIDE_RETICLE 						0x38 // [ CAMERA_COMMON | HIDE_RETICLE				  | 0 | 0 | 0 ]  // hide reticle
#define CAMERA_RETICLE_X_SET						0x39 // [ CAMERA_COMMON | CAMERA_RETICLE_X_SET		  | s16_position_value | 0 ]  // set reticle position on X axis
#define CAMERA_RETICLE_X_PLUS						0x3A // [ CAMERA_COMMON | CAMERA_RETICLE_X_PLUS       | 0 | 0 | 0 ]  // increase reticle position on X axis
#define CAMERA_RETICLE_X_MINUS						0x3B // [ CAMERA_COMMON | CAMERA_RETICLE_X_MINUS      | 0 | 0 | 0 ]  // decrease reticle position on X axis
#define CAMERA_RETICLE_Y_SET						0x3C // [ CAMERA_COMMON | CAMERA_RETICLE_Y_SET		  | s16_position_value | 0 ]  // set reticle position on Y axis
#define CAMERA_RETICLE_Y_PLUS						0x3D // [ CAMERA_COMMON | CAMERA_RETICLE_Y_PLUS       | 0 | 0 | 0 ]  // increase reticle position on Y axis
#define CAMERA_RETICLE_Y_MINUS						0x3E // [ CAMERA_COMMON | CAMERA_RETICLE_Y_MINUS      | 0 | 0 | 0 ]  // decrease reticle position on Y axis
#define CAMERA_SAVE_RETICLE_DATA					0x3F // [ CAMERA_COMMON | CAMERA_SAVE_RETICLE_DATA      | 0 | 0 | 0 ]  // save reticle related data

#define CAMERA_ZOOM_VALUE                           0x40 // [ CAMERA_COMMON | CAMERA_ZOOM_VALUE           | u16_zoom_value | 0 ]
#define CAMERA_ZOOM_IN                              0x41 // [ CAMERA_COMMON | CAMERA_ZOOM_IN              | 0 | 0 | 0 ] //uC_2_uC_ZOOM_IN
#define CAMERA_ZOOM_OUT                             0x42 // [ CAMERA_COMMON | CAMERA_ZOOM_OUT             | 0 | 0 | 0 ] //uC_2_uC_ZOOM_OUT
#define CAMERA_ZOOM_STOP                            0x43 // [ CAMERA_COMMON | CAMERA_ZOOM_STOP            | 0 | 0 | 0 ] //uC_2_uC_ZOOM_STOP
#define CAMERA_ZOOM_NARROW							0x44 // [ CAMERA_COMMON | CAMERA_ZOOM_NARROW                 | 0 | 0 | 0 ] //uC_2_uC_ZOOM_NARROW

// Iris Commands
#define CAMERA_IRIS_VALUE							0x45 // [ CAMERA_COMMON | CAMERA_IRIS_VALUE          | u16_iris_value | 0 ]
#define CAMERA_IRIS_IN								0x46 // [ CAMERA_COMMON | CAMERA_IRIS_IN             | 0 | 0 | 0 ]
#define CAMERA_IRIS_OUT								0x47 // [ CAMERA_COMMON | CAMERA_IRIS_OUT            | 0 | 0 | 0 ]
// Safir IR
#define CAMERA_FOCUS_NEAR_STOP                       0x48 // [ CAMERA_COMMON | CAMERA_FOCUS_NEAR_STOP              | 0 | 0 | 0 ] //uC_2_uC_FOCUS_NEAR_STOP
#define CAMERA_FOCUS_FAR_STOP                        0x49 // [ CAMERA_COMMON | CAMERA_FOCUS_FAR_STOP            | 0 | 0 | 0 ] //uC_2_uC_FOCUS_FAR_STOP


// Sony TV Exclusive
#define CAMERA_HIGH_RESOLUTION_MODE                 0x50 // [ CAMERA_COMMON | CAMERA_HIGH_RESOLUTION_MODE | u8_switch | 0 | 0 ] // u8_switch contain {on = 1, off = 0}
#define CAMERA_INFRARED_MODE                        0x51 // [ CAMERA_COMMON | CAMERA_INFRARED_MODE        | u8_switch | 0 | 0 ]
#define CAMERA_POWER_MODE                           0x52 // [ CAMERA_COMMON | CAMERA_POWER_MODE           | u8_switch | 0 | 0 ]
#define CAMERA_FOCUS_MODE                           0x53 // [ CAMERA_COMMON | CAMERA_FOCUS_MODE           | u8_switch | 0 | 0 ]

//Safir IR
#define CAMERA_OPEN_DOOR                            0x54 // [ CAMERA_COMMON | CAMERA_OPEN_DOOR               | 0 | 0 | 0 ] //uC_2_uC_IR_OPEN_DOOR
#define CAMERA_CLOSE_DOOR                           0x55 // [ CAMERA_COMMON | CAMERA_CLOSE_DOOR                 | 0 | 0 | 0 ] //uC_2_uC_IR_CLOSE_DOOR
#define CAMERA_IMAGE_FREEZE                         0x56 // [ CAMERA_COMMON | CAMERA_IMAGE_FREEZE                 | 0 | 0 | 0 ] //uC_2_uC_IR_IMAGE_FREEZE 
#define CAMERA_IMAGE_LIVE                           0x57 // [ CAMERA_COMMON | CAMERA_IMAGE_LIVE                  | 0 | 0 | 0 ] //uC_2_uC_IR_IMAGE_LIVE
#define CAMERA_AGC_ON								0x58 // [ CAMERA_COMMON | CAMERA_AGC_ON	                 | 0 | 0 | 0 ] //uC_2_uC_IR_AGC_ON
#define CAMERA_AGC_OFF								0x59 // [ CAMERA_COMMON | CAMERA_AGC_OFF                 | 0 | 0 | 0 ] //uC_2_uC_IR_AGC_OFF




// Sh-Shiraz IR Exclusive
#define CAMERA_CROSSHAIR_DISPLAY                    0x60 // [ CAMERA_COMMON | CAMERA_CROSSHAIR_DISPLAY      | 0 | 0 | 0 ]
#define CAMERA_CROSSHAIR_HIDDEN                     0x61 // [ CAMERA_COMMON | CAMERA_CROSSHAIR_HIDDEN       | 0 | 0 | 0 ]
#define CAMERA_CROSSHAIR_X_COORDINATE               0x62 // [ CAMERA_COMMON | CAMERA_CROSSHAIR_X_COORDINATE | data_low | data_high | 0 ] // Set cross hair X coordinate to a specific value, range = [0, 720], default = 340.
#define CAMERA_CROSSHAIR_Y_COORDINATE               0x63 // [ CAMERA_COMMON | CAMERA_CROSSHAIR_Y_COORDINATE | data_low | data_high | 0 ] // Set cross hair Y coordinate to a specific value, range = [0, 576], default = 288.
#define CAMERA_MANUAL_BACKGROUND_ADJUSTMENT         0x64 // [ CAMERA_COMMON | CAMERA_MANUAL_BACKGROUND_ADJUSTMENT | 0 | 0 | 0 ]
#define CAMERA_MANUAL_SHUTTER_ADJUSTMENT            0x65 // [ CAMERA_COMMON | CAMERA_MANUAL_SHUTTER_ADJUSTMENT    | 0 | 0 | 0 ]
//#define CAMERA_IMAGE_ENHANCEMENT_ON                   0x76 // [ CAMERA_COMMON | CAMERA_IMAGE_ENHANCEMENT_ON   | 0 | 0 | 0 ]
//#define CAMERA_IMAGE_ENHANCEMENT_OFF                  0x77 // [ CAMERA_COMMON | CAMERA_IMAGE_ENHANCEMENT_OFF  | 0 | 0 | 0 ]
#define CAMERA_CROSSHAIR_X_COORDINATE_PLUS          0x66 // [ CAMERA_COMMON | CAMERA_CROSSHAIR_X_COORDINATE_PLUS | 0 | 0 | 0 ]
#define CAMERA_CROSSHAIR_X_COORDINATE_MINUS         0x67 // [ CAMERA_COMMON | CAMERA_CROSSHAIR_X_COORDINATE_MINUS | 0 | 0 | 0 ]
#define CAMERA_CROSSHAIR_Y_COORDINATE_PLUS          0x68 // [ CAMERA_COMMON | CAMERA_CROSSHAIR_Y_COORDINATE_PLUS | 0 | 0 | 0 ]
#define CAMERA_CROSSHAIR_Y_COORDINATE_MINUS         0x69 // [ CAMERA_COMMON | CAMERA_CROSSHAIR_Y_COORDINATE_MINUS | 0 | 0 | 0 ]



// CamVD565 IR Exclusive
#define CAMERA_MODE_INCREASE                        0x7B // [ CamVD565_COMMON | CamVD565_MODE_INCREASE    | 0 | 0 | 0 ] //PC_2_CamVD565_Mode_Increse
#define CAMERA_MODE_DECREASE                        0x7C // [ CamVD565_COMMON | CamVD565_MODE_DECREASE    | 0 | 0 | 0 ] //PC_2_CamVD565_Mode_Decrease
#define CAMERA_MODE_CALIBRATION                     0x7D // [ CamVD565_COMMON | CamVD565_MODE_CALIBRATION | 0 | 0 | 0 ] //PC_2_CamVD565_Mode_Calbraition
#define CAMERA_BUTTON_REBOUND                       0x7E // [ CamVD565_COMMON | CamVD565_BUTTON_REBOUND   | 0 | 0 | 0 ] //PC_2_CamVD565_Button_Rebound
#define CAMERA_CONFIGURATION                        0x7F // [ CamVD565_COMMON | CamVD565_CONFIGURATION    | 0 | 0 | 0 ] //Camera_VD565_Configuration


// Laser
#define LASER_COMMON                                0xB1     // [ LASER_COMMON | command                      | 0 | 0 | 0 ]
#define LASER_ON                                    0x01 // [ LASER_COMMON | LASER_ON                     | 0 | 0 | 0 ] //LEASER_ON
#define LASER_OFF                                   0x02 // [ LASER_COMMON | LASER_OFF                    | 0 | 0 | 0 ] //LEASER_OFF
#define LASER_SHOOT                                 0x03 // [ LASER_COMMON | LASER_SHOOT                  | 0 | 0 | 0 ]
#define LASER_CHARGE                                0x04 // [ LASER_COMMON | LASER_CHARGE                 | 0 | 0 | 0 ]
#define LASER_CANCEL                                0x05 // [ LASER_COMMON | LASER_CANCEL                 | 0 | 0 | 0 ]
#define LASER_SET_BLOCK_DISTANCE                    0x06 // [ LASER_COMMON | LASER_SET_BLOCK_DISTANCE     | u16_distance | 0 ]
#define LASER_ON_AND_SHOOT                          0x07 // enable laser range finder then shoot, and disable it after reading data
#define LASER_SET_CHARGING_TIME_MILLI_SECONDS       0x11 // [ LASER_COMMON | LASER_SET_CHARGING_TIME_MILLI_SECONDS | u16_time | 0 ]
#define LASER_SET_TIMEOUT_TIME_MILLI_SECONDS        0x12 // [ LASER_COMMON | LASER_SET_TIMEOUT_TIME_MILLI_SECONDS  | u16_time | 0 ]
#define LASER_SET_INHIBIT_TIME_MILLI_SECONDS        0x13 // [ LASER_COMMON | LASER_SET_INHIBIT_TIME_MILLI_SECONDS  | u16_time | 0 ]
#define LASER_SET_REPETITION_PERIOD_MILLI_SECONDS   0x14 // [ LASER_COMMON | LASER_SET_REPETITION_PERIOD_MILLI_SECONDS | u16_time | 0 ] // for fadak41
#define LASER_DISABLE				                0x15 // [ LASER_COMMON | LASER_DISABLE | 0 | 0 ] // for fadak41
#define LASER_ENABLE                                0x16 // [ LASER_COMMON | LASER_ENABLE  | 0 | 0 ] // for fadak41
#define LASER_CHARGE_AND_SHOOT                      0x17 // [ LASER_COMMON | LASER_CHARGE_AND_SHOOT  | 0 | 0 ] // for fadak41
#define LASER_AUTO_SHOOT                            0x18 // [ LASER_COMMON | LASER_CHARGE_AND_SHOOT  | 0 | 0 ] // for fadak41
#define LASER_AUTO_ENABLE_OFF                       0x19 // [ LASER_COMMON | LASER_AUTO_ENABLE_OFF   | 0 | 0 ] // for fadak41
#define LASER_AUTO_ENABLE_ON                        0x1A // [ LASER_COMMON | LASER_AUTO_ENABLE_ON    | 0 | 0 ] // for fadak41

#define RELAY_COMMON                            	0xB2
#define RELAY_USE_TV                                0x01
#define RELAY_USE_IR                                0x02
#define RELAY_TV_OFF                                0x03
#define RELAY_TV_ON                                 0x04
#define RELAY_IR_OFF                                0x05
#define RELAY_IR_ON                                 0x06
#define RELAY_LRF_OFF                               0x07
#define RELAY_LRF_ON                                0x08
#define RELAY_LRF_DISABLE                           0x09
#define RELAY_LRF_ENABLE                            0x0A

//------------------------------------ MAX_7456 loading characters into EEPROM ---------------------------------------

//#define MAX_7456_COMMON							0xB0 //Could we!!!
#define MAX_7456_LOAD_CHARACTER_ADRESS          0xB2 // [ MAX_7456_LOAD_CHARACTER_ADRESS   | u16_address  | 0 | 0 ] //MAX_7456_LOAD_CHARACTER_ADRESS
#define MAX_7456_LOAD_CHARACTER_BYTES           0xB3 // [ MAX_7456_LOAD_CHARACTER_BYTES    | ?                    ] //MAX_7456_LOAD_CHARACTER_BYTES
#define MAX_7456_SHIFT_HORIZONTAL_PIXELS        0xB4 // [ MAX_7456_SHIFT_HORIZONTAL_PIXELS | ?                    ] //MAX_7456_SHIFT_HORIZONTAL_PIXELS
#define MAX_7456_SHIFT_VERTICAL_PIXELS          0xB5 // [ MAX_7456_SHIFT_VERTICAL_PIXELS   | ?                    ] //MAX_7456_SHIFT_VERTICAL_PIXELS

//------------------------------------ to PT_3001CR ---------------------------------------
#define PT3001CR_COMMON                         0xB6     // [ PT3001CR_COMMON   | u8_command               | 0 | 0 | 0 ]
#define PT3001CR_MOVE_LEFT                          0x01 // [ PT3001CR_COMMON   | PT3001CR_MOVE_LEFT       | 0 | 0 | 0 ] //uC_2_PT_3001CR_PAN_LEFT
#define PT3001CR_MOVE_RIGHT                         0x02 // [ PT3001CR_COMMON   | PT3001CR_MOVE_RIGHT      | 0 | 0 | 0 ] //uC_2_PT_3001CR_PAN_RIGHT
#define PT3001CR_MOVE_UP                            0x03 // [ PT3001CR_COMMON   | PT3001CR_MOVE_UP         | 0 | 0 | 0 ] //uC_2_PT_3001CR_TILT_UP
#define PT3001CR_MOVE_DOWN                          0x04 // [ PT3001CR_COMMON   | PT3001CR_MOVE_DOWN       | 0 | 0 | 0 ] //uC_2_PT_3001CR_TILT_DOWN
#define PT3001CR_MOVE_UP_RIGHT                      0x05 // [ PT3001CR_COMMON   | PT3001CR_MOVE_UP_RIGHT   | 0 | 0 | 0 ] //PC_2_uC_TILT_UP_PAN_RIGHT
#define PT3001CR_MOVE_DOWN_RIGHT                    0x06 // [ PT3001CR_COMMON   | PT3001CR_MOVE_DOWN_RIGHT | 0 | 0 | 0 ] //PC_2_uC_TILT_DOWN_PAN_RIGHT
#define PT3001CR_MOVE_UP_LEFT                       0x07 // [ PT3001CR_COMMON   | PT3001CR_MOVE_UP_LEFT    | 0 | 0 | 0 ] //PC_2_uC_TILT_UP_PAN_LEFT
#define PT3001CR_MOVE_DOWN_LEFT                     0x08 // [ PT3001CR_COMMON   | PT3001CR_MOVE_DOWN_LEFT  | 0 | 0 | 0 ] //PC_2_uC_TILT_DOWN_PAN_LEFT

//we could use PAN_POSITION_REF instead ?
#define PT3001CR_SET_PAN_POSITION               0xB7 // [ PT3001CR_SET_PAN_POSITION  | ? ] //uC_2_PT_3001CR_SET_PAN_POSITION
#define PT3001CR_SET_TILT_POSITION              0xB8 // [ PT3001CR_SET_TILT_POSITION | ? ] //uC_2_PT_3001CR_SET_TILT_POSITION

//#define PT3001CR_GROUP_POSITION					0xAE//uC_2_PT_3001CR_GROUP_POSITION

//------------------------------------ to Load "Telescope" ---------------------------------------
// Header of Telescope Frames
#define TELESCOPE_COMMON                        0xB9     // [ TELESCOPE_COMMON | u8_command                | 0 | 0 | 0 ]
#define TELESCOPE_DIRECTION_RESET                   0x01 // [ TELESCOPE_COMMON | TELESCOPE_DIRECTION_RESET | 0 | 0 | 0 ] //uC_2_PC_TELESCOPE_RESET_DIR
#define TELESCOPE_ELEVETION_RESET                   0x02 // [ TELESCOPE_COMMON | TELESCOPE_ELEVETION_RESET | 0 | 0 | 0 ] //uC_2_PC_TELESCOPE_RESET_ELV
#define TELESCOPE_REQUEST_DATA                      0x03 // [ TELESCOPE_COMMON | TELESCOPE_REQUEST_DATA    | 0 | 0 | 0 ] //uC_2_PC_TELESCOPE_DATA_REQUEST
//#define Telescope_SilentMode					    0x04//uC_2_PC_TELESCOPE_SILENT_MODE	!!!
//#define Telescope_BavardMode					    0x05//uC_2_PC_TELESCOPE_BAVARD_MODE !!!


//#define                                       0xBA
//#define                                       0xBB
//#define                                       0xBC
//#define                                       0xBD
//#define                                       0xBE
//#define                                       0xBF

//#define                                       0xC0
//#define                                       0xC1
//#define                                       0xC2
//#define                                       0xC3
//#define                                       0xC4
//#define                                       0xC5
//#define                                       0xC6
//#define                                       0xC7
//#define                                       0xC8
//#define                                       0xC9
//#define                                       0xCA
//#define                                       0xCB
//#define                                       0xCC
//#define                                       0xCD
//#define                                       0xCE
//#define                                       0xCF

//#define                                       0xD0
//#define                                       0xD1
//#define                                       0xD2
//#define                                       0xD3
//#define                                       0xD4
//#define                                       0xD5
//#define                                       0xD6
//#define                                       0xD7
//#define                                       0xD8
//#define                                       0xD9
//#define                                       0xDA
//#define                                       0xDB
//#define                                       0xDC
//#define                                       0xDD
//#define                                       0xDE
//#define                                       0xDF


//------------------------------------ Inquiry ---------------------------------------3 / 16

//------------------------------------ to PT_3001CR or from it ---------------------------------------
#define QUERY_PT3001CR_PAN_POSITION             0xE0 // [ QUERY_PT3001CR_PAN_POSITION      | 0 | 0 | 0 | 0 ] // pc_send     //uC_2_PT_3001CR_QUERY_PAN_POSITION	//Spec
// [ QUERY_PT3001CR_PAN_POSITION      | u16_position  ] // pc_receive

#define QUERY_PT3001CR_TILT_POSITION            0xE1 // [ QUERY_PT3001CR_TILT_POSITION     | 0 | 0 | 0 | 0 ] // pc_send     //uC_2_PT_3001CR_QUERY_TILT_POSITION	//Spec
// [ QUERY_PT3001CR_TILT_POSITION     | u16_position  ] // pc_receive

#define QUERY_PT3001CR_PAN_TILT_POSITION        0xE2 // [ QUERY_PT3001CR_PAN_TILT_POSITION | 0 | 0 | 0 | 0 ] // pc_send     //uC_2_PT_3001CR_QUERY_PAN_TILT_POSITION	//Spec
// [ QUERY_PT3001CR_PAN_TILT_POSITION | u16_pan_position | u16_tilt_position ] // pc_receive

//------------------------------------ to Load or from it ---------------------------------------
//#define QUERY_LOAD_ZOOM_AND_FOCUS			    0xE3 // [ QUERY_LOAD_ZOOM_AND_FOCUS      | 0 | 0 | 0 | 0 ] // pc_send
// [ QUERY_LOAD_ZOOM_AND_FOCUS      | u16_position  ] // pc_receive
// to [ 0 | 0 | 0 | 0 ], from [ u16_zoom : u16_focus ],    //ZOOM_INQUERY

//#define QUERY_LOAD_LRF						    0xE4    // to [ 0 | 0 | 0 | 0 ], from [ u16_target0 : u16_target1 ],   //LFR _INQUERY

//#define QUERY_LOAD                              0xE5    // will be sent to PC

//#define                                       0xE3
//#define                                       0xE4
//#define                                       0xE5
//#define                                       0xE6
//#define                                       0xE7
//#define                                       0xE8
//#define                                       0xE9
//#define                                       0xEA
//#define                                       0xEB
//#define                                       0xEC
//#define                                       0xED
//#define                                       0xEE
//#define                                       0xEF

//------------------------------------	Unused ---------------------------------------0 / 16
//#define 										0xF0
//#define 										0xF1
//#define 										0xF2
//#define 										0xF3
//#define 										0xF4
//#define 										0xF5
//#define 										0xF6
//#define 										0xF7
//#define 										0xF8
//#define 										0xF9
//#define 										0xFA
//#define 										0xFB
//#define 										0xFC
//#define 										0xFD
//#define 										0xFE
//#define 										0xFF

#define GEN_SAVE                                0xF0 //[GEN_SAVE            | u32_function_id]
#define GEN_LOAD                                0xF1 //[GEN_LOAD            | u32_function_id]
#define GEN_RESTORE_DEFAULT                     0xF2 //[GEN_RESTORE_DEFAULT | u32_function_id]
#define GEN_WRITE                               0xF3 //[GEN_WRITE           | u32_function_id]
#define GEN_READ                                0xF4 //[GEN_READ            | u32_function_id]
#define GEN_RESPONSE                            0xF5 //[GEN_READ            | u32_function_id]


//Spec
//#define JS_2_uC_DIGITAL_AND_ANALOG_INPUTS		0x47//to4SkidWheel





#define STATE_FAIL			0
#define STATE_OK			1

#define STATE_OFF			0
#define STATE_ON			1

#define STATE_FALSE			0
#define STATE_TRUE			1

#define STATE_DISABLE		0
#define STATE_ENABLE		1

#define STATE_DEACTIVATE	0
#define STATE_ACTIVATE		1


//note: When (Board ID = X), and (Unit ID = Y), send it to X board, Y Unit,
//  and When (Board ID = X), and (Unit ID = 0), send it to all units with (Board ID = X),
//  and When (Board ID = 0), send it to all boards.

// D = DIR = Direction			= P = PAN = Panoramic
// E = ELV(ELEV) = Elevation	= T = TIL(TILT)
// B = PANTILT = Pan and Tilt
// L = Load Board = "Camera", "Laser", "Telescope", "etc...".
// P = POS = Position
// V = VEL = Velocity
// A = ACC = Acceleration
// C = CTRL = Control
// PC = Personal Computer
// JS = Joystick
// uC = micro Controller
// Cam = Camera
// CONF = Configuration
// $ for future usage
// @ reused again and again

// for some reasons it has been applied a "inquiry" commands:
//  it send a command frame to ask for some data,
//  and receive that data with the same header.


//for GEN_STATUS:
//it's deferent from one part to another.
//for Load: {1:Day, 2:Night, 3:Laser} Camera


//TODO
//battery voltage and related functions.
//CURRENT LIMIT, VOLTAGE LIMIT


#endif // SYSTEMS_SERIAL_HEADERS_H
