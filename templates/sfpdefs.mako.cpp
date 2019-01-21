/* This is a generated file. */
#include "types.hpp"
#include "manaager.hpp"

using namespace phosphor::sfp;
using std::literals;

const std::vector<SfpDefinition> Manager::sfpDefinitions
{

% for sfp in sfps:
	SfpDefinition{
		"${sfp['name']}"s,
		"${sfp['inventory']}"s,
                 GpioDefinition{
                          ${sfp['present']['key']},
                          "${sfp['present']['devpath']}"s,
                 },  
                 GpioDefinition{
                          ${sfp['reset']['key']},
                          "${sfp['reset']['devpath']}"s,
                 },  
                 GpioDefinition{
                          ${sfp['low_power_mode']['key']},
                          "${sfp['low_power_mode']['devpath']}"s,
                 },  
		 Eeprom{
			 ${sfp['eeprom']['bus']},
			 ${sfp['eeprom']['addr']},
		 }
          },
% endfor
};
