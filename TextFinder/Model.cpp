#include "Model.hpp"

Model::Model() {}

void Model::setData(datastructures::DataToStartSearching &data) noexcept {
    m_HtmlVertexHandler.setStartUrlAndTextToFind(data.m_Url, data.m_TextToFind);
}

void Model::processRequestAndFillVertex(std::shared_ptr<datastructures::Vertex> vertex) noexcept {
    auto htmlContent = m_HtmlTextAcquisition.getTextFromSource(vertex->m_Url);
    m_HtmlVertexHandler.handleVertex(vertex, htmlContent);
}
