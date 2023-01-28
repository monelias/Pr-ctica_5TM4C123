    #include "lib/include.h"
    
//_____________________________________Configuración PWM___________________________//


//____________________________________ Experimento 1 __________________________//
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 50,000,000 Hz
  junto con el generador 1  habilitar alguno de los pwm's asociados y obtener un PWM
  cuya frecuencia sea de 10KHz
  usando el M0 PWM3 pin B5*/

/*extern void Configuracion_PWM_E1(uint16_t freq)
    {
// Pag 354 RCGCPWM proporciona la capacidad de activar y desactivar los módulos PWM
    SYSCTL->RCGCPWM |= (1<<0); // M0PWM

// Pag RCGCGPIO proporciona la capacidad de activar y desactivar modulos GPIO (puertos)
    SYSCTL->RCGCGPIO |= (1<<1); // Puerto B
   
// Pag 254 RCC Configura el reloj del PWM (divisorparafrecuencia) 
    SYSCTL-> RCC |= (0 << 20);// 0 al pin 20 ya que no se requiere un divisor

// Pag 671 GPIOAFSEL funciónes alternativas (analogico)
    GPIOB->AFSEL |=  (1<<5); // habilitación de pin B5

/Pag 688 GPIOPCTL señal periférica para cada pin GPIO cuando se utiliza el modo de función alternativa,
    las funciones alternativas vienen en Pag 651 /   
    GPIOB->PCTL &= ~(0xFF0FFFFF); //habilitación de la función 4 de acuerdo a la tambla
    GPIOB->PCTL |=  (0x00400000); // M0PWM3
   
// Pag 683 GPIODEN Habilita/deshabilita registro digital
   GPIOB->DEN |= (1<<5); 
  
//  Pag 1270 pwm block enable Este registro proporciona control sobre los bloques de PWM
    PWM0->_1_CTL &= ~(1<<0); // apagao
    PWM0->_1_CTL &= ~(1<<1); //

 
// Pag 1232/1239 generación de señal dependiendo del pwm
    PWM0->_1_GENB = (0x0000080C); 
    

    PWM0->_1_LOAD = (int)(50000000/freq); //carga 
    
    PWM0->_1_CMPB = (int)((1.0 - (50 / 100.0)) * (50000000/freq)); //ciclo de trabajo 


    PWM0->_1_CTL = (1<<0); 

    PWM0->ENABLE = (1<<3); 
    } */
    
//_______________________________________ Experimento 2 ___________________________________
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 20,000,000 Hz
  junto con el genemrador 0,1,2  habilitar alguno de los pwm's asociados y obtener un PWM
  cuya frecuencia sea de 50Hz con tres potenciometros variar el ciclo de trabajo
  para controlar la posicion de tres s
  ervos sg90 o otros.
  PB7
  PB4
  PE4 */

  
extern void Configuracion_PWM_E1(uint16_t freq)
    {
// Pag 354 RCGCPWM proporciona la capacidad de activar y desactivar los módulos PWM
    SYSCTL->RCGCPWM |= (1<<0); // M0PWM

// Pag 1233 RCGCGPIO proporciona la capacidad de activar y desactivar modulos GPIO (puertos)*dependiendo de los generadores
// generador 0 PB7 pwm1, generador 1 PB4 pwm2, generador 2 PE4 pwm4 
    SYSCTL->RCGCGPIO |= (1<<1)|(1<<4); 

// Pag 254 RCC Configura el reloj del PWM (divisorparafrecuencia) 
    SYSCTL-> RCC |= (1 << 20) | (1 << 19) | (0 << 18) | (1 << 17); // 0 al pin 20 ya que no se requiere un divisor

// Pag 671 GPIOAFSEL funciónes alternativas (analogico) 
    GPIOB->AFSEL |=  (1<<7) | (1<<4); //B7,B4
    GPIOE->AFSEL |=  (1<<4); // E4

/*Pag 688 GPIOPCTL señal periférica para cada pin GPIO cuando se utiliza el modo de función alternativa,
    las funciones alternativas vienen en Pag 651 */   
    GPIOB->PCTL &= ~(0x0FF0FFFF); //B7,B4 función 4
    GPIOB->PCTL |=  (0x40040000); //B7,B4 función 4
    GPIOE->PCTL &= ~(0xFFF0FFFF); //E4 función 4
    GPIOE->PCTL |=  (0x00040000); //E4 función 4
   
// Pag 683 GPIODEN Habilita/deshabilita registro digital
   GPIOB->DEN |= (1<<7) | (1<<4); //B7, B4
   GPIOE->DEN |= (1<<4); //E4
  
//  Pag 1270 pwm block enable Este registro proporciona control sobre los bloques de PWM
    PWM0->_1_CTL &= ~(1<<0); // apagao
    PWM0->_1_CTL &= ~(1<<1); 

    PWM0->_1_CTL &= ~(1<<0); 
    PWM0->_1_CTL &= ~(1<<1); 
    PWM0->_2_CTL &= ~(1<<0); 
    PWM0->_2_CTL &= ~(1<<1); 

    PWM0->_0_GENB = (0x0000080C); //1232
    PWM0->_1_GENA = (0x0000008C); 
    PWM0->_2_GENA = (0x0000008C); 

    PWM0->_0_LOAD = (int)(312500/freq); 
    PWM0->_1_LOAD = (int)(312500/freq); 
    PWM0->_2_LOAD = (int)(312500/freq); 

    PWM0->_0_CMPB = (int)((1.0 - (50 / 100.0)) * (312500/freq));//frecuencia
    PWM0->_1_CMPA = (int)((1.0 - (50 / 100.0)) * (312500/freq));
    PWM0->_2_CMPA = (int)((1.0 - (50/ 100.0)) * (312500/freq));

    PWM0->_0_CTL = (1<<0); 
    PWM0->_1_CTL = (1<<0);
    PWM0->_2_CTL = (1<<0);

    PWM0->ENABLE = (1<<1)|(1<<2)|(1<<4); 
    } 
    
