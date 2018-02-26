#ifndef UTIL_QUEUE_H_
#define UTIL_QUEUE_H_

#include <queue>

#include "unise/boost_wrap.h"

namespace unise
{

/// @brief Thread-safe queue template with blocking and non-blocking pop()
/// interface, and open/close control.
/// @note This queue is not an abstract data type. It is more like an object
/// pipe between threads with pipe close to notify subsribers to stop
/// running.
template<typename T>
class Queue
{
public:
    typedef T   value_type;
    Queue(): _status(kOpen) {
    }

    /// @brief Push an item in queue
    /// @param t
    /// @return
    bool push(const T& t) {
        if (kOpen == _status) {
            boost::mutex::scoped_lock lock(_mutex);
            _queue.push(t);
            lock.unlock();
            _cond.notify_one();
            return true;
        } else {
            return false;
        }
    }

    /// @brief is queue empty?
    bool empty() const {
        boost::mutex::scoped_lock lock(_mutex);
        return _queue.empty();
    }

    /// @brief Thread-safe and blocking pop
    /// @param[out] t : Poped item
    /// @return
    bool pop(T& t) {
        boost::mutex::scoped_lock lock(_mutex);
        while (kOpen == _status && _queue.empty()) {
            _cond.wait(lock);
        }
        if (kClosed == _status || _queue.empty()) {
            return false;
        } else {
            t = _queue.front();
            _queue.pop();
            return true;
        }
    }

    /// @brief Thread-safe and non-blocking pop
    /// @param[out] t : Poped item
    /// @return
    bool try_pop(T& t) {
        boost::mutex::scoped_lock lock(_mutex);
        if (kClosed == _status || _queue.empty()) {
            return false;
        } else {
            t = _queue.front();
            _queue.pop();
            return true;
        }
    }

    /// @brief Queue size
    /// @return
    size_t size() const {
        boost::mutex::scoped_lock lock(_mutex);
        return _queue.size();
    }

    /// @brief reopen the queue
    void open() {
        boost::mutex::scoped_lock lock(_mutex);
        _status = kOpen;
    }

    /// @brief close the queue
    /// @param[in] immediately :
    void close(bool immediately = false) {
        boost::mutex::scoped_lock lock(_mutex);
        _status = immediately ? kClosed : kClosing;
        _cond.notify_all();
    }

private:
    enum Status {
        kOpen,      ///< The queue is opened
        kClosing,   ///< The queue is closing
        kClosed,    ///< The queue is closed
    };
    Status                      _status;    ///< Queus status
    mutable boost::mutex        _mutex;     ///< Lock
    boost::condition_variable   _cond;      ///< Condition variable
    std::queue<T>               _queue;     ///< Container
};

}
#endif
