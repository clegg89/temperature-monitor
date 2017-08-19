/**
 * @file network-queue.hpp
 *
 * @author C. Smith
 */

#ifndef _NETWORK_QUEUE_HPP_
#define _NETWORK_QUEUE_HPP_

#include <Arduino.h>

namespace app
{

class NetworkQueue
{
  public:
    NetworkQueue() = default;
    virtual ~NetworkQueue() = default;

    virtual bool enqueue(const String& message);
    virtual String dequeue();
};

}

#endif /* _NETWORK_QUEUE_HPP_ */
