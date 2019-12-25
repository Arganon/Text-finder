#ifndef MODEL_HPP
#define MODEL_HPP

#include <memory>

#include "Utils/HtmlVertexHandler.hpp"
#include "Utils/HtmlTextAcquisition.hpp"
#include "DataStructures/DataToStartSearching.hpp"

namespace utils {
    class HtmlVertexHandler;
    class HtmlTextAcquisition;
}

namespace datastructures {
    struct Vertex;
}

class Model {
    public:
        Model();
        void setData(datastructures::DataToStartSearching &data) noexcept;
        void processRequestAndFillVertex(std::shared_ptr<datastructures::Vertex> vertex) noexcept;

    private:
        utils::HtmlVertexHandler m_HtmlVertexHandler;
        utils::HtmlTextAcquisition m_HtmlTextAcquisition;
};

#endif // MODEL_HPP
