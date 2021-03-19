#ifndef __THREADSAFE_QUEUE_H__
#define __THREADSAFE_QUEUE_H__

#include <deque>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadsafeQueue {

  std::deque<T> _data;
  std::mutex _lock;
  std::condition_variable _notEmpty;
  size_t _size;


  public:
    ThreadsafeQueue();

    void enqueue(T value);
    T dequeue();
};

#endif