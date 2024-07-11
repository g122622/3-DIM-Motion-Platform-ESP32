#pragma once
#include <driver/i2c.h>

class I2C
{
public:
    void init(int scl = 22, int sda = 21, int frequency = 100000, int port = 0);
    void write(uint8_t addr, uint8_t data);
    void write(uint8_t addr, uint8_t *data, size_t size);
    void read(uint8_t addr, uint8_t *data, size_t size);

private:
    i2c_port_t i2c_master_port = i2c_port_t::I2C_NUM_0;
};
