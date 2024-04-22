 /*
 #include "LIB/std_types.h"
 #include "HAL/LCD/LCD.h"
 #include "HAL/LED/LED.h"

void stringcbf(void)
{
 	LED_SetStatus(LED_RED, LED_STATE_ON); }

 void LCD_TestAPP(void)
 {
 	u32 static counter=0;
 	    counter++;
 	    if(counter==1)
 	    {
 	    	LCD_enuWriteString_asynch("Farah",stringcbf);

 	   }
 	   else if(counter==2)
 	    {
 		   LCD_ClearScreen_async();
 	    }

 	    else if(counter==3)
 	    {
 	    	LCD_GotoPos_XY_async(1,0,NULLPTR);
 	    }
 	    else if(counter==4)
 	    {
 	    	LCD_enuWriteString_asynch("Mohey",stringcbf);
 	    }
 }
 */