#include "iconbutton.hpp"

IconButton::IconButton(QWidget *parent) :
    QPushButton(parent)
{
    setCheckable(true);
    setChecked(false);

    setFixedSize(100, 100);
    connect(this, SIGNAL(clicked(bool)), this, SLOT(check()));
}

void IconButton::setCheckedIcon(QIcon icon)
{
    mCheckedIcon = icon;
}

void IconButton::setCheckedIcon(QString path)
{
    setCheckedIcon(QIcon(path));
}

void IconButton::setUncheckedIcon(QIcon icon)
{
    mUncheckedIcon = icon;
}

void IconButton::setUncheckedIcon(QString path)
{
    setUncheckedIcon(QIcon(path));
}

QIcon IconButton::checkedIcon() const
{
    return icon();
}

QIcon IconButton::uncheckedIcon() const
{
    return icon();
}

void IconButton::slotToggle()
{
    // Do stuff
}
