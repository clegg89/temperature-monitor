#! /usr/bin/python3
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2017 clegg <clegg@baratheon>
#
# Distributed under terms of the MIT license.
'''
This is a simple script which will generate a C++ file
containing the provided MQTT information
'''

from string import Template
import os
import argparse
import getpass

if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog=os.path.split(__file__)[0],description='Set MQTT Broker information for ESP8266 firmware image')
    parser.add_argument('-n','--hostname',dest='hostname',help='The hostname of the MQTT broker')
    parser.add_argument('-o','--port',dest='port',default=1883,type=int,help='The port of the MQTT broker')
    parser.add_argument('-u','--username',dest='username',help='The username of the MQTT broker')
    parser.add_argument('-p','--password',dest='password',help='The password of the MQTT broker')
    args = parser.parse_args()

    script_dir = os.path.dirname(os.path.realpath(__file__))

    if not args.hostname:
        args.hostname = input('Please enter the Broker hostname: ')

    if not args.username:
        args.username = input('Please enter the Broker username: ')

    if not args.password:
        args.password = getpass.getpass('Please enter the Broker password: ')

    outputFilepath = os.path.realpath(script_dir + '/../../src/mqtt-broker-information.cpp')

    if os.path.exists(outputFilepath):
        os.remove(outputFilepath)

    with open(script_dir + '/mqtt-broker-information.cpp.in', 'r') as inputFile:
        template = Template(inputFile.read())
        outputRaw = template.substitute(hostname=args.hostname, port=args.port, username=args.username, password=args.password)
        with open(outputFilepath, 'w') as outputFile:
            outputFile.write(outputRaw)
