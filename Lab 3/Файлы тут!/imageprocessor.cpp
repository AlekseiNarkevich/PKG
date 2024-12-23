#include "imageprocessor.h"
#include <QMessageBox>
#include <algorithm>
QImage ImageProcessor::processImage(const QImage &image, const QString &colorModel) {
    if (image.isNull()) {
        QMessageBox::warning(nullptr, "Ошибка", "Исходное изображение пустое!");
        return QImage();
    }

    QImage processedImage;

    if (colorModel == "RGB") {
        processedImage = processInRGB(image);
    } else if (colorModel == "HSV") {
        processedImage = processInHSV(image);
    } else if (colorModel == "Gray") {
        processedImage = convertToGray(image);
    } else {
        QMessageBox::warning(nullptr, "Ошибка", "Неизвестная цветовая модель!");
        return QImage();
    }

    QImage contrastedImage = linearContrast(processedImage);
    if (contrastedImage.isNull()) {
        QMessageBox::warning(nullptr, "Ошибка", "Контрастированное изображение пустое!");
        return QImage();
    }

    return histogramEqualization(contrastedImage);
}

QImage ImageProcessor::linearContrast(const QImage &image) {
    QImage result = image; // Копируем исходное изображение в новый объект для обработки

    // Инициализация минимумов и максимумов для каждого канала
    int minRed = 255, maxRed = 0;
    int minGreen = 255, maxGreen = 0;
    int minBlue = 255, maxBlue = 0;

    // Находим минимумы и максимумы
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor color = image.pixelColor(x, y); // Получаем цвет пикселя
            int red = color.red();
            int green = color.green();
            int blue = color.blue();

            // Обновляем минимумы и максимумы для каждого канала
            minRed = std::min(minRed, red);
            maxRed = std::max(maxRed, red);
            minGreen = std::min(minGreen, green);
            maxGreen = std::max(maxGreen, green);
            minBlue = std::min(minBlue, blue);
            maxBlue = std::max(maxBlue, blue);
        }
    }

    // Применяем линейное контрастирование
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor color = image.pixelColor(x, y);
            int red = color.red();
            int green = color.green();
            int blue = color.blue();

            // Проверка на деление на ноль, чтобы избежать ошибок
            int contrastedRed = (maxRed > minRed) ? (red - minRed) * 255 / (maxRed - minRed) : red;
            int contrastedGreen = (maxGreen > minGreen) ? (green - minGreen) * 255 / (maxGreen - minGreen) : green;
            int contrastedBlue = (maxBlue > minBlue) ? (blue - minBlue) * 255 / (maxBlue - minBlue) : blue;

            // Устанавливаем новые значения пикселей с использованием std::clamp для ограничения значений
            result.setPixelColor(x, y, QColor{
                                           std::clamp(contrastedRed, 0, 255),
                                           std::clamp(contrastedGreen, 0, 255),
                                           std::clamp(contrastedBlue, 0, 255)
                                       });
        }
    }

    // Информируем пользователя о завершении обработки
    QMessageBox::information(nullptr, "Информация", "Линейное контрастирование завершено.");
    return result; // Возвращаем обработанное изображение
}

QImage ImageProcessor::histogramEqualization(const QImage &image) {
    QImage result(image.size(), QImage::Format_RGB32); // Создаем новое изображение в формате RGB32

    // Выделяем три массива для гистограмм
    int histogram[3][256] = {{0}}; // Для R, G и B
    int cumulative[3][256] = {{0}}; // Для накопленных значений

    // Построение гистограммы для каждого канала
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor color = image.pixelColor(x, y);
            histogram[0][color.red()]++;   // Гистограмма для красного канала
            histogram[1][color.green()]++; // Гистограмма для зеленого канала
            histogram[2][color.blue()]++;  // Гистограмма для синего канала
        }
    }

    // Накопленная сумма для каждого канала
    for (int i = 0; i < 3; ++i) {
        cumulative[i][0] = histogram[i][0]; // Начальное значение накопленной суммы
        for (int j = 1; j < 256; ++j) {
            cumulative[i][j] = cumulative[i][j - 1] + histogram[i][j]; // Накопление значений
        }
    }

    // Преобразование изображения для каждого канала
    int totalPixels = image.width() * image.height(); // Общее количество пикселей
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor color = image.pixelColor(x, y);
            int newRed = cumulative[0][color.red()] * 255 / totalPixels; // Новое значение для красного канала
            int newGreen = cumulative[1][color.green()] * 255 / totalPixels; // Для зеленого
            int newBlue = cumulative[2][color.blue()] * 255 / totalPixels; // Для синего

            // Устанавливаем новые значения пикселей
            result.setPixelColor(x, y, QColor{
                                           std::clamp(newRed, 0, 255),
                                           std::clamp(newGreen, 0, 255),
                                           std::clamp(newBlue, 0, 255)
                                       });
        }
    }
    QMessageBox::information(nullptr, "Информация", "Выравнивание гистограммы завершено."); // Информируем пользователя
    return result; // Возвращаем обработанное изображение
}


QImage ImageProcessor::processInRGB(const QImage &image) {
    QImage resultImage = image;
    for (int y = 0; y < resultImage.height(); ++y) {
        for (int x = 0; x < resultImage.width(); ++x) {
            QColor color = resultImage.pixelColor(x, y);

            // Инвертируем цвета
            int red = 255 - color.red();
            int green = 255 - color.green();
            int blue = 255 - color.blue();

            resultImage.setPixelColor(x, y, QColor(red, green, blue));
        }
    }
    return resultImage;
}

QImage ImageProcessor::processInHSV(const QImage &image) {
    QImage hsvImage = image.convertToFormat(QImage::Format_RGB32); // Конвертируем в формат для работы с HSV

    for (int y = 0; y < hsvImage.height(); ++y) {
        for (int x = 0; x < hsvImage.width(); ++x) {
            QColor color = QColor(hsvImage.pixel(x, y));

            // Преобразуем цвет в HSV
            int h, s, v;
            color.getHsv(&h, &s, &v);

            // Применяем обработку (например, увеличим яркость)
            v = std::min(v + 100, 255); // Увеличиваем яркость, но не выше 255

            // Устанавливаем новый цвет в HSV обратно
            color.setHsv(h, s, v);
            hsvImage.setPixel(x, y, color.rgb());
        }
    }

    return hsvImage;
}


QImage ImageProcessor::convertToGray(const QImage &image) {
    QImage grayImage(image.size(), QImage::Format_Grayscale8);

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor color = image.pixelColor(x, y);

            // Рассчитываем яркость по формуле: 0.3*R + 0.59*G + 0.11*B
            int gray = qGray(color.rgb());
            grayImage.setPixelColor(x, y, QColor(gray, gray, gray));
        }
    }
    return grayImage;
}

