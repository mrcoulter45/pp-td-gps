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

GroveGPS gps;
EthernetInterface net;

int main(void){

    int count = 0;

    printf("\r\nTreasure Data REST API Demo\n");

    // Connect to Wifi
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
    TreasureData_RESTAPI* latitude  = new TreasureData_RESTAPI(&net,"iot_test","latitude", MBED_CONF_APP_API_KEY);
    TreasureData_RESTAPI* longitude   = new TreasureData_RESTAPI(&net,"iot_test","longitude",  MBED_CONF_APP_API_KEY);


    // Buffers to create strings in
    char lat_buff  [BUFF_SIZE] = {0};
    char long_buff [BUFF_SIZE] = {0};

    // Start reading GPS data
    gps.start();
    
    // Get device health data, send to Treasure Data every 10 seconds
    while(1){
        gps.getLatitude(lat_buff); 

        // Send data to Treasure data
        printf("\r\n Sending latitude Data: '%s'\r\n",lat_buff);
        latitude->sendData(lat_buff,strlen(lat_buff));

        gps.getLongitude(long_buff); 

        // Send data to Treasure data
        printf("\r\n Sending longitude Data: '%s'\r\n",long_buff);
        longitude->sendData(long_buff,strlen(long_buff));
        wait(10);

    }

    net.disconnect();

}
