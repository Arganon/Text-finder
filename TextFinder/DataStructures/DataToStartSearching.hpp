#ifndef DATATOSTARTSEARCHING_HPP
#define DATATOSTARTSEARCHING_HPP

#include <QString>

namespace datastructures {
    struct DataToStartSearching {
        QString m_Url {};
        QString m_TextToFind {};
        int m_ThreadQuantity {0};
        int m_UrlQuantity {0};
    };
}

#endif // DATATOSTARTSEARCHING_HPP
