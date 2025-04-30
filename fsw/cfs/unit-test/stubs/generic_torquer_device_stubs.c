#include "utgenstub.h"
#include "generic_torquer_device.h"

int32_t GENERIC_TORQUER_Config(GENERIC_TORQUER_Device_tlm_t *trqHk, trq_info_t *trqDevice, uint8_t percent, uint8_t dir)
{
    UT_GenStub_SetupReturnBuffer(GENERIC_TORQUER_Config, int32_t);
    UT_GenStub_AddParam(GENERIC_TORQUER_Config, GENERIC_TORQUER_Device_tlm_t *, trqHk);
    UT_GenStub_AddParam(GENERIC_TORQUER_Config, trq_info_t *, trqDevice);
    UT_GenStub_AddParam(GENERIC_TORQUER_Config, uint8_t, percent);
    UT_GenStub_AddParam(GENERIC_TORQUER_Config, uint8_t, dir);

    status = trq_command(trqDevice, percent, dir);
    if (status == OS_SUCCESS)
    {
        trqHk->PercentOn = percent;
        trqHk->Direction = dir;
    }
    return status;
}
