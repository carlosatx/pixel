#ifndef PIXELCUBE_H
#define PIXELCUBE_H
#include <QWidget>
#include <QLabel>

class PixelCube: public QLabel
{
public:
    // constructors
    PixelCube(QWidget *parent = 0);
    // destructor
    ~PixelCube();

};

#endif // PIXELCUBE_H
