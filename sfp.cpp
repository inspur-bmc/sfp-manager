#include <iostream>
#include <sdbusplus/server.hpp>

#include "sfp.hpp"

void Sfp::reset()
{
    std::cout << "reset" << std::endl;
}
