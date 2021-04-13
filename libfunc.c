
#include "libfunc.h"

int libfunc_PinReturn = OUTPIN_ERROR;
int libfunc_MailReturn = MAIL_NOTSENT;

/*Dummy library function for analog pin set function */
int AnalogPin_Set(unsigned short pin_number, float volt)
{
	return libfunc_PinReturn;
}


/*Dummy library function for sending mail */
int Email_Send(const char* sender,const char* recepient, char* message_body)
{
	return libfunc_MailReturn;
}

