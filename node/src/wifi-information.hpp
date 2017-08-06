/**
 * @file wifi-information.hpp
 *
 * @author C. Smith
 */

#ifndef _WIFI_INFORMATION_HPP_
#define _WIFI_INFORMATION_HPP_

#include <Arduino.h>

class WifiInformation
{
  public:

    static const WifiInformation& instance()
    {
      static WifiInformation singleton;
      return singleton;
    }

    String ssid() const;
    String password() const;

  private:

    WifiInformation() = default;
    WifiInformation(const WifiInformation&) = delete;
    WifiInformation& operator=(const WifiInformation&) = delete;
};

#endif /* _WIFI_INFORMATION_HPP_ */
