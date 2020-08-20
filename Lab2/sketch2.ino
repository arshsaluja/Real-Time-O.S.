#include <Arduino_FreeRTOS.h> // Header file to include the RTOS and will load the code to be burned on the chip.

void TaskBlinkRed( void *pvParameters ); // task 1 to blink the RED led // it will use port 8 as the output port
void TaskBlinkGreen( void *pvParameters ); // task 2 to blink the Green led // it will use port 7 as the output port
void Taskprint( void *pvParameters );  // task to print on the serial console

void setup()


{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); 
  //Low priority numbers denote low priority tasks
//   BaseType_t xTaskCreate(    TaskFunction_t pvTaskCode,
//                            const char * const pcName,
//                            configSTACK_DEPTH_TYPE usStackDepth,
//                            void *pvParameters,
//                            UBaseType_t uxPriority,
//                            TaskHandle_t *pxCreatedTask
//                          );

 
  xTaskCreate(TaskBlinkRed,
              "redled", // string to provide the name
              128,      // stack size in word //arduino Word_size=8bit 128 Bytes
              NULL,     // NO parameter is passed so its value is NULL.
              1,        //  Task priority
              NULL );   //  Way to task handle
  //lowest priority task

  xTaskCreate(TaskBlinkGreen, "greenled", 128, NULL, 1, NULL ); // //2nd highest priority

  xTaskCreate(Taskprint, "print", 128, NULL , 1, NULL ); //highest priority

  vTaskStartScheduler(); // this will start the scheduler
  // Now its the responsibility of the Kernel to run the process
}

void loop()
{
}


void TaskBlinkRed(void *pvParameters)   // first task to create the led blink at port 8 // assume the RED led
{
  pinMode(8, OUTPUT); // Pin 8 as the output pin
  while (1)
  {
    Serial.println("Red Led is blinking ");
    digitalWrite(8, HIGH);
    vTaskDelay( 200);
    digitalWrite(8, LOW);
    vTaskDelay( 200);
  }
}
void TaskBlinkGreen(void *pvParameters) // first task to create the led blink at port 7 // assume the Green led
{
  pinMode(7, OUTPUT);
  while (1)
  {
    Serial.println("Green Led is blinking  ");
    digitalWrite(7, HIGH);
    vTaskDelay( 300);
    digitalWrite(7, LOW);
    vTaskDelay( 300);
  }
}


void Taskprint(void *pvParameters)
{
  int counter = 0;
  while (1)
  {
    counter++;
    Serial.println(counter);
    vTaskDelay(500);
  }
}
