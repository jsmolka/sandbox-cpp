#ifndef ICONBUTTON_HPP
#define ICONBUTTON_HPP

#include <QPushButton>
#include <QIcon>

class IconButton : public QPushButton
{
    Q_OBJECT

public:
    explicit IconButton(QWidget *parent = 0);

    void setIcon1(const QString &path);
    void setIcon2(const QString &path);

    QIcon icon1() const;
    QIcon icon2() const;

    void init(const QString &path, const QSize &size);
    void init(const QString &path1, const QString &path2, const QSize &size);

public slots:
    void toggleIcon();

private:
    QIcon m_icon1;
    QIcon m_icon2;
    bool m_toggle;
};

#endif // ICONBUTTON_HPP
