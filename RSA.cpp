#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <tuple>
#define int long long

using namespace std;



int decryption(int cypher, int d, int n) {
    int takenOut = 1;
    int base = cypher % n;

    while (d > 0) {
        if (d % 2 == 1) { 
            takenOut = (takenOut * base) % n;
        }
        d = d / 2;
        base = (base * base) % n;
    }

    return takenOut;
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

int gcd(int a, int b) {
    if (a == 0) {
        return b;
    }
    if(a > b){
        return gcd(a % b, b);
    }
    return gcd(b % a, a);
}


signed main() {
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};

    int e, n, m;

    if (!(cin >> e >> n >> m)) {
        cout << "Public key is not valid" << endl;
        return 0;
    }

    vector<int> cypherText(m);
    vector<long long> cypherTextDecrypted(m);
    int cypher;

    for(int i = 0; i < m; i++){
        cin >> cypherText[i];
    }

    // Find P and Q
    int p = 0, q = 0;
    for (int i = 0; primes[i] <= sqrt(n); i++) {
        if(n % primes[i] == 0){
            p = primes[i];
            q = n / primes[i];
            break;
        }
    }

    bool isPrime = false;
    for(int i = 0; i < primes.size(); i++){
        if(primes[i] == q){
            isPrime = true;
            break;
        }
    }

    if(!isPrime){
        cout << "Public key is not valid!";
        return 0;
    }

    // phi
    int phi = (p - 1) * (q - 1);

    // Decrypt
    int d = 0;
    for(int i = 1; i < phi; i++){
        if((e * i) % phi == 1){
            d = i;
            break;
        }
    }

    // Public key check
    if(p > q || p == q){
        cout << "Public key is not valid!";
        return 0;
    }

    if(gcd(phi, e) != 1){
        cout << "Public key is not valid!";
        return 0;
    }

    if(d == 0){
        cout << "Public key is not valid!";
        return 0;
    }

    cout << p << " ";
    cout << q << " ";
    cout << phi << " ";
    cout << d << endl;

    for(int i = 0; i < m; i++){
        cypherTextDecrypted[i] = decryption(cypherText[i], d, n);
    }

    for(int i = 0; i < m; i++){
        cout << cypherTextDecrypted[i] << " ";
    }

    cout << endl;

    for(int i = 0; i < m; i++){
        cout << num_to_char(cypherTextDecrypted[i]);
    }

    return 0;
}