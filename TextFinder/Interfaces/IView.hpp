#ifndef IVIEW_HPP
#define IVIEW_HPP

#include <QString>

#include "Enums/Enums.hpp"

namespace interfaces {
template <class Data>
    class IView {
        public:
            virtual ~IView() = default;
            virtual void updateProgressBar(int count) noexcept = 0;
            virtual void updateTextInPlainTextEditField(const QString data) noexcept = 0;
            virtual enums::Status getStatus() noexcept = 0;
            virtual Data getData() noexcept = 0;
            virtual void resetSettings() noexcept = 0;
    };
}

#endif // IVIEW_HPP
