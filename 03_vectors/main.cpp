#include <cmath>
#include <iostream>
#include <vector>
#include <format>

#include "../01_Buildingblocks/helpers.h"
static void vector_example_1 () {
    std::vector<int> v1{10,20,30,40,50};
    std::vector<int> v2(v1.size());
    std::vector<int> v3(v1.size(),7);
    print_container("v1:",v1);
    print_container("v2(initial values):",v2);
    print_container("v3:",v3);
    //operator[],at()
    for (size_t i=0;i<v1.size();++i) {
        v2[i] = v1[i]*v3.at(i);
    }
    print_container("v2 (after operation):",v2);
    //more vectors
    std::vector<unsigned long long> v4{100,200,300,400,500,600,700,800};
    std::vector<unsigned long long> v5 (v4.size(),100);
    std::vector <unsigned long long> v6 (v4.size());
    std::vector <unsigned long long> v7 {};
    print_container("v4 : ",v4);
    print_container("v5 : ",v5);
    print_container("v6 : ",v6);
    print_container("v7 : ",v7);
    // iteradores
    auto it4 = v4.begin();
    auto it5 = v5.begin();
    for (; it4 != v4.end(); ++it4, ++it5) {
        *it5 = *it4 /2;
    }
    print_container("v5 (after operation) : ",v5);
    //front(),back()
    std::cout <<std::format("v4.front(): {:6d}",v4.front()) <<std::endl;
    std::cout <<std::format("v4.back(): {:6d}",v4.back()) <<std::endl;
    //clear()
    v5.clear();
    print_container("v5 (after clear) : ",v5);
}
static void vector_example_2 () {
    constexpr size_t n{10};
    std::vector<double> v1{};
    //psuh_back
    for (size_t i=0;i<n;++i) {
        v1.push_back(std::sqrt(i+1));
    }
    print_container("v1 (initial values ) : " ,v1);
    while (v1.size()>= n/2) {
        v1.pop_back();
    }
    print_container("v1 (after pop_back ) : ",v1);
    // add elements
    std::array<double,n> a1{10,20,30,40,50,60,70,80,90,100};
    v1.insert(v1.begin() +2,a1.begin(),a1.end());
    print_container("v1 (after insert ) : ",v1);
    //add elements
    std::array<double,6>a2{-10.0,-20.0,-30.0,-40.0,-50.0,-60.0};
    v1.insert(v1.end(),a2.begin(),a2.end());
    print_container("v1 (after 2nd insert ) : ",v1);
    //remove
    v1.erase(v1.begin() +3,v1.begin()+5);
    print_container("v1 (after erase ) : ",v1);
    }
int main() {
    std::cout << "Vectors !! " << std::endl;
    vector_example_1();
    vector_example_2();
    return 0;
}
