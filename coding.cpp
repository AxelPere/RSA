#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

// Function for modular exponentiation
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;  // Handle base larger than mod
    while (exp > 0) {
        if (exp % 2 == 1) {  // If exponent is odd
            result = (result * base) % mod;
        }
        exp = exp >> 1;  // Divide exponent by 2
        base = (base * base) % mod;  // Square the base
    }
    return result;
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

    int e, n, m;

    if (!(cin >> e >> n >> m)) {
        cout << "Public key is not valid" << endl;
        return 0;
    }

    
    while (true) {
        getline(cin, input);
        
        // Break if the input is empty (user presses Enter without typing anything)
        if (input.empty()) {
            break;
        }
        
        // Create a stringstream from the input string to extract each number
        stringstream ss(input);
        int number;
        
        // Read numbers from the stringstream and add them to the vector
        while (ss >> number) {
            numbers.push_back(number);
        }
    }
    
    for (int num : numbers) {
        long long translation = mod_exp(num, 3703, 4453);  // Apply number conversion
        cout << translation << " ";
        char translated_char = num_to_char(translation);  // Convert number to character
        //cout << translated_char;
    }
    cout << endl;

    return 0;
}
