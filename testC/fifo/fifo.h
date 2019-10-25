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