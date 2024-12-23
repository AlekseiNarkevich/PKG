#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QImage>
#include <QImageReader>
#include <QMessageBox>
#include "imageprocessor.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void selectImage();
    void processImage();
    void saveProcessedImage();
    void setColorModelRGB();
    void setColorModelHSV();
    void setColorModelGray();
    void onRgbButtonClicked();
    void onHsvButtonClicked();
    void onGrayButtonClicked();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    void loadImage(const QString &filePath);


    QLabel *originalImageLabel;
    QLabel *processedImageLabel;
    QPushButton *selectImageButton;
    QPushButton *processButton;
    QPushButton *saveButton;
    QPushButton *rgbButton;
    QPushButton *hsvButton;
    QPushButton *grayButton;
    ImageProcessor *imageProcessor; // Объект для обработки изображений
    QString colorModel; // "RGB", "HSV", "Gray"
    QString originalImagePath; // Путь к оригинальному изображению
};

#endif // MAINWINDOW_H
