# sm
Sparse Matrix - Simple implementation of Sparse Matrix Operations in C++. 


Data Structure for Sparse matrix
Since there are lots of zeros, we only need to store nonzero elements. We can store each nonzero Element in a vector that describes the Matix 
ROW     COL     VAL
r01     c01     val01
r02     c02     val02
r03     c03     val03
r04     c04     val04
.....................
.....................
rmn     cmn     valmn

In following context, SIZE01 means size of vector that stores matrix 1, and similarly SIZE02 means size of vector that stores matrix 2
For multilication operation, only nonzero elements contribute to the result. Assuming matrix ROW and COL is in sorted order in input, first we transpose the second matrix and use one pointer for each vector and compare ROW, COL and VAL to do multilication operation. See implementation details. Complexity will be O(SIZE01 * SIZE02 * (SIZE01 + SIZE02)). Worst case performace (in case of full matrix) will be same as brute-force matrix multiplication complexity.

Addition operation is carried out in similar manner, except, no transpose is needed and we can do it in one iteration O(SIZE01 + SIZE02). 
Subtraction operation is carried out in similar manner, except, no transpose is needed and we can do it in one iteration O(SIZE01 + SIZE02). 

Test cases
I have included several test cases
1. squareMatrixMultiplication - for checking if algorithm works for square matrices. In case of floating point values (such as double), exact == cannot work, that's why I have included almostEqual function which will compare two floating-point matrices based on certain precision (precision can be set as parameter).
2. rectangleMatrixMultiplication - for checking if algorithm works for rectangular generic matrices.
3. test case as text file - I have included this case as an example to how to check matrix multilication using text files.
All expected value matrices has been calculated (and verified) with Python Numpy (matmul function). 