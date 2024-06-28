#include "include/pseudorandom.h"


#include <vector>


int linearCongruent(int previous, int a, int c, int m){
    return (a * previous + c) % m;
}

std::vector<double> linearCongruentSeq(int size, double seed, double a, double c, double m){
    std::vector<double> result;
    double previous {0};

    for (int i {0}; i < size; ++i){
        if (i==0){
            previous = linearCongruent(seed, a, c, m);
            result.push_back(previous);
        }
        else{
            previous = linearCongruent(previous, a, c, m);
            result.push_back(previous);
        }
    }
    return result;
}
