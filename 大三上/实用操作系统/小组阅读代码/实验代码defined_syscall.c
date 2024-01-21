#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "stdio.h"
#include "los_task.h"
#include "los_printf.h"

UINT32 g_taskHiId;
UINT32 g_taskLoId;
UINT32 g_taskCgId;
UINT32 g_taskHiStatus;
UINT32 g_taskLoStatus;
UINT32 g_taskCgStatus;
#define TSK_PRIOR_CG 5
#define TSK_PRIOR_HI 5
#define TSK_PRIOR_LO 22

UINT32 Example_TaskHi(VOID)
{
    UINT32 ret;
    //输出一下状态，确定Cg就绪
    PRINTK("Cg执行完初始时间片长度的时间,尾插到就绪队列尾部\n");
    PRINTK("---------------Enter TaskHi Handler.---------------\n");
    PRINTK("TaskCg:运行态->就绪态\nTaskHi:就绪态->运行态\n");
    TSK_INFO_S stateCg,stateHi,stateLo;
    ret = LOS_TaskInfoGet(g_taskCgId, &stateCg);
    PRINTK("TaskCg 状态: %x  ", stateCg.usTaskStatus);
    ret = LOS_TaskInfoGet(g_taskHiId, &stateHi);
    PRINTK("TaskHi 状态: %x  ", stateHi.usTaskStatus);
    ret = LOS_TaskInfoGet(g_taskLoId, &stateLo);
    PRINTK("TaskLo 状态: %x\n", stateLo.usTaskStatus);
    

    //Cg删除剩余两个任务
    PRINTK("TaskHi主动调用删除接口，删除TaskCg任务\n");
    ret=LOS_TaskDelete(g_taskCgId);
    if (ret != LOS_OK) {
        PRINTK("Delete TaskCg Failed.\n");
        return LOS_NOK;
    }


    /* 延时12个Tick，延时后该任务会挂起，TaskHi进入挂起态*/
    ret = LOS_TaskDelay(12);
    if (ret != LOS_OK) {
        PRINTK("Delay Task Failed.\n");
        return LOS_NOK;
    }
    PRINTK("TaskLo延时12Tick\n");
    PRINTK("TaskLo:运行态->阻塞态\n");
    PRINTK("---------------Enter TaskHi Handler.---------------\n");
    /* 2个Tick时间到了后，该任务恢复，继续执行 */
    PRINTK("TaskHi:阻塞态->运行态\n");
    PRINTK("TaskLo:运行态->阻塞态\n");
    ret = LOS_TaskInfoGet(g_taskHiId, &stateHi);
    PRINTK("TaskHi 状态: %x  ", stateHi.usTaskStatus);
    ret = LOS_TaskInfoGet(g_taskLoId, &stateLo);
    PRINTK("TaskLo 状态: %x\n", stateLo.usTaskStatus);

    /* 挂起自身任务 */
    ret = LOS_TaskSuspend(g_taskHiId);
    if (ret != LOS_OK) {
        PRINTK("Suspend TaskHi Failed.\n");
        return LOS_NOK;
    }


    PRINTK("TaskHi被TaskLo恢复为就绪态，TaskHi抢占TaskLo.\n");
    PRINTK("---------------Enter TaskHi Handler.---------------\n");
    PRINTK("TaskHi:挂起态->就绪态->运行态\n");
    PRINTK("TaskLo:运行态->就绪态\n");
    ret = LOS_TaskInfoGet(g_taskHiId, &stateHi);
    PRINTK("TaskHi 状态: %x  ", stateHi.usTaskStatus);
    ret = LOS_TaskInfoGet(g_taskLoId, &stateLo);
    PRINTK("TaskLo 状态: %x\n", stateLo.usTaskStatus);

    return ret;
}

/* 低优先级任务入口函数 */
UINT32 Example_TaskLo(VOID)
{
    UINT32 ret;
    PRINTK("TaskHi延时12Tick\n");
    PRINTK("TaskHi:运行态->阻塞态\n");
    TSK_INFO_S stateHi,stateLo;
    ret = LOS_TaskInfoGet(g_taskHiId, &stateHi);
    PRINTK("---------------Enter TaskLo Handler.---------------\n");
    PRINTK("TaskLo:就绪态->运行态\n");
    PRINTK("TaskHi 状态: %x  ", stateHi.usTaskStatus);
    ret = LOS_TaskInfoGet(g_taskLoId, &stateLo);
    PRINTK("TaskLo 状态: %x\n", stateLo.usTaskStatus);
    

    /* 延时12个Tick，延时后该任务会挂起，执行剩余任务中最高优先级的任务(背景任务) */
    ret = LOS_TaskDelay(12);
    if (ret != LOS_OK) {
        PRINTK("Delay TaskLo Failed.\n");
        return LOS_NOK;
    }
    
    
    //suspend状态，TaskHi主动挂起
    PRINTK("TaskHi调用suspend接口\n");
    PRINTK("TaskHi:运行态->挂起态\n");
    ret = LOS_TaskInfoGet(g_taskHiId, &stateHi);
    PRINTK("---------------Enter TaskLo Handler.---------------\n");
    PRINTK("TaskHi 状态: %x  ", stateHi.usTaskStatus);
    ret = LOS_TaskInfoGet(g_taskLoId, &stateLo);
    PRINTK("TaskLo 状态: %x\n", stateLo.usTaskStatus);


    /* 恢复被挂起的任务g_taskHiId */
    ret = LOS_TaskResume(g_taskHiId);
    if (ret != LOS_OK) {
        PRINTK("Resume TaskHi Failed.\n");
        return LOS_NOK;
    }


    PRINTK("TaskHi执行完成，自删除成功.\n");
    PRINTK("---------------Enter TaskLo Handler.---------------\n");
    PRINTK("TaskLo执行完成，自删除成功.\n");
    return ret;
}

VOID Example_CGTest(VOID)
{
    UINT32 ret;

    //同一优先级队列，输出优先级
    UINT16 Hi;
    UINT16 Lo;
    UINT16 Cg;
    Cg=LOS_TaskPriGet(g_taskCgId);
    Hi=LOS_TaskPriGet(g_taskHiId);
    Lo=LOS_TaskPriGet(g_taskLoId);
    PRINTK("三个任务优先级分别为：%u %u %u\n",Cg,Hi,Lo);


    PRINTK("TaskCg.priority==TaskHi.priority,TaskCg在初始化任务优先创建，同一优先级就绪队列中先进先出\n");
    PRINTK("---------------Enter TaskCg Handler.---------------\n");
    PRINTK("TaskCg:就绪态->运行态！");
    TSK_INFO_S stateCg,stateHi,stateLo;
    ret = LOS_TaskInfoGet(g_taskCgId, &stateCg);
    PRINTK("TaskCg 状态: %x  ", stateCg.usTaskStatus);
    ret = LOS_TaskInfoGet(g_taskHiId, &stateHi);
    PRINTK("TaskHi 状态: %x  ", stateHi.usTaskStatus);
    ret = LOS_TaskInfoGet(g_taskLoId, &stateLo);
    PRINTK("TaskLo 状态: %x\n", stateLo.usTaskStatus);


    ret = LOS_TaskResume(g_taskLoId);
    if (ret != LOS_OK) {
        PRINTK("Resume TaskLo Failed.\n");
    }
    
    PRINTK("TaskLo:挂起态->就绪态！");
    ret = LOS_TaskInfoGet(g_taskCgId, &stateCg);
    PRINTK("TaskCg 状态: %x  ", stateCg.usTaskStatus);
    ret = LOS_TaskInfoGet(g_taskHiId, &stateHi);
    PRINTK("TaskHi 状态: %x  ", stateHi.usTaskStatus);
    ret = LOS_TaskInfoGet(g_taskLoId, &stateLo);
    PRINTK("TaskLo 状态: %x\n", stateLo.usTaskStatus);

    while(1){}
}


/* 任务测试入口函数，创建两个不同优先级的任务 */
UINT32 DefinedSyscall(VOID)
{
    UINT32 ret;
    TSK_INIT_PARAM_S initParam;

    /* 锁任务调度，防止新创建的任务比本任务高而发生调度 */
    LOS_TaskLock();
    PRINTK("\nLOS_TaskLock() 成功，防止新创建的任务比本任务高而发生调度!\n");


    initParam.pfnTaskEntry = (TSK_ENTRY_FUNC)Example_CGTest;
    initParam.usTaskPrio = TSK_PRIOR_CG;
    initParam.pcName = "TaskCg";
    initParam.uwStackSize = 2048;
    initParam.uwResved   = LOS_TASK_STATUS_DETACHED;
	ret = LOS_TaskCreate(&g_taskCgId, &initParam);
    if (ret != LOS_OK) {
        LOS_TaskUnlock();
        PRINTK("TaskCg create Failed!\n");
        return LOS_NOK;
    }

    initParam.pfnTaskEntry = (TSK_ENTRY_FUNC)Example_TaskHi;
    initParam.usTaskPrio = TSK_PRIOR_HI;
    initParam.pcName = "TaskHi";
    initParam.uwStackSize = 2048;
    initParam.uwResved   = LOS_TASK_STATUS_DETACHED;
    /* 创建高优先级任务，由于锁任务调度，任务创建成功后不会马上执行 */
    ret = LOS_TaskCreate(&g_taskHiId, &initParam);
    if (ret != LOS_OK) {
        LOS_TaskUnlock();
        PRINTK("TaskHi create Failed!\n");
        return LOS_NOK;
    }


    initParam.pfnTaskEntry = (TSK_ENTRY_FUNC)Example_TaskLo;
    initParam.usTaskPrio = TSK_PRIOR_LO;
    initParam.pcName = "TaskLo";
    initParam.uwStackSize = 2048;
    initParam.uwResved   = LOS_TASK_STATUS_DETACHED;
    /* 创建低优先级任务，由于锁任务调度，任务创建成功后不会马上执行 */
    ret = LOS_TaskCreate(&g_taskLoId, &initParam);
    if (ret != LOS_OK) {
        LOS_TaskUnlock();

        PRINTK("Example_TaskLo create Failed!\n");
        return LOS_NOK;
    }
	
    
    
    PRINTK("TaskCg TaskHi TaskLo 创建成功!\n");
    TSK_INFO_S stateCg,stateHi,stateLo;
    ret = LOS_TaskInfoGet(g_taskCgId, &stateCg);
    PRINTK("TaskCg 状态: %x  ", stateCg.usTaskStatus);
    ret = LOS_TaskInfoGet(g_taskHiId, &stateHi);
    PRINTK("TaskHi 状态: %x  ", stateHi.usTaskStatus);
    ret = LOS_TaskInfoGet(g_taskLoId, &stateLo);
    PRINTK("TaskLo 状态: %x\n", stateLo.usTaskStatus);


    //挂起low
    ret = LOS_TaskSuspend(g_taskLoId);
    //输出状态
    PRINTK("TaskLo:就绪态->挂起态！\n");
    ret = LOS_TaskInfoGet(g_taskCgId, &stateCg);
    PRINTK("TaskCg 状态: %x  ", stateCg.usTaskStatus);
    ret = LOS_TaskInfoGet(g_taskHiId, &stateHi);
    PRINTK("TaskHi 状态: %x  ", stateHi.usTaskStatus);
    ret = LOS_TaskInfoGet(g_taskLoId, &stateLo);
    PRINTK("TaskLo 状态: %x\n", stateLo.usTaskStatus);
    
    
    LOS_TaskUnlock();
    return LOS_OK;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
