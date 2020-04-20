/*
 * MyNewTask.c
 *
 *  Created on: 15 abr 2020
 *      Author: Lilia Lobato
 */


#include "MyNewTask.h"

//Timer 1
osaEventId_t mMyEvents;
/* Global Variable to store our TimerID */
tmrTimerID_t myTimerID = gTmrInvalidTimerID_c;
/* Handler ID for task */
osaTaskId_t gMyTaskHandler_ID;
/* Local variable to store the current state of the LEDs */
static uint8_t ledsState = 0;

//Timer 2
osaEventId_t mMyEvents_2;
/* Global Variable to store our TimerID */
tmrTimerID_t myTimerID_2 = gTmrInvalidTimerID_c;
/* Handler ID for task */
osaTaskId_t gMyTaskHandler_ID_2;
/* Local variable to store the current counter of the LEDs */
static uint8_t ledsCounter = 0;
static uint8_t ledsCounter_next = 0;

/* This is the function called by the Timer 1 each time it expires */
static void myTaskTimerCallback(void *param)
{
OSA_EventSet(mMyEvents, gMyNewTaskEvent2_c);
}
/* This is the function called by the Timer 2 each time it expires */
static void myTaskTimerCallback_2(void *param)
{
OSA_EventSet(mMyEvents_2, gMyNewTaskEvent2_c);
}

/* Main custom task */
void My_Task(osaTaskParam_t argument)
{
	osaEventFlags_t customEvent;
	myTimerID = TMR_AllocateTimer();
	while(1)
	{
		OSA_EventWait(mMyEvents, osaEventFlagsAll_c, FALSE, osaWaitForever_c, &customEvent);
		if( !gUseRtos_c && !customEvent)
		{
			break;
		}
		/* Depending on the received event */
		switch(customEvent){
		case gMyNewTaskEvent1_c:
			TMR_StartIntervalTimer(myTimerID, /*myTimerID*/
									1000, /* Timer's Timeout */
									myTaskTimerCallback, /* pointer to myTaskTimerCallback function */
									NULL
			);
			TurnOffLeds(); /* Ensure all LEDs are turned off */
			break;
		case gMyNewTaskEvent2_c: /* Event called from myTaskTimerCallback */
			if(!ledsState) {
				TurnOnLeds();
				ledsState = 1;
			}
			else {
				TurnOffLeds();
				ledsState = 0;
			}
			break;
		case gMyNewTaskEvent3_c: /* Event to stop the timer */
			ledsState = 0;
			TurnOffLeds();
			TMR_StopTimer(myTimerID);
			break;
		default:
			break;
		}
	}
}

/* Main custom task */
void My_Task_2 (osaTaskParam_t argument)
{
	osaEventFlags_t customEvent_2;
	myTimerID_2 = TMR_AllocateTimer();
	while(1)
	{
		OSA_EventWait(mMyEvents_2, osaEventFlagsAll_c, FALSE, osaWaitForever_c, &customEvent_2);
		if( !gUseRtos_c && !customEvent_2)
		{
			break;
		}
		/* Depending on the received event */
		switch(customEvent_2){
		case gMyNewTaskEvent1_c:
			TMR_StartIntervalTimer(myTimerID_2, /*myTimerID*/
									3000, /* Timer's Timeout */
									myTaskTimerCallback_2, /* pointer to myTaskTimerCallback function */
									NULL
			);
			TurnOffLeds(); /* Ensure all LEDs are turned off */
			break;
		case gMyNewTaskEvent2_c: /* Event called from myTaskTimerCallback */
			ledsCounter = ledsCounter_next;
			switch (ledsCounter){
				case 0:
					TurnOffLeds();
					Led_TurnOn(RED);
					ledsCounter_next = 1;
					break;
				case 1:
					TurnOffLeds();
					Led_TurnOn(GREEN);
					ledsCounter_next = 2;
					break;
				case 2:
					TurnOffLeds();
					Led_TurnOn(BLUE);
					ledsCounter_next = 3;
					break;
				case 3:
					TurnOffLeds();
					TurnOnLeds();
					ledsCounter_next = 0;
					break;
				default:
					TurnOffLeds();
					ledsCounter_next = 0;
					break;
			}
			break;
		case gMyNewTaskEvent3_c: /* Event to stop the timer */
			ledsCounter = 0;
			TurnOffLeds();
			TMR_StopTimer(myTimerID_2);
			break;
		default:
			break;
		}
	}
}

/* OSA Task Definition*/
OSA_TASK_DEFINE(My_Task, gMyTaskPriority_c, 1, gMyTaskStackSize_c, FALSE );
OSA_TASK_DEFINE(My_Task_2, gMyTaskPriority2_c, 1, gMyTaskStackSize_c, FALSE );

/* Function to init the task Timer 1*/
void MyTask_Init(void)
{
mMyEvents = OSA_EventCreate(TRUE);
/* The instance of the MAC is passed at task creaton */
gMyTaskHandler_ID = OSA_TaskCreate(OSA_TASK(My_Task), NULL);
}

/* Function to init the task Timer 2*/
void MyTask2_Init(void)
{
mMyEvents_2 = OSA_EventCreate(TRUE);
/* The instance of the MAC is passed at task creaton */
gMyTaskHandler_ID_2 = OSA_TaskCreate(OSA_TASK(My_Task_2), NULL);
}

/* Function to init the task Timer 2*/
void MyTask2_Reload(int value)
{
	ledsCounter = value;
	ledsCounter_next = value+1;
	TMR_StopTimer(myTimerID_2);
	MyTask2Timer_Start();
}
/* Function to init the task Timer 2*/
int MyTask2_GetCounter(void)
{
	return ledsCounter;
}

/* Public function to send an event to start the timer 1*/
void MyTaskTimer_Start(void)
{
	OSA_EventSet(mMyEvents, gMyNewTaskEvent1_c);
}
/* Public function to send an event to start the timer 2*/
void MyTask2Timer_Start(void)
{
	OSA_EventSet(mMyEvents_2, gMyNewTaskEvent1_c);
}

/* Public function to send an event to stop the timer 1*/
void MyTaskTimer_Stop(void)
{
	OSA_EventSet(mMyEvents, gMyNewTaskEvent3_c);
}
/* Public function to send an event to stop the timer 2*/
void MyTask2Timer_Stop(void)
{
	OSA_EventSet(mMyEvents_2, gMyNewTaskEvent3_c);
}
