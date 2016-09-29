#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QScrollArea>
#include <QLabel>
#include <dirent.h>
#include <QRegularExpression>

#include "clickablelabel.h"
#include "/Users/Zera/Documents/git_project/ImageIndexing/libs/Distance.h"
#include "/Users/Zera/Documents/git_project/ImageIndexing/libs/ImageProcessingTools.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void loadImages(char* directory_path);
    ~MainWindow();

private slots:
    void handleButton();

private:
    Ui::MainWindow *ui;
    QImage img1;
    QImage img2;
    QGridLayout *_gdlayout;
};

#endif // MAINWINDOW_H
