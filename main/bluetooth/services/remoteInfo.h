/*
 * File: \remoteInfo.h
 * Project: services
 * Created Date: 2024-03-11 22:55:56
 * Author: Guoyi
 * -----
 * Last Modified: 2024-08-01 11:20:31
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "host/ble_hs.h"
#include "host/ble_uuid.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"
#include "services/ans/ble_svc_ans.h"

#include "utils/types/F1D.h"
#include "global/global.h"

// ===========================远程信息服务 0x1022================================== //

/* 服务的uuid */
static const ble_uuid16_t gatt_remoteInfo_svc_uuid = BLE_UUID16_INIT(0x1022);

/* 服务内的characteristic */
// 1.实时位置坐标
static float gatt_remoteInfo_chr_realtime_pos_val[3]; // 3个浮点数，x,y,抬笔状态
static uint16_t gatt_remoteInfo_chr_realtime_pos_val_handle;
static const ble_uuid16_t gatt_remoteInfo_chr_realtime_pos_uuid = BLE_UUID16_INIT(0x1023);
// 2.电源电压
static uint16_t gatt_remoteInfo_chr_power_voltage_val_handle;
static const ble_uuid16_t gatt_remoteInfo_chr_power_voltage_uuid = BLE_UUID16_INIT(0x1024);
// 3.当前执行指令编号和累计执行指令数量
static uint16_t gatt_remoteInfo_chr_cmd_number_val_handle;
static const ble_uuid16_t gatt_remoteInfo_chr_cmd_number_uuid = BLE_UUID16_INIT(0x1025);

// 访问回调函数
static int gatt_remoteInfo_svc_access(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg);
static int gatt_remoteInfo_svc_access(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    int rc;
    WriterBotInstance->bluetoothLED.blink(1, 200);

    switch (ctxt->op)
    {
    // 读操作 Append the value to ctxt->om if the operation is READ
    case BLE_GATT_ACCESS_OP_READ_CHR:
        if (attr_handle == gatt_remoteInfo_chr_realtime_pos_val_handle)
        {
            gatt_remoteInfo_chr_realtime_pos_val[0] = WriterBotInstance->xSlider.getCurrentRealPosition();
            gatt_remoteInfo_chr_realtime_pos_val[1] = WriterBotInstance->ySlider.getCurrentRealPosition();
            gatt_remoteInfo_chr_realtime_pos_val[2] = WriterBotInstance->isPenDown;

            rc = os_mbuf_append(ctxt->om,
                                gatt_remoteInfo_chr_realtime_pos_val,
                                sizeof(gatt_remoteInfo_chr_realtime_pos_val));
            return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
        }
        else if (attr_handle == gatt_remoteInfo_chr_power_voltage_val_handle)
        {
            float voltage = WriterBotInstance->powerADC.readVoltage();
            rc = os_mbuf_append(ctxt->om,
                                &voltage,
                                sizeof(voltage));
            return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
        }
        else if (attr_handle == gatt_remoteInfo_chr_cmd_number_val_handle)
        {
            int32_t result[2] = {WriterBotInstance->commandManager.currentCommandNumber,
                                 WriterBotInstance->commandManager.executedCommandCount};
            rc = os_mbuf_append(ctxt->om,
                                &result,
                                sizeof(result));
            return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
        }
        goto unknown;

    default:
        goto unknown;
    }

unknown:
    /* Unknown characteristic/descriptor;
     * The NimBLE host should not have called this function;
     */
    assert(0);
    return BLE_ATT_ERR_UNLIKELY;
}
