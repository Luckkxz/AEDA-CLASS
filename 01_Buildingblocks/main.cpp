#include <iostream>

template<typename T>
void static Swap(T & a, T & b) {
    T temp=a;
    a=b,
    b=temp;
}
void static Print(const int A[], int size) {
    for ( size_t i=0;i< size;i++){
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}
template<typename T>
void static Print2(const T& container) {
    for (auto element : container) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}
int main() {
    std::cout<<"Building Blocks !! " << std::endl;
    int A[]={8,9};
    Print(A,2);
    Swap(A[0],A[1]);
    Print(A,2);
    return 0;
}
