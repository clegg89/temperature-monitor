/*
 * @file network-messaging-task.cpp
 *
 * @author C. Smith
 */

#include "network-messaging-task.hpp"

#include <Crypto.h>
#include <AES.h>
#include <CBC.h>
#include <SHA256.h>
#include <ESP8266TrueRandom.h>
#include <cassert>
#include <array>
#include <vector>
#include <algorithm>

#include "security-information.hpp"

namespace app
{

static std::vector<uint8_t> performEncryption(const std::vector<uint8_t>& key,
                                              const std::vector<uint8_t>& iv,
                                              const std::vector<uint8_t>& data);
static std::vector<uint8_t> sign(const std::vector<uint8_t>& key,
                                 const std::vector<uint8_t>& data);
template <typename T>
static String hexify(const T& data);
static std::vector<uint8_t> padData(const std::vector<uint8_t>& data);

NetworkMessagingTask::NetworkMessagingTask(
    const std::shared_ptr<MqttClient>& client,
    const std::shared_ptr<NetworkQueue>& queue,
    const uint32_t timeInterval)
  : Task(timeInterval), m_client(client), m_queue(queue)
{
}

bool NetworkMessagingTask::OnStart()
{
  return true;
}

void NetworkMessagingTask::OnStop()
{
}

void NetworkMessagingTask::OnUpdate(uint32_t deltaTime)
{
  if(m_client->isConnected())
  {
    String msgString = m_queue->dequeue();

    if(msgString != "")
    {
      MqttClient::Message message;
      MqttClient::Error::type rc;

      Serial.print("Received Message: ");
      Serial.println(msgString);

      msgString = encrypt(msgString);

      Serial.print("Encrypted Message: ");
      Serial.println(msgString);

      message.qos = MqttClient::QOS0;
      message.retained = false;
      message.dup = false;
      message.payload = reinterpret_cast<void*>(
                          const_cast<char*>(msgString.c_str()));
      message.payloadLen = msgString.length();

      rc = m_client->publish("monitor", message);
      if(rc != MqttClient::Error::SUCCESS)
      {
        Serial.print("Error sending message: ");
        Serial.println(rc);
      }
    }
  }
}

String NetworkMessagingTask::encrypt(const String& message) const
{
  const SecurityInformation& info = g_securityInformation;
  std::vector<uint8_t> iv(16, 0);
  std::vector<uint8_t> encryptedIv;
  std::vector<uint8_t> cipherText;
  std::vector<uint8_t> signature;
  std::vector<uint8_t> fullMessage;
  std::vector<uint8_t> plainText = padData(std::vector<uint8_t>(message.c_str(), message.c_str() + message.length()));
  String result;

  ESP8266TrueRandom.memfill(reinterpret_cast<char*>(iv.data()), iv.size());

  encryptedIv = performEncryption(
      std::vector<uint8_t>(info.ivKey.begin(), info.ivKey.end()),
      std::vector<uint8_t>(info.staticIv.begin(), info.staticIv.end()),
      iv);
  cipherText = performEncryption(
      std::vector<uint8_t>(info.dataKey.begin(), info.dataKey.end()),
      iv,
      plainText);

  fullMessage.reserve(iv.size() + plainText.size());
  fullMessage = iv;
  fullMessage.insert(fullMessage.end(), plainText.begin(), plainText.end());
  signature = sign(info.hashKey, fullMessage);

  result = hexify(encryptedIv);
  result += ',';
  result += hexify(cipherText);
  result += ',';
  result += hexify(signature);

  return result;
}

static std::vector<uint8_t> performEncryption(const std::vector<uint8_t>& key,
                                              const std::vector<uint8_t>& iv,
                                              const std::vector<uint8_t>& data)
{
  CBC<AES128> cipher;
  std::vector<uint8_t> cipherText(data.size(), 0);;

  cipher.clear();

  assert(cipher.setKey(key.data(), key.size()));
  assert(cipher.setIV(iv.data(), iv.size()));
  assert(data.size() % 16 == 0);

  cipher.encrypt(cipherText.data(), data.data(), data.size());

  return cipherText;
}

static std::vector<uint8_t> sign(const std::vector<uint8_t>& key,
                                 const std::vector<uint8_t>& data)
{
  SHA256 hmac;
  std::vector<uint8_t> signature;

  signature.resize(hmac.hashSize());
  hmac.resetHMAC(key.data(), key.size());
  hmac.update(data.data(), data.size());
  hmac.finalizeHMAC(key.data(), key.size(), signature.data(), hmac.hashSize());

  return signature;
}

template <typename T>
static String hexify(const T& data)
{
  const char hexLookup[] = "0123456789ABCDEF";
  String result = "";

  for(auto x : data)
  {
    result += hexLookup[(x >> 4) & 0x0F];
    result += hexLookup[(x & 0x0F)];
  }

  return result;
}

static std::vector<uint8_t> padData(const std::vector<uint8_t>& data)
{
  std::vector<uint8_t> padded(data);

  while(padded.size() % 16 != 0)
  {
    padded.push_back(static_cast<uint8_t>(' '));
  }

  return padded;
}

}
