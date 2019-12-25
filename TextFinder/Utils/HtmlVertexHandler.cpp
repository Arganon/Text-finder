#include <regex>
#include <string>
#include <QDebug>
#include <QRegExp>
#include <iostream>
#include <QRegularExpression>

#include "HtmlVertexHandler.hpp"

using namespace utils;

HtmlVertexHandler::HtmlVertexHandler() {}

void HtmlVertexHandler::setStartUrlAndTextToFind(const QString startUrl, const QString textToFind) noexcept {
    m_StartUrl = startUrl;
    m_TextToFind = textToFind;
}

void HtmlVertexHandler::handleVertex(std::shared_ptr<datastructures::Vertex> &vertex, QString &source) {
    vertex->m_Children = extractHyperlinks(source);
    fixIncorrectUrls(vertex);
    removeTags(source);
    vertex->m_TextHitsCountOnThisVertexUrl = findText(source);
}

std::list<QString> HtmlVertexHandler::extractHyperlinks(QString page) noexcept {
      static QRegularExpression qrx("<a\\s*href\\s*=\\s*\"\\s*(.*?)\"");
      QRegularExpressionMatchIterator i = qrx.globalMatch(page);
      std::list<QString> result;

      while (i.hasNext()) {
          QRegularExpressionMatch match = i.next();
          result.push_back(match.captured(1));
      }
      return result;
}

void HtmlVertexHandler::fixIncorrectUrls(std::shared_ptr<datastructures::Vertex> &urlVertex) noexcept {
    QRegExp qrx("/(\\w.*)");

    for (auto it = urlVertex->m_Children.begin();  it != urlVertex->m_Children.end(); ) {
        if ( it->contains(m_StartUrl, Qt::CaseInsensitive)) {
            ++it;
        }
        else if ( it->contains("www", Qt::CaseInsensitive)
                  || it->contains("http", Qt::CaseInsensitive)
                  || it->isEmpty())
        {
            it = urlVertex->m_Children.erase(it);
            continue;
        }
        else {
            int pos = 0;
            if ((pos = qrx.indexIn(*it, pos)) != -1)  {
                *it = m_StartUrl + *it;
            }
            ++it;
        }
    }
}

void HtmlVertexHandler::removeTags(QString &htmlText) noexcept {
    htmlText.remove(QRegExp("<[^>]*>"));
}

int HtmlVertexHandler::findText(QString &data) noexcept {
    return data.count(m_TextToFind, Qt::CaseInsensitive);
}
