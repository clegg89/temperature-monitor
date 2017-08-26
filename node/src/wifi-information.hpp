/**
 * @file wifi-information.hpp
 *
 * @author C. Smith
 */

#ifndef _WIFI_INFORMATION_HPP_
#define _WIFI_INFORMATION_HPP_

#include <Arduino.h>
#include <vector>

namespace app
{

struct WifiInformation
{
  const String ssid;
  const String password;
};

extern const std::vector<app::WifiInformation> g_wifiNetworks;

}

#endif /* _WIFI_INFORMATION_HPP_ */
