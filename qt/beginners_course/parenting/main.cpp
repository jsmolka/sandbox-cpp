#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);

    QWidget window;
    window.setFixedSize(480, 360);

    QPushButton *button = new QPushButton("Hello World", &window);
    button->setGeometry(10, 10, 460, 340);

    QPushButton *child = new QPushButton("Child", button);
    child->setGeometry(20, 20, 40, 40);

    window.show();
    return app.exec();
}
