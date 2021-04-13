
#include "breach.h"


/*Dummy library function for analog pin set function */
int AnalogPin_Set(unsigned short pin_number, float volt)
{
	int retval= libfunc_PinReturn;
	return retval;
}


/*Dummy library function for sending mail */
int Email_Send(const char* sender,const char* recepient, char* message_body)
{
	return libfunc_MailReturn;
}

