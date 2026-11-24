#include <stdio.h>
#define PI 3.14
#define SQUARE(x) ((x)*(x))

// Test comment
int main() {
    /* Multi-line comment */
    double area = PI * SQUARE(5);
    printf("Area: %f\n", area);
    return 0;
}
