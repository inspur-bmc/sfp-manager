#!/usr/bin/env python

import os
import sys
import yaml
from argparse import ArgumentParser
from mako.template import Template

if __name__ == '__main__':
    parser = ArgumentParser(description = "Phosphor sfp definition parser");

    parser.add_argument('-s','--sfpdefs_yaml',dest='sfpdefs_yaml',default='example/sfpdefs.yaml',
            help='sfp definitional yaml')
    parser.add_argument('-t','--sfpdefs_mako',dest='sfpdefs_mako',default='templates/sfpdefs.mako.cpp',
            help='sfp definitional mako')
    parser.add_argument('-o','--output_dir',dest='output_dir',default='.',
            help='output directory')

    args = parser.parse_args()

    if not args.sfpdefs_yaml:
        parser.print_usage()
        sys.exit(1)

    with open(args.sfpdefs_yaml,'r') as sfpdefs_input:
        sfpdefs_data = yaml.safe_load(sfpdefs_input) or {}

    print(sfpdefs_data)

    for sfp in sfpdefs_data:
        print(sfp)
    print(args.sfpdefs_mako)
    templ = Template(filename=args.sfpdefs_mako,input_encoding='utf-8')
    output_file = os.path.join(args.output_dir,'sfpdefs.cpp')
    with open(output_file,'w') as output:
        output.write(templ.render(sfps=sfpdefs_data))

    print("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    print(output_file);
    print("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

