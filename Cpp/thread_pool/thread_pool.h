#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <future>
#include <queue>

class ThreadPool {
public:
    explicit ThreadPool(size_t size)
            : stop_(false) {
        for (size_t i = 0; i < size; i++) {
            workers_.emplace_back(
                    [this] {
                        for (;;) {
                            std::function<void()> task;
                            {
                                std::unique_lock<std::mutex> lock(this->queue_mutex_);

                                this->condition_.wait(lock, [this] { return this->stop_ || !this->tasks_.empty(); });
                                if (this->stop_ && this->tasks_.empty()) {
                                    return;
                                }

                                task = std::move(this->tasks_.front());
                                this->tasks_.pop();
                            }
                            task();
                        }
                    }
            );
        }
    }

    ThreadPool(const ThreadPool &) = delete;

    ThreadPool(ThreadPool &&) = delete;

    ThreadPool &operator=(const ThreadPool &) = delete;

    ThreadPool &operator=(ThreadPool &&) = delete;

    // the destructor joins all threads
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            stop_ = true;
        }
        condition_.notify_all();
        for (auto &worker : workers_) {
            worker.join();
        }
    }

    // add new task to the pool
    template<class F, class... Args>
    auto Enqueue(F &&f, Args &&...args) -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> result = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);

            // don't allow enqueueing after stopping the pool
            if (stop_) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }

            tasks_.emplace([task]() { (*task)(); });
        }
        condition_.notify_one();
        return result;
    };

private:
    // need to keep track of threads so we can join them
    std::vector<std::thread> workers_;
    // the task queue
    std::queue<std::function<void()>> tasks_;
    // synchronization
    std::mutex queue_mutex_;
    std::condition_variable condition_;
    bool stop_;
};

#endif //THREAD_POOL_H
