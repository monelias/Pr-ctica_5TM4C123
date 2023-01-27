    #include "lib/include.h"
    
//_____________________________________Configuración PWM___________________________//


//____________________________________ Experimento 1 __________________________//
/*Usando el modulo 0 de PWM con una frecuencia de reloj del sistema de 50,000,000 Hz
  junto con el generador 1  habilitar alguno de los pwm's asociados y obtener un PWM
  cuya frecuencia sea de 10KHz
  usando el M0 PWM3 pin B5*/

extern void Configuracion_PWM_E1(uint16_t freq)
    {
// Pag 354 RCGCPWM proporciona la capacidad de activar y desactivar los módulos PWM
    SYSCTL->RCGCPWM |= (1<<0); // M0PWM

// Pag RCGCGPIO proporciona la capacidad de activar y desactivar modulos GPIO (puertos)
    SYSCTL->RCGCGPIO |= (1<<1); // Puerto B
   
// Pag 254 RCC Configura el reloj del PWM (divisorparafrecuencia) 
    SYSCTL-> RCC |= (0 << 20);// 0 al pin 20 ya que no se requiere un divisor

// Pag 671 GPIOAFSEL funciónes alternativas (analogico)
    GPIOB->AFSEL |=  (1<<5); // habilitación de pin B5

/*Pag 688 GPIOPCTL señal periférica para cada pin GPIO cuando se utiliza el modo de función alternativa,
    las funciones alternativas vienen en Pag 651*/   
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
    }
    
    
