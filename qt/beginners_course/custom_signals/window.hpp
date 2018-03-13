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

signals:
    void counterReached();

private slots:
    void slotButtonClicked(bool checked);

private:
    int mCounter;
    QPushButton *mButton;
};

#endif // WINDOW_HPP
