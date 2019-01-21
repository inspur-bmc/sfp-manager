#pragma once
#include "file.hpp"
#include "gpio.hpp"
#include "types.hpp"

#include <sdbusplus/server.hpp>
#include <sdeventplus/event.hpp>
#include <xyz/openbmc_project/Sfp/Sfp/server.hpp>

namespace phosphor
{
namespace sfp
{

using SfpObject = sdbusplus::server::object_t<
    sdbusplus::xyz::openbmc_project::Sfp::server::Sfp>;

class Sfp : public SfpObject
{
  public:
    Sfp(sdbusplus::bus::bus& bus, const std::string& path,
        const SfpDefinition& sfpDefinition, sdeventplus::Event& event) :
        SfpObject(bus, path.c_str()),
        event(event),
        gpioLowPowerMode(
            std::get<pathField>(std::get<lowPoerModeField>(sfpDefinition)),
            std::get<keyField>(std::get<lowPoerModeField>(sfpDefinition)),
            event),
        gpioReset(std::get<pathField>(std::get<resetField>(sfpDefinition)),
                  std::get<keyField>(std::get<resetField>(sfpDefinition)),
                  event)
    {
    }

    void reset() override;
    bool lowPowerMode(bool value) override;
    std::vector<uint8_t> eeprom(std::vector<uint8_t> value) override;
    bool present(bool value) override;

  private:
    sdeventplus::Event& event;
    Gpio gpioLowPowerMode;
    Gpio gpioReset;
};
} // namespace sfp
} // namespace phosphor
