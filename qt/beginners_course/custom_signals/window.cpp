#include "Window.hpp"

Window::Window(QWidget *parent) :
    QWidget(parent)
{
    // Set size of window
    setFixedSize(480, 360);

    // Set counter to zero
    m_counter = 0;

    // Create and position the button
    m_button = new QPushButton("Hello World", this);
    m_button->setGeometry(10, 10, 460, 340);
    m_button->setCheckable(true);

    // Create connections
    connect(m_button, &QPushButton::clicked, this, &Window::slotButtonClicked);
    connect(this, &Window::counterReached, QApplication::instance(), &QApplication::quit);
}

void Window::slotButtonClicked(bool checked)
{
    if (checked)
        m_button->setText("Checked");
    else
        m_button->setText("Hello World");

    m_counter++;

    if (m_counter == 10)
        emit counterReached();
}
