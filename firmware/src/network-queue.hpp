/**
 * @file network-queue.hpp
 *
 * @author C. Smith
 */

#ifndef _NETWORK_QUEUE_HPP_
#define _NETWORK_QUEUE_HPP_

#include <Arduino.h>
#include <queue>

namespace app
{

class NetworkQueue
{
  public:

    NetworkQueue() = default;
    virtual ~NetworkQueue() = default;

    virtual bool enqueue(const String& message);
    virtual String dequeue();
    virtual bool hasMessage();

  private:

    static const std::size_t MAX_QUEUE_SIZE = 20;

    std::queue<String> m_queue;
};

}

#endif /* _NETWORK_QUEUE_HPP_ */
