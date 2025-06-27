#ifndef MOTOR_H_
#define MOTOR_H_

#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "tim.h"
#include "pid.h"
#include "math.h"
#include "struct_typedef.h"

/**
  * @struct  Motor_InitTypeDef
  * @brief   电机初始化配置结构体 | Motor initialization config struct
  *
  * @note    包含 PWM 定时器、通道和方向控制 GPIO 信息
  *          Holds PWM timer, channel, and GPIO pins for direction control
  */
typedef struct {
    TIM_HandleTypeDef *htim;     /**< PWM 定时器句柄 | PWM timer handle */
    uint32_t Channel_1;            /**< PWM 通道 1| PWM channel */
    uint32_t Channel_2;            /**< PWM 通道 2| PWM channel */
    GPIO_TypeDef *IN1_GPIOx;     /**< 方向控制 IN1 端口 | Direction control IN1 port */
    uint16_t IN1_GPIO_Pin;       /**< 方向控制 IN1 引脚 | Direction control IN1 pin */
    GPIO_TypeDef *IN2_GPIOx;     /**< 方向控制 IN2 端口 | Direction control IN2 port */
    uint16_t IN2_GPIO_Pin;       /**< 方向控制 IN2 引脚 | Direction control IN2 pin */
} Motor_InitTypeDef;

/**
  * @struct  Motor
  * @brief   电机对象结构体 | Motor object struct
  *
  * @note    包含初始化配置、当前方向、目标转速和移动函数指针
  *          Contains init config, current direction, target RPM, and Move function pointer
  */
typedef struct Motor Motor;

typedef struct Motor {
    Motor_InitTypeDef Init;      /**< 初始化配置 | Init config */
    pid_type_def pid;
    uint8_t direction;           /**< 当前方向 (BRAKE/ FORWARD/ BACKWARD/ FREE)
                                       Current direction (BRAKE/FORWARD/BACKWARD/FREE) */
    fp32 setRPM;                /**< 当前目标转速 | Current target RPM */

    void (*Move)(struct Motor *self, uint8_t isBrake, fp32 setRPM);
    /**< 移动函数 | Move function */
} Motor;

/**
  * @brief   创建并初始化电机实例 | Create and initialize a Motor instance
  * @param   Init  电机初始化配置 | Motor initialization config
  * @return  返回初始化后的 Motor 对象 | Returns initialized Motor object
  */
Motor newMotor(Motor_InitTypeDef Init);

/**
  * @brief   控制电机运动 | Control motor movement
  * @param   self     指向 Motor 实例的指针 | Pointer to Motor instance
  * @param   isBrake  是否刹车 (1 = 刹车, 0 = 正/反转) | Brake flag (1=brake, 0=forward/reverse)
  * @param   setRPM   目标转速，可正可负 (正 = 正转, 负 = 反转) | Target RPM (positive=forward, negative=reverse)
  */
void Move(Motor *self, uint8_t isBrake, fp32 setRPM);

#endif /* MOTOR_H_ */
