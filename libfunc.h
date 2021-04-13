/*Defines for PIN output possible values */
#define OUTPIN_ERROR   0
#define OUTPIN_SET     1

/*define for mail function possible return values*/
#define MAIL_SENT           1
#define MAIL_NOTSENT        0


int AnalogPin_Set(unsigned short pin_number, float volt);

int Email_Send(const char* sender,const char* recepient, char* message_body);