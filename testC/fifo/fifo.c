#include <assert.h>
#include "fifo.h"

void fifo_init(fifoCtrl_t* p_fifoCtrl,void* buffAddr,unsigned char cellSize,unsigned char cellAmount)
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
	return (p_fifoCtrl->cellCount==p_fifoCtrl->cellAmount)?1:0;
}
unsigned char fifo_isEmpty(fifoCtrl_t* p_fifoCtrl)
{
	assert_param(p_fifoCtrl!=NULL);
	return (p_fifoCtrl->cellCount==0)?1:0;
}
unsigned char fifo_push(fifoCtrl_t* p_fifoCtrl,void* p_cellDataFrom)
{
	assert_param(p_fifoCtrl!=NULL);
	int i=0;
	unsigned char* p_inAddr=(unsigned char*)(p_fifoCtrl->inAddr);
	unsigned char* p_dataFrom=(unsigned char*)(p_cellDataFrom);
	if(p_fifoCtrl->cellCount==p_fifoCtrl->cellAmount)return FIFO_ERR;//FIFO is FULL
	for(i=0;i<p_fifoCtrl->cellSize;i++)
	{
		p_inAddr[i]=p_dataFrom[i];
	}
	p_fifoCtrl->cellCount++;
	p_fifoCtrl->inAddr=p_fifoCtrl->cellSize+(unsigned char*)(p_fifoCtrl->inAddr);
	if(p_fifoCtrl->inAddr>=(unsigned char*)p_fifoCtrl->buffAddr+p_fifoCtrl->cellAmount*(p_fifoCtrl->cellSize))
	{
		p_fifoCtrl->inAddr=p_fifoCtrl->buffAddr;
	}
	return FIFO_OK;
}
unsigned char fifo_pop(fifoCtrl_t* p_fifoCtrl,void* p_cellDataSaveTo)
{
	assert_param(p_fifoCtrl!=NULL);
	if(p_fifoCtrl->cellCount==0)return FIFO_ERR;
	int i=0;
	unsigned char* p_outAddr=(unsigned char*)(p_fifoCtrl->outAddr);
	unsigned char* p_dataSaveTo=(unsigned char*)(p_cellDataSaveTo);
	for(i=0;i<p_fifoCtrl->cellSize;i++)
	{
		p_dataSaveTo[i]=p_outAddr[i];
	}
	p_fifoCtrl->cellCount--;
	p_fifoCtrl->outAddr=p_fifoCtrl->cellSize+(unsigned char*)(p_fifoCtrl->outAddr);
	if(p_fifoCtrl->outAddr>=(unsigned char*)p_fifoCtrl->buffAddr+p_fifoCtrl->cellAmount*(p_fifoCtrl->cellSize))
	{
		p_fifoCtrl->outAddr=p_fifoCtrl->buffAddr;
	}
	return FIFO_OK;
}
