#! /usr/bin/python3
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2017 clegg <clegg@baratheon>
#
# Distributed under terms of the MIT license.
'''
This is a simple script which will generate a C++ file
containing the provided SSID and password for a user's
WiFi.
'''

from string import Template
import os
import argparse
import getpass

if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog=os.path.split(__file__)[0],description='Set WiFi SSID and Password for ESP8266 firmware image')
    parser.add_argument('-s','--ssid',dest='ssid',help='The SSID of your network')
    parser.add_argument('-p','--password',dest='password',help='The password to join your network')
    args = parser.parse_args()

    if not args.ssid:
        args.ssid = input('Please enter your WiFi SSID: ')

    if not args.password:
        args.password = getpass.getpass('Please enter your WiFi password: ')

    outputFilePath = os.path.realpath('../../lib/secrets/secrets.cpp')

    if os.path.exists(outputFilePath):
        os.remove(outputFilePath)

    with open('secrets.cpp.in', 'r') as inputFile:
        inputRaw = inputFile.read()
        template = Template(inputRaw)
        outputRaw = template.substitute(ssid=args.ssid,password=args.password)
        with open(outputFilePath, 'w') as outputFile:
            outputFile.write(outputRaw)
