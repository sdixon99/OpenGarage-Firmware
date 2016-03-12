/* OpenGarage Firmware
 * Copyright (C) 2015 by OpenGarageDoor.com
 *
 * ESPConnect functions
 * Mar 2016 @ OpenGarageDoor.com
 *
 * This file is part of the OpenGarage library
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
 
#include "espconnect.h"
#include "html_ap_home.h"
#include "html_sta_options.h"
#include "html_sta_home.h"
#include "html_sta_update.h"
#include "html_sta_logs.h"

// R is a C++ literal for raw string
const char html_mobile_header[] PROGMEM = R"(<head><meta name='viewport' content='width=device-width,initial-scale=1.0,minimum-scale=1.0,user-scalable=no'><title>OpenGarage</title><style>body{font-family:'helvetica';}</style></head>)";

const char html_jquery_header[] PROGMEM = "<head><title>OpenGarage</title><meta name='viewport' content='width=device-width, initial-scale=1'><link rel='stylesheet' href='http://code.jquery.com/mobile/1.3.1/jquery.mobile-1.3.1.min.css' type='text/css'><script src='http://code.jquery.com/jquery-1.9.1.min.js' type='text/javascript'></script><script src='http://code.jquery.com/mobile/1.3.1/jquery.mobile-1.3.1.min.js' type='text/javascript'></script></head>";

const char html_ap_redirect[] PROGMEM = "<h3>WiFi config saved. Now switching to station mode.</h3>";

String scan_network() {
  DEBUG_PRINTLN(F("scan network"));
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  byte n = WiFi.scanNetworks();
  if (n>32) n = 32; // limit to 32 ssids max
  String ssids = "{\"ssids\":["; 
  for(int i=0;i<n;i++) {
    ssids += "\"";
    ssids += WiFi.SSID(i);
    ssids += "\"";
    if(i<n-1) ssids += ",\r\n";
  }
  ssids += "]}";
  return ssids;
}

void start_network_ap(const char *ssid, const char *pass) {
  if(!ssid) return;
  DEBUG_PRINTLN(F("AP mode"));
  if(pass)
    WiFi.softAP(ssid, pass);
  else
    WiFi.softAP(ssid);
  WiFi.mode(WIFI_AP_STA); // start in AP_STA mode
  WiFi.disconnect();  // disconnect from router
}

void start_network_sta_with_ap(const char *ssid, const char *pass) {
  if(!ssid || !pass) return;
  DEBUG_PRINTLN(F("STA mode with AP"));
  WiFi.begin(ssid, pass);
}

void start_network_sta(const char *ssid, const char *pass) {
  if(!ssid || !pass) return;
  DEBUG_PRINTLN(F("STA mode"));
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
}

