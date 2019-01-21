#include "sfp.hpp"
#include "gpio.hpp"

#include <iostream>
#include <sdbusplus/server.hpp>
#include <thread>

namespace phosphor
{
namespace sfp
{

void Sfp::reset()
{
    gpioReset.set(Gpio::Value::low);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    gpioReset.set(Gpio::Value::high);
}

bool Sfp::lowPowerMode(bool value)
{
    if (value)
    {
           gpioLowPowerMode.set(Gpio::Value::high); 
    }
    else
    {
        gpioLowPowerMode.set(Gpio::Value::low);
    }

    return SfpObject::lowPowerMode(value);
}

std::vector<uint8_t> Sfp::eeprom(std::vector<uint8_t> value)
{
    return SfpObject::eeprom(value);
}

bool Sfp::present(bool value)
{
    return SfpObject::present(value);
}
} // namespace sfp
} // namespace phosphor
