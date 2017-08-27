#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2017 clegg <clegg@baratheon>
#
# Distributed under terms of the MIT license.

"""
The main application
"""

import paho.mqtt.client as paho
import ssl
import os
from security_information import APP_KEYS
from mqtt_broker_information import MQTT_INFORMATION

def on_connect(mosq, objc, flags, rc):
    print("rc: " + str(rc))

def on_message(mosq, obj, msg):
    print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))

def on_publish(mosq, obj, mid):
    print("mid: " + str(mid))

def on_subscribe(mosq, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

def on_log(mosq, obj, level, string):
    print(string)

if __name__ == "__main__":
    mqttc = paho.Client()

    script_dir = os.path.realpath(os.path.dirname(__file__))
    cacert = os.path.join(script_dir,'cacert.pem')

    if not os.path.exists(cacert):
        print("Error: CA Certificate not found")
        exit(1)

    mqttc.tls_set(cacert)

    mqttc.on_message = on_message
    mqttc.on_connect = on_connect
    mqttc.on_publish = on_publish
    mqttc.on_subscribe = on_subscribe

    mqttc.username_pw_set(MQTT_INFORMATION['username'], MQTT_INFORMATION['password'])

    try:
        mqttc.connect(MQTT_INFORMATION['hostname'], MQTT_INFORMATION['port'])
    except ssl.SSLError as err:
        print("SSL Error connecting to " + MQTT_INFORMATION['hostname'] + ": {0}".format(err))
        exit(1)


    print("subscribe: " + str(mqttc.subscribe('monitor', 0)))

    rc = 0
    while rc == 0:
        rc = mqttc.loop()

    print("rc: " + str(rc))
