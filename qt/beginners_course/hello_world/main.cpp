#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton button("Hello world!");
    button.setText("My Text");
    button.setToolTip("A tooltip");
    button.setFont(QFont("Courier"));
    button.setFixedSize(480, 360);
    button.show();

    return app.exec();
}
