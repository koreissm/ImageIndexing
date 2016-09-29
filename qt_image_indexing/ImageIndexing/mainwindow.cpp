#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->label->hide();

    //img1.load("/Users/Zera/Documents/git_project/ImageIndexing/imagesJPG/vache1.jpg");
    //ui->img_1->setPixmap(QPixmap::fromImage(img1));

    //loadImages("/Users/Zera/Documents/git_project/ImageIndexing/imagesJPG/");
    loadImages("/Users/Zera/Documents/git_project/ImageIndexing/big_imagesJPG/");
    connect(ui->pushButton, SIGNAL (released()), this, SLOT (handleButton()));
}

void MainWindow::loadImages(char *directory_path){

    DIR* dir = opendir(directory_path);
    struct dirent* dp;

    char* buffer = new char[100];
    int row = 0, col = 0;
    _gdlayout = new QGridLayout;

    while ((dp = readdir(dir)) != NULL){
        QRegularExpression re(".*jpg$");
        QRegularExpressionMatch match = re.match(dp->d_name);
        if(match.hasMatch()){
            sprintf(buffer, "%s%s", directory_path, dp->d_name);
            QImage image;
            image.load(buffer);
            ClickableLabel *labelImage = new ClickableLabel("", this, buffer, ui);
            labelImage->setPixmap(QPixmap::fromImage(image));
            labelImage->setFixedSize(250,250);
            labelImage->setScaledContents( true );
            labelImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
            _gdlayout->addWidget(labelImage,row,col);
            col++;
            if(col==4){
                row++;
                col=0;
            }
        }
    }
    ui->scrollAreaWidgetContents->setLayout(_gdlayout);
    ui->scrollArea->setWidgetResizable(true);
}

void MainWindow::handleButton()
{

    Distance distance(256);
    char* baseImageName = "/Users/Zera/Documents/git_project/ImageIndexing/big_imagesJPG/71.jpg";
    char* cstr;
    string fname = ui->label->text().toStdString();
    cstr = new char [fname.size()+1];
    strcpy( cstr, fname.c_str() );
    char ** similarImages = distance.getSimilarImages(cstr);
    for (int i = 0; i < 5; i++) {
        printf("%s\n", similarImages[i]);
    }
    QImage imgF_s1;QImage imgF_s2;QImage imgF_s3;QImage imgF_s4;QImage imgF_s5;
    imgF_s1.load(similarImages[4]);
    imgF_s2.load(similarImages[3]);
    imgF_s3.load(similarImages[2]);
    imgF_s4.load(similarImages[1]);
    imgF_s5.load(similarImages[0]);
    ui->img_s1->setPixmap(QPixmap::fromImage(imgF_s1));
    ui->img_s2->setPixmap(QPixmap::fromImage(imgF_s2));
    ui->img_s3->setPixmap(QPixmap::fromImage(imgF_s3));
    ui->img_s4->setPixmap(QPixmap::fromImage(imgF_s4));
    ui->img_s5->setPixmap(QPixmap::fromImage(imgF_s5));
}

MainWindow::~MainWindow()
{
    delete ui;
}
