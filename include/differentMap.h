#ifndef DIFFERENTMAP_H
#define DIFFERENTMAP_H

#include <iostream>
#include <map>
#include <cmath>
#include "ImageMap.h"

typedef std::map<std::string,long long> inner_map;
typedef std::map<std::string, inner_map> outer_map;

class differentMap
{
    outer_map different;
public:
    differentMap(ImageMap images);

    long long getMin(std::string &s1, std::string &s2);

    int getSize();

    void resolveDifferentMap(std::string s1, std::string s2);

    void outputDifferentMap();
};

#endif // DIFFERENTMAP_H
