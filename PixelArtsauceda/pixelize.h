#ifndef PIXELIZE_H
#define PIXELIZE_H

#include<QImage>
#include<pixelcube.h>

class Pixelize
{
public:
    Pixelize();

    //-- settor for the pixel size
    void set_cubeSize(int size);

    //-- get the pixel size
    int get_cubeSize();

    //--- pixelize image
    void pixelize_image(QImage img);

    //--- set the image to pixelize
    void set_pixelized_image(QImage img);

    //-- get the pixelized image
    QImage get_pixelized_image();

    //--- get the colors values
    int get_cube_red_color();
    int get_cube_green_color();
    int get_cube_blue_color();
    int get_cube_alpha_color();
    int m_cubeSize = 0;

private:
    QImage m_image;

};

#endif // PIXELIZE_H
