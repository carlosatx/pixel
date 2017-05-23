#include "pixelize.h"
#include"QImage"
#include"QDebug"
#include"pixelcube.h"

//-- constructor for pixelize
Pixelize::Pixelize()
{
    Pixelize::m_cubeSize = 5;
}

// set image for the pixelized
void Pixelize::set_pixelized_image(QImage img)
{
    m_image = img;
}

//-- set the new pixel size
void Pixelize::set_cubeSize(int size)
{
    m_cubeSize = size;
}

//-- get the new pixel siize
int Pixelize::get_cubeSize()
{
    return m_cubeSize;
}

//-- get the pixelized image --
QImage Pixelize::get_pixelized_image()
{
    return m_image;
}

void Pixelize::pixelize_image(QImage img)
{

    int pixelationAmount = m_cubeSize; //you can change it!! //-- set the pixel size
    int width = img.width();  //-- get iimage width
    int height = img.height();  //-- get iimage height
    int avR,avB,avG,avA; // store average of rgb
    // int pixel;

    for(int x = 0; x < width; x+= pixelationAmount)
    { // do the whole image   //--- increase width by each pixel
        for(int y = 0; y < height; y+= pixelationAmount)
        {   //--- increase height by each pixel
            avR = 0; avG = 0; avB =0; avA = 0;


            int bx = x + pixelationAmount;  // -- update by each pixel on width wise
            int by = y + pixelationAmount;  // -- update by each pixel on height wise

            if(by >= height)        //--- if by is greater than whole image height then set exact height
                by = height;

            if(bx >= width)         //--- if bx is greater than whole image width then set exact width
                bx = width;

            //----- in Loops // -- get the colors values in each pixel (red,green,blue,alpha)
            for(int xx =x; xx < bx;xx++)
            {
                for(int yy= y; yy < by;yy++)
                {       // this is scanning the colors
                    //pixel = img.pixel(xx,yy);
                    QColor color(img.pixel(xx,yy));
                    avR += color.red();
                    avA += color.alpha();
                    avG += color.green();
                    avB += color.blue();
                }
            }

            //--- divide all by the amount of samples taken to get an average

            //-- take avg value of color from two pixel

            avR/= pixelationAmount*pixelationAmount;
            avG/= pixelationAmount*pixelationAmount;
            avB/= pixelationAmount*pixelationAmount;
            avA/= pixelationAmount*pixelationAmount;

            for(int xx =x; xx < bx;xx++)// YOU WILL WANT TO PUT SOME OUT OF BOUNDS CHECKING HERE
            {
                for(int yy= y; yy <by;yy++)
                {
                    //--- set the colors value on pixels

                    QColor color;
                    color.setBlue(avB);
                    color.setGreen(avG);
                    color.setAlpha(avA);
                    color.setRed(avR);
                    img.setPixelColor(xx,yy,color);
                }
            }
        }

        //-- again set the image on the label of window for the display

        Pixelize::set_pixelized_image(img);
    }
}
