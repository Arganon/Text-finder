#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <list>
#include <QString>

namespace datastructures {
    struct Vertex {
        QString m_Url {};
        std::list<QString> m_Children {};
        int m_TextHitsCountOnThisVertexUrl {0};
        explicit Vertex(QString url) : m_Url(url) {}
    };
}

#endif // VERTEX_HPP
