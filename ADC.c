#include "lib/include.h"
//____________________________________ Configuración ADC ____________________________________________________/

/*Para el modulo 1 se asigna secuenciador 1 y los canales 1 3 4 correspondientes a los pines PE2,PE0 y PD3
PE0
PE2
PD3 */
extern void Configurar_ADC(void)
{
// Pag 352 RCGCADC cuando esta habilitado activa modulos de ADC proporcionando un reloj
    SYSCTL->RCGCADC = (1 << 1); // inicializar modulo 1

// Pag 340 Puertos para  habilitar señales de acuerdo a los canales 
//canal 1 pin PE2, canal 3 pin PE0, canal 4 pin PD3
    SYSCTL->RCGCGPIO |=  (1 << 3) | (1 << 4); // D,E

 // Pag 663 GPIODIR habilira los pines como entradas o salidas, 0 para input, 1 para output
      GPIOE->DIR = (0 << 0) | (0 << 2); // Puerto E (PE0, PE2)
      GPIOD->DIR =  (0 << 3); // puerto D (PD3)
      
// Pag 671 GPIOAFSEL funciónes alternativas (analogico)
      GPIOE->AFSEL = (1 << 0) | (1 << 2); // PE0, PE2 
      GPIOD->AFSEL = (1 << 3); // PD3
      
 // Pag 683 GPIODEN Habilita/deshabilita registro digital
      GPIOE->DEN = (0 << 0) | (0 << 2)| (0 << 2); // PE0, PE2
      GPIOD->DEN = (0 << 3); // PD3
        

/*Pag 688 GPIOPCTL señal periférica para cada pin GPIO cuando se utiliza el modo de función alternativa,
    las funciones alternativas vienen en Pag 1351*/
      GPIOE->PCTL = GPIOE->PCTL & (0xFFFFF0F0); // PE0, PE2
      GPIOD->PCTL = GPIOD->PCTL & (0xFFFF0FFF); // PD3

// P ag.687 GPIOAMSEL habilitar analogico
         GPIOE->AMSEL = (1 << 0) | (1 << 2) |(1 << 4); // PE0, PE2 
         GPIOD->AMSEL =  (1 << 3); // PD3

// Pag 891 El registro ADCPC  velocidad por segundo (0111) sete para 1Ms
         ADC1->PC = ((1 << 2) | (1 << 1) | (1 << 0)); // 1 Msps modulo 1

// Pag 841 ADCSSPRI configuracción de prioridad 0 para la mas alta y 3 a la más baja
         ADC1->SSPRI = 0x3102; // prioridad de secuenciador 1 = 0

// Pag 821 ADCACTSS Este registro controla la desactivación de los secuenciadores de muestras
            ADC1->ACTSS = (0 << 3) | (0 << 2) | (0 << 1) | (0 << 0);

// Pag 833 ADCEMUX selecciona el evento (trigger)
            ADC1->EMUX = (0x0000);//m1

// Pag 867 ADCSSMUX2 define la configuracion de entradas analógicas para cada muestra y secuencia (orden en que se da la lectura)
            ADC1->SSMUX1 = 0x0431; // Lectura 3 Canal 4  Lectura 2 Canal 3 Lectura 1 Canal 1

// pag 868 ADCSSCTL2 configura el ancho de bit de control de muestreo y de interrupción
            ADC1->SSCTL1 = (1 << 9) | (1 << 10); 
//Pag 825 Registro muy importante* controla/activa la interrupción cuando le llega un dato
            ADC1->IM |= (1 << 1); //sec1

// Pag 821 ADCACTSS activación de secuenciadores
            ADC1->ACTSS = (0 << 3) | (0 << 2) | (1 << 1) | (0 << 0); // Activa sec 1 m1
            ADC1->PSSI |= (1 << 1);                                  
}

extern void Lectura_ADC(uint16_t *Result) //**pendiente
{
    

//_______________________________Experimento 3_________________//
    /*utilizando el uart de la practica 3
  se enviara dato desde interfaz de simulink para controlar la intensidad luminosa
  usando un led RGB externa*/
       
    ADC1->PSSI = 0x00000002;           // 
    while ((ADC1->RIS & 0x02) == 0)
    {
    };                                 
    Result[0] = ADC1->SSFIFO1 & 0xFFF; // lectura de datos para veren grafica
    Result[1] = ADC1->SSFIFO1 & 0xFFF;  
    Result[2] = ADC1->SSFIFO1 & 0xFFF;
    ADC1->ISC = 0x0002;  
       duty[0] = (int) ((Result[0] * 6250) / 4096.0); 
       duty[1] = (int) ((Result[1] * 6250) / 4096.0); 
       duty[2] = (int) ((Result[2] * 6250) / 4096.0);                        
}

