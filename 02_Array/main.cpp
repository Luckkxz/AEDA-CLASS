#include <iostream>
#include <array>
#include <format>

static void array_example_1() {
    std::array<int,9> x_vals = {100,200,300,400,500,600,700,800,900};
    std::cout << x_vals[0] << std::endl;
    for (int i=0;i<x_vals.size();i++) {
        std::cout << x_vals.at(i) << std::endl;
    }
    for (auto value: x_vals) {
        std::cout << value << " " ;
    }
    std::cout << std::endl;
    for (auto value: x_vals) {
        std::cout << std::format("{:6d}",value);
    }
    std::cout << std::endl;
    std::cout << x_vals[1] << std::endl;
    //iteradores
    for (auto it = x_vals.begin(); it != x_vals.end(); ++it) {
        std::cout << std::format("{:7d}",*it) ;
    }
    std::cout << std::endl;
    //iterador reverso
    for (auto it = x_vals.rbegin(); it != x_vals.rend(); ++it) {
        std::cout << std::format("{:5d}",*it) ;
    }
}
int main() {
    std::cout << " Arrays !!! " << std::endl;
    array_example_1();
    array_example_1();
    return 0;
}