//本文将状态机与模块化编程思想结合，提出一种状态机在单片机上的编程架构，用于解决单核单线程下的并发问题
void main()
{
	while(1)
	{
		//系统分模块，每个模块占用CPU的时间都很短，代码里不可以出现长时间的死等（delay）
		//在关于时间的处理上要始终记得：时间到了做，而不是等时间到了做。是if而不是while
		moduleX_process();
		moduleY_process();
		//...
	}
}

//各模块的处理
void module_x_process(void)
{
	//全局子模块
	moduleX_subModuleP_porcess();
	moduleX_subModuleQ_porcess();
	//...
	switch(moduleX_status)
	{
		case 0:
			//局部状态子模块
			moduleX_subModuleR_porcess();
			moduleX_subModuleS_porcess();
			if(conditon)//满足条件
			{
				doSometingQuick();//状态处理，很短的执行时间
				changeStatus();//状态跳转
			}
			break;
		case 1:
			//...
			break;
		default:
			//...
			break;
	}
}

//子模块的处理：与模块的处理一样，将子模块抽象为模块
void moduleX_subModuleX_porcess()
{
	//...
	switch(moduleX_subModuleX_status)
	{
		//...
	}
}

//根据以上思想可以抽象出状态机模型
//全局子模块可以理解为为任何状态都执行的局部状态子模块，将模型进一步简化
//整个系统就是一个模块树，递归定义模块树就是模块，模块树的每个枝桠也都是模块
