#ifndef HTMLVERTEXHANDLER_HPP
#define HTMLVERTEXHANDLER_HPP

#include <list>
#include <QString>

#include "DataStructures/Vertex.hpp"

namespace utils {
    class HtmlVertexHandler {
        public:
            HtmlVertexHandler();
            ~HtmlVertexHandler() = default;

            void setStartUrlAndTextToFind(const QString startUrl, const QString textToFind) noexcept;
            void handleVertex(std::shared_ptr<datastructures::Vertex> &vertex, QString &source);

        private:
            QString m_TextToFind{};
            QString m_StartUrl{};

            std::list<QString> extractHyperlinks(QString page) noexcept;
            void fixIncorrectUrls(std::shared_ptr<datastructures::Vertex> &urlVertex) noexcept;
            void removeTags(QString &htmlText) noexcept;
            int findText(QString &data) noexcept;
    };
}
#endif // HTMLVERTEXHANDLER_HPP
