#include "my_ad9833.h"
#include <AD9833.h>
#include <MCP_POT.h>
#include "state.h" // 访问 systemState 和 lastState

#define FSYNC 5 // FSYNC 接 GPIO5（你可改）
#define CS_POT 4 // MCP41010 片选

AD9833 gen(FSYNC);
// 实例化 MCP41010
MCP41010 pot(CS_POT, 255, 255);

void initAD9833()
{
    SPI.begin();  // 注意：必须先初始化 SPI
    pot.begin(128); // 将电位器初始化为最大值（最大增益）
    gen.Begin();
    gen.ApplySignal(SINE_WAVE, REG0, systemState.sineFreq);
    gen.EnableOutput(true);
}

void updateAD9833()
{
    if (systemState.sineFreq != lastState.sineFreq)
    {
        gen.SetFrequency(REG0, systemState.sineFreq);
        lastState.sineFreq = systemState.sineFreq;
    }
}



void setFrequency(float freq)
{
    systemState.sineFreq = freq;
    updateAD9833(); // 立即生效
}
