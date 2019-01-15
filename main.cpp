#include <iostream>
#include <sdbusplus/bus.hpp>
#include <sdeventplus/event.hpp>
#include "manager.hpp"
int main()
{
    auto event = sdeventplus::Event::get_default();
    auto bus = sdbusplus::bus::new_default();

    bus.attach_event(event.get(), SD_EVENT_PRIORITY_NORMAL);

    Manager manager{bus,"/org/inspur/sfp"};
    bus.request_name("org.inspur.Sfp");


    return event.loop();
}
