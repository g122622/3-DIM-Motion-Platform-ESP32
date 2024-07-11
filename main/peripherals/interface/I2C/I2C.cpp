#include "I2C.h"
#include <driver/i2c.h>

void I2C::init(int scl, int sda, int frequency, int port)
{
    if (port < 0 || port > 1)
    {
        printf("Invalid I2C port number: %d\n", port);
        return;
    }
    i2c_config_t conf;
    this->i2c_master_port = static_cast<i2c_port_t>(port); /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
    const int I2C_MASTER_TX_BUF_DISABLE = 0;               /*!< I2C master doesn't need buffer */
    const int I2C_MASTER_RX_BUF_DISABLE = 0;               /*!< I2C master doesn't need buffer */
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = sda; // select GPIO specific to your project
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = scl; // select GPIO specific to your project
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = frequency; // select frequency specific to your project
    conf.clk_flags = 0;
    i2c_param_config(i2c_master_port, &conf);
    i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

void I2C::write(uint8_t addr, uint8_t *data, size_t size)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, addr << 1 | I2C_MASTER_WRITE, I2C_MASTER_ACK);
    i2c_master_write(cmd, data, size, 0);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(i2c_master_port, cmd, 1 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
}

void I2C::write(uint8_t addr, uint8_t data)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    esp_err_t err = i2c_master_write_byte(cmd, addr << 1 | I2C_MASTER_WRITE, I2C_MASTER_ACK);
    if (err != ESP_OK)
    {
        printf("Error writing to I2C bus: %d\n", err);
    }

    i2c_master_write_byte(cmd, data, 0);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(i2c_master_port, cmd, 1 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
}

void I2C::read(uint8_t addr, uint8_t *data, size_t size)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, addr << 1 | I2C_MASTER_READ, I2C_MASTER_ACK);
    i2c_master_read(cmd, data, size, I2C_MASTER_ACK);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(i2c_master_port, cmd, 1 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
}
