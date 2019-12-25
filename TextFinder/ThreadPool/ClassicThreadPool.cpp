#include "ClassicThreadPool.hpp"

using namespace threadpool;

ClassicThreadPool::ClassicThreadPool() {}

ClassicThreadPool::~ClassicThreadPool() {
    stop();
}

void ClassicThreadPool::addTask(interfaces::Task task) noexcept {
    {
        std::unique_lock<std::mutex> lock{m_Mutex};
        m_Tasks.emplace(std::move(task));
    }
    m_Cv.notify_one();
}

size_t ClassicThreadPool::getCountOfActiveTasks() noexcept {
    return m_Tasks.size();
}

void ClassicThreadPool::setThreadQuantity(const int amount) noexcept {
    m_IsStopping = false;
    start(amount);
}

void ClassicThreadPool::stopAllThreads() noexcept {
    stop();
}

void ClassicThreadPool::start(const int threadsCount) {
    for (int i = 0; i < threadsCount; ++i) {
        m_Threads.emplace_back
        (
        [=]{
                while (true) {
                    interfaces::Task task;
                    {
                        std::unique_lock<std::mutex> lock{m_Mutex};
                        m_Cv.wait(lock, [=]{ return m_IsStopping || !m_Tasks.empty(); });

                        if (m_IsStopping) {
                            break;
                        }
                        task = std::move(m_Tasks.front());
                        m_Tasks.pop();
                    }

                    task();
                }
            }
        );
    }
}

void ClassicThreadPool::stop() {
    {
        std::unique_lock<std::mutex> lock{m_Mutex};
        m_IsStopping = true;
    }

    m_Cv.notify_all();
    for (auto& thread : m_Threads) {
        thread.detach();
    }
    m_Threads.clear();

    std::queue<interfaces::Task> empty;
    std::swap(m_Tasks, empty);
}
