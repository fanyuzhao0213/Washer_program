/**********************************************************************
 * @File          : ringbuff.h
 * @ChangeLogs    :
 * Date           Author       Notes
 * 2017-12-29     Jerry           the first version
 **********************************************************************/
#ifndef __RING_BUF_H____
#define __RING_BUF_H____

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/*环形缓冲区管理器*/
typedef struct
{
     unsigned char *buf;    /*环形缓冲区        */
     unsigned int size;     /*总产犊        */
     unsigned int front;    /*头指针            */
     unsigned int rear;     /*尾指针            */
     unsigned int read;     /*读取            */     
}ring_buf_t;
/*-------------------------外部接口声明----------------------------*/
int ring_buf_create(ring_buf_t *r,unsigned char *buf,unsigned int size);
void ring_buf_clr(ring_buf_t *r);
unsigned int ring_buf_len(ring_buf_t *r);
unsigned int ring_buf_put(ring_buf_t *r,unsigned char *buf,unsigned int len);
unsigned int ring_buf_get(ring_buf_t *r,unsigned char *buf,unsigned int len);
unsigned int ring_buf_read(ring_buf_t *r,unsigned char *buf,unsigned int len);
unsigned int ring_buf_read_len(ring_buf_t *r);
void ring_buf_read_submit(ring_buf_t *r);
void ring_buf_read_cancel(ring_buf_t *r);
#ifdef __cplusplus
}
#endif //__cplusplus

#endif

/********** (C) COPYRIGHT 2018 Jerry.XL *****END OF FILE**************/
