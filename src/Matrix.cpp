//
// Created by albertczhang on 6/9/19.
//

#include <iostream>
#include <iomanip>
#include "Matrix.h"
#include "Complex.h"

template<class T>
vector<T> kNums(int k, T x) {
    vector<T> v;
    for (int i = 0; i < k; i++) {
        v.push_back(x);
    }
    return v;
}

template<class T>
Matrix<T>::Matrix() {
    m = 2, n = 2;
    for (int i = 0; i < 2; i++) {
        vector<T> r = kNums<T>(2, 0);
        mat.push_back(r);
    }
}

template<class T>
Matrix<T>::Matrix(int M, int N) {
    m = M, n = N;
    for (int i = 0; i < m; i++) {
        vector<T> r = kNums<T>(n, 0);
        mat.push_back(r);
    }
}


//int size(double **a) {
//    return sizeof(a) / sizeof(*a);
//}


template<class T>
void Matrix<T>::set(int i, int j, T x) {
    i--;
    j--;
    mat[i][j] = (T) x;
}


template<class T>
T Matrix<T>::get(int i, int j) const {
    i--;
    j--;
    if (i >= m || j >= n) {
        cout << "Matrix indices out of bounds, exiting...";
        exit(0);
    }
    return mat[i][j];
}


template<class T>
void Matrix<T>::show(int padding, double maxError) {
    int w = padding;
    if (m == 1) {
        cout << "[";
        for (int j = 0; j < n - 1; j++) {
            if (abs(mat[0][j]) < maxError)
                cout << 0 << setw(w) << setfill(' ');
            else
                cout << mat[0][j] << setw(w) << setfill(' ');
        }
        if (abs(mat[0][n - 1]) < maxError)
            cout << 0 << "]\n";
        else
            cout << mat[0][n - 1] << "]\n";
    } else {
        cout << "⎡";
        for (int j = 0; j < n - 1; j++) {
            if (abs(mat[0][j]) < maxError)
                cout << 0 << setw(w) << setfill(' ');
            else
                cout << mat[0][j] << setw(w) << setfill(' ');
        }
        if (abs(mat[0][n - 1]) < maxError)
            cout << 0 << "⎤\n";
        else
            cout << mat[0][n - 1] << "⎤\n";
        for (int i = 1; i < m - 1; i++) {
            cout << "⎢";
            for (int j = 0; j < n - 1; j++) {
                if (abs(mat[i][j]) < maxError)
                    cout << 0 << setw(w) << setfill(' ');
                else
                    cout << mat[i][j] << setw(w) << setfill(' ');
            }
            if (abs(mat[i][n - 1]) < maxError)
                cout << 0 << "⎥\n";
            else
                cout << mat[i][n - 1] << "⎥\n";
        }
        cout << "⎣";
        for (int j = 0; j < n - 1; j++) {
            if (abs(mat[m - 1][j]) < maxError)
                cout << 0 << setw(w) << setfill(' ');
            else
                cout << mat[m - 1][j] << setw(w) << setfill(' ');
        }
        if (abs(mat[m - 1][n - 1]) < maxError)
            cout << 0 << "⎦\n";
        else
            cout << mat[m - 1][n - 1] << "⎦\n";
    }
}


/***************************************************
 **************  OPERATOR OVERLOADING **************
 ***************************************************/
template<class T>
vector<T> Matrix<T>::operator[](int i) {
    if (i >= m) {
        cout << "Array index out of bound, exiting...";
        exit(0);
    }
    return mat[i];
}


template<class T>
Matrix<T> Matrix<T>::operator+(Matrix<T> other) {
    if (m != other.m || n != other.n) {
        cout << "Dimensions don't match, exiting...";
        exit(0);
    }
    Matrix<T> result(m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result.set(i + 1, j + 1, mat[i][j] + other.get(i + 1, j + 1));
        }
    }
    return result;
}

template<class T>
Matrix<T> Matrix<T>::operator-(Matrix<T> other) {
    if (m != other.m || n != other.n) {
        cout << "Dimensions don't match, exiting...";
        exit(0);
    }
    Matrix<T> result(m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result.set(i + 1, j + 1, mat[i][j] - other.get(i + 1, j + 1));
        }
    }
    return result;
}

template<class T>
Matrix<T> Matrix<T>::operator*(Matrix<T> other) {
    if (n != other.m) {
        cout << "Dimensions don't match, exiting...";
        exit(0);
    }

    /**** NAIVE MATRIX MULTIPLICATION ****/
    Matrix<T> result(m, other.n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < other.n; j++) {
            T dot = 0;
            for (int k = 0; k < n; k++) {
                dot = dot + mat[i][k] * other.get(k + 1, j + 1);
            }
            result.set(i + 1, j + 1, dot);
        }
    }
    return result;
}


template<class T>
bool Matrix<T>::operator==(Matrix<T> other) {
    if (m != other.m || n != other.n) {
        return false;
    } else {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] != other.get(i + 1, j + 1))
                    return false;
            }
        }
        return true;
    }
}

template<class T>
bool Matrix<T>::operator!=(Matrix<T> other) {
    return !((*this) == other);
}


/***************************************************
 **************** MATRIX OPERATIONS ****************
 ***************************************************/

template<class T>
Matrix<T> Matrix<T>::getT() const {
    /* RETURNS THE TRANSPOSE */
    Matrix<T> transpose(n, m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            transpose.set(j + 1, i + 1, mat[i][j]);
        }
    }
    return transpose;
}

template<>
Matrix<idouble> Matrix<idouble>::getH() const {
    /* RETURNS THE HERMITIAN TRANSPOSE (ONLY FOR COMPLEX MATRICES) */
    Matrix<idouble> H(n, m);
    H = (*this).getT();
    for (int i = 0; i < H.m; i++) {
        for (int j = 0; j < H.n; j++) {
            H.set(i + 1, j + 1, H.get(i + 1, j + 1).getConj());
        }
    }
    return H;
}

template<>
Matrix<ifloat> Matrix<ifloat>::getH() const {
    /* RETURNS THE HERMITIAN TRANSPOSE (ONLY FOR COMPLEX MATRICES) */
    Matrix<ifloat> H(n, m);
    H = (*this).getT();
    for (int i = 0; i < H.m; i++) {
        for (int j = 0; j < H.n; j++) {
            H.set(i + 1, j + 1, H.get(i + 1, j + 1).getConj());
        }
    }
    return H;
}


template<>
Matrix<iint> Matrix<iint>::getH() const {
    /* RETURNS THE HERMITIAN TRANSPOSE (ONLY FOR COMPLEX MATRICES) */
    Matrix<iint> H(n, m);
    H = (*this).getT();
    for (int i = 0; i < H.m; i++) {
        for (int j = 0; j < H.n; j++) {
            H.set(i + 1, j + 1, H.get(i + 1, j + 1).getConj());
        }
    }
    return H;
}


template<class T>
void Matrix<T>::rowMinus(int i1, int i2, T factor) {
    for (int j = 1; j <= n; j++) {
        set(i2, j, get(i2, j) - get(i1, j) * factor);
    }
}

template<class T>
void Matrix<T>::rowSwap(int i1, int i2) {
    vector<T> temp = mat[i1 - 1];
    mat[i1 - 1] = mat[i2 - 1];
    mat[i2 - 1] = temp;
}

template<class T>
void Matrix<T>::rowMult(int i, T factor) {
    for (int j = 1; j <= n; j++) {
        set(i, j, factor * get(i, j));
    }
}

template<class T>
void Matrix<T>::rowDiv(int i, T factor) {
    for (int j = 1; j <= n; j++) {
        set(i, j, get(i, j) / factor);
    }
}


template<class T>
T Matrix<T>::det(int algo) const {
    /* RETURNS DETERMINANT OF MATRIX IF M=N */
    if (m != n) {
        cout << "Not a square matrix, operation invalid, exiting...";
        exit(0);
    }
    /* 0: Gaussian Elimination (ONLY WORKS WITH DOUBLES/IDOUBLES NOT INTS/IINTS)
     * 1: naive (inefficient) algorithm
     * */
    if (algo == 0) {
        Matrix<T> copy(n, n);
        copy = *this;
        T result(1);
        for (int j = 1; j <= n; j++) {
            bool flag = false;
            for (int i = j; i <= m; i++) {
                T entry = copy.get(i, j);
                if (entry != 0) {
                    flag = true;
                    if (i == j)
                        break;
                    else if (i > j) {
                        copy.rowSwap(i, j);
                        T flip(-1);
                        result = result * flip;
                        break;
                    }
                }
            }
            if (!flag) {
                T d(0);
                return d;
            }
            T factor(copy.get(j, j));
            result = result * factor;
            copy.rowDiv(j, factor);
            if (j + 1 <= m) {
                for (int i = j + 1; i <= m; i++) {
                    copy.rowMinus(j, i, copy.get(i, j));
                }
            }
        }
        return result;
    } else if (algo == 1) {

        if (m == 1 && n == 1) {
            return get(1, 1);
        }
        T result = 0;
        for (int j = 1, f = 1; j <= n; j++, f *= -1) {
            Matrix<T> minor(m - 1, n - 1);
            for (int i = 2; i <= m; i++) {
                for (int k = 1; k < j; k++) {
                    minor.set(i - 1, k, get(i, k));
                }
                for (int k = j + 1; k <= n; k++) {
                    minor.set(i - 1, k - 1, get(i, k));
                }
            }
            T factor(f);
            result = result + factor * get(1, j) * minor.det(1);
        }
        return result;
    } else {
        cout << "invalid, exiting... " << endl;
        exit(0);
    }
}


template<class T>
void Matrix<T>::gaussElim() {
    // STEP 1
    int r = 1;
    for (int j = 1; j <= n; j++) {
        bool flag = false; // flag denotes if pivot found in column
        for (int i = r; i <= m; i++) {
            T entry = get(i, j);
            if (entry != 0) {
                flag = true;
                if (i == r) {
                    break;
                } else if (i > r) {
                    rowSwap(i, r);
                    break;
                }
            }
        }

        if (flag) {
            T factor(get(r, j));
            rowDiv(r, factor);
            if (r + 1 <= m) {
                for (int i = r + 1; i <= m; i++) {
                    rowMinus(r, i, get(i, j));
                    // set to 0 here, correcting the -0 error
                }
            }
            r++;
        }
    }
    // STEP 2
    for (int i = r - 1; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            T pivot = get(i, j);
            if (pivot != 0) {
                if (i == 1)
                    break;
                for (int up = i - 1; up >= 1; up--) {
                    rowMinus(i, up, get(up, j));
                }
                break;
            }
        }
    }
}

template<class T>
void Matrix<T>::gaussElim(int col) {
    // STEP 1
    int r = 1;
    for (int j = 1; j <= col; j++) {
        bool flag = false; // flag denotes if pivot found in column
        for (int i = r; i <= m; i++) {
            T entry = get(i, j);
            if (entry != 0) {
                flag = true;
                if (i == r) {
                    break;
                } else if (i > r) {
                    rowSwap(i, r);
                    break;
                }
            }
        }

        if (flag) {
            T factor(get(r, j));
            rowDiv(r, factor);
            if (r + 1 <= m) {
                for (int i = r + 1; i <= m; i++) {
                    rowMinus(r, i, get(i, j));
                    // set to 0 here, correcting the -0 error
                }
            }
            r++;
        }
    }

    // STEP 2
    for (int i = r - 1; i >= 1; i--) {
        for (int j = 1; j <= col; j++) {
            T pivot = get(i, j);
            if (pivot != 0) {
                if (i == 1)
                    break;
                for (int up = i - 1; up >= 1; up--) {
                    rowMinus(i, up, get(up, j));
                }
                break;
            }
        }
    }
}

template<class T>
Matrix<T> Matrix<T>::inverse() {
    if (m != n) {
        cout << "Matrix is not square, exiting..." << endl;
        exit(0);
    }
    Matrix<T> copier(n, 2 * n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            copier.set(i, j, get(i, j));
        }
        copier.set(i, n + i, (T) 1);
    }
    copier.gaussElim(n);
    if (copier.get(n, n) != 1) {
        cout << "Matrix is not invertible." << endl;
        Matrix<T> singular(n, n);
        return singular;
    }
    Matrix<T> inv(n, n);
    for (int i = 1; i <= n; i++) {
        for (int j = n + 1; j <= 2 * n; j++) {
            inv.set(i, j - n, copier.get(i, j));
        }
    }
    return inv;
}

template
class Matrix<int>;

template
class Matrix<float>;

template
class Matrix<double>;

template
class Matrix<iint>;

template
class Matrix<ifloat>;

template
class Matrix<idouble>;