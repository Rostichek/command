#include "mainwindow.h"

#include "clickcanvaswidget.h"
#include "core/eventfilter.h"
#include "core/interactionsrecorder.h"
#include "core/serialization/textscriptserializer.h"

#include "ui_mainwindow.h"

#include <QDir>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow{}),
      m_serializer(std::make_shared<TextScriptSerializer>(
          QDir(QCoreApplication::applicationDirPath()).filePath(QStringLiteral("macro_script.txt")))),
      m_eventFilter(new EventFilter(this)),
      m_statusKeyLabel(new QLabel("Ready", this))
{
    m_ui->setupUi(this);
    m_ui->statusbar->addPermanentWidget(m_statusKeyLabel, 1);
    m_ui->canvasWidget->setMouseTracking(true);
    m_ui->canvasWidget->installEventFilter(m_eventFilter);

    m_engine = new InteractionsRecrorder(m_ui->canvasWidget, m_serializer, m_eventFilter, this);

    auto subscribe = [this](auto property, auto&& functor) { m_notifiers.emplace_back(property.addNotifier(functor)); };

    subscribe(m_engine->bindableIsRecording(), [this]() {
        bool recording = m_engine->isRecording();

        m_ui->btnRecord->setText(recording ? tr("Finish") : tr("Record"));
        m_ui->btnRecord->setStyleSheet(recording ? QStringLiteral("background-color: #ff5555; color: white;") : QString());

        m_ui->btnReplay->setEnabled(!recording);
        m_ui->chkLoopReplay->setEnabled(!recording);

        if (recording) {
            m_statusKeyLabel->setText(tr("Recording..."));
        } else if (!m_engine->isReplaying()) {
            m_statusKeyLabel->setText(tr("Script Saved. Ready."));
        }
    });

    subscribe(m_engine->bindableIsReplaying(), [this]() {
        bool replaying = m_engine->isReplaying();

        m_ui->btnRecord->setEnabled(!replaying);
        m_ui->btnReplay->setEnabled(!replaying);
        m_ui->chkLoopReplay->setEnabled(!replaying);

        if (replaying) {
            m_statusKeyLabel->setText(tr("Replaying from file..."));
        } else if (!m_engine->isRecording()) {
            m_statusKeyLabel->setText(tr("Replay Complete. Ready."));
        }
    });

    connect(m_ui->btnRecord, &QPushButton::clicked, m_engine, &InteractionsRecrorder::toggleRecording);
    connect(m_ui->btnReplay, &QPushButton::clicked, m_engine, &InteractionsRecrorder::startReplay);
    connect(m_ui->chkLoopReplay, &QCheckBox::toggled, m_engine, &InteractionsRecrorder::setLooping);
}

MainWindow::~MainWindow() {}
