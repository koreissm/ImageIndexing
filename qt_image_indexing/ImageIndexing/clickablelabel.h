#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include "ui_mainwindow.h"
#include "mainwindow.h"


class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    ClickableLabel( const QString & text="", QWidget * parent = 0, char* filename = NULL, Ui::MainWindow* mainWindows = NULL);
    ~ClickableLabel(){}

signals:
    void clicked();

public slots:
    void slotClicked();

protected:
    void mousePressEvent ( QMouseEvent * event ) ;

private:
    char* _filename;
    Ui::MainWindow* _mainWindows;
};

#endif // CLICKABLELABEL_H
