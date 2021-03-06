
#include "kernelcoop.h"

#include <common_types.h>
#include <system.h>
#include <uart.h>
#include <uda1341ts.h>
#include <s3cev40.h>
#include <s3c44b0x.h>
#include <Keypad.h>
#include <timers.h>
#include <rtc.h>
#include <pbs.h>
#include <lcd.h>
#include <iis.h>
#include "sintesisVoz.h"
#include "draw.h"

#define INIT    (0)
#define RUN        (1)

#define WAIT_KEYDOWN (1)
#define SCAN         (2)
#define WAIT_KEYUP   (3)
#define END_SCAN     (4)

/* Declaraci?n de recursos */
uint8 Alarmmin;
uint8 Alarmhour;
uint8 PbScancode;
uint8 scancode 	   = KEYPAD_FAILURE ;
boolean Alarm      = FALSE;
boolean PbLeft	   = FALSE;
boolean PbRight    = FALSE;
boolean flaglcd    = TRUE;
boolean flagTask5  = FALSE;


volatile boolean pb_pressed = FALSE;

/* Declaraci?n de tareas */

void Task1( uint32 *state, uint32 *period );
void Task2( uint32 *state, uint32 *period );
void Task3( uint32 *state, uint32 *period );
void Task4( uint32 *state, uint32 *period );
void Task5( uint32 *state, uint32 *period );
void Task6( uint32 *state, uint32 *period );

/* Declaraci?n de RTI */

void isr_pb( void ) __attribute__ ((interrupt ("IRQ")));
void isr_keypad( void ) __attribute__ ((interrupt ("IRQ")));


void main( void )
{
	      /* Inicializa el sistema */
	timers_init();
	leds_init();
	segs_init();
	rtc_init();
	pbs_init();
	keypad_init();
	sys_init();										 /* Inicializa sistemas y perif?ricos */
	uart0_init();
	lcd_init();
    uda1341ts_init();
    iis_init( IIS_POLLING );

          /* Muestra mensaje por la UART0 (conectar termite) */

    lcd_clear();
    lcd_on();
	//lcd_puts( 20, 16, BLACK, "Recitando El Quijote" );          /* Muestra mensaje por el LCD (regular contraste) */

    uda1341ts_setvol( VOL_MAX );



    scheduler_init();


    create_task( Task1, INIT, 50 );   /* Crea las tareas de la aplicaci?n */
    create_task( Task2, INIT, 10 );   /* La prioridad de las tareas es seg?n el orden de creaci?n: Task1 > Task2 > Task3 > ... */
    create_task( Task3, INIT, 50 );
    create_task( Task4, INIT, 30 );
    create_task( Task5, INIT, 30 );
    create_task( Task6, INIT, 50);                          /* Instala isr_pb como RTI por presi?n de pulsadores  */

    timer0_open_tick( scheduler, TICKS_PER_SEC );  /* Instala scheduler como RTI del timer0  */
       pbs_open( isr_pb );                            /* Instala isr_pb como RTI por presi?n de pulsadores  */
       keypad_open( isr_keypad );
      while( 1 )
      {
          sleep();        /* Entra en estado IDLE, sale por interrupci?n */



          dispacher();  /* Todas las tareas preparadas se ejecutan en esta hebra en orden de prioridad */
      }

  }



void Task1( uint32 *state, uint32 *period )
{
	 rtc_time_t rtc_time;

	    switch( *state )
	    {
	        case INIT:
	            uart0_puts( " Task 1: iniciada.\n" );  /* Muestra un mensaje inicial en la UART0 (no es necesario sem?foro) */
	            *state = RUN;
	            break;
	        default:                       /* Cada 1s se escribe por pantalla la hora  */
	        	if(flaglcd==TRUE){

	        	rtc_gettime( &rtc_time );
	        	 lcd_puts_x2(160,80,0xf,":");
	        	 if(rtc_time.hour<10){
	        		 lcd_putintx10(5,32,0xf,0);
	        		 lcd_putintx10(80,32,0xf,rtc_time.hour);
	        	 }
	        	 else{
	        		 lcd_putintx10(5,32,0xf,rtc_time.hour);
	        	 }
	        	 if(rtc_time.min<10){
	        		 lcd_putintx10(180,32,0xf,0 );
	        		 lcd_putintx10(260,32,0xf,rtc_time.min );
	        	 }
	        	 else
                lcd_putintx10(180,32,0xf,rtc_time.min );
	        	}
	        	 break;
	    };
}

void Task2( uint32 *state, uint32 *period )  /* Cada 0,1 segundos (10 ticks) muestrea el keypad y env?a el scancode a otras tareas */
{
    switch( *state )
    {
        case INIT:
            uart0_puts( " Task 2: iniciada.\n" );  /* Muestra un mensaje inicial en la UART0 (no es necesario sem?foro) */
            *state = WAIT_KEYDOWN;
            break;
        case WAIT_KEYDOWN:
          if(scancode==KEYPAD_KEY2){
        	  flagTask5=TRUE;
          }
          break;
    };
}

void Task3( uint32 *state, uint32 *period  )
{
    rtc_time_t rtc_time;

    switch( *state )
    {
        case INIT:
            uart0_puts( " Task 3: iniciada.\n" );  /* Muestra un mensaje inicial en la UART0 (no es necesario sem?foro) */
            *state = RUN;
            break;
        default:
        	if(PbLeft==TRUE){

        		rtc_gettime( &rtc_time );
        		if(rtc_time.hour!=1){
        		iis_textToSpeech( "Las" );
        		}else	iis_textToSpeech( "La" );
        		iis_textToSpeechInteger((uint32)rtc_time.hour);
        		 uart0_putint((uint32)rtc_time.hour);
        		 uart0_puts(":");
        		 uart0_putint((uint32)rtc_time.min);
        		iis_textToSpeech(" horas y ");
        		iis_textToSpeechInteger((uint32)rtc_time.min);
        		iis_textToSpeech(" minutos");
        		PbLeft=FALSE;
        	}
            break;
    };
}


void Task4( uint32 *state, uint32 *period )
{
	 rtc_time_t rtc_time;
	 uint8 ajustes;
    switch( *state )
    {
        case INIT:
            uart0_puts( " Task 4: iniciada.\n" );
            *state = RUN;
            break;
        default:

        	if(PbRight==TRUE){
        	ajustes=0;
        	flaglcd=FALSE;
        	PbRight=FALSE;
        	rtc_gettime( &rtc_time );
        	while(ajustes<3){

           lcd_puts_x2(160,80,0xf,":");
        		if(rtc_time.hour<10){
        		lcd_putintx10(5,32,0xf,0);
        		lcd_putintx10(80,32,0xf,rtc_time.hour);
        			 }
        		 else{
        	    lcd_putintx10(5,32,0xf,rtc_time.hour);
        		 }

            if(ajustes<2){
            	if(rtc_time.min<10){
            	 lcd_putintx10(180,32,0xf,0 );
            	 lcd_putintx10(260,32,0xf,rtc_time.min );
            	  }
            	 else{
            	 lcd_putintx10(180,32,0xf,rtc_time.min );
            	 }
            }
            else{
            	if(rtc_time.sec<10){
            	lcd_putintx10(180,32,0xf,0 );
            	lcd_putintx10(260,32,0xf,rtc_time.sec );
            	}
            	else{
            	lcd_putintx10(180,32,0xf,rtc_time.sec );
            	}

            }
            if(ajustes==0){
            lcd_puts_x2(5,160,0xf,"Editando horas");
            iis_textToSpeech("Editando horas");
            }else if(ajustes==1){
            lcd_puts_x2(5,160,0xf,"Editando minutos");
            iis_textToSpeech("Editando minutos");
            }
            else if(ajustes==2){
            iis_textToSpeech("Editando segundos");
            lcd_puts_x2(5,160,0xf,"Editando segundos");
            }
            if(scancode==KEYPAD_KEY0){

            	if(ajustes==0){
            		rtc_time.hour++;
            		iis_textToSpeech("sumando horas");
            	}
            	else if(ajustes==1){
            		rtc_time.min++;
            		iis_textToSpeech("sumando minutos");
            	}else{
            		rtc_time.sec++;
            		iis_textToSpeech("sumando segundos");
            	}
            }
            if(scancode==KEYPAD_KEY1){

                 if(ajustes==0){
                 	rtc_time.hour--;
                 	iis_textToSpeech("restando horas");
                 }
                 else if(ajustes==1){
                    rtc_time.min--;
                    iis_textToSpeech("restando minutos");
                 }else{
                	rtc_time.sec--;
                	iis_textToSpeech("restando segundos");
                 }
          	 }
            scancode = KEYPAD_FAILURE;
            if(PbRight==TRUE){
            	ajustes++;
            	PbRight=FALSE;
            }
            PbScancode=0;
        	}
        	lcd_clear();
            rtc_puttime(&rtc_time);
            PbRight = FALSE;
            flaglcd=TRUE;
        	}
            break;
    };
}

void Task5( uint32 *state, uint32 *period )  /* Cada vez que reciba un scancode lo muestra por la UART0 */
{


	uint8 ajustes;
    switch( *state )
    {
        case INIT:
            uart0_puts( " Task 5: iniciada.\n" );  /* Muestra un mensaje inicial en la UART0 (no es necesario sem?foro) */
            Alarmhour = 0;
            Alarmmin =  0;
            *state = RUN;
            break;
        default:
            if( flagTask5 == TRUE )
            {

            	ajustes=0;
            	flaglcd=FALSE;

            	while(ajustes<2){
            	 lcd_puts_x2(160,80,0xf,":");
            	 if(Alarmhour<10){
            	 lcd_putintx10(5,32,0xf,0);
            	 lcd_putintx10(80,32,0xf,Alarmhour);
            	 }
            	 else{
            	 lcd_putintx10(5,32,0xf,Alarmhour);
            	  }
            	 if(ajustes<2){
            	 if(Alarmmin<10){
            	  lcd_putintx10(180,32,0xf,0 );
            	  lcd_putintx10(260,32,0xf,Alarmmin );
            	  }
            	  else{
            	   lcd_putintx10(180,32,0xf,Alarmmin );
            	   }
            	  }
            	 if(ajustes==0){
            	   lcd_puts_x2(5,160,0xf,"Editando horas");
            	   iis_textToSpeech("Editando horas");
            	  }else if(ajustes==1){
            	   iis_textToSpeech ("Editando minutos");
            	  lcd_puts_x2(5,160,0xf,"Editando minutos");
            	  }
            	  if(scancode==KEYPAD_KEY0){
            	      if(ajustes==0){
            	    	  Alarmhour++;
            	    	  iis_textToSpeech("sumando horas de alarma");
            	       }
            	       else if(ajustes==1){
            	    	   Alarmmin++;
            	    	   iis_textToSpeech("sumando minutos de alarma");
            	     }
            	  }
            	  if(scancode==KEYPAD_KEY1){
            	       if(ajustes==0){
            	    	   Alarmhour--;
            	    	   iis_textToSpeech("restando horas de alarma");
            	        }
            	        else if(ajustes==1){
            	        	Alarmmin--;
            	           iis_textToSpeech("restando minutos de alarma");
            	     }
            	  }
            	  scancode = KEYPAD_FAILURE;
            	  if(PbRight==TRUE){
            	      ajustes++;
                  	 PbRight=FALSE;
            	      }
            	  }
            	    PbScancode=0;

            	    lcd_clear();

            	    PbRight = FALSE;
            	    iis_textToSpeech("Estado de alarma");
            	    if(Alarm==TRUE){
            	    iis_textToSpeech("Alarma activada");
            	    lcd_puts_x2(5,160,0xf,"Alarma activada");
            	    }
            	    else{
            	    iis_textToSpeech("Alarma desactivada");
            	    lcd_puts_x2(5,160,0xf,"Alarma desactivada");
            	    }
            	    scancode = KEYPAD_FAILURE;
            	    iis_textToSpeech("Pulse la tecla 0 para activar");
            	    iis_textToSpeech(" o tecla 1 para desactivar");

            	    do{
                    if(scancode==KEYPAD_KEY0){
                    	Alarm=TRUE;
                    	scancode=KEYPAD_KEY0;
                    }else if(scancode==KEYPAD_KEY1){
                    	scancode=KEYPAD_KEY1;
                    	Alarm=FALSE;
                    }
            	    }while (scancode!=KEYPAD_KEY0&&scancode!=KEYPAD_KEY1);

            	    lcd_clear();

            	    flagTask5=FALSE;
                    flaglcd=TRUE;
            }

            break;
    };
}

void Task6( uint32 *state, uint32 *period )  /* Cada vez que reciba un scancode lo muestra por los 7 segmentos */
{
	rtc_time_t rtc_time;
    switch( *state )
    {
        case INIT:
            uart0_puts( " Task 6: iniciada.\n" );  /* Muestra un mensaje inicial en la UART0 (no es necesario sem?foro) */
            *state = RUN;
            break;
        default:
            if(Alarm==TRUE){
            	rtc_gettime( &rtc_time );
            	if(rtc_time.hour==Alarmhour&&rtc_time.min==Alarmmin){
            	iis_textToSpeech( "Alarma" );
            	sw_delay_s(1);
            	iis_textToSpeech( "Alarma" );
            	sw_delay_s(2);
            	iis_textToSpeech( "Alarma" );
            	sw_delay_s(2);
            	iis_textToSpeech( "Alarma" );
            	sw_delay_s(3);
            	Alarm=FALSE;
            	}
            }
            break;
    };
}




/*******************************************************************/


void isr_keypad ( void ){
	scancode=keypad_timeout_getchar(500);

	I_ISPC = BIT_KEYPAD;
}

void isr_pb( void )
{

	  PbScancode=pb_timeout_getchar(500);
	  if(PbScancode==PB_LEFT){
	       PbLeft=TRUE;
	        	  }
	  else if(PbScancode==PB_RIGHT){
	        		  PbRight=TRUE;
	     }
        /* Solo se?aliza, el mensaje en la UART0 lo env?a la hebra background para evitar proteger el recurso */
    EXTINTPND = BIT_RIGHTPB;
    EXTINTPND = BIT_LEFTPB;
    I_ISPC = BIT_PB;
}

