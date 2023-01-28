#include "lib/include.h"
int main(void)
{
  uint16_t duty[3];
  uint16_t Result[3];
 //Configurar_PLL_E1(_50);      // E1 Confiuracion de Frecuencia de velocidad de sistema
 //Configuracion_PWM_E1(10000); //E1 configuracion de frecuencia de reloj del sistema 
 Configurar_PLL_E1(); 
 Configurar_ADC();
 Configuracion_PWM_E1(50);
      while(1)
  {
    Lectura_ADC(Result,duty); //llamada a la conversion por procesador
       PWM0->_0_CMPB = duty[0];
       PWM0->_1_CMPA = duty[1];
       PWM0->_2_CMPA = duty[2];
    }
} 