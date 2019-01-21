#pragma once

#include "file.hpp"

#include <linux/gpio.h>
#include <systemd/sd-event.h>

#include <functional>
#include <sdeventplus/event.hpp>
#include <string>

namespace phosphor
{
namespace sfp
{
using GpioNumber =
    std::remove_reference<decltype(gpiohandle_request::lineoffsets[0])>::type;
using GpioValue =
    std::remove_reference<decltype(gpiohandle_data::values[0])>::type;

using EdgeCallback = std::function<void()>;

class Gpio
{
  public:
    enum class Direction
    {
        input,
        output
    };

    enum class Value
    {
        low,
        high
    };

    Gpio() = delete;
    Gpio(const Gpio&) = delete;
    Gpio(Gpio&&) = delete;
    Gpio& operator=(const Gpio&) = delete;
    Gpio& operator=(Gpio&&) = delete;
    ~Gpio() = default;

    Gpio(const std::string& path, GpioNumber number, sdeventplus::Event &event,
         Direction direction = Direction::output) :
        devpath(path),
        gpio(number), event(event), direction(direction)
    {
        requestLine();
    }

    void set(Value vaule);

    void setEdgeCallback(EdgeCallback rising, EdgeCallback falling)
    {
        risingEdgeCallback = rising;
        fallingEdgeCallback = falling;
    }

  private:
    void requestHandleLine(FileDescriptor& fd,
                           Value defaultValue = Value::high);
    void requestEventLine(FileDescriptor& fd);
    void requestLine();
    void registerCallback();
    static int processEvents(sd_event_source* source, int fd, uint32_t revents,
                       void* userdata);
    const std::string devpath;
    const GpioNumber gpio;
    sdeventplus::Event& event;
    const Direction direction;

    EdgeCallback risingEdgeCallback;
    EdgeCallback fallingEdgeCallback;
    FileDescriptor lineFd;
};
} // namespace sfp
} // namespace phosphor
