/*
 * @file network-queue.cpp
 *
 * @author C. Smith
 */

#include "network-queue.hpp"

namespace app
{

bool NetworkQueue::enqueue(const String& message)
{
  if(m_queue.size() == MAX_QUEUE_SIZE)
  {
    return false;
  }

  m_queue.push(message);

  return true;
}

String NetworkQueue::dequeue()
{
  if(m_queue.empty())
  {
    return "";
  }
  else
  {
    String result = m_queue.front();

    m_queue.pop();

    return result;
  }
}

bool NetworkQueue::hasMessage()
{
  return (!m_queue.empty());
}

}
