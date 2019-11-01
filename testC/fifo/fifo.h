#ifndef FILE_FIFO_H
#define FILE_FIFO_H

#ifndef NULL
	#define NULL ((void*)0)
#endif
#ifndef FIFO_ERR
	#define FIFO_ERR 0
#endif
#ifndef FIFO_OK
	#define FIFO_OK 1
#endif

#ifdef USE_FULL_ASSERT
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void)0)

#endif /* USE_FULL_ASSERT */
//简单的FIFO控制结构，用于管理数组，这里要求每个存入fifo的单元要有同样的size
typedef struct fifoCtrl_t
{
	void * buffAddr;
	void * inAddr;
	void * outAddr;
	unsigned char cellSize;
	unsigned char cellCount;
	unsigned char cellAmount;
}fifoCtrl_t;

unsigned char fifo_init(fifoCtrl_t* p_fifoCtrl,void* buffAddr,unsigned char cellSize,unsigned char cellAmount);
unsigned char fifo_isFull(fifoCtrl_t* p_fifoCtrl);
unsigned char fifo_isEmpty(fifoCtrl_t* p_fifoCtrl);
unsigned char fifo_push(fifoCtrl_t* p_fifoCtrl,void* p_cellDataFrom);
unsigned char fifo_pop(fifoCtrl_t* p_fifoCtrl,void* p_cellDataSaveTo);


#endif