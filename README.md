# Houdini Matrix Library
### This is so useless to so many people, but if you're idiotic enough to embark on a large matrix adventure in Houdini, let me aid you in your journey.



## USAGE

This is a framework for NxM matrix operations in Houdini, to get started simply clone the repo `https://github.com/jakericedesigns/Houdini-Matrix-Library.git` or download it on github. 

One method of installation involves doing a custom include path in your `houdini.env` but I'm honestly too lazy to figure out what that is. I think Nick Taylor's Aelib does something like that, you can stalk his repo if you desperately want to do that, otherwise just `#include PATH/TO/THE/INCLUDE/largeMat.h` in your wrangles like a normal human.

### Matrices and vectors are column major in operation and construction.

Matrices are stored in as a `large_mat` struct. I gave a few different constructor methods for building your matrices. Below are a few different methods:

```c

large_mat A = buildmat(3, 3); //(columns, rows), initializes an empty matrix

matrix3 m = ident();
large_mat B = buildmat(m); //build matrix from Houdini matrices, works with all types of matrices, 4x4 and below.

float mat[] = [1, 0, 0, 1];
large_mat C = large_mat(mat, 2, 2); //float arrays can be used to fill the large_mat by just setting the struct members

int N = 2;
large_mat D = largeident(N); //builds an identity matrix of size NxN

```

Vectors, like matrices are stored as a `large_mat`. Like Eigen, vectors are just treated as Nx1 matrices. Vectors are default column vectors, and will need to be transposed into row vectors if you're into that kind of thing. 
Here's how to quickly build vectors:

```c
vector x_temp = {1,0,0};
large_mat x = largevect(x_temp); //works with all vector types

//construction with float arrays
float vect[] = [1, 0, 0, 1, 5, 1, 2, 3, 5, 8];
large_mat y = largevect(vect);
```




