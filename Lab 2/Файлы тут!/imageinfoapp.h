#ifndef IMAGEINFOAPP_H
#define IMAGEINFOAPP_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include <QStringList>

class ImageInfoApp : public QMainWindow {
    Q_OBJECT

public:
    explicit ImageInfoApp(QWidget *parent = nullptr);
private slots:
    void loadImagesFromFolder();
    void processImageFile(const QString &filePath);
    void onTableRowClicked(int row, int column);
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    QTableWidget *table;
    QLabel *imageLabel;
    QLabel *dragDropLabel; // Новая метка для перетаскивания
    QStringList imageFilePaths; // Список путей к изображениям
};

#endif // IMAGEINFOAPP_H
