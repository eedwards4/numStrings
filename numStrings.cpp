// Created by Ethan Edwards on 10/11/2024
#include <iostream>
#include <vector>
#include <chrono> // For timing
#include "mini-gmp/mini-gmp.h"

const std::vector<int> alphabet = {'a', 'b', 'c', 'd'};

// Determine if a state is valid
bool isValid(std::vector<int>& v){
    std::vector<bool> found (4, false);
    for (int i : v){
        if (i == 1){
            found[0] = true;
        } else if (i == 2){
            found[1] = true;
        } else if (i == 3){
            found[2] = true;
        } else if (i == 4){
            found[3] = true;
        }
    }
    return found[0] && found[1] && found[2] && found[3];
}

// Main function to recursively calculate number of valid strings of length n
void numStringsHelper(mpz_t& result, int n, int depth, std::vector<int> prev_5){

}

// Caller target
void numStrings(int n, mpz_t& result) {
    mpz_set_ui(result, 0); // Initialize the result to 0
}

int main() {
    std::cout << "Please input the number: ";
    int num;
    std::cin >> num;
    if (num < 4 || num > 300) {
        std::cout << "The number must be between 1 and 300." << std::endl;
        return 1;
    }

    // Start timing
    auto start = std::chrono::high_resolution_clock::now();

    mpz_t result;
    mpz_init(result); // Initialize the Mini-GMP variable

    // Calculate the solution
    numStrings(num, result);

    // Output the solution
    std::cout << "n = " << num << "     ";
    mpz_out_str(stdout, 10, result); // Output the result in decimal format
    std::cout << std::endl;

    // Stop timing
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "\nElapsed time: " << elapsed.count() << " seconds\n";

    mpz_clear(result); // Clear the Mini-GMP variable
    return 0;
}
