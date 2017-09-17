#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2017 clegg <clegg@baratheon>
#
# Distributed under terms of the MIT license.
'''
This is a simple script whcih will generate a python file
containing the provided influxdb information necessary for
the application
'''

from string import Template
import os
import argparse
import getpass

if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog=os.path.split(__file__)[0], description='Set InfluxDB database, username, and password for middleware application')
    parser.add_argument('-d','--database',dest='database',help='The name of the database used by the application')
    parser.add_argument('-u','--username',dest='username',help='Username of the database')
    parser.add_argument('-p','--password',dest='password',help='Password of the database user')
    args = parser.parse_args()

    script_dir = os.path.dirname(os.path.realpath(__file__))

    if not args.database:
        args.database = input('Please enter the database name: ')

    if not args.username:
        args.username = input('Please enter the username: ')

    if not args.password:
        args.password = getpass.getpass('Please enter the password: ')

    template_map = dict()

    for key in ['database','username','password']:
        template_map[key] = getattr(args,key)

    outputFilePath = os.path.realpath(script_dir + '/../../influxdb_information.py')

    if os.path.exists(outputFilePath):
        os.remove(outputFilePath)

    with open(script_dir + '/influxdb_information.py.in', 'r') as inputFile:
        inputRaw = inputFile.read()
        template = Template(inputRaw)
        outputRaw = template.substitute(template_map)
        with open(outputFilePath, 'w') as outputFile:
            outputFile.write(outputRaw)
