// Created by Ethan Edwards on 10/11/2024
#include <iostream>
#include <vector>
#include <chrono> // For timing
#include <thread>
#include <mutex>
#include "mini-gmp/mini-gmp.h"

bool contains_all_four(std::vector<int> prev) {
    bool found[4] = {false, false, false, false};
    for (int c : prev) {
        if (c == 1) {
            found[0] = true;
        } else if (c == 2) {
            found[1] = true;
        } else if (c == 3) {
            found[2] = true;
        } else if (c == 4) {
            found[3] = true;
        }
    }
    return found[0] && found[1] && found[2] && found[3];
}

// Main function to recursively calculate number of valid strings of length n
void numStringsHelper(mpz_t& result, int n, int depth, std::vector<int> prev, int next){
    prev.push_back(next); // Add the next character to the previous characters

    if (depth == n) {
        if (contains_all_four(prev)) {
            mpz_add_ui(result, result, 1); // Increment the result by 1
        }
    }
    else {
        if (depth > 6) { // If the depth is less than 6 we are still building the window
            if (!contains_all_four(prev)) { // If the window does not contain all four characters, we can return early
                return;
            }
            prev.erase(prev.begin()); // Remove the first character from the window
        }
        for (int i = 1; i <= 4; i++) { // Recursively call the function for each possible next character
            numStringsHelper(result, n, depth + 1, prev, i);
        }
    }
}

// Caller target
void numStrings(int n, mpz_t& result) {
    mpz_set_ui(result, 0); // Initialize the result to 0

    for (int i = 1; i <= 4; i++) {
        std::vector<int> prev;
        numStringsHelper(result, n, 1, prev, i);
    }
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
