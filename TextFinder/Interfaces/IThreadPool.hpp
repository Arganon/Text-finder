#ifndef ITHREADPOOL_HPP
#define ITHREADPOOL_HPP

#include <QString>

namespace interfaces {
    using Task = std::function<void()>;
    class IThreadPool {
        public:
            virtual ~IThreadPool() = default;
            virtual void addTask(Task task) noexcept = 0;
            virtual void setThreadQuantity(const int amount) noexcept = 0;
            virtual size_t getCountOfActiveTasks() noexcept = 0;
            virtual void stopAllThreads() noexcept = 0;
    };
}

#endif // ITHREADPOOL_HPP
