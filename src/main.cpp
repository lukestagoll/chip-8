// #include "Application.h"
#include "MainWindow.h"
#include <QApplication>
#include <QSurfaceFormat>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: chip8 <rom_file>" << std::endl;
        return 1;
    }

    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setWindowIcon(QIcon(":/icons/chip8_256x256.png"));

    MainWindow window(argv[1]);
    window.show();
    return app.exec();
}
