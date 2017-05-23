#include "canvas.h"
#include <QPainter>
#include <QGraphicsColorizeEffect>
#include <QDebug>
Canvas::Canvas(QWidget *parent) : QLabel(parent)
{
     m_effect = new QGraphicsColorizeEffect(this);


}

void Canvas::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    if(m_primaryImage.isNull())
    {
        return;
    }
    QPainter painter(this); //creates the painter object
    int height = m_primaryImage.size().height();//find heigh of original image
    int width = m_primaryImage.size().width();// find width of original image
    QRect rect(0,0,width, height);// create  a rectangle for the drawing area as per the image size or else it will draw in the whole canvas
    painter.drawImage(rect,m_primaryImage);//draws the image on the canvas in specified region

    if(m_secondaryImage.isNull())
    {
        qDebug()<<"m_secondaryImage null";
        return;
    }

    for(int x = 0; x < width; x+= m_cubeSize)
    {    // do the whole image

        for(int y = 0; y < height; y+= m_cubeSize)    //--- increase height by each pixel
        {
            m_effect->setColor(QColor(m_primaryImage.pixel(x,y)));
            m_pixcube.setGraphicsEffect(m_effect); //colorizes image to pixel cube color
            painter.drawImage(x,y,m_pixcube.grab().toImage());
        }
    }
}
