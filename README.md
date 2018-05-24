# Houdini Matrix Library
### Here's a library for large linear operations with VEX in Houdini. 
#### ALPHA RELEASE 002
Don't use this for anything important, like it's not going to be fast, it's being written for learning purposes. A better tool for this is without a doubt SciPy or if you're really feeling it, Eigen (C++)

ALPHA 002 NOTES: We added a cholesky decomp method as well as changed all construction methods to be as effecient as possible. Note the changes to the below readme.



## USAGE

This is a framework for NxM matrix operations in Houdini, to get started simply clone the repo `https://github.com/jakericedesigns/Houdini-Matrix-Library.git` or download it on github. 

One method of installation involves doing a custom include path in your `houdini.env` but I'm honestly too lazy to figure out what that is. I think Nick Taylor's Aelib does something like that, you can stalk his repo if you desperately want to do that, otherwise just `#include PATH/TO/THE/INCLUDE/largeMat.h` in your wrangles like a normal human.

### Matrices and vectors are column major in operation and construction.

Matrices are stored in as a `large_mat` struct. I gave a few different constructor methods for building your matrices. Below are a few different methods:

```c

large_mat A;
A->buildmat(3, 3); //(columns, rows), initializes an empty matrix

matrix3 m = ident();
large_mat B;
B->buildmat(m); //build matrix from Houdini matrices, works with all types of matrices, 4x4 and below.

float mat[] = [1, 0, 0, 1];
large_mat C = large_mat(mat, 2, 2); //float arrays can be used to fill the large_mat by just setting the struct members

int N = 2;
large_mat D;
D->largeident(N); //builds an identity matrix of size NxN

```

Vectors, like matrices are stored as a `large_mat`. Like Eigen, vectors are just treated as Nx1 matrices. Vectors are default column vectors, and will need to be transposed into row vectors if you're into that kind of thing. 
Here's how to quickly build vectors:

```c
vector x_temp = {1,0,0};
large_mat x = largevect(x_temp); //works with all vector types

//construction with float arrays
float vect[] = [1, 0, 0, 1, 5, 1, 2, 3, 5, 8];
large_mat y;
y->largevect(vect);
```

Let's computer the outer product of vector **b** and its' transpose **b^T** for our first useage example:

```c
#include "PATH_TO_HEADER/largeMat.h"

float b_init[] = {1, 2, 3, 4, 5, 6 ,7 ,8};
large_mat b;
b->largevect(b);

b->matrixproduct(b->largetranspose()); //matrix multiplication works between NxM and MxP sized inputs.
b->printAsCols(); 
```

And then this is the expected result of that snippet:
```
{1, 2, 3, 4, 5, 6, 7, 8} 
{2, 4, 6, 8, 10, 12, 14, 16} 
{3, 6, 9, 12, 15, 18, 21, 24} 
{4, 8, 12, 16, 20, 24, 28, 32} 
{5, 10, 15, 20, 25, 30, 35, 40} 
{6, 12, 18, 24, 30, 36, 42, 48} 
{7, 14, 21, 28, 35, 42, 49, 56} 
{8, 16, 24, 32, 40, 48, 56, 64} 
```
Can't do that in vex by default, now can you? :smirk:


Currently all solvers and decompositions live in their own include files, so be sure to check those out. The currently implemented methods are as follows:

`SVDecomp()` - Returns a struct SVD which contains the 3 decomposed matrices, U, Sigma and V. This will work for non square matrices. Keep in mind that this currently uses the power method and is therefore not stable. You will get unexpected sign flipping. Should be updated to use householder reflections, but I'm too lazy currently.

`LUDecomp()` - Returns a struct LU, which contains your upper and lower triangular matrices (currently due to a bug you must use the `extractupper()/extractlower()` functions to extract a large_mat from the LU Struct, will reach out to sidefx for help soon).
+`solveLU()` takes in an LU struct and some vector `b` and solves for `Ax = b`
+`LUDeterminant()` takes in an LU struct and returns the matrix's determinant
+`LUInverse()` takes in an LU struct and returns the matrix's inverse

`CholDecomp()` - Returns a struct Chol, which contains your lower triangular matrix and its conjugate transpose. 
+`solveChol()` takes a struct Chol and some vector `b` and solves for `Ax = b`

## TO DO:
1. I'd love to go back through and ensure that all functions work with the column major way I've written this. (looking at you SVD and Cholesky)
2. Add in a Conjugate Gradient solver. 
3. Add in sparse and diagonal type matrices for added speed.
4. More constructor methods.
5. Convert all this vex into C++ to improve both speed and ease of use through custom C++ vex functions.
