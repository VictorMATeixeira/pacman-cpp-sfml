#include <iostream>

int main () {
    int n;


    std::cout << "Digite um numero e eu vou te dizer se ele e par ou impar: ";
    std::cin >> n;

    if (n%2 == 0) {
        std::cout << n << " e numero par" << std::endl;
    } else {
        std::cout << n << " numero impar" << std::endl;
    }

    return 0;
}