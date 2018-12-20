#include <iostream>
#include <vector>
#include <fstream>
// #include <stdlib.h> 
#include "sparsematrix.hpp"

bool squareMatrixMultiplication(){
    SparseMatrix<int> m1(10, 10);
    m1.set(0, 0, 1);
    m1.set(0, 4, 2);
    m1.set(0, 8, 3);
    m1.set(1, 2, 4);
    m1.set(1, 6, 5);
    m1.set(2, 9, 12);
    m1.set(3, 4, 6);
    m1.set(4, 6, 7);
    m1.set(5, 0, 11);
    m1.set(6, 2, 8);
    m1.set(8, 9, 10);
    m1.set(9, 4, 9);

    SparseMatrix<int> m2(10, 10);
    m2.set(0, 0, 11);
    m2.set(0, 3, 12);
    m2.set(0, 7, 13);
    m2.set(2, 1, 1);
    m2.set(2, 5, 2);
    m2.set(2, 7, 3);
    m2.set(5, 0, 5);
    m2.set(7, 8, 7);
    m2.set(8, 1, 4);
    m2.set(9, 5, 6);
    m2.set(9, 9, 8);

    auto m1m2 = m1 * m2;
    //m1m2.print();
    
    SparseMatrix<int> m1m2_expected(10, 10);    // expected result is calculated using Python Numpy
    m1m2_expected.set(0, 0, 11);
    m1m2_expected.set(0, 1, 12);
    m1m2_expected.set(0, 3, 12);
    m1m2_expected.set(0, 7, 13);
    m1m2_expected.set(1, 1, 4);
    m1m2_expected.set(1, 5, 8);
    m1m2_expected.set(1, 7, 12);
    m1m2_expected.set(2, 5, 72);
    m1m2_expected.set(2, 9, 96);
    m1m2_expected.set(5, 0, 121);
    m1m2_expected.set(5, 3, 132);
    m1m2_expected.set(5, 7, 143);
    m1m2_expected.set(6, 1, 8);
    m1m2_expected.set(6, 5, 16);
    m1m2_expected.set(6, 7, 24);
    m1m2_expected.set(8, 5, 60);
    m1m2_expected.set(8, 9, 80);

    if(m1m2 != m1m2_expected){
        std::cout << "m1 * m2 @ squareMatrixMultiplication FAIL" << std::endl;
        return false;
    }
    
    SparseMatrix<double> m3(10, 10);
    m3.set(0, 0, 0.1);
    m3.set(0, 4, 0.4);
    m3.set(0, 8, 0.9);
    m3.set(2, 0, 2.0);
    m3.set(2, 1, 2.1);
    m3.set(2, 4, 2.4);
    m3.set(2, 8, 2.9);
    m3.set(3, 6, 3.6);
    m3.set(5, 2, 7.9);
    m3.set(6, 6, 9.9);
    m3.set(7, 0, 7.7);
    m3.set(8, 3, 4.4);
    m3.set(8, 9, 8.8);
    m3.set(9, 1, 6.6);
    m3.set(9, 7, 8.8);

    SparseMatrix<double> m4(10, 10);
    m4.set(0, 0, 1.1);
    m4.set(0, 9, 11);
    m4.set(1, 3, 2.2);
    m4.set(2, 6, 3.3);
    m4.set(3, 3, 8.8);
    m4.set(4, 0, 10);
    m4.set(4, 5, 12.4);
    m4.set(5, 8, 4.4);
    m4.set(6, 5, 9.9);
    m4.set(7, 2, 7.7);
    m4.set(8, 7, 5.5);
    m4.set(9, 5, 6.6);

    auto m3m4 = m3 * m4;
    // m3m4.print();

    SparseMatrix<double> m3m4_expected(10, 10);
    m3m4_expected.set(0, 0, 4.11);
    m3m4_expected.set(0, 5, 4.96);
    m3m4_expected.set(0, 7, 4.95);
    m3m4_expected.set(0, 9, 1.1);
    m3m4_expected.set(2, 0, 26.2);
    m3m4_expected.set(2, 3, 4.62);
    m3m4_expected.set(2, 5, 29.76);
    m3m4_expected.set(2, 7, 15.95);
    m3m4_expected.set(2, 9, 22);
    m3m4_expected.set(3, 5, 35.64);
    m3m4_expected.set(5, 6, 26.07);
    m3m4_expected.set(6, 5, 98.01);
    m3m4_expected.set(7, 0, 8.47);
    m3m4_expected.set(7, 9, 84.7);
    m3m4_expected.set(8, 3, 38.72);
    m3m4_expected.set(8, 5, 58.08);
    m3m4_expected.set(9, 2, 67.76);
    m3m4_expected.set(9, 3, 14.52);

    // Because floating point cannot be compared with ==, use almostEqual instead with epsilon parameter setting
    if(!m3m4.almostEqual(m3m4_expected)){
        std::cout << "m3 * m4 @ squareMatrixMultiplication FAIL" << std::endl;
        return false;
    }

    return true;
}

bool rectangleMatrixMultiplication(){
    SparseMatrix<int> m1(20, 10);
    m1.set(0, 0, 1);
    m1.set(0, 3, 2);
    m1.set(0, 6, 3);
    m1.set(6, 8, 6);
    m1.set(8, 2, 4);
    m1.set(13, 1, 7);
    m1.set(13, 7, 5);
    m1.set(16, 6, 8);
    m1.set(19, 7, 9);

    SparseMatrix<int> m2(10, 20);
    m2.set(0, 2, 1);
    m2.set(0, 10, 2);
    m2.set(1, 17, 3);
    m2.set(3, 2, 8);
    m2.set(4, 12, 9);
    m2.set(6, 4, 7);
    m2.set(6, 19, 4);
    m2.set(8, 9, 6);
    m2.set(9, 16, 5);

    auto m1m2 = m1 * m2;
    // m1m2.print();

    SparseMatrix<int> m1m2_expected(20, 20);
    m1m2_expected.set(0, 2, 17);
    m1m2_expected.set(0, 4, 21);
    m1m2_expected.set(0, 10, 2);
    m1m2_expected.set(0, 19, 12);
    m1m2_expected.set(6, 9, 36);
    m1m2_expected.set(13, 17, 21);
    m1m2_expected.set(16, 4, 56);
    m1m2_expected.set(16, 19, 32);

    if(m1m2 != m1m2_expected){
        std::cout << "m1 * m2 @ rectangleMatrixMultiplication FAIL" << std::endl;
        return false;
    }    

    return true;
}

int main(int argc, char * argv []){

    bool result1 = squareMatrixMultiplication();
    bool result2 = rectangleMatrixMultiplication();

    if(result1 && result2)
        std::cout << "All tests passed!" << std::endl;   
    
    // text file test input 
    std::ifstream m1("tests/m1.txt");
    std::ifstream m2("tests/m2.txt");
    std::string line;
    
    std::vector<std::vector<int>> m1_vec;
    std::vector<std::vector<int>> m2_vec;

    if (m1.is_open()){
        while(getline(m1, line)){
            std::vector<int> line_vec;
            for(auto& i : line){
                if(i != ' ')
                    line_vec.push_back(i - '0');
            }
            m1_vec.push_back(line_vec);        
        }
        m1.close();
    }

    if (m2.is_open()){
        while(getline(m2, line)){
            std::vector<int> line_vec;
            for(auto& i : line){
                if(i != ' ')
                    line_vec.push_back(i - '0');
            }
            m2_vec.push_back(line_vec);
        }
        m2.close();
    }

    int rows = m1_vec.size();
    int cols = m1_vec[0].size();
    SparseMatrix<int> m1_mat(rows, cols);

    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            if(m1_vec[i][j] != 0) m1_mat.set(i, j, m1_vec[i][j]);

    rows = m2_vec.size();
    cols = m2_vec[0].size();
    SparseMatrix<int> m2_mat(rows, cols);

    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            if(m2_vec[i][j] != 0) m2_mat.set(i, j, m2_vec[i][j]);

    auto m1m2 = m1_mat * m2_mat;

    SparseMatrix<int> m1m2_expected(20, 20);    // expected result is calculated using Python Numpy
    m1m2_expected.set(2, 15, 6);
    m1m2_expected.set(5, 10, 27);
    m1m2_expected.set(7, 5, 16);
    m1m2_expected.set(9, 10, 9);
    m1m2_expected.set(11, 3, 45);
    m1m2_expected.set(14, 16, 45);
    m1m2_expected.set(15, 17, 49);
    m1m2_expected.set(19, 2, 30);
    m1m2_expected.set(19, 14, 63);

    if(m1m2 == m1m2_expected)
        std::cout << "Text test passed!" << std::endl;

    return 0;
}