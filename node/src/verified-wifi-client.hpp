/**
 * @file verified-wifi-client.hpp
 *
 * @author C. Smith
 */

#ifndef _VERIFIED_WIFI_CLIENT_HPP_
#define _VERIFIED_WIFI_CLIENT_HPP_

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <vector>

/**
 * A wrapper around WifiClientSecure which verifies
 * the Certificate of the server
 */
class VerifiedWifiClient : public WiFiClientSecure
{
  public:
    VerifiedWifiClient(const std::vector<uint8_t> rootCaCertificate);
    virtual ~VerifiedWifiClient() = default;

    /* WiFiClientSecure requires domain name for verification,
     * event though this is not strictly required. For now
     * only verify connections via domain names. In the future
     * can extend support if necessary.
     */
    int connect(const char * name, uint16_t port) override;
};

#endif /* _VERIFIED_WIFI_CLIENT_HPP_ */
