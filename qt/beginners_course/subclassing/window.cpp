#include "window.hpp"

Window::Window(QWidget *parent) :
    QWidget(parent)
{
    // Set size of window
    setFixedSize(480, 360);

    // Create and position button
    m_button = new QPushButton("Hello World", this);
    m_button->setGeometry(10, 10, 460, 340);

    connect(m_button, &QPushButton::clicked,  qApp, &QApplication::quit);
}
