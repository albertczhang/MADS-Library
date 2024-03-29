//
// Template Declarations for Complex int and Complex Double
//

#ifndef MADS_LIBRARY_COMPLEX_H
#define MADS_LIBRARY_COMPLEX_H

#include <math.h>
#include <ostream>
#include <iomanip>

using namespace std;

template<class T>
class Complex {
public:
    T a, b;
    T r2;
    double r;

    Complex();

    Complex(T A);

    Complex(T A, T B);

    Complex<T> operator+(Complex<T>);

    Complex<T> operator-(Complex<T>);

    Complex<T> operator*(Complex<T>);

    Complex<T> operator/(Complex<T>);

    bool operator==(Complex<T>);

    bool operator!=(Complex<T>);

    void set(T A, T B);

    void conj();

    Complex<T> getConj() const;

};

template<class T>
double abs(Complex<T> z) {
    return sqrt((double)(z.a * z.a + z.b * z.b));
}

template <class T>
Complex<T> pow(Complex<T> z, int exp) {
    if (exp == 0)
        return 1;
    else {
        return z * pow(z, exp - 1);
    }
}

template<class T>
std::ostream &operator<<(std::ostream &os, Complex<T> z) {
//    if (z.a == 0 && false) {
//        if (z.b == 1)
//            return os << "i";
//        else if (z.b > 0)
//            return os << z.b << "i";
//        else if (z.b == 0)
//            return os << z.a;
//        else if (z.b == -1)
//            return os << "-i";
//        else
//            return os << z.b << "i";
//    } else {
    int w = 2;
    if (z.b == 1)
        return os << z.a << setw(w) << setfill(' ') << "+" << setw(w) << setfill(' ') << " " << "i";
    else if (z.b >= 0)
        return os << z.a << setw(w) << setfill(' ') << "+" << setw(w) << setfill(' ') << z.b << "i";
//    else if (z.b == 0)
//        return os << z.a << setw(2) << setfill(' ') << "+" << z.b << "i";
    else if (z.b == -1)
        return os << z.a << setw(w) << setfill(' ') << "-" << setw(w) << setfill(' ') << " " << "i";
    else
        return os << z.a << setw(w) << setfill(' ') << "-" << setw(w) << setfill(' ') << -z.b << "i";
//    }
}


typedef Complex<int> iint;
typedef Complex<double> idouble;
typedef Complex<float> ifloat;


#endif //MADS_LIBRARY_COMPLEX_H
