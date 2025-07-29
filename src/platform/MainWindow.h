#pragma once

#include <QAction>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStackedWidget>
#include <QWidget>

#include "DefaultWidget.h"
#include "EmulationWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(const char *romFile, QWidget *parent = nullptr);
    ~MainWindow();

  private slots:
    void loadROM();
    void startEmulation();
    void stopEmulation();
    void pauseEmulation();

  private:
    DefaultWidget *defaultWidget_ = nullptr;
    EmulationWidget *emulationWidget_ = nullptr;
    QStackedWidget *stackedWidget_ = nullptr;

    void createActions();
    void createMenus();

    QMenu *fileMenu_;
    QMenu *emulationMenu_;
    QAction *loadROMAction_;
    QAction *exitAction_;
    QAction *startEmulationAction_;
    QAction *pauseEmulationAction_;
    QAction *stopEmulationAction_;
    QLabel *infoLabel_;
};
