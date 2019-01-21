#include "gpio.hpp"

#include <fcntl.h>
#include <sys/ioctl.h>

#include <cassert>
#include <cstring>
#include <stdexcept>
#include <system_error>

namespace phosphor
{
namespace sfp
{

constexpr auto consumer_label = "sfp-manager";

void Gpio::set(Value value)
{
    assert(direction == Direction::output);
    gpiohandle_data data;
    data.values[0] = static_cast<GpioValue>(value);

    auto rc = ioctl(lineFd(), GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    if (rc == -1)
    {
        throw std::runtime_error("FAILED GPIOHANDLE_SET_LINE_VALUES_IOCTL");
    }
}

void Gpio::requestEventLine(FileDescriptor& fd)
{
    gpioevent_request request;
    std::strncpy(request.consumer_label, consumer_label,
                 sizeof(request.consumer_label));
    request.handleflags = GPIOHANDLE_REQUEST_OPEN_DRAIN;
    request.eventflags =
        GPIOEVENT_EVENT_RISING_EDGE | GPIOEVENT_EVENT_FALLING_EDGE;
    auto rc = ioctl(fd(), GPIO_GET_LINEEVENT_IOCTL, &request);
    if (rc == -1)
    {
        throw std::runtime_error("Failed GPIO_GET_LINEEVENT_IOCTL");
    }
    lineFd.set(request.fd);
}

void Gpio::requestHandleLine(FileDescriptor& fd, Value defaultValue)
{
    gpiohandle_request request{};
    std::strncpy(request.consumer_label, consumer_label,
                 sizeof(request.consumer_label));
    request.flags = GPIOHANDLE_REQUEST_OUTPUT;
    request.lineoffsets[0] = gpio;
    request.lines = 1;
    request.default_values[0] = static_cast<GpioValue>(defaultValue);
    auto rc = ioctl(fd(), GPIO_GET_LINEHANDLE_IOCTL, &request);
    if (rc == -1)
    {
        throw std::runtime_error("Failed GPIO_GET_LINEHANDLE_IOCTL");
    }
    lineFd.set(request.fd);

    registerCallback();
}

void Gpio::requestLine()
{
    FileDescriptor fd{open(devpath.c_str(), O_RDWR)};
    if (fd() == -1)
    {
        throw std::runtime_error("Failed openning GPIO device");
    }

    if (direction == Direction::output)
    {
        requestHandleLine(fd);
    }
    else
    {
        requestEventLine(fd);
    }
}

int Gpio::processEvents(sd_event_source* source, int fd, uint32_t revents,
                         void* userdata)
{
    auto gpioInstance = static_cast<Gpio*>(userdata);
    gpioevent_data data;

    auto rc = read(gpioInstance->lineFd(), &data, sizeof(data));
    if (rc == -1)
    {
        throw std::system_error(errno, std::generic_category(),
                                "gpioevent read");
    }
    if (rc != sizeof(data))
    {
        throw std::runtime_error("event read didn't get enough data");
    }

    if (data.id == GPIOEVENT_EVENT_RISING_EDGE)
    {
        gpioInstance->risingEdgeCallback();
    }
    else
    {
        gpioInstance->fallingEdgeCallback();
    }

    return 0;
}

void Gpio::registerCallback()
{
    sd_event_source* source = nullptr;

    auto rc = sd_event_add_io(event.get(), &source, lineFd(), EPOLLIN,
                              processEvents, this);
    if (rc < 0)
    {
        throw std::runtime_error("registerCallback error ");
    }
}

} // namespace sfp
} // namespace phosphor
