#include "state.h"

SystemState systemState; // 会自动使用结构体中默认值
SystemState lastState;

void initState()
{
    lastState = systemState;
}
