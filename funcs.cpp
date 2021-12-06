//https://contest.yandex.ru/contest/27794/problems/J/

#include "funcs.h"
#include <bits/stdc++.h>

void parseFile(std::istream & input, std::ostream & output){

    int k;
    input >> k;
    std::vector<std::pair<int,int>> points(k);
    for(int i = 0; i<k; ++i){
        input >> points[i].first >> points[i].second;
    }

    std::vector<std::vector<unsigned long int>>
        squareDists(k,std::vector<unsigned long int>(k));

    long dx, dy;
    for(int i = 0; i < k; ++i){
        for(int j = i+1; j<k; ++j){
            dx = points[i].first-points[j].first;
            dy = points[i].second-points[j].second;
            squareDists[i][j] = dx*dx + dy*dy;
            squareDists[j][i] = squareDists[i][j];
        }
    }

    unsigned long int equilaterals = 0, triangles = 0;
    for(int i = 0; i<k; ++i){
        //! @brief dist - index i
        std::map<unsigned long int, std::vector<int>> dists;
        for(int j = 0; j<k; ++j){
            auto dist = squareDists[i][j];
            for(auto index : dists[dist]){
                //check triangle:
                auto distB = squareDists[index][j];
                if(distB == dist){
                    ++equilaterals;
                    ++triangles;
                } else {
                    auto a = sqrt(dist);
                    auto b = sqrt(distB);
                    std::array<double,3> sides = {a, a, b};
                    std::sort(sides.begin(),sides.end());
                    if(sides[0]+sides[1]>sides[2]){
                        ++triangles;
                    }
                }
            }
            dists[dist].push_back(j);
        }
    }

    triangles -= 2*equilaterals/3;

    output << triangles;
}
