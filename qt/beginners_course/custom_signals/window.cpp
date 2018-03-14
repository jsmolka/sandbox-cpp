#include "Window.hpp"

Window::Window(QWidget *parent) :
    QWidget(parent)
{
    // Set size of window
    setFixedSize(480, 360);

    // Set counter to zero
    mCounter = 0;

    // Create and position the button
    mButton = new QPushButton("Hello World", this);
    mButton->setGeometry(10, 10, 460, 340);
    mButton->setCheckable(true);

    // Create connections
    connect(mButton, SIGNAL(clicked(bool)), this, SLOT(slotButtonClicked(bool)));
    connect(this, SIGNAL(counterReached()), QApplication::instance(), SLOT(quit()));
}

void Window::slotButtonClicked(bool checked)
{
    if (checked)
        mButton->setText("Checked");
    else
        mButton->setText("Hello World");

    mCounter++;

    if (mCounter == 10)
        emit counterReached();
}
