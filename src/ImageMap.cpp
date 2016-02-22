#include "ImageMap.h"

ImageMap::ImageMap()
{
    std::vector<ImagePng> ImagesMap;
    boost::filesystem::create_directory("temp");
}

ImageMap::~ImageMap()
{
    boost::filesystem::remove_all("temp");
}

void ImageMap::addToImageMap(ImagePng image)
{
    ImagesMap.push_back(image);
}

void ImageMap::toOneSize()
{
    meanHight=0;
    meanWidth=0;
    for(unsigned int i=0; i<ImagesMap.size(); ++i)
    {
        meanHight+=ImagesMap[i].getHight();
        meanWidth+=ImagesMap[i].getWidth();
    }
    meanHight=round((double(meanHight))/ImagesMap.size());
    meanWidth=round((double(meanWidth))/ImagesMap.size());
    for(unsigned int i=0; i<ImagesMap.size(); ++i)
    {
        ImagesMap[i].resizeImage(meanHight,meanWidth);
    }
}

void ImageMap::toRGB()
{
    for(unsigned int i=0; i<ImagesMap.size(); ++i)
    {
        ImagesMap[i].RGBAtoRGB();
    }
}

void ImageMap::toOneColor()
{
    for(unsigned int i=0; i<ImagesMap.size(); ++i)
    {
        ImagesMap[i].setBWImage();
    }
}

void ImageMap::fillColorMap()
{
    for(unsigned int i=0; i<ImagesMap.size(); ++i)
    {
        ImagesMap[i].fillColorMap();
    }
}

int ImageMap::getSize()
{
    return ImagesMap.size();
}

int ImageMap::getMeanHight()
{
    return meanHight;
}

int ImageMap::getMeanWidth()
{
    return meanWidth;
}

