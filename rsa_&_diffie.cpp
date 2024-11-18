#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

// GCD to find suitable exponent 'e'
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

void rsa() {
    int p = 61, q = 53;

    int n = p * q;
    int phi = (p - 1) * (q - 1);

    int e;
    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1) break;
    }

    int d;
    for (d = 1; d < phi; d++) {
        if ((e * d) % phi == 1) break;
    }

    cout << "Public Key: (" << e << ", " << n << ")\n";
    cout << "Private Key: (" << d << ", " << n << ")\n";

    int message;
    cout << "Enter a message to encrypt (integer value): ";
    cin >> message;

    if (message >= n) {
        cout << "Message must be less than " << n << ". Try again." << endl;
        return;
    }

    long long encrypted = modExp(message, e, n);
    cout << "Encrypted message: " << encrypted << endl;

    long long decrypted = modExp(encrypted, d, n);
    cout << "Decrypted message: " << decrypted << endl;
}

void diffieHellman() {
    int p = 23, g = 5;  

    cout << "Publicly shared prime (p): " << p << endl;
    cout << "Publicly shared base (g): " << g << endl;

    int a, b;
    cout << "Enter private key for user A: ";
    cin >> a;
    cout << "Enter private key for user B: ";
    cin >> b;

    long long A = modExp(g, a, p);
    long long B = modExp(g, b, p);

    cout << "Public key for A: " << A << endl;
    cout << "Public key for B: " << B << endl;

    long long sharedKeyA = modExp(B, a, p);
    long long sharedKeyB = modExp(A, b, p);

    cout << "Shared secret key computed by A: " << sharedKeyA << endl;
    cout << "Shared secret key computed by B: " << sharedKeyB << endl;

    if (sharedKeyA == sharedKeyB) {
        cout << "Key exchange successful! Shared secret: " << sharedKeyA << endl;
    } else {
        cout << "Key exchange failed!" << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\nChoose an algorithm to implement:\n";
        cout << "1. RSA Encryption and Decryption\n";
        cout << "2. Diffie-Hellman Key Exchange\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: \n";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                rsa();
                break;
            case 2:
                diffieHellman();
                break;
            case 3:
                exit(0);
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
