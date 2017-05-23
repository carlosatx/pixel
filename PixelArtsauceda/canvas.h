#ifndef CANVAS_H
#define CANVAS_H

#include <QLabel>
#include "pixelcube.h"

class QGraphicsColorizeEffect;

class Canvas : public QLabel
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);
    void setPrimaryImage(QImage image) { m_primaryImage = image;}
    void setSecondaryImage(QImage image)
    {
        m_secondaryImage = image;
        m_pixcube.setPixmap(QPixmap::fromImage(m_secondaryImage));
        m_pixcube.setScaledContents(true);
    }
    void setCubeSize(int cubeSize)
    {
        m_cubeSize = cubeSize;
        m_pixcube.resize(cubeSize,cubeSize);
    }

private:
    void paintEvent(QPaintEvent *event);
    QImage m_primaryImage;
    QImage m_secondaryImage;
    PixelCube m_pixcube;
    int m_cubeSize = 0;
    QGraphicsColorizeEffect *m_effect = nullptr;
};

#endif // CANVAS_H
