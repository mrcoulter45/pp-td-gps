/* WiFi Example
 * Copyright (c) 2016 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed.h"
#include "EthernetInterface.h"
#include "TCPSocket.h"
#include "treasure-data-rest.h"
#include "GroveGPS.h"
 
#define BUFF_SIZE   200

GroveGPS gps(D1, D0);
EthernetInterface net;

int main(void){

    int count = 0;

    printf("\r\nTreasure Data REST API  + GPS Demo\n");

    // Connect to Ethernet
    printf("\nConnecting to ethernet...\n");
    int ret = net.connect();
    if (ret != 0) {
        printf("\nConnection error: %d\n", ret);
        return -1;
    }

    printf("Success\n\n");
    printf("MAC: %s\n", net.get_mac_address());
    printf("IP: %s\n", net.get_ip_address());

    // Create Treasure data objects (Network, Database, Table, APIKey)
    TreasureData_RESTAPI* gps_td  = new TreasureData_RESTAPI(&net,"gps_test_michael","GPS", MBED_CONF_APP_API_KEY);

    // Start reading GPS data
    gps.start();
    
    // Get GPS data, send to Treasure Data every 10 seconds
    while(1){
        char lat_buff  [16] = {0};
        char long_buff [16] = {0};
        // Query GPS module
        gps.getLatitude(lat_buff); 
        gps.getLongitude(long_buff); 

        char gps_buff  [BUFF_SIZE] = {0};
        int x = sprintf(gps_buff,"{\"lat\":\"%s\",\"long\":\"%s\"}", lat_buff, long_buff);
        gps_buff[x] = 0;

        // Send data to Treasure data
        printf("\r\n Sending GPS Data: '%s'\r\n",gps_buff);
        gps_td->sendData(gps_buff,strlen(gps_buff));

        wait(10);

    }

    net.disconnect();

}
