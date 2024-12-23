#include <QApplication>
#include <QFile>
#include "imageinfoapp.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Загрузка файла стилей
    QFile styleFile(":/style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        qApp->setStyleSheet(style);
    }

    // Создание и отображение главного окна
    ImageInfoApp window;
    window.setWindowTitle("Image Info Application");
    window.setWindowIcon(QIcon(":/icon.ico"));
    window.show();

    return app.exec();
}
