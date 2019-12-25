#include "ThreadPool/QTThreadPool.hpp"

using namespace threadpool;

#include <QThreadPool>

QTThreadPool::QTThreadPool() {}

QTThreadPool::~QTThreadPool() {
    stopAllThreads();
}

void QTThreadPool::addTask(interfaces::Task task) noexcept {
    QThreadPool::globalInstance()->start(new TaskHandler(std::move(task)));
}

size_t QTThreadPool::getCountOfActiveTasks() noexcept {
    return QThreadPool::globalInstance()->stackSize();
}

void QTThreadPool::setThreadQuantity(const int amount) noexcept {
    QThreadPool::globalInstance()->setMaxThreadCount(amount);
}

void QTThreadPool::stopAllThreads() noexcept {
    QThreadPool::globalInstance()->waitForDone(400);
    QThreadPool::globalInstance()->setMaxThreadCount(0);
}


TaskHandler::TaskHandler(interfaces::Task task) : m_Task(std::move(task)) {}

void TaskHandler::run() {
    m_Task();
}
