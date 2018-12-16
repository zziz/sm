#ifndef __SPARSEMATRIX_HPP__
#define __SPARSEMATRIX_HPP__

#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned int uint;

template <class T> 
struct Element {
    uint row, col;
    T value;
};

template <class T> 
class SparseMatrix{
public:
    SparseMatrix(uint n);                   // Square Matrix
    SparseMatrix(uint rows, uint cols);     // Generic Matrix

    // Get and Set
    T get(uint row, uint col) const;
    bool set(uint row, uint col, T value); 

    // Operator overloads
    SparseMatrix operator*(const SparseMatrix& mat) const;
    SparseMatrix operator+(const SparseMatrix& mat) const;
    SparseMatrix operator-(const SparseMatrix& mat) const;
    bool operator==(const SparseMatrix & mat) const;                            // for comparing non-floating point matrices
    bool operator!=(const SparseMatrix & mat) const;                            // for comparing non-floating point matrices
    bool almostEqual(const SparseMatrix & mat, double epsilon = 1e-12) const;   // for comparing floating-point matrices

    // Get information about matrix
    uint rows() const;
    uint cols() const;
    uint size() const;

    // Other functions
    void print(bool full = false) const;

    void transpose();                       // transpose of matrix
    SparseMatrix copy() const;              // deep copy of matrix
    std::vector<Element<T> > data;          // data of matrix
private:
    uint m_rows, m_cols;
};

// We have to include function definitions in header file as well because of templated class/functions. 
// This can be fixed by moving function definitions to .cpp file with help of EXTERN TEMPLATE but let's keep things simple - Header-only Templated Sparse Matrix class
template<typename T> 
SparseMatrix<T>::SparseMatrix(uint n){
    if(n < 1)    
        throw "Matrix dimentions must be positive integer.";
    this->m_rows = n;
    this->m_cols = n;
}

template<typename T> 
SparseMatrix<T>::SparseMatrix(uint rows, uint cols){
    if(rows < 1 || cols < 1)    
        throw "Matrix dimentions must be positive integer.";
    this->m_rows = rows;
    this->m_cols = cols;
}

template <typename T> 
T SparseMatrix<T>::get(uint row, uint col) const{
    for(auto& it : data)
        if(it.row == row && it.col == col)  return it.value;
    
    return 0;
}

template <typename T> 
bool SparseMatrix<T>::set(uint row, uint col, T value){
    if(row > this->m_rows || col > this->m_cols){
        throw "Cannot insert this element. Index is too big!";
        return false;
    }

    data.push_back({row, col, value});
    return true;

}

template <typename T> 
SparseMatrix<T> SparseMatrix<T>::operator*(const SparseMatrix& mat) const{
    if(this->cols() != mat.rows())
        throw "For multiplication, rows and cols of first matrix must match cols and rows of second matrix, respectively!";

    SparseMatrix<T> result(this->m_rows, mat.cols());   
    auto mat_t = mat.copy();
    mat_t.transpose();
    
    for(uint i = 0; i < this->data.size();){
        uint nRow = this->data[i].row;
        for(uint j = 0; j < mat_t.data.size();){
            uint nCol = mat_t.data[j].row;
            uint i_curr = i, j_curr = j;    // take a temporary pointer for each matrix and calculate this entry
            T sum = 0;
            
            while(i_curr < this->data.size() && this->data[i_curr].row == nRow && j_curr < mat_t.data.size() && mat_t.data[j_curr].row == nCol) {
                if(this->data[i_curr].col < mat_t.data[j_curr].col)         i_curr++;
                else if(this->data[i_curr].col >mat_t.data[j_curr].col)     j_curr++;
                else{
                    sum += this->data[i_curr].value * mat_t.data[j_curr].value;
                    i_curr++;
                    j_curr++;
                }
            }

            if (sum != 0)   {
                result.set(nRow, nCol, sum);
            }

            while (j < mat_t.data.size() && mat_t.data[j].row == nCol)  j++;    // the rest of matrix
        }
        while (i < this->data.size() && this->data[i].row == nRow)  i++;        // the rest of other matrix
    }
    return result;
}

// Problem doesn't require implementation of "+" operation. Including it for completeness.
template <typename T> 
SparseMatrix<T> SparseMatrix<T>::operator+(const SparseMatrix& mat) const{
    if(this->m_rows != mat.cols() || this->m_cols != mat.rows())
        throw "For addition, rows and cols must match for two matrices!";

    SparseMatrix<T> result(this->m_rows, this->m_cols);
    uint i = 0, j = 0;      // take pointers (two-pointers) to each matrix and advance to do addition

    while(i < this->data.size() && j < mat.data.size()){
        if(this->data[i].row < mat.data[j].row || (this->data[i].row == mat.data[j].row && this->data[i].col < mat.data[j].col)){
            result.set(this->data[i].row, this->data[i].col, this->data[i].value);
            i++;
        }

        else if(this->data[i].row > mat.data[j].row || (this->data[i].row == mat.data[j].row && this->data[i].col > mat.data[j].col)){
            result.set(mat.data[j].row, mat.data[j].col, mat.data[j++].value);
            j++;
        }

        else{
            result.set(this->data[i].row, this->data[i].col, this->data[i].value + mat.data[j].value);
            i++;
            j++;
        }
    }

    while(i < this->data.size()){
        result.set(this->data[i].row, this->data[i].col, this->data[i].value);
        i++;
    }

    while(j < mat.data.size()){
        result.set(mat.data[j].row, mat.data[j].col, mat.data[j].value);
        j++;
    }

    return result;
}

// Problem doesn't require implementation of "-" operation. Including it for completeness.
template <typename T> 
SparseMatrix<T> SparseMatrix<T>::operator-(const SparseMatrix& mat) const{
    if(this->m_rows != mat.cols() || this->m_cols != mat.rows())
        throw "For subtraction, rows and cols must match for two matrices!";

    SparseMatrix<T> result(this->m_rows, this->m_cols);
    uint i = 0, j = 0;      // very similar to case of addition operation

    while(i < this->data.size() && j < mat.data.size()){
        if(this->data[i].row < mat.data[j].row || (this->data[i].row == mat.data[j].row && this->data[i].col < mat.data[j].col)){
            result.set(this->data[i].row, this->data[i].col, this->data[i].value);
            i++;
        }

        else if(this->data[i].row > mat.data[j].row || (this->data[i].row == mat.data[j].row && this->data[i].col > mat.data[j].col)){
            result.set(mat.data[j].row, mat.data[j].col, - mat.data[j].value);
            j++;
        }

        else{
            result.set(this->data[i].row, this->data[i].col, this->data[i].value - mat.data[j].value);
            i++;
            j++;
        }

    }

    while(i < this->data.size()){
        result.set(this->data[i].row, this->data[i].col, this->data[i].value);
        i++;
    }

    while(j < mat.data.size()){
        result.set(mat.data[j].row, mat.data[j].col, - mat.data[j].value);
        j++;
    }

    return result;
}

template <typename T> 
bool SparseMatrix<T>::operator==(const SparseMatrix& mat) const{    // this will only work for non-floating point values
    if(this->data.size() != mat.data.size())
        return false;
    
    for(uint i = 0; i < this->data.size(); i++){
        if(this->data[i].row == mat.data[i].row && this->data[i].col == mat.data[i].col && this->data[i].value == mat.data[i].value)  continue;
        else    return false;
    }
    return true;
}

template <typename T> 
bool SparseMatrix<T>::operator!=(const SparseMatrix& mat) const{
    if(*this == mat)    return false;
    else                return true;
}

template <typename T> 
bool SparseMatrix<T>::almostEqual(const SparseMatrix& mat, double epsilon) const{       // alternative to == operation for floating-point values
    if(this->data.size() != mat.data.size())
        return false;

    for(uint i = 0; i < this->data.size(); i++){
        if(this->data[i].row == mat.data[i].row && this->data[i].col == mat.data[i].col && (this->data[i].value - mat.data[i].value < epsilon))   continue;
        else    return false;
    }    
    return true;
}


template <typename T> 
uint SparseMatrix<T>::rows() const {      
    return this->m_rows;    
}

template <typename T> 
uint SparseMatrix<T>::cols() const {      
    return this->m_cols;    
}

template <typename T> 
uint SparseMatrix<T>::size() const {      
    return data.size();     
}

template <typename T> 
void SparseMatrix<T>::print(bool full) const{
    if(full){
        for(int i = 0; i < m_rows; i++){
            for(int j = 0; j < m_cols; j++){
                if(this->get(i, j) != 0)
                    std::cout << this->get(i,j) << "    ";
                else
                    std::cout << "0" << "   ";
            }
            std::cout << std::endl;
        }
    }
    else{
        std::cout << "(ROW, COL, VAlUE)" << std::endl;
        for(auto& it : this->data){
            std::cout << "(" << it.row << ", " << it.col << ", " << it.value << ")" << std::endl;
        }
    }
}

template <typename T> 
void SparseMatrix<T>::transpose(){
    for(unsigned int i=0; i< this->data.size(); ++i)
        std::swap(this->data[i].row, this->data[i].col);            
    std::sort(this->data.begin(), this->data.end(), [](const Element<T>& e1, const Element<T>& e2) { return e1.row < e2.row; } );        
}

template <typename T> 
SparseMatrix<T> SparseMatrix<T>::copy() const{
    SparseMatrix<T> _copy(this->m_rows, this->m_cols);   
    _copy.data = this->data;
    return _copy;
}

#endif