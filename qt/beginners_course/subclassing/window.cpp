#include "window.hpp"

Window::Window(QWidget *parent) :
QWidget(parent)
{
    // Set size of window
    setFixedSize(480, 360);

    // Create and position button
    mButton = new QPushButton("Hello World", this);
    mButton->setGeometry(10, 10, 460, 340);
}
