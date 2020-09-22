#include "class_name.hpp"

int main() {
    double x = 2;
    double y = 2;
    int n = 4;

    TestCalc my_product;
    my_product.initialize(x, y, n);
    my_product.calculations1();
    // my_product.calculations2();
}
