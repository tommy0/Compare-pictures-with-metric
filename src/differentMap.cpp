#include "differentMap.h"

differentMap::differentMap(ImageMap images)
{
    int vSize = images.getSize();
    for(int i=0; i<vSize; ++i)
    {
        inner_map temp;
        for(int j=0; j<vSize; ++j)
        {
            if(i<=j)
            {
                temp.insert(std::pair<std::string,long long>(images.ImagesMap[j].getName(), -1));
                continue;
            }
            long long diference=images.ImagesMap[i]-images.ImagesMap[j];
            temp.insert(std::pair<std::string,long long>(images.ImagesMap[j].getName(), diference));
        }
        different.insert(std::pair<std::string, inner_map>(images.ImagesMap[i].getName(), temp));
    }
}

long long differentMap::getMin(std::string &s1, std::string &s2)
{
    long long minimum=999999999999999;
    for( auto i=different.begin(); i!=different.end(); ++i)
    {
        for( auto j=i->second.begin(); j!=i->second.end(); ++j)
        {
            if(j->second == -1) continue;
            if(j->second<minimum)
            {
                minimum=j->second;
                s1=i->first;
                s2=j->first;
            }
        }
    }
    if (minimum ==999999999999999) minimum=-1;
    return minimum;
}

int differentMap::getSize()
{
    return different.size();
}

void differentMap::resolveDifferentMap(std::string s1, std::string s2)
{
    for(auto i=different.begin(); i!=different.end();++i)
    {
        if(different[s1][i->first]!=-1)
        {
            if(different[s2][i->first]!=-1)
            {
                different[s1][i->first]=std::min(different[s1][i->first],different[s2][i->first]);
            }
            else
            {
                different[s1][i->first]=std::min(different[s1][i->first],different[i->first][s2]);
            }
        }
        else
        {
            if(different[s2][i->first]!=-1)
            {
                different[i->first][s1]=std::min(different[s1][i->first],different[s2][i->first]);
            }
            else
            {
                different[i->first][s1]=std::min(different[s1][i->first],different[i->first][s2]);
            }
        }
    }
    different.erase(s2);
    for( auto i=different.begin(); i!=different.end(); ++i)
    {
        (i->second).erase(s2);
    }
}


void differentMap::outputDifferentMap()
{
    for(auto i=different.begin(); i!=different.end(); ++i)
    {
        for( auto j=i->second.begin(); j!=i->second.end(); ++j)
        {
            std::cout<<j->second<<" ";
        }
        std::cout<<std::endl;
    }
}
