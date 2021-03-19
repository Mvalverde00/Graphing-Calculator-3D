#include "threadsafe_queue.h"

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
  _lock.lock();
   _notEmpty.wait(_lock, [&] { return !_data.empty(); });
  T returnVal = _data.pop_front();
  _lock.unlock();

  return returnVal;
}
