#include "MainWindow.h"
#include <QFileDialog>

MainWindow::MainWindow(const char *romFile, QWidget *parent) : QMainWindow(parent)
{
    emulationWidget_ = new EmulationWidget(this);
    defaultWidget_ = new DefaultWidget(emulationWidget_, this);
    connect(defaultWidget_, &DefaultWidget::loadROM, this, &MainWindow::loadROM);

    stackedWidget_ = new QStackedWidget(this);
    stackedWidget_->addWidget(defaultWidget_);
    stackedWidget_->addWidget(emulationWidget_);
    setCentralWidget(stackedWidget_);

    createActions();
    createMenus();
    connect(exitAction_, &QAction::triggered, this, &QMainWindow::close);
}

MainWindow::~MainWindow()
{
    delete defaultWidget_;
    delete emulationWidget_;
}

void MainWindow::createActions()
{

    loadROMAction_ = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen), tr("&Load ROM"), this);
    loadROMAction_->setShortcuts(QKeySequence::New);
    loadROMAction_->setStatusTip(tr("Load a Chip-8 ROM"));
    connect(loadROMAction_, &QAction::triggered, this, &MainWindow::loadROM);

    exitAction_ = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::SystemShutdown), tr("&Exit"), this);
    exitAction_->setShortcuts(QKeySequence::New);
    exitAction_->setStatusTip(tr("Close Application"));
    connect(exitAction_, &QAction::triggered, this, &QMainWindow::close);

    startEmulationAction_ =
        new QAction(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart), tr("&Start/Resume Emulation"), this);
    startEmulationAction_->setShortcuts(QKeySequence::New);
    startEmulationAction_->setStatusTip(tr("Start/Resume Emulation"));
    connect(startEmulationAction_, &QAction::triggered, this, &MainWindow::startEmulation);

    pauseEmulationAction_ =
        new QAction(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackPause), tr("&Start Emulation"), this);
    pauseEmulationAction_->setShortcuts(QKeySequence::New);
    pauseEmulationAction_->setStatusTip(tr("Pause Emulation"));
    connect(pauseEmulationAction_, &QAction::triggered, this, &MainWindow::pauseEmulation);

    stopEmulationAction_ =
        new QAction(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStop), tr("&Stop Emulation"), this);
    stopEmulationAction_->setShortcuts(QKeySequence::New);
    stopEmulationAction_->setStatusTip(tr("Stop Emulation"));
    connect(stopEmulationAction_, &QAction::triggered, this, &MainWindow::stopEmulation);
}

void MainWindow::createMenus()
{
    fileMenu_ = menuBar()->addMenu(tr("&File"));
    fileMenu_->addAction(loadROMAction_);
    fileMenu_->addAction(exitAction_);

    fileMenu_ = menuBar()->addMenu(tr("&Emulation"));
    fileMenu_->addAction(startEmulationAction_);
    fileMenu_->addAction(stopEmulationAction_);
    fileMenu_->addAction(pauseEmulationAction_);
}

void MainWindow::loadROM()
{
    emulationWidget_->stopEmulation();
    int result = emulationWidget_->loadROM();
    if (result != 0)
    {
        if (stackedWidget_->currentIndex() == 1)
        {
            stackedWidget_->setCurrentWidget(defaultWidget_);
        }
        return;
    }
    if (stackedWidget_->currentIndex() == 0)
    {
        stackedWidget_->setCurrentWidget(emulationWidget_);
    }
    emulationWidget_->startEmulation();
}

void MainWindow::startEmulation()
{
    if (stackedWidget_->currentIndex() == 0)
    {
        stackedWidget_->setCurrentWidget(emulationWidget_);
    }
    emulationWidget_->startEmulation();
}

void MainWindow::stopEmulation()
{
    if (stackedWidget_->currentIndex() == 0) return;
    emulationWidget_->stopEmulation();
    stackedWidget_->setCurrentWidget(defaultWidget_);
}

void MainWindow::pauseEmulation()
{
    if (stackedWidget_->currentIndex() == 0) return;
    emulationWidget_->pauseEmulation();
}
