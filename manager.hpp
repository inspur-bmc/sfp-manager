#include <sdbusplus/sdbus.hpp>
#include <memory>
#include <vector>
#include <experimental/filesystem>
#include <xyz/openbmc_project/Sfp/Manager/server.hpp>
#include "sfp.hpp"

using ManagerObject = sdbusplus::server::object_t<
    sdbusplus::xyz::openbmc_project::Sfp::server::Manager>;


class Manager : public ManagerObject
{
  public:
    Manager(sdbusplus::bus::bus& bus, const std::string& path) :
        ManagerObject(bus, path.c_str())
    {
            for(int i = 0;i<2;i++){
                    std::string realpath = path + "/" + std::to_string(i);
                    auto sfp = std::make_shared<Sfp>(bus,realpath);
                    sfps.push_back(sfp);
            }
    }

  private:
    std::vector<std::shared_ptr<Sfp>> sfps;
};
