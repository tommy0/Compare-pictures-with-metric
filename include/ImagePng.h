#ifndef IMAGEPNG_H
#define IMAGEPNG_H

#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/extension/io/png_io.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include "../png/png.hpp"
#include <vector>

class ImagePng
{
    std::vector<int> colormap;
public:

    ImagePng(std::string name);

    void setBWImage();

    void RGBAtoRGB();

    void resizeImage(int hight, int width);

    int getHight();

    int getWidth();

    std::string getName();

    void fillColorMap();

    long long operator-(ImagePng &second);

private:
    std::string name;
    int hight;
    int width;
};

#endif // IMAGEPNG_H
