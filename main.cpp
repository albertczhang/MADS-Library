#include <iostream>
#include <math.h>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

#include "Matrix.h"
#include "Graph.h"
#include "Polynomial.h"

using namespace std;

int randInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

double randDouble(double min, double max) {
    return (max - min) * ((double) rand() / (double) RAND_MAX) + min;
}

void testDet(int trials);


double f1(double x) {
    return -1 * pow(x, 4) + 3 * pow(x, 3) - 2 * pow(x, 2) + 5;
}

int main() {

    /* How to INITIALIZE a matrix:
    double m2[4][4] = {{1, 2, 3, 4},
                       {3, 1, 2, 5},
                       {5, 1, 6, 7},
                       {2, 5, 3, 6}};
    Matrix<double> m1 (4, 4);
    m1 = makeMatrix<double, 4, 4>(m2);

    m1.show(); */

//    cout << setprecision(2);


    Polynomial<double> L;
    vector<double> points = {-1, 0, 1, 2, 3};
    L = L_interpolate(f1, points);
    cout << L << endl;


    vector<double> coeffs = {1, -1, 1};
    Polynomial<double> p(coeffs);
    p.show();
    cout << endl;


    vector<double> coeffs2 = {1, 1, 1};
    Polynomial<double> p2(coeffs2);
    p2.show();
    cout << endl;

    Polynomial<double> psum;
    psum = p * p2;
    cout << psum.coeffs[4]<< endl;

    psum.show();
    cout << endl;

//    vector<idouble> cc = {idouble(-1, 0), idouble(1, 0), idouble(-1, 0)};
//    Polynomial<idouble> p3(cc, 'y');
//    p3.show();
//
//    idouble w3(-0.5, pow(3, 0.5)/2);
//    cout << endl << p3.eval(w3) << endl;







    return 0;
}



void testGraphBasic() {
    AdjMatrix g(5);
    g.connect(1, 2, 3.2);
    g.disconnect(2, 2);
    g.connect(2, 3);
    g.direct(3, 4);
    g.connect(4, 2);
    g.show();
    cout << g.isConnected(3, 4) << endl;
    cout << g.isConnected(2, 1) << endl;
    cout << g.weight(2, 1) << endl;
}

void testInv() {
    double arr[4][8] = {{1, 2, 3, 4, 1, 0, 0, 0},
                        {3, 1, 2, 5, 0, 1, 0, 0},
                        {5, 1, 6, 7, 0, 0, 1, 0},
                        {2, 5, 3, 6, 0, 0, 0, 1}};
    Matrix<double> m(4, 8);
    m = makeMatrix<double, 4, 8>(arr);

    Matrix<double> m1(4, 4);
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            m1.set(i, j, m.get(i, j));
        }
    }
    m.show();
    m.gaussElim(4);
    m.show(6);
    Matrix<double> m2(4, 4);
    for (int i = 1; i <= 4; i++) {
        for (int j = 5; j <= 8; j++) {
            m2.set(i, j - 4, m.get(i, j));
        }
    }

    m1.show();
    m2.show();
    Matrix<double> m3(4, 4);

    m3 = m1 * m2;
    m3.show(10);

    double arr2[4][4] = {{1, 2, 3, 4},
                         {3, 1, 2, 5},
                         {5, 1, 6, 7},
                         {2, 5, 3, 6}};
    Matrix<double> mtest(4, 4);
    mtest = makeMatrix<double, 4, 4>(arr2);
    Matrix<double> mtestInv(4, 4);
    mtestInv = mtest.inverse();
    mtestInv.show();
}

void testDet(int trials) {
    srand(time(NULL));

    cout << setprecision(2);
    int NUM_TRIALS = trials;
    int good_count = 0;
    int rough_count = 0;
    int bad_count = 0;
    double error = 0;
    for (int trials = 0; trials < NUM_TRIALS; trials++) {

        int n = rand() % 7 + 2;
        Matrix<double> m1(n, n);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                m1.set(i, j, randDouble(-10, 10));

            }
        }
        m1.show(6);
        int d1 = m1.det(1);
        int d2 = m1.det();
        if (d1 == d2) {
            good_count++;
            cout << "Determinants match: " <<
                 d1 << " = " << d2 << endl << endl;
        } else if (d1 - d2 > -2 && d1 - d2 < 2) {
            rough_count++;
            error += abs((d1 - d2) / d1 * 100);
            cout << "Determinants are off by 1: " <<
                 d1 << " = " << d2 << endl << endl;
            cout << "error: " << error << endl;
        } else {
            bad_count++;
            error += abs((d1 - d2) / d1 * 100);
            cout << "Determinants don't match: " <<
                 d1 << " != " << d2 << endl << endl;
            cout << "error: " << error << endl;
        }
    }
    error /= NUM_TRIALS;
    cout << "Matching: " << good_count << endl;
    cout << "Off by one: " << rough_count << endl;
    cout << "Not Matching: " << bad_count << endl;
    cout << "Mean Error: " << error << "%" << endl;
}


