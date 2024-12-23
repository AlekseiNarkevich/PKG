#include <QApplication>
#include <QFile>
#include <QIcon>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Установка иконки для всего приложения
    a.setWindowIcon(QIcon(":/ico.ico"));
    // Применение стилей
    QFile file(":/style.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet); // Применение стиля ко всему приложению
    }

    MainWindow w;
    w.show();
    return a.exec();
}
