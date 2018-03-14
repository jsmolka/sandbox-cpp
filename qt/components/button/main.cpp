#include <QApplication>
#include <QPushButton>
#include <QTextStream>
#include <QFile>

QString read(QString fileName)
{
    QFile styleFile(fileName);

    // Try opening the file
    if (!styleFile.open(QFile::ReadOnly | QFile::Text))
    {
        // Return emptry string if opening fails
        return QString();
    }

    // Read text file
    QTextStream textStream(&styleFile);
    QString styleSheet = textStream.readAll();
    styleFile.close();

    // Return read text
    return styleSheet;
}

void setupButton(QPushButton *button)
{
    // Set geometry
    button->setGeometry(10, 10, 460, 340);

    // Set icon
    button->setIcon(QIcon(":/assets/icon.png"));
    button->setIconSize(QSize(100, 100));

    // Set style
    button->setStyleSheet(read(":/assets/style.css"));

    // Set color
    QPalette palette = button->palette();
    palette.setBrush(QPalette::ButtonText, Qt::red);
    button->setPalette(palette);

    // Update to apply changes
    button->update();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setFixedSize(480, 360);

    QPushButton *button = new QPushButton("", &window);
    setupButton(button);

    button->show();
    window.show();

    return app.exec();
}
