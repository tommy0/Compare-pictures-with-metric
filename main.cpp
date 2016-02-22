#include <iostream>
#include <vector>
#include <map>
#include "ImageMap.h"
#include "differentMap.h"
#include <windows.h>
#include <sstream>

void input(ImageMap &images)
{
    WIN32_FIND_DATA FindFileData;
    HANDLE hf;
    hf = FindFirstFile("image\\*.png",&FindFileData);
    if(hf != INVALID_HANDLE_VALUE)
    {
        do
        {
            images.addToImageMap(ImagePng(FindFileData.cFileName));
        }
        while(FindNextFile(hf,&FindFileData) != 0);
        FindClose(hf);
    }
}

void clusterization(differentMap dif,ImageMap images, std::map<std::string,std::vector<std::string>> &result)
{
    unsigned long long int C=images.getMeanHight()*images.getMeanWidth()*255*255*0.2;
    if(C>1000000000) C=1000000000;
    unsigned long long Min;
    std::string s1,s2;
    while(dif.getSize()>1)
    {
        //dif.outputDifferentMap();
        Min=dif.getMin(s1,s2);
        if(Min==-1) break;
        dif.resolveDifferentMap(s1,s2);
        if(Min<C)
        {
            if (result.count(s1)>0)
            {
                result[s1].push_back(s2);
            }
            else
            {
                std::vector<std::string> temp;
                temp.push_back(s1);
                temp.push_back(s2);
                result.insert(std::pair<std::string,std::vector<std::string>>(s1,temp));
            }
        }
        else
        {
            std::vector<std::string> temp;
            if(result.count(s1)<=0)
            {
                temp.push_back(s1);
                result.insert(std::pair<std::string,std::vector<std::string>>(s1,temp));
            }
            if(result.count(s2)<=0)
            {
                temp.clear();
                temp.push_back(s2);
                result.insert(std::pair<std::string,std::vector<std::string>>(s2,temp));
            }
        }
    }
    for(auto i=result.begin(); i!=result.end(); ++i)
    {
        for(auto j=(i->second).begin(); j!=(i->second).end(); ++j)
        {
            if((i->first)==*j) continue;
            if(result.count(*j)>0)
            {
                for(auto k=result[*j].begin(); k!=result[*j].end(); ++k)
                {
                    result[i->first].push_back(*k);
                }
                result.erase(*j);
            }
        }
    }
}

void output(std::map<std::string,std::vector<std::string>> result)
{
    boost::filesystem::remove_all("result");
    boost::filesystem::create_directory("result");
    int k=0;
    std::ostringstream s;
    for(auto i=result.begin(); i!=result.end(); ++i)
    {
        s.clear();
        s.str("");
        s<<k;
        std::string temp(s.str());
        boost::filesystem::create_directory("result\\"+temp);
        for(auto j=(i->second).begin(); j!=(i->second).end(); ++j)
        {
            boost::filesystem::copy("image\\"+(*j),"result\\"+temp+"\\"+(*j));
        }
        ++k;
    }
}

void outputFileName(std::map<std::string,std::vector<std::string>> result)
{
    for(auto i=result.begin(); i!=result.end(); ++i)
    {
        for(auto j=(i->second).begin(); j!=(i->second).end(); ++j)
        {
            std::cout<<*j<<" ";
        }
        std::cout<<std::endl;
    }

}

int main()
{
    ImageMap images;
    input(images);
    images.toRGB();
    images.toOneSize();
    images.toOneColor();
    images.fillColorMap();
    differentMap dif(images);
    std::map<std::string,std::vector<std::string>> result;
    clusterization(dif,images,result);
    //outputFileName(result);
    output(result);
    return 0;
}
