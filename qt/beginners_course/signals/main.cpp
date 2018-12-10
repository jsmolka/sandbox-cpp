#include <QApplication>
#include <QProgressBar>
#include <QSlider>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create a container window
    QWidget window; window.setFixedSize(480, 110);

    // Create a progress bar
    QProgressBar *progressBar = new QProgressBar(&window);
    progressBar->setRange(0, 100); progressBar->setValue(0); progressBar->setGeometry(10, 10, 460, 40);

    // Create horizontal slider
    QSlider *slider = new QSlider(&window);
    slider->setOrientation(Qt::Horizontal);
    slider->setRange(0, 100);
    slider->setValue(0);
    slider->setGeometry(10, 60, 460, 40);

    window.show();

    // Create connection
    QObject::connect(slider, &QSlider::valueChanged, progressBar, &QProgressBar::setValue);

    return app.exec();
}
