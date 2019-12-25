#ifndef HTMLTEXTACQUISITION_HPP
#define HTMLTEXTACQUISITION_HPP

#include <QString>

namespace utils {
    class HtmlTextAcquisition {
        public:
            HtmlTextAcquisition();
            ~HtmlTextAcquisition() = default;

            QString getTextFromSource(const QString url) noexcept;

        private:
            static size_t writeContent(char *data, size_t size, size_t nmemb, QString &buffer) noexcept;
    };
}
#endif // HTMLTEXTACQUISITION_HPP
