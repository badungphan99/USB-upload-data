//
// Created by dungpb on 21/08/2020.
//

#ifndef AUTOUPLOADDATA_BLOCKINGQUEUE_H
#define AUTOUPLOADDATA_BLOCKINGQUEUE_H

#include <mutex>
#include <queue>

template <typename T>
class BlockingQueue {
private:
    std::mutex mutex_;
    std::queue<T> queue_;
public:
    T pop() {
        this->mutex_.lock();
        T value;
        if( !this->queue_.empty() )
        {
            value = this->queue_.front();
            this->queue_.pop();
        }
        this->mutex_.unlock();
        return value;
    }

    void push(T value) {
        this->mutex_.lock();
        this->queue_.push(value);
        this->mutex_.unlock();
    }

    bool empty() {
        this->mutex_.lock();
        bool check = this->queue_.empty();
        this->mutex_.unlock();
        return check;
    }

    bool isExist(T value) {
        this->mutex_.lock();
        bool flag = false;
        std::queue<T> temp;
        T tmpValue;
        while (!this->queue_.empty()){
            tmpValue = this->queue_.front();
            this->queue_.pop();
            if (value == tmpValue){
                flag = true;
            }
            temp.push(tmpValue);
        }
        this->queue_ = temp;
        return flag;
    }
};

#endif //AUTOUPLOADDATA_BLOCKINGQUEUE_H
