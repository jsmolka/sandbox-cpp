#ifndef ICONBUTTON_HPP
#define ICONBUTTON_HPP

#include <QPushButton>
#include <QPixmap>
#include <QIcon>

class IconButton : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(QIcon checkedIcon READ checkedIcon WRITE setCheckedIcon)
    Q_PROPERTY(QIcon uncheckedIcon READ uncheckedIcon WRITE setUncheckedIcon)

public:
    explicit IconButton(QWidget *parent = 0);

    void setCheckedIcon(QIcon icon);
    void setCheckedIcon(QString path);
    void setUncheckedIcon(QIcon icon);
    void setUncheckedIcon(QString path);

    QIcon checkedIcon() const;
    QIcon uncheckedIcon() const;

private slots:
    void slotToggle();

private:
    QIcon mCheckedIcon;
    QIcon mUncheckedIcon;
};

#endif // ICONBUTTON_HPP
