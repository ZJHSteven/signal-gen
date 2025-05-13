#include "my_ad9833.h"
#include <AD9833.h>
#include "state.h" // 访问 systemState 和 lastState

#define FSYNC 5 // FSYNC 接 GPIO5（你可改）

AD9833 gen(FSYNC);

void initAD9833()
{
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
