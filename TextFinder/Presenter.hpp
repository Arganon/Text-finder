#ifndef PRESENTER_HPP
#define PRESENTER_HPP

#include <set>
#include <memory>
#include <queue>
#include <mutex>

#include "Model.hpp"
#include "Enums/Enums.hpp"
#include "Interfaces/IView.hpp"
#include "Interfaces/IPresenter.hpp"
#include "Interfaces/IThreadPool.hpp"
#include "DataStructures/DataToStartSearching.hpp"

class Presenter : public interfaces::IPresenter {
    public:
        Presenter(interfaces::IView<datastructures::DataToStartSearching> *view);
        virtual ~Presenter() override;
        virtual void update() noexcept override final;

    private:
        Model m_Model;
        std::atomic<enums::Status> m_Status {enums::Status::INIT};
        std::set<QString> m_VisitedUrls {};
        int m_MaxUrlScanCount {0};
        std::atomic<bool> m_IsInitialized {false};
        std::atomic<int> m_UrlCounter {0};
        std::atomic<int> m_SummaryHitsCount {0};
        std::recursive_mutex m_RecurciveMutex {};

        interfaces::IView<datastructures::DataToStartSearching> *m_View {nullptr};
        interfaces::IThreadPool* m_ThreadPool {nullptr}; // изменить на указатель
        std::queue< std::shared_ptr<datastructures::Vertex> > m_WebPageUrlVertices {};

        void choseAction() noexcept;
        void initializeSearchProcess() noexcept;
        inline void fixUrl(QString &url) noexcept;

        void searchProcessBuilder() noexcept;
        std::shared_ptr<datastructures::Vertex> getAndManageVertexFromQueue() noexcept;

        // there was used bfs graph search, so we use naming like Vertices
        void updateVertexQueue(std::shared_ptr<datastructures::Vertex> vertex) noexcept;
        void updateStatus() noexcept;
        void stopSearching() noexcept;
        void updateView(std::shared_ptr<datastructures::Vertex> vertex) noexcept;

};

#endif // PRESENTER_HPP
