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
import glob

ROOT_PATH = os.path.realpath(os.path.join(os.path.dirname(os.path.realpath(__file__)),'../..'))

class InputTemplate:
    def __init__(self, inputFileName):
        self.inputFileName = inputFileName
        self._determineOutputPath()

    def writeOutput(self, mapping):
        if os.path.exists(self.outputPath):
            os.remove(self.outputPath)

        with open(self.inputFileName,'r') as inputFile:
            template = Template(inputFile.read())
            outputRaw = template.substitute(self._revise(mapping))
            with open(self.outputPath,'w') as outputFile:
                outputFile.write(outputRaw)

    def _determineOutputPath(self):
        outName = os.path.splitext(os.path.basename(self.inputFileName))[0]
        fileType = os.path.splitext(outName)[1]

        if fileType == '.cpp':
            self.fileType = 'c'
            middle = 'firmware/src'
        elif fileType == '.py':
            self.fileType = 'python'
            middle = 'middleware'
        else:
            print('Unrecognized file type: ' + fileType)
            raise

        self.outputPath = os.path.join(ROOT_PATH,middle,outName)

    def _revise(self, mapping):
        newMap = dict()
        newMap['hostname'] = mapping['hostname']
        newMap['port'] = mapping['port']

        if self.fileType == 'c':
            newMap['username'] = mapping['firmware_username']
            newMap['password'] = mapping['firmware_password']
        elif self.fileType == 'python':
            newMap['username'] = mapping['middleware_username']
            newMap['password'] = mapping['middleware_password']
        else:
            raise

        return newMap

def genTempates(directory):
    return [InputTemplate(f) for f in glob.glob(os.path.join(directory,'*.in'))]

if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog=os.path.split(__file__)[0],description='Set MQTT Broker information for ESP8266 firmware image')
    parser.add_argument('-n','--hostname',dest='hostname',help='The hostname of the MQTT broker')
    parser.add_argument('-o','--port',dest='port',default=1883,type=int,help='The port of the MQTT broker')
    args = parser.parse_args()

    if not args.hostname:
        args.hostname = input('Please enter the Broker hostname: ')

    middleware_username = input('Please enter the username for the middleware application: ')
    middleware_password = getpass.getpass('Please enter the password for the host application: ')
    firmware_username = input('Please enter the username for the firmware application: ')
    firmware_password = getpass.getpass('Please enter the password for the firmware application: ')

    mapping = {
            'hostname' : args.hostname,
            'port' : args.port,
            'middleware_username' : middleware_username,
            'middleware_password' : middleware_password,
            'firmware_username' : firmware_username,
            'firmware_password' : firmware_password
            }

    script_dir = os.path.dirname(os.path.realpath(__file__))

    for template in genTempates(script_dir):
        template.writeOutput(mapping)
