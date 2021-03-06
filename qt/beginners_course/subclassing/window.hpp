#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QWidget>
#include <QApplication>
#include <QPushButton>

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);

private:
    QPushButton *m_button;
};

#endif // WINDOW_HPP
