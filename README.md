## Introduction
This example demonstrates how to use the Treasure Data REST API to send data from mbed OS to Treasure Data. In this example we will use the [Grove GPS module](https://os.mbed.com/components/Grove-GPS/) to read GPS data and send it to treasure data over Ethernet. 

## Pre-Requisites
- Treasure Data Account
- Treasure Data REST API Key
- Mbed OS Account
- Mbed board with Ethernet and Serial Tx/Rx
- [Grove GPS module](https://os.mbed.com/components/Grove-GPS/) 

## Hardware 
1. Connect the GPS module with serial TX connected to D1 and RX to D0
   - If you need to connect to a different set of pins, you'll need to use [this constructor](https://github.com/sarahmarshy/vert-td-gps/blob/master/main.cpp#L25) to set them.
1. Plug in the ethernet cable to the board

## How to use
1) Copy / Paste your Treasure Data API key (My Profile->API Keys) into the mbed_app.json file
1) Create Database called `gps_test` (Data workbench->Databases->New Database) for the program to send data to
1) Compile and Run code on board (`mbed compile --target auto --toolchain GCC_ARM --flash --sterm`)
1) View data in Treasure Data

## How is this working?
See the readme on the [Treasure Data REST API Library](https://github.com/blackstoneengineering/mbed-os-treasuredata-rest).

## Liscense
Apache 2.0
