#include "types.hpp"
#include "manager.hpp"

namespace phosphor
{
namespace sfp
{
const std::vector<SfpDefinition> Manager::sfpDefinitions
{
        SfpDefinition{
                "sfp1",
                "/sys/sfp1",
                GpioDefinition{124,"/dev/input/by-path/xxx"},
                GpioDefinition{124,"/dev/input/by-path/xxx"},
                GpioDefinition{124,"/dev/input/by-path/xxx"},
                Eeprom{1,54}
        },
        SfpDefinition{
                "sfp2",
                "/sys/sfp2",
                GpioDefinition{134,"/dev/input/by-path/xxx"},
                GpioDefinition{134,"/dev/input/by-path/xxx"},
                GpioDefinition{134,"/dev/input/by-path/xxx"},
                Eeprom{1,55}
        }
};

}
}
