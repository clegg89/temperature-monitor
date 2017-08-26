/**
 * @file security-information.hpp
 *
 * @author C. Smith
 */

#ifndef _SECURITY_INFORMATION_HPP_
#define _SECURITY_INFORMATION_HPP_

#include <Arduino.h>
#include <array>
#include <vector>

namespace app
{

struct SecurityInformation
{
  const std::array<uint8_t,16> dataKey;
  const std::array<uint8_t,16> ivKey;
  const std::array<uint8_t,16> staticIv;
  const std::vector<uint8_t> hashKey;
};

extern const SecurityInformation g_securityInformation;

}

#endif /* _SECURITY_INFORMATION_HPP_ */
