#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "host/ble_hs.h"
#include "host/ble_uuid.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"
#include "services/ans/ble_svc_ans.h"
#include "../utils/gatt_svr_write.h"

#include "global/global.h"

// ===========================遥控器服务 0xffe0================================== //

/* 服务的uuid */
static const ble_uuid16_t gatt_remoteControll_svc_uuid = BLE_UUID16_INIT(0xffe0);

/* 服务内的characteristic */
// 1.PID配置
// 2个PID配置，每个配置含5个float数据，(KP,KI,KD,再加一个积分上限和PID总输出上限共5个float数据)
static float gatt_remoteControll_chr_PID_val[2 * 5];
static uint16_t gatt_remoteControll_chr_PID_val_handle;
static const ble_uuid16_t gatt_remoteControll_chr_PID_uuid = BLE_UUID16_INIT(0xffe1);
// 2.运行状态（一个int，表示开始，暂停，中止等）
static uint16_t gatt_remoteControll_chr_system_status_val_handle;
static const ble_uuid16_t gatt_remoteControll_chr_system_status_uuid = BLE_UUID16_INIT(0xffe2);
// 3.上位机所提交的任务batch
static uint16_t gatt_remoteControll_chr_task_batch_val_handle;
static const ble_uuid16_t gatt_remoteControll_chr_task_batch_uuid = BLE_UUID16_INIT(0xffe3);
// 4.笔 lift 和 drop 角度，以及舵机当前角度
static uint16_t gatt_remoteControll_chr_pen_val_handle;
static const ble_uuid16_t gatt_remoteControll_chr_pen_uuid = BLE_UUID16_INIT(0xffe4);

void convertPIDtoBle()
{
    gatt_remoteControll_chr_PID_val[0] = WriterBotInstance->xSlider.motor.pid.Kp;
    gatt_remoteControll_chr_PID_val[1] = WriterBotInstance->xSlider.motor.pid.Ki;
    gatt_remoteControll_chr_PID_val[2] = WriterBotInstance->xSlider.motor.pid.Kd;
    gatt_remoteControll_chr_PID_val[3] = WriterBotInstance->xSlider.motor.pid.integralLimit;
    gatt_remoteControll_chr_PID_val[4] = WriterBotInstance->xSlider.motor.pid.outputLimit;

    gatt_remoteControll_chr_PID_val[5] = WriterBotInstance->ySlider.motor.pid.Kp;
    gatt_remoteControll_chr_PID_val[6] = WriterBotInstance->ySlider.motor.pid.Ki;
    gatt_remoteControll_chr_PID_val[7] = WriterBotInstance->ySlider.motor.pid.Kd;
    gatt_remoteControll_chr_PID_val[8] = WriterBotInstance->ySlider.motor.pid.integralLimit;
    gatt_remoteControll_chr_PID_val[9] = WriterBotInstance->ySlider.motor.pid.outputLimit;
}

void convertBletoPID()
{
    WriterBotInstance->xSlider.motor.pid.Kp = gatt_remoteControll_chr_PID_val[0];
    WriterBotInstance->xSlider.motor.pid.Ki = gatt_remoteControll_chr_PID_val[1];
    WriterBotInstance->xSlider.motor.pid.Kd = gatt_remoteControll_chr_PID_val[2];
    WriterBotInstance->xSlider.motor.pid.integralLimit = gatt_remoteControll_chr_PID_val[3];
    WriterBotInstance->xSlider.motor.pid.outputLimit = gatt_remoteControll_chr_PID_val[4];

    WriterBotInstance->ySlider.motor.pid.Kp = gatt_remoteControll_chr_PID_val[5];
    WriterBotInstance->ySlider.motor.pid.Ki = gatt_remoteControll_chr_PID_val[6];
    WriterBotInstance->ySlider.motor.pid.Kd = gatt_remoteControll_chr_PID_val[7];
    WriterBotInstance->ySlider.motor.pid.integralLimit = gatt_remoteControll_chr_PID_val[8];
    WriterBotInstance->ySlider.motor.pid.outputLimit = gatt_remoteControll_chr_PID_val[9];

    printf("[BLE]received PID config of X -> Kp: %f, Ki: %f, Kd: %f, integralLimit: %f, outputLimit: %f\n",
           gatt_remoteControll_chr_PID_val[0], gatt_remoteControll_chr_PID_val[1], gatt_remoteControll_chr_PID_val[2],
           gatt_remoteControll_chr_PID_val[3], gatt_remoteControll_chr_PID_val[4]);

    printf("[BLE]received PID config of Y -> Kp: %f, Ki: %f, Kd: %f, integralLimit: %f, outputLimit: %f\n",
           gatt_remoteControll_chr_PID_val[5], gatt_remoteControll_chr_PID_val[6], gatt_remoteControll_chr_PID_val[7],
           gatt_remoteControll_chr_PID_val[8], gatt_remoteControll_chr_PID_val[9]);
}

// 读写回调函数
static int gatt_remoteControll_svc_access(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg);
static int gatt_remoteControll_svc_access(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    int rc;

    switch (ctxt->op)
    {
    // 读操作 Append the value to ctxt->om if the operation is READ
    case BLE_GATT_ACCESS_OP_READ_CHR:
        if (attr_handle == gatt_remoteControll_chr_PID_val_handle)
        {
            convertPIDtoBle();
            rc = os_mbuf_append(ctxt->om,
                                gatt_remoteControll_chr_PID_val,
                                sizeof(gatt_remoteControll_chr_PID_val));
            return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
        }
        else if (attr_handle == gatt_remoteControll_chr_system_status_val_handle)
        {
            rc = os_mbuf_append(ctxt->om,
                                &global_system_status,
                                sizeof(global_system_status));
            return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
        }
        else if (attr_handle == gatt_remoteControll_chr_task_batch_val_handle)
        {
            // 不支持读取任务batch。只支持写入任务batch。直接返回0代表成功。
            return 0;
        }
        goto unknown;

    // 写操作 Write ctxt->om to the value if the operation is WRITE
    case BLE_GATT_ACCESS_OP_WRITE_CHR:
        // if (conn_handle != BLE_HS_CONN_HANDLE_NONE)
        // {
        //     MODLOG_DFLT(INFO, "Characteristic write; conn_handle=%d attr_handle=%d",
        //                 conn_handle, attr_handle);
        // }
        // else
        // {
        //     MODLOG_DFLT(INFO, "Characteristic write by NimBLE stack; attr_handle=%d",
        //                 attr_handle);
        // }

        if (attr_handle == gatt_remoteControll_chr_PID_val_handle)
        {
            rc = gatt_svr_write(ctxt->om,
                                sizeof(gatt_remoteControll_chr_PID_val),
                                sizeof(gatt_remoteControll_chr_PID_val),
                                gatt_remoteControll_chr_PID_val, NULL);
            convertBletoPID();
        }
        else if (attr_handle == gatt_remoteControll_chr_system_status_val_handle)
        {
            rc = gatt_svr_write(ctxt->om,
                                sizeof(global_system_status),
                                sizeof(global_system_status),
                                &global_system_status, NULL);
        }
        else if (attr_handle == gatt_remoteControll_chr_task_batch_val_handle)
        {
            const int BATCH_SIZE = 16;      // 每一个batch共BATCH_SIZE条任务
            uint8_t data[12 * BATCH_SIZE]; // 每条任务12字节，共BATCH_SIZE条任务
            rc = gatt_svr_write(ctxt->om,
                                sizeof(data),
                                sizeof(data),
                                data, NULL);
            // 处理任务batch
            WriterBotInstance->commandManager.sendBatchToQueue(data, BATCH_SIZE);
        }
        else if (attr_handle == gatt_remoteControll_chr_pen_val_handle)
        {
            float data[3];

            rc = gatt_svr_write(ctxt->om,
                                sizeof(data),
                                sizeof(data),
                                data, NULL);

            WriterBotInstance->penUpAngle = data[0];   // lift
            WriterBotInstance->penDownAngle = data[1]; // drop
            WriterBotInstance->penServo.setAngle(data[2]);

            printf("received pen config -> lift: %f, drop: %f, servoAngle: %f\n", data[0], data[1], data[2]);
        }
        else
        {
            goto unknown;
        }
        // Send notification (or indication) to any connected devices that
        // have subscribed for notification (or indication) for specified characteristic.
        ble_gatts_chr_updated(attr_handle);
        // MODLOG_DFLT(INFO, "Notification/Indication scheduled for all subscribed peers.\n");
        return rc;

    case BLE_GATT_ACCESS_OP_READ_DSC:
        goto unknown;

    case BLE_GATT_ACCESS_OP_WRITE_DSC:
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
