#include "clickablelabel.h"

ClickableLabel::ClickableLabel( const QString & text, QWidget * parent, char* filename, Ui::MainWindow* mainWindows)
    :QLabel(parent)
    {
        _filename = new char[80];
        sprintf(_filename, "%s", filename);
        _mainWindows = mainWindows;
        connect( this, SIGNAL( clicked() ), this, SLOT( slotClicked() ) );
}

void ClickableLabel::slotClicked(){
        printf("Clicked.. %s\n", _filename);
        QImage img1;
        img1.load(_filename);
        _mainWindows->img_1->setPixmap(QPixmap::fromImage(img1));
        _mainWindows->label->setText(_filename);
        _mainWindows->tabWidget->setCurrentIndex(0);
}

void ClickableLabel::mousePressEvent ( QMouseEvent * event ){
        emit clicked();
}
