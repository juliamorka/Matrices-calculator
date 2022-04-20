#include <iostream>
#include "Matrix.h"
#define VECTOR_TEST
#define MATRIX_TEST
using namespace std;

int main()
{
#ifdef VECTOR_TEST 
    Vector v1;
    Vector v2(2);
    Vector v3(3,1);
    Vector v4(3);
    cout << "Enter the values of v4 (nDim = 3): ";
    cin >> v4;
    int x = v3[2];
    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    cout << "v3 = " << v3 << endl;
    cout << "v4 = " << v4 << endl;
    cout << "Does v1 equal v2? " << (v1 == v2) << endl;
    cout << "-v3 = " << -v3 << endl;
    cout << "v3 + 3 = " << 3 + v3 << " = " << v3 + 3 << endl;
    cout << "v3 + v4 = " << v3 + v4 << endl;
    cout << "v3 - 3 = "  << v3 - 3 << endl;
    cout << "v3 - v4 = " << v3 - v4 << endl;
    cout << "v3 * 3 = " << 3 * v3 << " = " << v3 * 3 << endl;
    cout << "v3 * v4 = " << v3 * v4 << endl;
    cout << "v3[2] = " << v3[2] << " = " << x << endl;
#endif
    Matrix m1;
    Matrix m2(2,2,0);
    Matrix m3(3,3,1);
    Matrix m4(3,2,3);
    Matrix m5(4,2);

    cout << "Enter the 5th matrix m5 (4x2): "; 
    cin >> m5;
    cout << "m1 = " << m1 << endl;
    cout << "m2 = " << m2 << endl;
    cout << "m3 = " << m3 << endl;
    cout << "m4 = " << m4 << endl;
    cout << "m5 = " << m5 << endl;
    cout << "m3 * v3 = " << m3 * v3 << endl;
    cout << "m3 * m4 = " << m3 * m4 << endl; 
    return 0;
}