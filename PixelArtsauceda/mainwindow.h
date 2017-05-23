#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include<qdebug.h>
#include <QString>
#include <QImage>
#include "pixelize.h"
#include "pixelcube.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);   //--- constructor
    ~MainWindow();                  //--- destructor

private slots:
    void on_btnLoad_clicked();      //-- click handler for load button

    void on_btnSave_clicked();      //-- click handler for save button

    void on_btnExit_clicked();      //-- click handler for exit button

    void on_btnPixelize_clicked();  //-- click handler for pixelize button

    void on_cubeSizeSlider_valueChanged(int);   //--- value cahnge handler for slider

    void on_btnArt_clicked();       //-- click handler for art it button

private:
    Ui::MainWindow *m_pUI;  //-- pointer of GUI main window
    int m_cubeSize = 5;     //-- input from user for the size of each pixel
    QImage m_image;         //-- for new image after pixelize
    QImage m_initialImage;  //-- for initial image
    Pixelize m_pix;         //-- for each new pixel size

};

#endif // MAINWINDOW_H
