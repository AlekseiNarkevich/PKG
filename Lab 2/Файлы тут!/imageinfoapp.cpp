#include "imageinfoapp.h"
#include <QImageReader>
#include <QFileDialog>
#include <QDirIterator>
#include <QHeaderView>
#include <QFileInfo>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QPixmap>
#include <QImage>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QLabel>
#include <QApplication>
#include <QMessageBox>
#include <QScrollBar>
ImageInfoApp::ImageInfoApp(QWidget *parent) : QMainWindow(parent) {
    // Установка иконки
    this->setWindowIcon(QIcon(":/icon.ico"));
    // Разрешаем drag-and-drop
    setAcceptDrops(true);
    setMinimumSize(1200, 800);
    // Создаем таблицу для отображения данных
    table = new QTableWidget(this);
    table->setFocusPolicy(Qt::NoFocus);
    table->setColumnCount(5);  // Имя файла, Размер, Размер файла (КБ), Глубина цвета, Сжатие
    QStringList headers = {"Имя файла", "Размер (пиксели)", "Размер файла (КБ)", "Глубина цвета", "Сжатие"};
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical {"
        "   background: #3498db;"  // Фон слайдера
        "   width: 15px;"          // Ширина слайдера
        "   margin: 22px 0 22px 0;"
        "   border: 2px solid #3498db;" // Убедимся, что фон закруглен
        "   border-radius: 7.5px;" // Закругленные края фона
        "}"
        "QScrollBar::handle:vertical {"
        "   background: #e67e22;"  // Цвет ползунка
        "   min-height: 20px;"
        "   border-radius: 7.5px;"  // Закругленные края ползунка
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "   background: none;"      // Скрыть стрелки
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "   background: none;"
        "}"
        );
    // Отключаем возможность редактирования ячеек
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Подключаем сигнал выбора строки к слоту для отображения изображения
    connect(table, &QTableWidget::cellClicked, this, &ImageInfoApp::onTableRowClicked);

    // Метка для отображения изображения (миниатюры)
    imageLabel = new QLabel(this);
    imageLabel->setFixedSize(400, 400);  // Увеличиваем размер миниатюры
    imageLabel->setStyleSheet("border: 1px solid black;");
    imageLabel->setAlignment(Qt::AlignCenter);

    // Создаем контейнер для миниатюры и текста
    QWidget *imageContainer = new QWidget(this);
    QVBoxLayout *imageLayout = new QVBoxLayout(imageContainer);
    imageLayout->setAlignment(Qt::AlignCenter);

    // Метка для сообщения о перетаскивании
    dragDropLabel = new QLabel("Перетащите изображение сюда", this);
    dragDropLabel->setAlignment(Qt::AlignCenter);
    dragDropLabel->setStyleSheet("font-size: 16px;"); // Увеличиваем размер шрифта

    // Добавляем миниатюру и текст в контейнер
    imageLayout->addWidget(imageLabel);
    imageLayout->addWidget(dragDropLabel);

    // Кнопка для выбора папки
    QPushButton *selectFolderButton = new QPushButton("Выбрать папку", this);

    // Подключаем сигнал нажатия кнопки к слоту выбора папки
    connect(selectFolderButton, &QPushButton::clicked, this, &ImageInfoApp::loadImagesFromFolder);

    // Компоновка для отображения таблицы, кнопки и изображения
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);  // Основная вертикальная компоновка
    QHBoxLayout *layout = new QHBoxLayout();  // Горизонтальная компоновка для таблицы и изображения
    layout->addWidget(table);
    layout->addWidget(imageContainer);  // Добавляем контейнер с миниатюрой и текстом
    mainLayout->addWidget(selectFolderButton);  // Добавляем кнопку вверху
    mainLayout->addLayout(layout);  // Добавляем таблицу и изображение под кнопку
    setCentralWidget(centralWidget);
}

void ImageInfoApp::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void ImageInfoApp::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        foreach (const QUrl &url, mimeData->urls()) {
            QString filePath = url.toLocalFile();
            processImageFile(filePath); // Обработка изображения

            // Отображаем миниатюру изображения
            QPixmap pixmap(filePath);
            if (!pixmap.isNull()) {
                imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

                // Ищем строку с загруженным изображением
                int row = imageFilePaths.indexOf(filePath); // Получаем индекс строки для загруженного файла
                if (row != -1) {
                    table->selectRow(row); // Выделяем строку
                }

                // Устанавливаем цвет фона для последней добавленной строки в таблице (светло-зеленый цвет)
                for (int col = 0; col < table->columnCount(); ++col) {
                    table->item(row, col)->setBackground(QColor(144, 238, 144)); // Светло-зеленый (салатовый) цвет
                }
            }
        }
    }
}



void ImageInfoApp::loadImagesFromFolder() {
    QString folderPath = QFileDialog::getExistingDirectory(this, "Выберите папку с изображениями");
    if (folderPath.isEmpty()) return;

    // Очищаем таблицу перед загрузкой новых изображений
    table->setRowCount(0);
    imageFilePaths.clear();  // Очищаем список путей к файлам

    // Используем QSet для уникальности путей
    QSet<QString> uniquePaths;

    // Считаем количество изображений в папке
    int imageCount = 0;

    QDirIterator it(folderPath, QStringList() << "*.jpg" << "*.png" << "*.gif" << "*.bmp" << "*.tif" << "*.pcx", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString filePath = it.next();
        if (!uniquePaths.contains(filePath)) { // Проверка на уникальность
            uniquePaths.insert(filePath); // Добавляем в набор уникальных путей
            imageCount++;
        }
    }

    // Если в папке есть изображения, показываем сообщение
    if (imageCount > 0) {
        QMessageBox::information(this, "Изображения найдены",
                                 QString("В папке \"%1\" найдено %2 изображений.").arg(folderPath).arg(imageCount));
    } else {
        QMessageBox::warning(this, "Нет изображений",
                             QString("В папке \"%1\" нет изображений.").arg(folderPath));
    }
    // Загружаем изображения в таблицу
    QElapsedTimer timer;
    timer.start();  // Запускаем таймер
    // Загружаем изображения в таблицу
    for (const QString &filePath : uniquePaths) {
        processImageFile(filePath);
    }
    double elapsedTimeInSeconds = timer.elapsed() / 1000.0; // Переводим миллисекунды в секунды
    QMessageBox::information(this, "Загрузка завершена",
                             QString("Время загрузки изображений: %1 сек").arg(elapsedTimeInSeconds));
}





void ImageInfoApp::processImageFile(const QString &filePath) {
    QFileInfo fileInfo(filePath);
    QImageReader reader(filePath);
    // Проверка на дубликаты
    if (imageFilePaths.contains(filePath)) {
        return; // Если файл уже есть, не добавляем его снова
    }
    if (!reader.canRead()) {
        // Обработка ошибок чтения изображения
        return;
    }

    QString fileName = fileInfo.fileName();
    QSize imageSize = reader.size();
    int width = imageSize.width();
    int height = imageSize.height();

    // Получаем размер файла в килобайтах
    double fileSizeKB = fileInfo.size() / 1024.0;  // Размер в KB

    // Загрузка изображения для получения глубины цвета
    QImage image(filePath);
    if (image.isNull()) {
        return;  // Если изображение не удалось загрузить
    }
    int depth = image.depth();  // Глубина цвета

    // Определение метода сжатия
    std::string compression = "N/A";
    if (fileInfo.suffix().toLower() == "jpg" || fileInfo.suffix().toLower() == "jpeg") {
        compression = "С потерями";  // JPEG использует сжатие с потерями
    } else if (fileInfo.suffix().toLower() == "png") {
        compression = "Без потерь";  // PNG использует сжатие без потерь
    }

    // Добавляем информацию в таблицу
    int row = table->rowCount();
    table->insertRow(row);

    // Добавляем путь к файлу в список для доступа при выборе строки
    imageFilePaths.append(filePath);

    table->setItem(row, 0, new QTableWidgetItem(fileName));
    table->setItem(row, 1, new QTableWidgetItem(QString("%1x%2").arg(width).arg(height)));
    table->setItem(row, 2, new QTableWidgetItem(QString::number(fileSizeKB, 'f', 2) + " KB")); // Размер в KB с 2 знаками после запятой
    table->setItem(row, 3, new QTableWidgetItem(QString::number(depth)));
    table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(compression)));

    // Отключаем редактирование ячеек
    for (int col = 0; col < table->columnCount(); ++col) {
        table->item(row, col)->setFlags(table->item(row, col)->flags() & ~Qt::ItemIsEditable);
    }
}

void ImageInfoApp::onTableRowClicked(int row, int column) {
    if (row >= 0 && row < table->rowCount()) {
        QString filePath = imageFilePaths[row];
        QPixmap pixmap(filePath);

        // Если миниатюра не была загружена, показываем пустую метку
        if (pixmap.isNull()) {
            imageLabel->clear();
        } else {
            imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
}
