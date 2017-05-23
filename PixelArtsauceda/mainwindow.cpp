#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pixelcube.h"

//Qt classes
#include <QFileDialog>
#include <QDebug>
#include <QStandardPaths>
#include <QMessageBox>
#include <QGraphicsColorizeEffect>
#include <QPainter>
#include <QPaintEvent>

//-- "parent" params. they are used when you want a windows hierarchy, say you have a main window
//-- and you want to construct smaller windows (QWidgets) inside it;
//-- when you create the small window you pass along the main window as the "parent" argument to the constructor.
//-- Then they are connected, so that the small window follows the big one around when you drag it or resize etc.

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_pUI(new Ui::MainWindow)
{
    m_pUI->setupUi(this);
    m_pUI->cubeSizeSlider->setValue(m_cubeSize);
    QObject::connect(m_pUI->cubeSizeSlider,SIGNAL(valueChanged(int)),this,SLOT(on_cubeSizeSlider_valueChanged(int)));
}

//--- Destructor when you exit the window it delete the heap declared memory
MainWindow::~MainWindow()
{
    delete m_pUI;
}

//--- On press Load Button

void MainWindow::on_btnLoad_clicked()
{
    //--- load the broswe image file
    QString fileName = QFileDialog::getOpenFileName(
                this,
                "Select an image",
                "",
                "Images (*.png *.jpg *.jpeg)");

    m_image.load(fileName); // -- load image
    m_pUI->viewPort->setPixmap(QPixmap::fromImage(m_image));//-- image set on the label of the disply window which shows on screen

    const QPixmap *pixmap = m_pUI->viewPort->pixmap();   //-- declare pointer of Qpixmap

    m_initialImage=  pixmap->toImage();     //--change pixmap to qimage


    //m_pUI->pathLineEdit->setText(m_initialImage.width);//could not output two strings

    m_initialImage = m_image;
    m_pUI->pathLineEdit->setText(fileName);

    m_pUI->btnPixelize->setEnabled(true);
    m_pUI->btnSave->setEnabled(true);
    m_pUI->btnArt->setEnabled(false);
    m_pUI->cubeSizeSlider->setEnabled(true);
}


//-- On save button

void MainWindow::on_btnSave_clicked()
{
    //-- choose the file path where you want to save  ----

    QString imagePath = QFileDialog::getSaveFileName(this,tr("Save File"),"",
                                                     tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));

    QImage currentImage;
    const QPixmap *pixmap = m_pUI->viewPort->pixmap();  // set the pixelize image on pointer of pixmap
    if ( pixmap )
    {
        currentImage =  pixmap->toImage();  // -- use pointer of pixmap ,convert to image and set on image1
    }
    bool isSaved =  currentImage.save(imagePath);  //-- save the final image on the selected path

    qDebug() << isSaved;

    if(isSaved)
    {
        QMessageBox::information(this,"File Saved","File saved successfully.");
    }
    else
    {
        QMessageBox::warning(this,"Warning","Error while saving the file.");
    }


}

//-- On Exit button

void MainWindow::on_btnExit_clicked()
{
    //--- Close the Application
    QApplication::quit();
}

//-- On pixelize button --

void MainWindow::on_btnPixelize_clicked()
{
    QImage image1;
    const QPixmap *pixmap = m_pUI->viewPort->pixmap();  //-- get address of image from the label where image is placed
    if ( pixmap )
    {
        image1=  pixmap->toImage(); // convert the address of image to the real image
    }
    image1 = m_initialImage;  //-- set the first time loaded image to the image1
    m_pix.pixelize_image(image1);  // -- increase the pixel of that image

    m_pUI->viewPort->setPrimaryImage(m_pix.get_pixelized_image());   //-- after increase pixels, again show to window
    m_pUI->viewPort->update();
    m_pUI->btnArt->setEnabled(true);
}

//--- set the size of pixel
void MainWindow::on_cubeSizeSlider_valueChanged(int arg1)
{
    if (arg1==0)
    {
        arg1=1;
    }
    m_pix.set_cubeSize(arg1);

}

//--- On art Button ---

void MainWindow::on_btnArt_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(
                this,
                "Select an image",
                QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
                "Images (*.png *.jpg *.jpeg)");

    QImage artItImage;
    if (!fileName.isEmpty())   //-- if filename is not empty
    {
        bool valid = artItImage.load(fileName); // -- load image
        if (!valid)  //-- check image valid
        {
            QMessageBox::warning(this,"Warning","Error while loading the file.");
            return;
        }
    }

    int pixelCubeSize = m_pix.get_cubeSize();
    m_pUI->viewPort->setCubeSize(pixelCubeSize);

    m_pUI->viewPort->setSecondaryImage(artItImage);
    m_pUI->viewPort->update(); // To repaint the canvas. This called paintEvent of Canvas.
}
