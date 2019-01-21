#include "sfp.hpp"
#include "types.hpp"

#include <experimental/filesystem>
#include <iostream>
#include <memory>
#include <sdbusplus/sdbus.hpp>
#include <sdeventplus/event.hpp>
#include <vector>
#include <xyz/openbmc_project/Sfp/Manager/server.hpp>

namespace phosphor
{
namespace sfp
{

using ManagerObject = sdbusplus::server::object_t<
    sdbusplus::xyz::openbmc_project::Sfp::server::Manager>;

class Manager : public ManagerObject
{
  public:
    Manager(sdbusplus::bus::bus& bus, const std::string& path,sdeventplus::Event &event) :
        ManagerObject(bus, path.c_str()),event(event)
    {
        using namespace std::string_literals;
        for (const auto& sfpDef : sfpDefinitions)
        {
            auto name = std::get<nameField>(sfpDef);
            auto realpath = path + "/"s + name;
            auto sfp = std::make_shared<Sfp>(bus, realpath,sfpDef,event);
            sfps.push_back(sfp);
        }
        ManagerObject::count(sfpDefinitions.size());
    }

  private:
    std::vector<std::shared_ptr<Sfp>> sfps;
    static const std::vector<SfpDefinition> sfpDefinitions;
    sdeventplus::Event &event;
};
} // namespace sfp
} // namespace phosphor
