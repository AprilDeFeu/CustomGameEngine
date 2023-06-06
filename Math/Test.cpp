#include <iomanip>
#include <iostream>
#include <cmath>
#include "Vectors.h"
#include "Geometry.h"
#include "Matrices.h"

using namespace std;

void PrintMatrix(void)
{
    cout << "Testing matrix printing...\n";
    Matrix2 M2 = Matrix2(1,2,3,4);
    Matrix3 M3 = Matrix3(1,1,1,
                         2,2,2,
                         3,3,3);
    Matrix4 M4 = Matrix4(1,3,5,7,
                        2,4,6,8,
                        3,5,7,9,
                        4,6,8,10);
    M2.Print();
    M3.Print();
    M4.Print();
}

void REF_Print(void)
{
    cout << setprecision(13);
    cout << "Testing 2D REF printing...\n";
    Matrix2 M2 = Matrix2(4, 9, 5, 1);
    float det = 1.0f;
    Matrix2 M2_REF = REF(M2,  &det);

    cout << "Given " << M2.ToString() << "We find its REF to be...\n" << M2_REF.ToString();
    cout << "My det was " << to_string(Det(M2)) << ", and the REF det was " << to_string(det) << endl;

    cout << "Testing 3D REF printing...\n";
    Matrix3 M3 = Matrix3(5, 4, 9, 1, 0, 3, 8, 4, 1);
    det = 1.0f;
    Matrix3 M3_REF = REF(M3,  &det);

    cout << "Given " << M3.ToString() << "We find its REF to be...\n" << M3_REF.ToString();
    cout << "My det was " << to_string(Det(M3)) << ", and the REF det was " << to_string(det) << endl;

    cout << "Testing 4D REF printing...\n";
    Matrix4 M4 = Matrix4(9,4,4,4,4,2,8,7,6,8,0,3,5,1,6,7);
    det = 1.0f;
    Matrix4 M4_REF = REF(M4,  &det);

    cout << "Given " << M4.ToString() << "We find its REF to be...\n" << M4_REF.ToString();
    cout << "My det was " << to_string(Det(M4)) << ", and the REF det was " << to_string(det) << endl;

}

int main()
{
    REF_Print();
    return 0;
}