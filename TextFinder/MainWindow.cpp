#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QPlainTextEdit>
#include <utility>
#include <iostream>

#include "Presenter.hpp"
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

using namespace widgetPositionConstants;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_Presenter(std::make_unique<Presenter>(this))
{
    createUserInterfaceComponents();
}

MainWindow::~MainWindow() {

    delete m_ButtonStop;
    delete m_ButtonStart;
    delete m_ButtonPause;
    delete m_ButtonContinue;

    delete m_LabelUrl;
    delete m_LabelTextToFind;
    delete m_LabelThreadQuantity;
    delete m_LabelUrlQuantityToFindText;

    delete m_LineEditUrl;
    delete m_LineEditTextToFind;
    delete m_LineEditThreadQuantity;
    delete m_LineEditUrlQuantityToFindText;

    delete m_ProgressBar;

    delete m_PlainTextEdit;
}

void MainWindow::createUserInterfaceComponents() noexcept {
    initMainWindowSize();
    initButtonObjects();
    initLabelObjects();
    initLineEditObjects();
    initProgressBar();
    initPlainTextEditField();
}

void MainWindow::initMainWindowSize() noexcept {
    this->setMinimumWidth(m_MainWindWidth);
    this->setMinimumHeight(m_MainWindHight);
}

void MainWindow::initButtonObjects() noexcept {
    QSize buttonSize {m_ButtonWidth, m_ButtonHight};

    m_ButtonStop = new QPushButton("&Stop", this);
    m_ButtonStop->setAccessibleName("m_ButtonStop");

    m_ButtonStart = new QPushButton("&Start", this);
    m_ButtonStart->setAccessibleName("m_ButtonStart");

    m_ButtonPause = new QPushButton("&Pause", this);
    m_ButtonPause->setAccessibleName("m_ButtonPause");

    m_ButtonContinue = new QPushButton("&Continue", this);
    m_ButtonContinue->setAccessibleName("m_ButtonContinue");

    m_ButtonStop->setFixedSize(buttonSize);
    m_ButtonStart->setFixedSize(buttonSize);
    m_ButtonPause->setFixedSize(buttonSize);
    m_ButtonContinue->setFixedSize(buttonSize);

    connect(m_ButtonStop, SIGNAL(clicked(bool) ), this, SLOT( on_Button_Stop_clicked() ));
    connect(m_ButtonStart, SIGNAL(clicked(bool) ), this, SLOT( on_Button_Start_clicked() ));
    connect(m_ButtonPause, SIGNAL(clicked(bool) ), this, SLOT( on_Button_Pause_clicked() ));
    connect(m_ButtonContinue, SIGNAL(clicked(bool) ), this, SLOT( on_Button_Continue_clicked() ));
}

void MainWindow::initLabelObjects() noexcept {
    QSize labelSize {m_LableWidth, m_LableHight};

    m_LabelUrl = new QLabel("URL:", this);
    m_LabelUrl->setAccessibleName("m_LabelUrl");

    m_LabelTextToFind = new QLabel("Text to find:", this);
    m_LabelTextToFind->setAccessibleName("m_LabelTextToFind");

    m_LabelThreadQuantity = new QLabel("Max threads:", this);
    m_LabelThreadQuantity->setAccessibleName("m_LabelThreadQuantity");

    m_LabelUrlQuantityToFindText = new QLabel("Max URL:", this);
    m_LabelUrlQuantityToFindText->setAccessibleName("m_LabelUrlQuantityToFindText");

    m_LabelUrl->setFixedSize(labelSize);
    m_LabelTextToFind->setFixedSize(labelSize);
    m_LabelThreadQuantity->setFixedSize(labelSize);
    m_LabelUrlQuantityToFindText->setFixedSize(labelSize);
}

void MainWindow::initLineEditObjects() noexcept {
    m_LineEditUrl = new QLineEdit(this);
    m_LineEditUrl->setAccessibleName("m_LineEditUrl");

    m_LineEditTextToFind = new QLineEdit(this);
    m_LineEditTextToFind->setAccessibleName("m_LineEditTextToFind");

    m_LineEditThreadQuantity = new QLineEdit(this);
    m_LineEditThreadQuantity->setAccessibleName("m_LineEditThreadQuantity");

    m_LineEditUrlQuantityToFindText = new QLineEdit(this);
    m_LineEditUrlQuantityToFindText->setAccessibleName("m_LineEditUrlQuantityToFindText");
}

void MainWindow::initProgressBar() noexcept {
    m_ProgressBar = new QProgressBar(this);
    m_ProgressBar->setAccessibleName("m_ProgressBar");

    m_ProgressBar->setMinimum(0);
    connect(this, SIGNAL(signalProgress(int) ), m_ProgressBar, SLOT( setValue(int) ));
}

void MainWindow::initPlainTextEditField() noexcept {
    m_PlainTextEdit = new QPlainTextEdit(this);
    m_PlainTextEdit->setAccessibleName("m_PlainTextEdit");

    connect(this, SIGNAL(signalAppendText(const QString) ), m_PlainTextEdit, SLOT( appendPlainText(const QString) ) );
}

void MainWindow::setWidgetsPositions() noexcept {
    QRect geometry = this->geometry();

    setButtonsPositions(geometry);
    setLabelPositions();
    setLineEditPositions();
    setProgressBarPosition(geometry);
    setPlainTextEdit();

    calculateLineEditWidth(geometry);
    calculatePlainTextEditFieldSize(geometry);
}

void MainWindow::setButtonsPositions(const QRect& geometry) noexcept {
    auto buttonStop = m_ValToCalculateWidgPos.at(m_ButtonStop->accessibleName());
    auto buttonStart = m_ValToCalculateWidgPos.at(m_ButtonStart->accessibleName());
    auto buttonPause = m_ValToCalculateWidgPos.at(m_ButtonPause->accessibleName());
    auto buttonContinue = m_ValToCalculateWidgPos.at(m_ButtonContinue->accessibleName());

    buttonStop.setX(geometry.width()-buttonStop.x());
    buttonStart.setX(geometry.width()-buttonStart.x());
    buttonPause.setX(geometry.width()-buttonPause.x());
    buttonContinue.setX(geometry.width()-buttonContinue.x());

    setWidgetPosition(*m_ButtonStop, buttonStop);
    setWidgetPosition(*m_ButtonStart, buttonStart);
    setWidgetPosition(*m_ButtonPause, buttonPause);
    setWidgetPosition(*m_ButtonContinue, buttonContinue);
}

void MainWindow::setLabelPositions() noexcept {
    setWidgetPosition(*m_LabelUrl, m_ValToCalculateWidgPos.at(m_LabelUrl->accessibleName()));
    setWidgetPosition(*m_LabelTextToFind, m_ValToCalculateWidgPos.at(m_LabelTextToFind->accessibleName()));
    setWidgetPosition(*m_LabelThreadQuantity, m_ValToCalculateWidgPos.at(m_LabelThreadQuantity->accessibleName()));
    setWidgetPosition(*m_LabelUrlQuantityToFindText, m_ValToCalculateWidgPos.at(m_LabelUrlQuantityToFindText->accessibleName()));
}

void MainWindow::setLineEditPositions() noexcept {
    setWidgetPosition(*m_LineEditUrl, m_ValToCalculateWidgPos.at(m_LineEditUrl->accessibleName() ));
    setWidgetPosition(*m_LineEditTextToFind, m_ValToCalculateWidgPos.at(m_LineEditTextToFind->accessibleName() ));
    setWidgetPosition(*m_LineEditThreadQuantity, m_ValToCalculateWidgPos.at(m_LineEditThreadQuantity->accessibleName() ));
    setWidgetPosition(*m_LineEditUrlQuantityToFindText, m_ValToCalculateWidgPos.at(m_LineEditUrlQuantityToFindText->accessibleName() ));
}

void MainWindow::setProgressBarPosition(const QRect& geometry) noexcept {
    m_ProgressBar->setFixedWidth(geometry.width() - m_Margin*2);
    setWidgetPosition(*m_ProgressBar, m_ValToCalculateWidgPos.at(m_ProgressBar->accessibleName() ));
}

void MainWindow::setPlainTextEdit() noexcept {
    setWidgetPosition(*m_PlainTextEdit, m_ValToCalculateWidgPos.at(m_PlainTextEdit->accessibleName() ));
}

void MainWindow::setWidgetPosition(QWidget& obj, const QPoint &point) noexcept {
    obj.move({point});
}

void MainWindow::calculateLineEditWidth(const QRect &geometry) noexcept {
    int lineEditWidth = geometry.width() - m_MarginBtwnThreeComponents - m_ButtonWidth - m_LableWidth;

    m_LineEditUrl->setFixedWidth(lineEditWidth);
    m_LineEditTextToFind->setFixedWidth(lineEditWidth);
    m_LineEditThreadQuantity->setFixedWidth(lineEditWidth);
    m_LineEditUrlQuantityToFindText->setFixedWidth(lineEditWidth);
}

void MainWindow::calculatePlainTextEditFieldSize(const QRect& geometry) noexcept {
    int hight = geometry.height() - m_ValToCalculateWidgPos.at(m_PlainTextEdit->accessibleName() ).y() - m_Margin;
    int width = geometry.width() - m_Margin*2;

    m_PlainTextEdit->setFixedSize({width, hight});
}

void MainWindow::updateProgressBar(int count) noexcept {
    emit signalProgress(count);
}

void MainWindow::updateTextInPlainTextEditField(const QString data) noexcept {
    emit signalAppendText(std::move(data));
}

enums::Status MainWindow::getStatus() noexcept {
    return m_Status;
}

datastructures::DataToStartSearching MainWindow::getData() noexcept {
    m_ProgressBar->setMaximum(m_LineEditUrlQuantityToFindText->text().toInt());

    return datastructures::DataToStartSearching {
        m_LineEditUrl->text(),
        m_LineEditTextToFind->text(),
        m_LineEditThreadQuantity->text().toInt(),
        m_LineEditUrlQuantityToFindText->text().toInt()
    };
}

void MainWindow::resetSettings() noexcept {
    m_PlainTextEdit->clear();
}

void MainWindow::on_Button_Start_clicked() noexcept {
    m_Status = enums::Status::INIT;
    m_Presenter->update();
}

void MainWindow::on_Button_Stop_clicked() noexcept {
    m_Status = enums::Status::STOP;
    m_Presenter->update();
}

void MainWindow::on_Button_Pause_clicked() noexcept {
    m_Status = enums::Status::PAUSE;
    m_Presenter->update();
}

void MainWindow::on_Button_Continue_clicked() noexcept {
    m_Status = enums::Status::SEARCHING;
    m_Presenter->update();
}

void MainWindow::resizeEvent(QResizeEvent *) {
    setWidgetsPositions();
}
