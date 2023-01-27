#include "lib/include.h"
int main(void)
{
    Configurar_PLL_E1();      //Confiuracion de Frecuencia de velocidad de sistema
    //Configurar_ADC();
   // ConfiguracionPWM(50);
   Configuracion_PWM_E1(10000); //configuracion de frecuencia de reloj del sistema E1
      while(1)
    {

    }
}