#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long a = 0, b = 1;
    long long sum = 0, i = 1;

    while(n > 0) {
        if (i % 2 == 0){
            sum += a;
            n--;
        }
        long long next = a + b;
        a = b;
        b = next;
        ++i;
    }

    cout << sum;
}
