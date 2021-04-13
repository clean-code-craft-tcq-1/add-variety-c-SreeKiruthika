#include "libfunc.h"

extern int libfunc_MailReturn;
extern int libfunc_PinReturn;

/*Dummy library function for analog pin set function */
int AnalogPin_Set(unsigned short pin_number, float volt)
{
	return libfunc_PinReturn;
}


/*Dummy library function for sending mail */
int email_send (char* sender,char* recepient, char* message_body)
{
	return libfunc_MailReturn;
}
