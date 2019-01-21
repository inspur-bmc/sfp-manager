#pragma once

#include <tuple>
#include <vector>

namespace phosphor
{
namespace sfp
{
constexpr auto busField = 0;
constexpr auto addrField = 0;
using Eeprom = std::tuple<int, int>;

constexpr auto keyField = 0;
constexpr auto pathField = 1;

using GpioDefinition = std::tuple<int, std::string>;

constexpr auto nameField = 0;
constexpr auto inventoryField = 1;
constexpr auto presentField = 2;
constexpr auto resetField = 3;
constexpr auto lowPoerModeField = 4;
constexpr auto eepromField = 5;

using SfpDefinition = std::tuple<std::string, std::string, GpioDefinition,
                                 GpioDefinition, GpioDefinition, Eeprom>;

} // namespace sfp
} // namespace phosphor
