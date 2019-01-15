#include <sdbusplus/server.hpp>
#include <xyz/openbmc_project/Sfp/Sfp/server.hpp>

using SfpObject =
    sdbusplus::server::object_t<sdbusplus::xyz::openbmc_project::Sfp::server::Sfp>;

class Sfp : public SfpObject
{
  public:
    Sfp(sdbusplus::bus::bus& bus, std::string& path) : SfpObject(bus, path.c_str())
    {
    }

    void reset() override;
};

