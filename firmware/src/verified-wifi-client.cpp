/*
 * @file verified-wifi-client.cpp
 *
 * @author C. Smith
 */

#include "verified-wifi-client.hpp"

VerifiedWifiClient::VerifiedWifiClient(const std::vector<uint8_t> rootCaCertificate)
  : WiFiClientSecure()
{
  this->setCACert(rootCaCertificate.data(), rootCaCertificate.size());
}

int VerifiedWifiClient::connect(const char * name, uint16_t port)
{
  if(!WiFiClientSecure::connect(name, port))
  {
    return 0;
  }

  if(!verifyCertChain(name))
  {
    return 0;
  }

  return 1;
}
