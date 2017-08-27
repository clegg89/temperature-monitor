#! /usr/bin/env python3.6
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2017 clegg <clegg@baratheon>
#
# Distributed under terms of the MIT license.

"""
Generate the Keys, Static IV and Hash input for our application
"""

from string import Template
import os
import glob
import secrets

ROOT_PATH = os.path.realpath(os.path.join(os.path.dirname(os.path.realpath(__file__)),'../..'))

class Key:
    def __init__(self, name, size):
        self.name = name
        self.value = secrets.token_bytes(size)
        self.cStr = self._cStr()

    def _cStr(self):
        keyStr = '{ '
        for x in self.value:
            keyStr += '0x' + format(x, '02X') + ', '

        keyStr += '}'

        return keyStr

class InputTemplate:
    def __init__(self, inputFileName):
        self.inputFileName = inputFileName
        self._determineOutputPath()

    def writeOutput(self, keys):
        if os.path.exists(self.outputPath):
            os.remove(self.outputPath)

        mapping = self._getMapping(keys)
        with open(self.inputFileName,'r') as inputFile:
            template = Template(inputFile.read())
            outputRaw = template.substitute(mapping)
            with open(self.outputPath,'w') as outputFile:
                outputFile.write(outputRaw)

    def _determineOutputPath(self):
        outName = os.path.splitext(os.path.basename(self.inputFileName))[0]
        fileType = os.path.splitext(outName)[1]

        if fileType == '.cpp':
            self.fileType = 'c'
            middle = 'node/src'
        elif fileType == '.py':
            self.fileType = 'python'
            middle = 'host'
        else:
            print('Unrecognized file type: ' + fileType)
            raise

        self.outputPath = os.path.join(ROOT_PATH,middle,outName)

    def _getMapping(self, keys):
        if self.fileType == 'c':
            return getMapping(keys, 'cStr')
        elif self.fileType == 'python':
            return getMapping(keys, 'value')
        else:
            raise

def genKeys(keySizeDict):
    return [Key(name,size) for name,size in keySizeDict.items()]

def getMapping(keys, attr):
    mapping = dict()

    for key in keys:
        mapping[key.name] = getattr(key,attr)

    return mapping

def genTempates(directory):
    return [InputTemplate(f) for f in glob.glob(os.path.join(directory,'*.in'))]

if __name__ == "__main__":

    keySizeDict = {
            'dataKey' : 16,
            'ivKey' : 16,
            'staticIv' : 16,
            'hashKey' : 16
            }

    keys = genKeys(keySizeDict)

    script_dir = os.path.dirname(os.path.realpath(__file__))

    for template in genTempates(script_dir):
        template.writeOutput(keys)
