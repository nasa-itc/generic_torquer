#include "utgenstub.h"
#include "generic_torquer_device.h"

int32_t GENERIC_TORQUER_ReadData(uart_info_t *device, uint8_t *read_data, uint8_t data_length)
{
    UT_GenStub_SetupReturnBuffer(GENERIC_TORQUER_ReadData, int32_t);

    UT_GenStub_AddParam(GENERIC_TORQUER_ReadData, uart_info_t *, device);
    UT_GenStub_AddParam(GENERIC_TORQUER_ReadData, uint8_t *, read_data);
    UT_GenStub_AddParam(GENERIC_TORQUER_ReadData, uint8_t, data_length);

    UT_GenStub_Execute(GENERIC_TORQUER_ReadData, Basic, NULL);

    return UT_GenStub_GetReturnValue(GENERIC_TORQUER_ReadData, int32_t);
}

int32_t GENERIC_TORQUER_CommandDevice(uart_info_t *device, uint8_t cmd, uint32_t payload)
{
    UT_GenStub_SetupReturnBuffer(GENERIC_TORQUER_CommandDevice, int32_t);

    UT_GenStub_AddParam(GENERIC_TORQUER_CommandDevice, uart_info_t *, device);
    UT_GenStub_AddParam(GENERIC_TORQUER_CommandDevice, uint8_t, cmd);
    UT_GenStub_AddParam(GENERIC_TORQUER_CommandDevice, uint32_t, payload);

    UT_GenStub_Execute(GENERIC_TORQUER_CommandDevice, Basic, NULL);

    return UT_GenStub_GetReturnValue(GENERIC_TORQUER_CommandDevice, int32_t);
}

int32_t GENERIC_TORQUER_RequestHK(uart_info_t *device, GENERIC_TORQUER_Device_HK_tlm_t *data)
{
    UT_GenStub_SetupReturnBuffer(GENERIC_TORQUER_RequestHK, int32_t);

    UT_GenStub_AddParam(GENERIC_TORQUER_RequestHK, uart_info_t *, device);
    UT_GenStub_AddParam(GENERIC_TORQUER_RequestHK, GENERIC_TORQUER_Device_HK_tlm_t *, data);

    UT_GenStub_Execute(GENERIC_TORQUER_RequestHK, Basic, NULL);

    return UT_GenStub_GetReturnValue(GENERIC_TORQUER_RequestHK, int32_t);
}

int32_t GENERIC_TORQUER_RequestData(uart_info_t *device, GENERIC_TORQUER_Device_Data_tlm_t *data)
{
    UT_GenStub_SetupReturnBuffer(GENERIC_TORQUER_RequestData, int32_t);

    UT_GenStub_AddParam(GENERIC_TORQUER_RequestData, uart_info_t *, device);
    UT_GenStub_AddParam(GENERIC_TORQUER_RequestData, GENERIC_TORQUER_Device_Data_tlm_t *, data);

    UT_GenStub_Execute(GENERIC_TORQUER_RequestData, Basic, NULL);

    return UT_GenStub_GetReturnValue(GENERIC_TORQUER_RequestData, int32_t);
}
