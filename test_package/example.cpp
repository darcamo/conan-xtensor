#include <iostream>
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xview.hpp>

#include <xtensor/xmath.hpp>

#include <xtensor/xrandom.hpp>

#include <xtensor/xbuilder.hpp>

#include <vector>
#include "xtensor/xbroadcast.hpp"

#include <algorithm>

int main(int argc, char *argv[])
{
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // Initialize a 2-D array and compute the sum of one of its rows and a 1-D array
    xt::xarray<double> arr1
        {{1.0, 2.0, 3.0},
         {2.0, 5.0, 7.0},
         {2.0, 5.0, 7.0}};

    xt::xarray<double> arr2
        {5.0, 6.0, 7.0};

    std::cout << xt::view(arr1, 1) + arr2;;

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // Initialize a 1-D array and reshape it inplace
    xt::xarray<int> arr
        {1, 2, 3, 4, 5, 6, 7, 8, 9};

    arr.reshape({3, 3});

    std::cout << arr;

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // Broadcasting the xt::pow universal functions
    xt::xarray<double> arr3
        {1.0, 2.0, 3.0};

    xt::xarray<unsigned int> arr4
        {4, 5, 6, 7};

    arr4.reshape({4, 1});

    std::cout << xt::pow(arr3, arr4);

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // Random arrays with the random module
    xt::xarray<double> arr5 = xt::random::randn<double>({4, 3});
    std::cout << arr5;

    std::cout << xt::random::randn<double>({4, 3});

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // Using linspace, arange, ones, zeros
    xt::xarray<double> ar = xt::linspace<double>(0.0, 10.0, 12);
    ar.reshape({4, 3});
    std::cout << ar;

    xt::xarray<double> fones = xt::ones<float>({2, 2});
    std::cout << fones;

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // Using xt::broadcast
    std::cout << xt::broadcast(xt::linspace<double>(0.0, 10.0, 4),
                               std::vector<std::size_t>({3, 4}));

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // Using standard algorithms with xexpressions
    xt::xarray<double> frand = xt::random::randn<double>({2, 2});

    std::cout << frand << std::endl << std::endl;

// begin() and end() provide and iterator pair iterating over the xexpression in a row-major fashion
    std::cout << std::accumulate(frand.begin(), frand.end(), 0.0);

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // Iterating over a prescribed broadcasted shape
    // begin(shape) and end(shape) provide and iterator pair iterating
    // over the xexpression broadcasted to the prescrived shape in a row-major fashion
    std::vector<std::size_t> shape = {3, 2, 2};
    std::cout << std::accumulate(frand.begin(shape), frand.end(shape), 0.0);

    return 0;
}
