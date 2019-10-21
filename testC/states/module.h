#ifndef FILE_MODULE_H
    #define FILE_MODULE_H
#ifndef NULL
    #define NULL (void*)0
#endif
#define DEBUG printf("FUNC:%S,FILE:%s,LINE:%d",__func__,__FILE__,__LINE__);
typedef struct statejump jump_t;//状态跳转
typedef struct state state_t;//状态
typedef struct module module_t;//模块
typedef unsigned char (*condition_callback_t)(void);//状态跳转条件函数指针类型
typedef void (*jumpRun_callback_t)(void);//状态跳转前的处理运行函数指针类型
struct statejump
{
	unsigned targetStateValue;//跳转目标状态值
	condition_callback_t condition;//状态跳转条件
	jumpRun_callback_t run;//状态跳转
	jumpRun_callback_t *nextJump;//跳转链表下一个节点
};
struct state
{
    unsigned char value;//状态值
	module_t* module;//拥有该状态的模块
	module_t* subModuleHead;//该状态下可用子模块链表头
	module_t* jumpHead;//跳转链表头
	state_t* nextState;//状态链表下一个节点
};
struct module
{
	unsigned char stateCurrent;//当前状态值
	state_t* stateHead;//模块拥有的状态链表头
	module_t* nextModule;//模块链表下一个节点
};
void module_add_state(module_t* module,state_t* state);
void state_add_subModule(state_t* state,module_t* subModule);
void state_add_jump(state_t* state,jump_t* jump);
void module_process(module_t* module);
#endif


