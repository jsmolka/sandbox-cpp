#include <QApplication>
#include <QWidget>
#include "iconbutton.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setFixedSize(200, 200);

    IconButton button(&window);
    button.init(":/assets/play.png", ":/assets/pause.png", QSize(100, 100));
    button.setFixedSize(QSize(200, 200));
    button.show();

    window.show();

    return app.exec();
}
