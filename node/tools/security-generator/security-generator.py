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
import secrets

def genKeyStr(keySize):
    key = secrets.token_bytes(keySize)

    keyStr = '{ '
    for x in key:
        keyStr += '0x' + format(x, '02X') + ', '

    keyStr += '}'

    return keyStr

if __name__ == "__main__":

    keySize = 16
    ivSize = 16
    hashKeySize = 16

    dataKeyStr = genKeyStr(keySize)
    ivKeyStr = genKeyStr(keySize)
    staticIvStr = genKeyStr(ivSize)
    hashKeyStr = genKeyStr(hashKeySize)

    script_dir = os.path.dirname(os.path.realpath(__file__))
    outputFilePath = os.path.realpath(script_dir + '/../../src/security-information.cpp')

    if os.path.exists(outputFilePath):
        os.remove(outputFilePath)

    with open(script_dir + '/security-information.cpp.in', 'r') as inputFile:
        template = Template(inputFile.read())
        outputRaw = template.substitute(dataKey=dataKeyStr,
                ivKey=ivKeyStr, staticIv=staticIvStr, hashKey=hashKeyStr)
        with open(outputFilePath, 'w') as outputFile:
            outputFile.write(outputRaw)
