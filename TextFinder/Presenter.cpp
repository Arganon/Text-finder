#include <iostream>
#include <QRegularExpression>

#include "Presenter.hpp"
#include "ThreadPool/QTThreadPool.hpp"
#include "ThreadPool/ClassicThreadPool.hpp"

Presenter::Presenter(interfaces::IView<datastructures::DataToStartSearching> *view)
    : m_View(view)
    , m_ThreadPool(new threadpool::QTThreadPool) // there is two wariant of threadpool: classic and qt
{}

Presenter::~Presenter() {
    delete m_ThreadPool;
}

void Presenter::update() noexcept {
    m_Status = m_View->getStatus();
    choseAction();
}

void Presenter::choseAction() noexcept {

    switch (m_Status) {
        case enums::Status::INIT:
                if (m_IsInitialized) {
                    stopSearching();
                }
                initializeSearchProcess();
                choseAction();
            break;

        case enums::Status::SEARCHING:
                if (m_IsInitialized) {
                    searchProcessBuilder();
                }
            break;

        case enums::Status::PAUSE:
            break;

        case enums::Status::STOP:
                if (m_IsInitialized) {
                    stopSearching();
                }
            break;

        default: break;
    }
}

void Presenter::initializeSearchProcess() noexcept {
    datastructures::DataToStartSearching data = m_View->getData();

    if (data.m_Url.isEmpty()) {
        m_Status = enums::Status::STOP;
    }
    else {
        m_Status = enums::Status::SEARCHING;
        m_IsInitialized = true;

        fixUrl(data.m_Url);

        m_MaxUrlScanCount = data.m_UrlQuantity;
        m_Model.setData(data);
        m_WebPageUrlVertices.emplace(std::make_shared<datastructures::Vertex>(data.m_Url));
        m_ThreadPool->setThreadQuantity(data.m_ThreadQuantity);
    }
}

void Presenter::fixUrl(QString &url) noexcept {
    if (!url.isEmpty() && url.back() == '/') {
        url.remove(QRegularExpression("\\/+$"));
    }
}

void Presenter::searchProcessBuilder() noexcept {
    if (auto vertex = getAndManageVertexFromQueue()) {

        m_ThreadPool->addTask([&, _vertex = vertex]() {
                m_Model.processRequestAndFillVertex(_vertex);
                updateVertexQueue(_vertex);
                updateView(_vertex);
                updateStatus();
                choseAction();
            }
        );
    }
}

std::shared_ptr<datastructures::Vertex> Presenter::getAndManageVertexFromQueue() noexcept {
    std::shared_ptr<datastructures::Vertex> vertex;
    m_RecurciveMutex.lock();

    if (!m_WebPageUrlVertices.empty()) {
        vertex = m_WebPageUrlVertices.front();
        m_WebPageUrlVertices.pop();

        fixUrl(vertex->m_Url);
        m_VisitedUrls.insert(vertex->m_Url);

    }
    m_RecurciveMutex.unlock();

    return vertex;
}

void Presenter::updateVertexQueue(std::shared_ptr<datastructures::Vertex> vertex) noexcept {
    if (vertex) {
        m_RecurciveMutex.lock();

        for (auto& url : vertex->m_Children) {
            fixUrl(url);

            if (m_VisitedUrls.insert(url).second == true) {
                m_WebPageUrlVertices.push(std::make_shared<datastructures::Vertex>(url));
            }
        }
        m_RecurciveMutex.unlock();
    }
}

void Presenter::updateStatus() noexcept {
    m_RecurciveMutex.lock();
    if (enums::Status::STOP != m_Status && enums::Status::PAUSE != m_Status) {
        if (m_WebPageUrlVertices.empty() && m_ThreadPool->getCountOfActiveTasks() == 0) {
            m_Status = enums::Status::STOP;
        } else if (m_WebPageUrlVertices.empty() && m_ThreadPool->getCountOfActiveTasks() > 0) {
            m_Status = enums::Status::PAUSE;
        } else if (m_UrlCounter >= m_MaxUrlScanCount) {
            m_Status = enums::Status::STOP;
        }
    }
    m_RecurciveMutex.unlock();
}

void Presenter::stopSearching() noexcept {
    m_IsInitialized = false;
    m_ThreadPool->stopAllThreads();
    std::queue<std::shared_ptr<datastructures::Vertex>> empty;
    std::swap(m_WebPageUrlVertices, empty);

    m_View->updateTextInPlainTextEditField("\nSummary text found " + QString::number(m_SummaryHitsCount) + " times.");
    if (m_UrlCounter < m_MaxUrlScanCount) {
        m_View->updateProgressBar(m_MaxUrlScanCount);
    }

    m_Status = enums::Status::INIT;
    m_VisitedUrls.clear();
    m_SummaryHitsCount = 0;
    m_UrlCounter = 0;
    m_MaxUrlScanCount = 0;
}

void Presenter::updateView(std::shared_ptr<datastructures::Vertex> vertex) noexcept {
    if (m_IsInitialized) {
        m_SummaryHitsCount += vertex->m_TextHitsCountOnThisVertexUrl;
        m_View->updateTextInPlainTextEditField("Text found " + QString::number(vertex->m_TextHitsCountOnThisVertexUrl) + " times by URL: " + vertex->m_Url);
        ++m_UrlCounter;
        m_View->updateProgressBar(m_UrlCounter.load());
    }
}
