#include "iconbutton.hpp"

IconButton::IconButton(QWidget *parent) :
    QPushButton(parent)
{
    m_toggle = true;

    setFlat(true);
    connect(this, &QPushButton::clicked, this, &IconButton::toggleIcon);
}

void IconButton::setIcon1(const QString &path)
{
    m_icon1 = QIcon(path);
}

QIcon IconButton::icon1() const
{
    return m_icon1;
}

void IconButton::setIcon2(const QString &path)
{
    m_icon2 = QIcon(path);
}

QIcon IconButton::icon2() const
{
    return m_icon2;
}

void IconButton::init(const QString &path, const QSize &size)
{
   init(path, QString(), size);
}

void IconButton::init(const QString &path1, const QString &path2, const QSize &size)
{
    setIcon1(path1);
    setIcon2(path2);
    setIconSize(size);

    setIcon(m_icon1);
}

void IconButton::toggleIcon()
{
    m_toggle = !m_toggle;

    if (m_toggle && !m_icon1.isNull())
    {
        setIcon(m_icon1);
    }
    else if (!m_icon2.isNull())
    {
        setIcon(m_icon2);
    }
}
