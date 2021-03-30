#ifndef UTILS_H_
#define UTILS_H_

#include <rtthread.h>

/* system status */
typedef enum{
    SYSTEM_STATUS_INIT,
    SYSTEM_STATUS_RUN,
    SYSTEM_STATUS_FAULT,
    SYSTEM_STATUS_SLEEP,
}SystemStatus;

void            system_go_to_fault_status(void);
void            set_system_status(SystemStatus status);
SystemStatus    get_system_status(void);
unsigned int    Crc32Calculation(void* input, unsigned int len) ;
unsigned short  crc_chk(unsigned char* data, unsigned char length);
unsigned char   calc_droppkg(unsigned char old_index, unsigned char new_index);
unsigned char 	sum_check(unsigned char *pbuf, unsigned int len) ;	
unsigned char   find_string(char *psrc,char *pdes);
char            *str_delim(unsigned char num,char *temp,char *delim);
#endif /* UTILS_H_ */
