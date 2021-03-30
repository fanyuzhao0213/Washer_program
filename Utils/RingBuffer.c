/**********************************************************************
 * @File          : ring_buff.c
 * @ChangeLogs    :
 * Date           Author       Notes
 * 2017-12-29     Jerry           the first version
 **********************************************************************/
#include "RingBuffer.h"
#include <string.h>
#include <stddef.h>
#include <assert.h>

#define min(a,b) ( (a) < (b) )? (a):(b)     

/******************************************************************************
 *函数�?  :ring_buf_init
 *函数功能 :构造一个空环形缓冲�?
 *输入参数 :r 环形缓冲区控制块
 *返回�?  :�?表示成功 
 *****************************************************************************/
int ring_buf_create(ring_buf_t *r,unsigned char *buf,unsigned int len)
{
    r->buf = buf;
    r->size = len;
    r->front = r->rear = 0;
    r->read = 0;
    return buf == NULL;
}
/**********************************************************************
 *函数�?  :ring_buf_clr
 *函数功能 :清空环形缓冲�?
 *输入参数 :r - 待清空的环形缓冲�?
 *返回�?  :None 
 *********************************************************************/
void ring_buf_clr(ring_buf_t *r)
{
    r->front = r->rear = 0;
    r->read = 0;
}

/**********************************************************************
 *函数�?  :ring_buf_len
 *函数功能 :计算环形缓冲区容�?(字节为单�?
 *输入参数 :r.环形缓冲区控制块
 *返回�?  :环形缓冲区中有效字节�?
 *********************************************************************/
unsigned int ring_buf_len(ring_buf_t *r)
{
    return r->rear - r->front;
}

/**********************************************************************
 *函数�?  :ring_buf_put
 *函数功能 :将指定长度的数据放到环形缓冲区中 
 *输入参数 :buf - 数据缓冲�?
 *          len - 缓冲区长�?
 *返回�?  :实际放到中的数据 
 *********************************************************************/
unsigned int ring_buf_put(ring_buf_t *r,unsigned char *buf,unsigned int len)
{
    unsigned int i;
    unsigned int space;                      
    space = r->size + r->front - r->rear;
    len = min(len , space);                  /*得到实际写入的数据长*/
    /*min(空闲空间大小,从real_in开始到缓冲区结尾的空间) -------------*/
    i = min(len, r->size - r->rear % r->size);   
    /*
     * 当len > l时，拷贝buffer中剩余的内容
     *而剩余的大小为len - l 
     */            
    memcpy(r->buf + r->rear % r->size, buf, i); 
    memcpy(r->buf, buf + i, len - i);       
    r->rear += len;     
    return len;

}


/**********************************************************************
 *函数�?  :rueueGet
 *函数功能 :从环形缓冲区中读取指定长度的数据 
 *输入参数 :len - 读取长度 
 *输出参数 :buf - 输出数据缓冲�?
 *返回�?  :实际读取长度 
 *********************************************************************/
unsigned int ring_buf_get(ring_buf_t *r,unsigned char *buf,unsigned int len)
{
    unsigned int i;
    unsigned int space;    
    space = r->rear - r->front;                     
    len = min(len , space);                                
    i = min(len, r->size - r->front % r->size );    
    memcpy(buf, r->buf + r->front % r->size, i);    
    memcpy(buf + i, r->buf, len - i);   
    r->front += len;    
    r->read = r->front;    
    return len;
}
unsigned int ring_buf_read(ring_buf_t *r,unsigned char *buf,unsigned int len)
{
    unsigned int i;
    unsigned int space;    
    space = r->rear - r->read;                     
    len = min(len , space);                                
    i = min(len, r->size - r->read % r->size );    
    memcpy(buf, r->buf + r->read % r->size, i);    
    memcpy(buf + i, r->buf, len - i);   
    r->read += len;        
    return len;
}
unsigned int ring_buf_read_len(ring_buf_t *r)
{
    return r->rear - r->read;
}
void ring_buf_read_submit(ring_buf_t *r)
{
    r->front = r->read;
}
void ring_buf_read_cancel(ring_buf_t *r)
{
    r->read = r->front;
}
