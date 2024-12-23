#include "mainwindow.h"
#include <QImage>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    originalImageLabel(new QLabel(this)),
    processedImageLabel(new QLabel(this)),
    selectImageButton(new QPushButton("Выбрать изображение", this)),
    processButton(new QPushButton("Применить обработку", this)),
    saveButton(new QPushButton("Сохранить обработанное изображение", this)),
    rgbButton(new QPushButton("RGB (с инверсией цветов)", this)),
    hsvButton(new QPushButton("HSV (с увеличенной яркостью)", this)),
    grayButton(new QPushButton("Серое", this)),
    imageProcessor(new ImageProcessor()),
    colorModel("RGB"),
    originalImagePath("") // Инициализация пустой строки для пути к изображению
{
    // Применение стилей
    QFile file(":/style.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }
    setWindowTitle("Image Processor");
    setWindowIcon(QIcon(":/ico.ico")); // Используйте путь из ресурсов
    setMinimumSize(1200, 1000);

    // Установка начальных текстов для меток
    originalImageLabel->setText("Оригинал (можно перетащить его сюда)");
    processedImageLabel->setText("Измененное изображение");

    // Настройка видимости миниатюр
    originalImageLabel->setStyleSheet("background-color: lightblue;"); // Цвет фона для видимости
    processedImageLabel->setStyleSheet("background-color: lightblue;"); // Цвет фона для видимости

    originalImageLabel->setAlignment(Qt::AlignCenter);
    processedImageLabel->setAlignment(Qt::AlignCenter);

    // Включаем поддержку перетаскивания
    originalImageLabel->setAcceptDrops(true);

    // Установка политики размера для миниатюр
    originalImageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    processedImageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Инициализация макета для оригинального изображения
    QVBoxLayout *originalLayout = new QVBoxLayout;
    originalLayout->addWidget(originalImageLabel);
    originalLayout->addWidget(new QLabel("Оригинал", this)); // Надпись под миниатюрой оригинала
    originalLayout->setAlignment(Qt::AlignCenter); // Центрируем вертикально

    // Инициализация макета для обработанного изображения
    QVBoxLayout *processedLayout = new QVBoxLayout;
    processedLayout->addWidget(processedImageLabel);
    processedLayout->addWidget(new QLabel("Измененное изображение", this)); // Надпись под миниатюрой обработанного изображения
    processedLayout->setAlignment(Qt::AlignCenter); // Центрируем вертикально

    // Макет для изображений
    QHBoxLayout *imageLayout = new QHBoxLayout;
    imageLayout->addLayout(originalLayout);
    imageLayout->addLayout(processedLayout);
    imageLayout->setAlignment(Qt::AlignCenter); // Центрируем горизонтально

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(imageLayout);
    mainLayout->addWidget(selectImageButton, 0, Qt::AlignCenter); // Центрируем кнопку выбора изображения

    // Добавляем кнопки выбора цветового пространства
    mainLayout->addWidget(rgbButton);
    mainLayout->addWidget(hsvButton);
    mainLayout->addWidget(grayButton);

    mainLayout->addWidget(processButton);
    mainLayout->addWidget(saveButton);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(selectImageButton, &QPushButton::clicked, this, &MainWindow::selectImage);
    connect(processButton, &QPushButton::clicked, this, &MainWindow::processImage);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveProcessedImage);

    connect(rgbButton, &QPushButton::clicked, this, &MainWindow::setColorModelRGB);
    connect(hsvButton, &QPushButton::clicked, this, &MainWindow::setColorModelHSV);
    connect(grayButton, &QPushButton::clicked, this, &MainWindow::setColorModelGray);
    connect(rgbButton, &QPushButton::clicked, this, &MainWindow::onRgbButtonClicked);
    connect(hsvButton, &QPushButton::clicked, this, &MainWindow::onHsvButtonClicked);
    connect(grayButton, &QPushButton::clicked, this, &MainWindow::onGrayButtonClicked);
}

// Переопределяем метод для обработки перетаскивания
void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        if (!urlList.isEmpty()) {
            QString filePath = urlList.first().toLocalFile();
            // Проверяем, является ли файл изображением
            if (QImageReader::supportedImageFormats().contains(QFileInfo(filePath).suffix().toLower().toUtf8())) {
                loadImage(filePath);
            } else {
                QMessageBox::warning(this, "Ошибка", "Файл не является изображением.");
            }
        }
    }
}

void MainWindow::loadImage(const QString &filePath) {
    QImage originalImage(filePath);
    if (originalImage.isNull()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить изображение.");
        return;
    }

    originalImageLabel->setPixmap(QPixmap::fromImage(originalImage).scaled(500, 500, Qt::KeepAspectRatio));
    originalImagePath = filePath; // Сохраняем путь к изображению
    QMessageBox::information(this, "Информация", "Выбрано изображение: " + originalImagePath);
}

MainWindow::~MainWindow() {
    delete imageProcessor;
}

void MainWindow::selectImage() {
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите изображение", QString(), "Images (*.png *.jpg *.bmp)");

    // Проверяем, выбрано ли изображение
    if (filePath.isEmpty()) {
        QMessageBox::information(this, "Информация", "Выбор изображения отменен."); // Информируем пользователя
        return; // Выход из функции, если выбор отменен
    }

    loadImage(filePath); // Используем общий метод для загрузки изображения
}

void MainWindow::processImage() {
    if (originalImagePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала выберите изображение.");
        return;
    }

    QImage originalImage(originalImagePath);
    if (originalImage.isNull()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить изображение.");
        return;
    }

    QImage processedImage = imageProcessor->processImage(originalImage, colorModel);
    if (processedImage.isNull()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось обработать изображение.");
        return;
    }

    processedImageLabel->setPixmap(QPixmap::fromImage(processedImage).scaled(500, 500, Qt::KeepAspectRatio));
    QMessageBox::information(this, "Информация", "Обработка изображения завершена.");
}

void MainWindow::saveProcessedImage() {
    if (processedImageLabel->pixmap().isNull()) {
        QMessageBox::warning(this, "Ошибка", "Сначала обработайте изображение.");
        return;
    }

    QString savePath = QFileDialog::getSaveFileName(this, "Сохранить изображение", QString(),
                                                    "PNG Files (*.png);;JPEG Files (*.jpg);;BMP Files (*.bmp);;All Files (*)");
    if (savePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Файл не сохранен.");
        return;
    }

    if (!savePath.endsWith(".png") && !savePath.endsWith(".jpg") && !savePath.endsWith(".bmp")) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, укажите расширение файла.");
        return;
    }

    QImage processedImage = processedImageLabel->pixmap().toImage();
    QString format;
    if (savePath.endsWith(".png")) {
        format = "PNG";
    } else if (savePath.endsWith(".jpg")) {
        format = "JPEG";
    } else {
        format = "BMP";
    }

    if (!processedImage.save(savePath, format.toUtf8().constData())) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить изображение.");
    } else {
        QMessageBox::information(this, "Успех", "Изображение успешно сохранено.");
    }
}

void MainWindow::setColorModelRGB() {
    colorModel = "RGB";
}

void MainWindow::setColorModelHSV() {
    colorModel = "HSV";
}

void MainWindow::setColorModelGray() {
    colorModel = "Gray";
}
void MainWindow::onRgbButtonClicked() {
    QMessageBox::information(this, "Модель цвета", "Вы выбрали модель RGB.");
}

// Метод для отображения информационного окна для HSV
void MainWindow::onHsvButtonClicked() {
    QMessageBox::information(this, "Модель цвета", "Вы выбрали модель HSV.");
}

// Метод для отображения информационного окна для Серого
void MainWindow::onGrayButtonClicked() {
    QMessageBox::information(this, "Модель цвета", "Вы выбрали модель Серое.");
}
