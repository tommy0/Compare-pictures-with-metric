#include "ImagePng.h"

ImagePng::ImagePng(std::string name)
{
    this->name=name;
    png::image< png::rgb_pixel > image("image\\"+ name);
    hight=image.get_height();
    width=image.get_width();
}

void ImagePng::RGBAtoRGB()
{
    png::image< png::rgba_pixel > images("image\\"+ name);
    png::image< png::rgb_pixel > image("image\\"+ name);
    for(int i=0; i<images.get_height(); i++)
    {
        for(int j=0; j<images.get_width(); j++)
        {
            image[i][j]=png::rgb_pixel(255-images[i][j].red*images[i][j].alpha+(1-images[i][j].alpha)*255   ,
                                      255-image[i][j].green*images[i][j].alpha+(1-images[i][j].alpha)*255,
                                       255-image[i][j].blue*images[i][j].alpha+(1-images[i][j].alpha)*255);
        }
    }
    image.write("temp\\"+name);
}

void ImagePng::setBWImage()
{
    png::image< png::rgb_pixel > image("temp\\"+ name);
    for(int i=0; i<hight; i++)
    {
        for(int j=0; j<width; j++)
        {
            int x=image[i][j].red+image[i][j].green+image[i][j].blue;
            x=(x>(255*3/2)?255:0);
            //x=x/3;
            image[i][j] = png::rgb_pixel(x,x,x);
        }
    }
    image.write("temp\\"+name);
}

void ImagePng::resizeImage(int hight, int width)
{
    this->hight=hight;
    this->width=width;
    boost::gil::rgb8_image_t image;
    boost::gil::rgb8_image_t newSize(width, hight);
    boost::gil::png_read_image(("temp\\"+this->name),image);
    boost::gil::resize_view(const_view(image), view(newSize), boost::gil::bilinear_sampler());
    boost::gil::png_write_view(("temp\\"+this->name),const_view(newSize));
}

int ImagePng::getHight()
{
    return hight;
}

int ImagePng::getWidth()
{
    return width;
}

std::string ImagePng::getName()
{
    return name;
}

void ImagePng::fillColorMap()
{
    png::image< png::rgb_pixel > image("temp\\"+ name);
    for(int i=0; i<hight; i++)
    {
        for(int j=0; j<width; j++)
        {
            colormap.push_back(image[i][j].red);
        }
    }
}

long long ImagePng::operator-(ImagePng &second)
{
    long long sum=0;
    for(long long i=0; i<colormap.size(); ++i)
    {
        sum+=(colormap[i]-second.colormap[i])*(colormap[i]-second.colormap[i]);
    }
    return sum;
}
