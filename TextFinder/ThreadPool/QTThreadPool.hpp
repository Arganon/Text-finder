#ifndef QTTHREADPOOL_HPP
#define QTTHREADPOOL_HPP

#include <QApplication>
#include <QRunnable>

#include "Interfaces/IThreadPool.hpp"
#include "DataStructures/Vertex.hpp"


namespace threadpool {
    class TaskHandler : public QRunnable {
        private:
            interfaces::Task m_Task;

        public:
            explicit TaskHandler(interfaces::Task task);
            void run() override;
    };

    class QTThreadPool final : public interfaces::IThreadPool {
        public:
            QTThreadPool();

            virtual ~QTThreadPool() override;
            virtual void addTask(interfaces::Task task) noexcept override;
            virtual void setThreadQuantity(const int amount) noexcept override;
            virtual size_t getCountOfActiveTasks() noexcept override;
            virtual void stopAllThreads() noexcept override;
    };
}


#endif // QTTHREADPOOL_HPP
