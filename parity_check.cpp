#include <iostream>
#include <string>

using namespace std;

char calculateParity(string data) {
    int count = 0;

    for (char bit : data) {
        if (bit == '1') 
            count++;
    }

    return (count % 2 == 0) ? '0' : '1';
}

bool checkParity(string receivedData) {
    string data = receivedData.substr(0, receivedData.size() - 1); 
    char receivedParity = receivedData.back();                    
    char calculatedParity = calculateParity(data);                

    return receivedParity == calculatedParity;
}

int main() {
    string data;
    cout << "Enter binary data: ";
    cin >> data;

    char parityBit = calculateParity(data);
    string transmittedData = data + parityBit;

    cout << "Transmitted data with parity bit: " << transmittedData << endl;

    string receivedData;
    cout << "Enter received data: ";
    cin >> receivedData;

    if (checkParity(receivedData))
        cout << "Parity check passed: No error in transmission." << endl;
    else 
        cout << "Parity check failed: Error detected in transmission." << endl;

    return 0;
}
