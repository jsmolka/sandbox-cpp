#include <QApplication>
#include <QWidget>
#include <iconbutton.hpp>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;

    IconButton button(&window);
    button.show();

    window.show();

    return app.exec();
}
