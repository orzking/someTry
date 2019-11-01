#include <assert.h>
#include "fifo.h"

unsigned char fifo_init(fifoCtrl_t* p_fifoCtrl,void* buffAddr,unsigned char cellSize,unsigned char cellAmount)
{
	assert_param(p_fifoCtrl!=NULL);
	assert_param(buffAddr!=NULL);
	p_fifoCtrl->buffAddr=buffAddr;
	p_fifoCtrl->inAddr=buffAddr;
	p_fifoCtrl->outAddr=buffAddr;
	p_fifoCtrl->cellSize=cellSize;
	p_fifoCtrl->cellCount=0;
	p_fifoCtrl->cellAmount=cellAmount;

}
unsigned char fifo_isFull(fifoCtrl_t* p_fifoCtrl)
{
	assert_param(p_fifoCtrl!=NULL);
	return (cellCount==cellAmount)?1:0;
}
unsigned char fifo_isEmpty(fifoCtrl_t* p_fifoCtrl)
{
	assert_param(p_fifoCtrl!=NULL);
	return (cellCount==0)?1:0;
}
unsigned char fifo_push(fifoCtrl_t* p_fifoCtrl,void* p_cellDataFrom)
{
	assert_param(p_fifoCtrl!=NULL);
}
unsigned char fifo_pop(fifoCtrl_t* p_fifoCtrl,void* p_cellDataSaveTo)
{
	assert_param(p_fifoCtrl!=NULL);
}