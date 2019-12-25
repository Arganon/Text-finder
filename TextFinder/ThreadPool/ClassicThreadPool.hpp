#ifndef CLASSICTHREADPOOL_HPP
#define CLASSICTHREADPOOL_HPP

#include <queue>
#include <mutex>
#include <vector>
#include <thread>
#include <condition_variable>

#include "Interfaces/IThreadPool.hpp"

namespace threadpool {
    class ClassicThreadPool final : public interfaces::IThreadPool {
        private:
            std::vector<std::thread> m_Threads;
            std::queue<interfaces::Task> m_Tasks;
            std::condition_variable m_Cv;
            std::mutex m_Mutex;
            bool m_IsStopping;

            void start(const int threadsCount);

            void stop();
    public:
        ClassicThreadPool();

        virtual ~ClassicThreadPool() override;
        virtual void addTask(interfaces::Task task) noexcept override;
        virtual void setThreadQuantity(const int amount) noexcept override;
        virtual size_t getCountOfActiveTasks() noexcept override;
        virtual void stopAllThreads() noexcept override;
    };
}

#endif // CLASSICTHREADPOOL_HPP
