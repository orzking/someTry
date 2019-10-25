#include "module.h"
void module_state_run(state_t* state);
void subModule_list_process(module_t* module);

void module_add_state(module_t* module,state_t* state)
{
	state_t* stateTemp, *statePre;
	state->module=module;
	stateTemp=module->stateHead;
	//头节点空
	if(stateTemp==NULL)
	{
		module->stateHead=state;
		return;
	}
	//遍历状态链表
	while(stateTemp!=NULL)
	{
		statePre=stateTemp;
		stateTemp=stateTemp->nextState;
	}
	//找到链表尾,增加状态
	statePre->nextState=state;
}
void state_add_subModule(state_t* state,module_t* subModule)
{
	module_t* subModuleTemp, *subModulePre;
	subModuleTemp=state->subModuleHead;
	if(subModuleTemp==NULL)
	{
		state->subModuleHead=subModule;
		return;
	}
	while(subModuleTemp!=NULL)
	{
		subModulePre=subModuleTemp;
		subModuleTemp=subModuleTemp->nextModule;
	}
	subModulePre->nextModule=subModule;
}
void state_add_jump(state_t* state,jump_t* jump)
{
	jump_t* jumpTemp,*jumpPre;
	jumpTemp=state->jumpHead;
	if(jumpTemp==NULL)
	{
		state->jumpHead=jump;
		return;
	}
	while(jumpTemp!=NULL)
	{
		jumpPre=jumpTemp;
		jumpTemp=jumpTemp->nextJump;
	}
	jumpPre->nextJump=jump;
}


void module_process(module_t* module)
{

	state_t* state;
	state=module->stateHead;
	//遍历状态链表
	while(state!=NULL)
	{
		//找到模块当前状态
		if(state->value==module->stateCurrent)
		{
			//执行当前状态下的处理
			module_state_run(state);
			break;
		}
		state=state->nextState;
	}

}
void module_state_run(state_t* state)
{
	module_t* subModule=state->subModuleHead;
	jump_t* jump=state->jumpHead;
	subModule_list_process(subModule);
	//遍历跳转链表
	while(jump!=NULL)
	{
		if(jump->condition==NULL)//未添加跳转函数，认为满足跳转条件
		{
			if(jump->run!=NULL)
			{
				jump->run();//跳转前执行回调
			}
			state->module->stateCurrent=jump->targetStateValue;//执行跳转
			break;
		}
		if(jump->condition())//满足跳转条件
		{
			if(jump->run!=NULL)
			{
				jump->run();//跳转前执行回调
			}
			state->module->stateCurrent=jump->targetStateValue;//执行跳转
			break;
		}
		jump=jump->nextJump;
	}
}
//遍历子模块链表，执行各子模块处理函数
void subModule_list_process(module_t* module)
{
	while(module!=NULL)
	{
		module_process(module);
		module=module->nextModule;
	}
}
