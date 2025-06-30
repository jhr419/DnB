#include "car.h"
#include "pid.h"
#include "communication.h"
//#include "cmsis_os.h"

// 全局小车对象 | Global car instance
Car car;

// PID 输出变量 | PID output variables
int Vertical_out, Velocity_out, Turn_out;

/**
  * @brief   创建并初始化小车实例 | Create and initialize a car instance
  * @return  返回初始化后的 Car 对象 | Returns the initialized Car object
  */
Car newCar(void) {
    Car c = {
            .isBrake               = FALSE,    // 刹车标志 | Brake flag
            .motionState           = CAR_MOTION_STOP, // 当前运动状态 | Current motion state
            .targetLinearSpeed     = 0,        // 目标线速度 | Target linear speed
            .targetAngularSpeed    = 0,        // 目标角速度 | Target angular speed
            .targetStartLinearSpeed= 8,        // 初始启动速度 | Initial start speed
            .balanceBias           = MECHANICAL_BALANCE_BIAS, // 平衡偏置 | Balance bias
            .cmd                   = CMD_STOP  // 默认命令 | Default command
    };

    // 左电机初始化参数 | Left motor init parameters
    Motor_InitTypeDef motor_l_Init = {
            .htim         = &MOTOR_TIM,
            .Channel_1    = MOTOR_L_CHANNEL_1,
            .Channel_2    = MOTOR_L_CHANNEL_2,
            .IN1_GPIOx    = MOTOR_L_IN1_PORT,
            .IN1_GPIO_Pin = MOTOR_L_IN1_PIN,
            .IN2_GPIOx    = MOTOR_L_IN2_PORT,
            .IN2_GPIO_Pin = MOTOR_L_IN2_PIN
    };

    // 右电机初始化参数 | Right motor init parameters
    Motor_InitTypeDef motor_r_Init = {
            .htim         = &MOTOR_TIM,
            .Channel_1    = MOTOR_R_CHANNEL_1,
            .Channel_2    = MOTOR_R_CHANNEL_2,
            .IN1_GPIOx    = MOTOR_R_IN1_PORT,
            .IN1_GPIO_Pin = MOTOR_R_IN1_PIN,
            .IN2_GPIOx    = MOTOR_R_IN2_PORT,
            .IN2_GPIO_Pin = MOTOR_R_IN2_PIN
    };

    // 创建左右电机对象 | Create motor instances
    c.motor_l = newMotor(motor_l_Init);
    c.motor_r = newMotor(motor_r_Init);

    // 初始化左右编码器 | Initialize encoders
    c.encoder_l = newEncoder(&ENCODER_L_TIM, TIM_CHANNEL_ALL);
    c.encoder_r = newEncoder(&ENCODER_R_TIM, TIM_CHANNEL_ALL);

    // 初始化并启用 IMU | Initialize and enable IMU
    c.imu = newImu();
    c.imu.Enable(&c.imu);

    // 绑定移动函数 | Bind move function
    c.CarMove = CarMove;

    return c;
}

/**
  * @brief   小车移动控制函数 | Car movement control function
  * @param   self      指向 Car 对象的指针 | Pointer to Car object
  * @param   setSpeed  未使用参数，可保留 | Unused parameter, can be retained
  * @note    调用 PID 计算，判断刹车条件，并设置左右电机 PWM | Run PID, check brake, set left/right motor PWM
  */
void CarMove(Car *self, int8_t setSpeed) {
//    int32_t PWM_out, motor_l_pwm, motor_r_pwm;

//    checkMotionCommand();  // 更新目标速度 | Update target speeds

    // 发送 PWM 给电机并处理刹车 | Send PWM to motors and handle brake
//    self->motor_l.Move(&self->motor_l, car.isBrake, motor_l_pwm);
//    self->motor_r.Move(&self->motor_r, car.isBrake, motor_r_pwm);
}
