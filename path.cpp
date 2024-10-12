//
// Created by evane on 10/11/2024.
//

#include "path.h"

const int ALPHABET_SIZE = 4; // 'a', 'b', 'c', 'd'
const int MASK_ALL = (1 << ALPHABET_SIZE) - 1; // Mask for 'abcd' = 1111 (binary)

// Function to update mask with a character
int updateMask(int mask, char c) {
    return mask | (1 << (c - 'a')); // Update the mask for character c
}

// Function to check if the mask contains all characters
bool hasAllCharacters(int mask) {
    return (mask & MASK_ALL) == MASK_ALL; // Check if all characters are present
}

void numStrings(int n, mpz_t& result) {
    // Dynamic allocation of DP table with mpz_t type
    mpz_t** dp = new mpz_t*[n + 1];
    for (int i = 0; i <= n; ++i) {
        dp[i] = new mpz_t[16];
        for (int j = 0; j < 16; ++j) {
            mpz_init(dp[i][j]); // Initialize each element to 0
        }
    }
    mpz_set_ui(dp[0][0], 1); // Base case: 1 way to have a length of 0 with an empty mask

    // Iterate through lengths of the string
    for (int length = 0; length < n; ++length) {
        for (int mask = 0; mask < 16; ++mask) {
            // If we have any valid strings for this length and mask
            if (mpz_cmp_ui(dp[length][mask], 0) > 0) {
                for (char c = 'a'; c <= 'd'; ++c) {
                    int newMask = updateMask(mask, c);
                    mpz_add(dp[length + 1][newMask], dp[length + 1][newMask], dp[length][mask]); // Transition to the next length with the new character
                }
            }
        }
    }

    // Calculate the valid strings of length n that contain all characters
    mpz_t totalValidStrings;
    mpz_init(totalValidStrings); // Initialize to 0
    for (int mask = 0; mask < 16; ++mask) {
        if (hasAllCharacters(mask)) {
            mpz_add(totalValidStrings, totalValidStrings, dp[n][mask]); // Sum valid permutations of length n
        }
    }

    // Set the result in Mini-GMP format
    mpz_set(result, totalValidStrings);

    // Deallocate the DP table
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < 16; ++j) {
            mpz_clear(dp[i][j]); // Clear mpz_t values
        }
        delete[] dp[i];
    }
    delete[] dp;

    mpz_clear(totalValidStrings); // Clear totalValidStrings variable
}

// 144518781838828768850216
// 5192294765144295951433911702741624
// 1977534936356037866334857000386560

const std::vector<int> ALPHABET = {1, 2, 3, 4}; // The alphabet

bool isValid(std::vector<int>& v) { // Compare the sum of the vector to the mask
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

// Function to generate all permutations of a string recursively
void numStrings(mpz_t& result, int n, int depth, std::vector<int> prev_5){
    if (depth > 5){
        prev_5.erase(prev_5.begin()); // Remove the first element of the vector
    }
    if (depth == n){
        for (int i : ALPHABET){
            prev_5.push_back(i); // Add the current letter to the vector
            if (isValid(prev_5)){ // If the vector is valid, increment the result
                mpz_add_ui(result, result, 1);
            }
            prev_5.pop_back(); // Remove the current letter from the vector
        }
        return; // Return early on the base case
    }
    for (int i : ALPHABET){
        prev_5.push_back(i); // Add the current letter to the vector
        if (isValid(prev_5)){
            numStrings(result, n, depth + 1, prev_5); // Recursively call the function
        }
        prev_5.pop_back(); // Remove the current letter from the vector
    }
}

// Function to calculate the number of strings
void numStrings_helper(mpz_t& result, int n) {
    // Generate all permutations of the string up to the minimum size (5)
    if (n < 4) { return; } // If the string is less than 5 characters, there are no valid permutations
    std::vector<std::vector<int>> initial_permutations;
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            for (int k = 1; k <= 4; k++) {
                for (int l = 1; l <= 4; l++) {
                    for (int m = 1; m <= 4; m++) {
                        std::vector<int> tmp = {i, j, k, l, m};
                        if (isValid(tmp)){
                            initial_permutations.push_back(tmp);
                        }
                    }
                }
            }
        }
    }

    // Enter recursive function to generate all permutations of the string
    for (auto & initial_permutation : initial_permutations) {
        numStrings(result, n, 5, initial_permutation);
    }
}
