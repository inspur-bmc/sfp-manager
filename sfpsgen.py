#!/usr/bin/env python

import os
import sys
import yaml
from argparse import ArgumentParser
from mako.template import Template

tmpl = '''\
/* This is a generated file. */
#include "types.hpp"
#include "manager.hpp"

using namespace phosphor::sfp;
using namespace std::string_literals;

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
'''

if __name__ == '__main__':
    parser = ArgumentParser(description = "Phosphor sfp definition parser");

    parser.add_argument('-s','--sfpdefs_yaml',dest='sfpdefs_yaml',default='example/sfpdefs.yaml',
            help='sfp definitional yaml')
    parser.add_argument('-o','--output_dir',dest='output_dir',default='.',
            help='output directory')

    args = parser.parse_args()

    with open(args.sfpdefs_yaml,'r') as sfpdefs_input:
        sfpdefs_data = yaml.safe_load(sfpdefs_input) or {}

    output_file = os.path.join(args.output_dir,'sfpdefs.cpp')
    with open(output_file,'w') as output:
        output.write(Template(tmpl).render(sfps=sfpdefs_data))

