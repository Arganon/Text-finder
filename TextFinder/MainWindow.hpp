#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <map>
#include <QMainWindow>

#include "Enums/Enums.hpp"
#include "Interfaces/IView.hpp"
#include "Interfaces/IPresenter.hpp"
#include "DataStructures/DataToStartSearching.hpp"

#define LINE_TWO 2
#define LINE_THREE 3
#define LINE_FOUR 4
#define LINE_FIVE 5

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLabel;
class QLineEdit;
class QPushButton;
class QProgressBar;
class QPlainTextEdit;

namespace widgetPositionConstants {
    constexpr int m_Margin {42/2};
    constexpr int m_MarginBtwnThreeComponents {42 + 42/2};
    constexpr int m_MainWindWidth {42*15};
    constexpr int m_MainWindHight {42*10};
    constexpr int m_MinDistncBtwnWidgets {42};
    constexpr int m_ButtonWidth {42*2+42/2};
    constexpr int m_ButtonHight {42-10};
    constexpr int m_LableWidth {42*2};
    constexpr int m_LableHight {42-10};

    constexpr int distanceFromTopBound = m_Margin + m_ButtonHight + m_MinDistncBtwnWidgets;
    constexpr int distanceFromLeftBoundForLineEdit = m_Margin + m_LableWidth;

    const std::map<QString, QPoint> m_ValToCalculateWidgPos {
        {"m_ButtonStop", {m_ButtonWidth + m_Margin, m_Margin} },
        {"m_ButtonStart", {m_ButtonWidth + m_Margin, m_Margin + m_MinDistncBtwnWidgets} },
        {"m_ButtonPause", {m_ButtonWidth + m_Margin, m_Margin + m_MinDistncBtwnWidgets*LINE_TWO} },
        {"m_ButtonContinue", {m_ButtonWidth + m_Margin, m_Margin + m_MinDistncBtwnWidgets*LINE_THREE} },
        {"m_LabelUrl", {m_Margin, m_Margin} },
        {"m_LabelTextToFind", {m_Margin, m_Margin + m_MinDistncBtwnWidgets} },
        {"m_LabelThreadQuantity", {m_Margin, m_Margin + m_MinDistncBtwnWidgets*LINE_TWO} },
        {"m_LabelUrlQuantityToFindText", {m_Margin, m_Margin + m_MinDistncBtwnWidgets*LINE_THREE} },
        {"m_LineEditUrl", {distanceFromLeftBoundForLineEdit, m_Margin} },
        {"m_LineEditTextToFind", {distanceFromLeftBoundForLineEdit, m_Margin + m_MinDistncBtwnWidgets} },
        {"m_LineEditThreadQuantity", {distanceFromLeftBoundForLineEdit, m_Margin + m_MinDistncBtwnWidgets*LINE_TWO} },
        {"m_LineEditUrlQuantityToFindText", {distanceFromLeftBoundForLineEdit, m_Margin + m_MinDistncBtwnWidgets*LINE_THREE} },
        {"m_ProgressBar", {m_Margin, m_Margin + m_MinDistncBtwnWidgets*LINE_FOUR} },
        {"m_PlainTextEdit", {m_Margin, m_Margin + m_MinDistncBtwnWidgets*LINE_FIVE} }
    };
}

class MainWindow : public QMainWindow, public interfaces::IView<datastructures::DataToStartSearching> {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        virtual ~MainWindow() override;

        MainWindow(const MainWindow &mw) = delete;
        MainWindow(MainWindow &&mw) = delete;
        MainWindow& operator=(const MainWindow &mw) = delete;
        MainWindow& operator=(MainWindow &&mw) = delete;

        virtual void updateProgressBar(int count) noexcept override final;
        virtual void updateTextInPlainTextEditField(const QString data) noexcept override final;
        virtual enums::Status getStatus() noexcept override final;
        virtual datastructures::DataToStartSearching getData() noexcept override final;
        virtual void resetSettings() noexcept override final;

        void calculatePlainTextEditFieldSize(const QRect& geometry) noexcept;

    signals:
        void signalProgress(int);
        void signalAppendText(const QString);

    private slots:
        void on_Button_Start_clicked() noexcept;
        void on_Button_Stop_clicked() noexcept;
        void on_Button_Pause_clicked() noexcept;
        void on_Button_Continue_clicked() noexcept;

    private:
        std::unique_ptr<interfaces::IPresenter> m_Presenter;

        enums::Status m_Status {enums::Status::INIT};

        QPushButton * m_ButtonStop;
        QPushButton *m_ButtonStart;
        QPushButton *m_ButtonPause;
        QPushButton *m_ButtonContinue;

        QLabel *m_LabelUrl;
        QLabel *m_LabelTextToFind;
        QLabel *m_LabelThreadQuantity;
        QLabel *m_LabelUrlQuantityToFindText;

        QLineEdit *m_LineEditUrl;
        QLineEdit *m_LineEditTextToFind;
        QLineEdit *m_LineEditThreadQuantity;
        QLineEdit *m_LineEditUrlQuantityToFindText;

        QProgressBar *m_ProgressBar;

        QPlainTextEdit *m_PlainTextEdit;

        void createUserInterfaceComponents() noexcept;
        void initMainWindowSize() noexcept;
        void initButtonObjects() noexcept;
        void initLabelObjects() noexcept;
        void initLineEditObjects() noexcept;
        void initProgressBar() noexcept;
        void initPlainTextEditField() noexcept;

        void setWidgetsPositions() noexcept;
        void setButtonsPositions(const QRect& geometry) noexcept;
        void setLabelPositions() noexcept;
        void setLineEditPositions() noexcept;
        void setProgressBarPosition(const QRect& geometry) noexcept;
        void setPlainTextEdit() noexcept;

        void setWidgetPosition(QWidget& obj, const QPoint &point) noexcept;

        void calculateLineEditWidth(const QRect &geometry) noexcept;
        virtual void resizeEvent(QResizeEvent *event) override;
};

#endif // MAINWINDOW_HPP
