#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int calculateParity(vector<int> &bits, int position) {
    int parity = 0;
    int n = bits.size();
    for (int i = position; i <= n; i += 2 * position) {
        for (int j = 0; j < position && (i + j) <= n; j++) {
            parity ^= bits[i + j - 1];
        }
    }
    return parity;
}

vector<int> hammingEncode(vector<int> &data) {
    vector<int> encoded(7, 0);

    encoded[2] = data[0];
    encoded[4] = data[1];
    encoded[5] = data[2];
    encoded[6] = data[3];
    
    encoded[0] = calculateParity(encoded, 1);
    encoded[1] = calculateParity(encoded, 2); 
    encoded[3] = calculateParity(encoded, 4);

    return encoded;
}

vector<int> hammingDecode(vector<int> &received) {
    vector<int> decoded;
    int n = received.size();
    int errorPos = 0;

    for (int i = 0; i < 3; i++) {
        int parity = calculateParity(received, pow(2, i));
        if (parity != 0) {
            errorPos += pow(2, i);
        }
    }

    if (errorPos != 0) {
        cout << "Error detected at position: " << errorPos << endl;
        received[errorPos - 1] ^= 1; 
    } else 
        cout << "No error detected." << endl;
    
    decoded.push_back(received[2]);
    decoded.push_back(received[4]);
    decoded.push_back(received[5]);
    decoded.push_back(received[6]);

    return decoded;
}

int main() {
    vector<int> data(4);
    cout << "Enter 4 data bits (separated by space): ";
    for (int i = 0; i < 4; i++) 
        cin >> data[i];

    vector<int> encoded = hammingEncode(data);
    cout << "Encoded data (7 bits): ";
    for (int bit : encoded) 
        cout << bit;
    cout << endl;

    vector<int> received = encoded;
    cout << "Enter received data (7 bits): ";
    for (int i = 0; i < 7; i++) 
        cin >> received[i];

    vector<int> decoded = hammingDecode(received);
    cout << "Decoded data (4 bits): ";
    for (int bit : decoded) 
        cout << bit;
    cout << endl;

    return 0;
}
