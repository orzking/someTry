#include <assert.h>
#include "fifo.h"

unsigned char fifo_init(fifoCtrl_t* p_fifoCtrl,void* buffAddr,unsigned char cellSize,unsigned char cellAmount)
{
	if(p_fifoCtrl==NULL)return FIFO_ERR;
	if()

}
unsigned char fifo_isFull(fifoCtrl_t* p_fifoCtrl)
{
	if(p_fifoCtrl==NULL)return FIFO_ERR;
}
unsigned char fifo_isEmpty(fifoCtrl_t* p_fifoCtrl)
{
	if(p_fifoCtrl==NULL)return FIFO_ERR;
}
unsigned char fifo_push(fifoCtrl_t* p_fifoCtrl,void* p_cellDataFrom)
{
	if(p_fifoCtrl==NULL)return FIFO_ERR;
}
unsigned char fifo_pop(fifoCtrl_t* p_fifoCtrl,void* p_cellDataSaveTo)
{
	if(p_fifoCtrl==NULL)return FIFO_ERR;
}