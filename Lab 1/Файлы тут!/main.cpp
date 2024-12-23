#include "mainwindow.h"
#include <QFile>
#include <QMainWindow>
#include <QPushButton>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/style.qss");  // Если файл находится в ресурсах, иначе укажите путь к файлу
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet);  // Применение стиля к приложению
    }
    MainWindow w;
    w.setWindowTitle("Color Converter");
    w.setWindowIcon(QIcon(":/icon.ico"));
    w.show();
    return a.exec();
}
