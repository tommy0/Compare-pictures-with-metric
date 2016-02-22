#ifndef IMAGEMAP_H
#define IMAGEMAP_H
#include "ImagePng.h"
#include <vector>
#include <boost/filesystem.hpp>

class ImageMap
{
public:
    std::vector<ImagePng> ImagesMap;

    ImageMap();

    ~ImageMap();

    void addToImageMap(ImagePng image);

    void toRGB();

    void toOneSize();

    void toOneColor();

    void fillColorMap();

    int getSize();

    int getMeanHight();

    int getMeanWidth();

private:
    int meanHight;
    int meanWidth;
};

#endif // IMAGEMAP_H
