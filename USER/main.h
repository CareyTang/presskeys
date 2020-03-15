/******************************define********************************/
#define KEY_PORT                             GPIOE
#define KEY_PIN                              GPIO_Pin_4
#define LED_PORT                             GPIOB
#define LED_PIN                              GPIO_Pin_5
#define ValuePressed                         0
#define ValueNotPressed                      1
#define TimeLongPress                        200
#define TimeDoublePress                      100
#define StateNotPressed                      0x11
#define StatePressed                         0x22
#define StateLongPress                       0x33
#define StateDoublePress                     0x44
#define StateSinglePress                     0x55
#define StateNextState                       0x66

/*******************************变量********************************/
extern int valueNow, //记录上一个TIM中断时读取的按键状态
           valueBefore;//记录当前TIM中断时读取的按键状态

extern int timePressed,//按键第一次被按下到抬起的时长
           timeBreak;//两次按键间隔时长
extern int cnt;//用来计算发生了多少次TIM
extern int stateNow;//定义初始状态为未按键状态

extern int isExtiEnable;//是否使能外部按键中断
extern int isPwmEnable;//是否使能PWM输出
extern int isIntHappen;//外部EXTI中断是否进入，相当于ucos的临界段，防止中断被打断
extern int valuePwm;//双击按键时输出的PWM比较值
extern int flagPwm ;//pwm占空比增加还是减少的标志位
extern int ValueBright[];//单击按键时输出的PWM三种亮度的值
extern int valueIndex;//单击按键时输出的PWM三种亮度的值的下标
extern int flagQuit;//初始状态下不退出当前的动作

/*************************函数定义********************/
void Single_Press(void);//单击动作函数
void Double_Press(void);//双击动作函数
void TIM3_Handler(void);//定时器TIM3中断处理函数
void EXTIX_Init(void);//外部中断处理函数
void CLEAR_ALL_PARA(void);//还原所有变量至初始化函数
