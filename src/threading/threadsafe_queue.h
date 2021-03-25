#ifndef __THREADSAFE_QUEUE_H__
#define __THREADSAFE_QUEUE_H__

#include <deque>
#include <mutex>
#include <condition_variable>

/*
 * A generic threadsafe queue, supporting enqueue and dequeue operations from multiple
 * producer/consumer threads.  Some methods are not threadsafe, since in certain 
 * circumstances it would be unnecessary and slow.  Such methods are prefixed with 'unsafe'.
 */
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
    bool unsafeEmpty();
};


template <typename T>
ThreadsafeQueue<T>::ThreadsafeQueue() {
}

template <typename T>
void ThreadsafeQueue<T>::enqueue(T value) {
  _lock.lock();
  _data.push_back(value);
  _lock.unlock();

  _notEmpty.notify_all();
}

template <typename T>
T ThreadsafeQueue<T>::dequeue() {
  std::unique_lock<std::mutex> lock(_lock);

  _notEmpty.wait(lock, [&] { return !_data.empty(); });
  T returnVal = _data.front();
  _data.pop_front();

  return returnVal;
}

template <typename T>
bool ThreadsafeQueue<T>::unsafeEmpty() {
  return _data.empty();
}
#endif