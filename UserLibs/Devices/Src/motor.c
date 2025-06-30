#include "motor.h"
#include "car.h"

extern Car car;

/* 控制模式枚举 | Control modes */
#define BRAKE     0   /**< 刹车 | Brake */
#define FORWARD   1   /**< 正转 | Forward */
#define BACKWARD  2   /**< 反转 | Backward */
#define FREE      3   /**< 空闲 | Free */

/* 电机转速范围 | Motor RPM limits */
#define MOTOR_MIN_RPM 0     /**< 最小转速 | Min RPM */
#define MOTOR_MAX_RPM 330   /**< 最大转速 | Max RPM */

#define MOTOR_TIM_ARR 60000.0

#define MOTOR_PID_MAX_OUT MOTOR_TIM_ARR
#define MOTOR_PID_MAX_IOUT 30000.0

fp32 pid_k[3]={800.0,20.0,0.0};

/**
  * @brief   创建并初始化电机实例 | Create and initialize motor instance
  * @param   Init  电机初始化参数 | Motor initialization parameters
  * @return  返回 Motor 结构体 | Returns Motor struct
  */
Motor newMotor(Motor_InitTypeDef Init) {
    Motor m;
    m.Init = Init;                   // 保存初始化配置 | store Init config
    m.direction = BRAKE;             // 初始方向前进 | default direction FORWARD
    m.setRPM = MOTOR_MIN_RPM;        // 初始转速最小 | default RPM = MOTOR_MIN_RPM
    m.Move = Move;                   // 绑定 Move 函数 | bind Move function

    PID_init(&m.pid,PID_POSITION,pid_k,MOTOR_PID_MAX_OUT,MOTOR_PID_MAX_IOUT);

    HAL_TIM_PWM_Start(Init.htim, Init.Channel_1);  // 启动 PWM | start PWM on channel
    HAL_TIM_PWM_Start(Init.htim, Init.Channel_2);  // 启动 PWM | start PWM on channel

    return m;                        // 返回实例 | return instance
}

/**
  * @brief   控制电机动作 | Control motor action
  * @param   self    指向 Motor 实例 | Pointer to Motor instance
  * @param   isBrake 是否刹车 | Brake flag
  * @param   setRPM  目标 RPM，可正可负 | Target RPM (positive/negative)
  */
void Move(Motor *self, uint8_t isBrake, fp32 setRPM) {
    if (isBrake) {
        // 刹车：IN1、IN2 都高 | Brake: IN1/IN2 high
        __HAL_TIM_SET_COMPARE(self->Init.htim, self->Init.Channel_1, MOTOR_TIM_ARR);
        __HAL_TIM_SET_COMPARE(self->Init.htim, self->Init.Channel_2, MOTOR_TIM_ARR);
        self->direction = BRAKE;     // 方向设为刹车 | set direction BRAKE
    } else {
      PID_calc(&self->pid,car.encoder_l.rpm,setRPM);
      fp32 PWM_OUT = fabsf(self->pid.out);
        if (setRPM > 0) {
            // 正转：IN1 高、IN2 低 | Forward: IN1 high, IN2 low
            __HAL_TIM_SET_COMPARE(self->Init.htim, self->Init.Channel_1, PWM_OUT);
            __HAL_TIM_SET_COMPARE(self->Init.htim, self->Init.Channel_2, 0);
            self->direction = FORWARD; // 设置方向前进 | set direction FORWARD
        } else if (setRPM < 0) {
            // 反转：IN1 低、IN2 高 | Reverse: IN1 low, IN2 high
            __HAL_TIM_SET_COMPARE(self->Init.htim, self->Init.Channel_1, 0);
            __HAL_TIM_SET_COMPARE(self->Init.htim, self->Init.Channel_2, PWM_OUT);
            self->direction = BACKWARD; // 设置方向后退 | set direction BACKWARD
        } else {
            // 停止：IN1、IN2 都低 | Stop: IN1/IN2 low
            __HAL_TIM_SET_COMPARE(self->Init.htim, self->Init.Channel_1, 0);
            __HAL_TIM_SET_COMPARE(self->Init.htim, self->Init.Channel_2, 0);
        }
    }

    self->setRPM = (float)setRPM;    // 更新目标转速 | update target RPM
}
