#include <iostream>
#include <string>

using namespace std;

string xorOperation(string dividend, string divisor) {
    string result = "";
    for (int i = 1; i < divisor.length(); i++) {
        result += (dividend[i] == divisor[i]) ? '0' : '1';
    }
    return result;
}

string calculateCRC(string data, string divisor) {
    int dataLength = data.length();
    int divisorLength = divisor.length();

    string temp = data.substr(0, divisorLength);

    while (divisorLength < dataLength) {
        if (temp[0] == '1') {
            temp = xorOperation(temp, divisor) + data[divisorLength];
        } else {
            temp = xorOperation(temp, string(divisorLength, '0')) + data[divisorLength];
        }
        divisorLength++;
    }

    if (temp[0] == '1') {
        temp = xorOperation(temp, divisor);
    } else {
        temp = xorOperation(temp, string(divisor.length(), '0'));
    }

    return temp;
}

int main() {
    string data, divisor;

    cout << "Enter the data bits: ";
    cin >> data;
    cout << "Enter the divisor bits: ";
    cin >> divisor;

    int divisorLength = divisor.length();
    string appendedData = data + string(divisorLength - 1, '0');

    cout << "Appended data: " << appendedData << endl;

    string remainder = calculateCRC(appendedData, divisor);

    cout << "CRC: " << remainder << endl;

    string transmittedData = data + remainder;
    cout << "Transmitted data: " << transmittedData << endl;

    return 0;
}
