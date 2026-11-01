#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

void readArray(int a[], int n, int i = 0) {
    if (i == n) return;
    cin >> a[i];
    if (!cin || a[i] < -10 || a[i] > 10) return;
    readArray(a, n, i + 1);
}
void printArray(const int a[], int n, int i = 0) {
    if (i == n) { cout << '\n'; return; }
    cout << setw(5) << a[i];
    printArray(a, n, i + 1);
}
// Even element numbers are array indices 1,3,5,... (1-based positions 2,4,6,...).
long long productEvenPositions(const int a[], int n, int i = 1) {
    if (i >= n) return 1;
    return a[i] * productEvenPositions(a, n, i + 2);
}
int findFirstZero(const int a[], int n, int i = 0) {
    if (i == n) return -1;
    if (a[i] == 0) return i;
    return findFirstZero(a, n, i + 1);
}
int findLastZero(const int a[], int i) {
    if (i < 0) return -1;
    if (a[i] == 0) return i;
    return findLastZero(a, i - 1);
}
long long sumRange(const int a[], int first, int last) {
    if (first >= last) return 0;
    return a[first] + sumRange(a, first + 1, last);
}
bool sumBetweenZeros(const int a[], int n, long long& result) {
    const int first = findFirstZero(a, n);
    const int last = findLastZero(a, n - 1);
    if (first < 0 || first == last) return false;
    result = sumRange(a, first + 1, last);
    return true;
}
int countNonNegative(const int a[], int n, int i = 0) {
    if (i == n) return 0;
    return (a[i] >= 0 ? 1 : 0) + countNonNegative(a, n, i + 1);
}
void fillPartition(const int a[], int b[], int n, int i,
    int positiveIndex, int negativeIndex) {
    if (i == n) return;
    if (a[i] >= 0) {
        b[positiveIndex] = a[i];
        fillPartition(a, b, n, i + 1, positiveIndex + 1, negativeIndex);
    }
    else {
        b[negativeIndex] = a[i];
        fillPartition(a, b, n, i + 1, positiveIndex, negativeIndex + 1);
    }
}
void copyArray(int a[], const int b[], int n, int i = 0) {
    if (i == n) return;
    a[i] = b[i];
    copyArray(a, b, n, i + 1);
}
void stablePartition(int a[], int n) {
    int* b = new int[n];
    fillPartition(a, b, n, 0, 0, countNonNegative(a, n));
    copyArray(a, b, n);
    delete[] b;
}
#ifndef UNIT_TEST
int main() {
    int n;
    cout << "Enter n (2..20): ";
    if (!(cin >> n) || n < 2 || n > 20) {
        cerr << "Invalid array size.\n"; return 1;
    }
    int* a = new int[n]();
    cout << "Enter " << n << " integers between -10 and 10: ";
    readArray(a, n);
    bool valid = static_cast<bool>(cin);
    for (int i = 0; i < n; ++i)
        if (a[i] < -10 || a[i] > 10) valid = false;
    if (!valid) {
        cerr << "Invalid array element.\n";
        delete[] a;
        return 1;
    }
    cout << "Initial: "; printArray(a, n);
    cout << "Product (even positions): " << productEvenPositions(a, n) << '\n';
    long long sum = 0;
    if (sumBetweenZeros(a, n, sum))
        cout << "Sum between first and last zero: " << sum << '\n';
    else cout << "Fewer than two zeros; sum is undefined.\n";
    stablePartition(a, n);
    cout << "Modified: "; printArray(a, n);
    delete[] a;
    return 0;
}
#endif
