#include <algorithm>
#include <format>
#include <iostream>
#include <array>


static void array_example_2() {

}
static void array_example_3() {
    std::array<double,8> radios{1.0,1.4,1.0,2.8,4.8,5.6,8.0,11.0};
    std::array<double,radios.size()> areas{};
    //calculo
    auto it_a =areas.begin();
    for (auto it_r = radios.begin();it_r != radios.end();++it_r,++it_a) {
        *it_a = std ::numbers::pi* *it_r * *it_r ;
    }
    //print
    it_a = areas.begin();
    for (auto it_r = radios.begin();it_r != radios.end();++it_r , ++it_a) {
        std::cout<< std::format("{:6.1f}{:12.6f}", *it_r , *it_a)<<std::endl;
    }
    std::cout <<std::format("{:6s} {:12s}","radios","areas");
}
static void array_example_4() {
    constexpr size_t epl_max{5};
    std::array<std::string ,15> colors_1{"red","green","blue","white","yellow","blue","cyan","magenta","black","gray","orange","purple","brown"};
    auto colors_2 {colors_1};
    print_container("colors_1",colors_1 , epl_max);
    print_container("colors_2",colors_2,epl_max);
    //sort
    std::sort(colors_1.begin(),colors_1.end());
    print_container("colors_1"(after sort):",colors_1, epl_max);")
    ///comparation
    std::cout  << std::format{"colors_1== colors_2: {:s}",colors_1 == oolors_2 <<std::endl}<<std::endl;
}
int main() {
    std::cout << "Arrays !!! " << std::endl;
    array_example_3();
    array_example_4();
    return 0;
}