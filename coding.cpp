// Created by: Axel Perez & Zami Alam

#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <tuple>

using namespace std;

// Function for modular exponentiation
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;  // Handle base larger than mod
    while (exp > 0) {
        if (exp % 2 == 1) {  // If exponent is odd
            result = (result * base) % mod;
        }
        exp = exp/2;  // Divide exponent by 2
        base = (base * base) % mod;  // Square the base
    }
    return result;
}

// Extended Euclidean Algorithm to find modular inverse
long long mod_inverse(long long e, long long phi) {
    long long t = 0, new_t = 1;
    long long r = phi, new_r = e;

    while (new_r != 0) {
        long long quotient = r / new_r;
        
        // Swap `t` and `new_t` using temporary variable
        long long temp_t = t;
        t = new_t;
        new_t = temp_t - quotient * new_t;

        // Swap `r` and `new_r` using temporary variable
        long long temp_r = r;
        r = new_r;
        new_r = temp_r - quotient * new_r;
    }

    // Ensure d is positive
    if (t < 0) {
        t += phi;
    }
    return t;
}

// Function to map number to custom character
char num_to_char(long long num) {
    if (num >= 7 && num <= 32) {
        return static_cast<char>('A' + (num - 7));
    }
    switch (num) {
        case 33: return ' ';
        case 34: return '"';
        case 35: return ',';
        case 36: return '.';
        case 37: return '\'';
        default: return '?';
    }
}

int main() {
    vector<int> numbers;
    string input;

    int e, n;

    if (!(cin >> e >> n)) {
        cout << "Public key is not valid" << endl;
        return 0;
    }

    int p = 0, q = 0;

    // Find P and Q
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            cout << "p = " << i << ", q = " << n / i << endl;
            p = i;
            q = n / i;
            break;
        }
    }

    // Calculate phi(n)
    int phi = (p - 1) * (q - 1);
    cout << "phi(n) = " << phi << endl;

    // Calculate d (modular inverse of e modulo phi)
    long long d = mod_inverse(e, phi);
    cout << "Private key (d) = " << d << endl;

    // Read encrypted numbers
    cin.clear();  // Clear error flags
    cin.ignore();  // Ignore the newline character in the buffer

    while (true) {
        getline(cin, input);
        
        // Break if the input is empty (user presses Enter without typing anything)
        if (input.empty()) {
            break;
        }
        
        stringstream ss(input);
        int number;
        
        while (ss >> number) {
            numbers.push_back(number);
        }
    }
    
    // Decrypt and print only the integer values first
    for (int num : numbers) {
        long long translation = mod_exp(num, d, n);
        cout << translation << " ";
    }
    cout << endl << endl;

    // Print the corresponding characters
    for (int num : numbers) {
        long long translation = mod_exp(num, d, n);
        char translated_char = num_to_char(translation);
        cout << translated_char;
    }

    cout << endl;

    return 0;
}
