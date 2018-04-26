
The below code instantly crashes for me, the crash is even more intense if you uncomment the determinant code at the base. however if you do this with the non broken include, it should work...
Tbh im not sure if this matrix actually has a determinant, but that's totally besides the point, it shouldn't just crash.

```c
#include "PATH_TO_REPO\Houdini-Matrix-Library\largeMat.h" 
#include "PATH_TO_REPO\Houdini-Matrix-Library\largeMat_LU_BROKEN.h" 


float testerVector[] = {1, 2, 3, 4, 5, 6 ,7 ,8};
large_mat R = largevect(testerVector);
R->matrixproduct(R->largetranspose());

LU ALU = LUDecomp(R);



large_mat L = ALU.L;
large_mat U = ALU.U;
large_mat A = matrixproduct(L, U);


@rows = R.rows;
@cols = R.cols;


//@det = LUDeterminant(ALU);
```
