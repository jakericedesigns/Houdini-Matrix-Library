struct Cholesky{
    float L[];
    float LT[];
    int n;

    large_mat extractlower(){
        return large_mat(L, n, n);
    }
    large_mat extractconjugate(){
        return large_mat(LT, n, n);
    }

}



Cholesky CholDecomp(large_mat A){
    //doolittle's algo
    
    //SOMETHING FUCKY IS HAPPENING
    large_mat lower, conjugate;
    lower->buildmat(A.cols, A.rows);
    conjugate->buildmat(A.cols, A.rows); 
    
    if(A.rows != A.cols){
        printf("ERROR: Matrix is not square, returning LLT = 0 \n");
        return Cholesky(lower.mat, conjugate.mat, A.rows);
    }
    

    int n = A.rows;

    for(int i = 0; i  < n; i++){
        
        //build upper
        for(int j = 0; j <= i; j++){
            float sum = 0.;
            if(j == i){
                for(int k = 0; k < j; k++){
                    sum += pow(lower->val(j, k), 2);
                }
               // printf("%g", sum);
                int index = lower->index(j, j);
                lower.mat[index] = sqrt(A->val(j, j) - sum);
            }else{
                for(int k = 0; k < j; k++){
                    sum += lower->val(i, k) * lower->val(j, k);
                }
               // printf("%g", sum);
                int index = lower->index(i, j);
                lower.mat[index] = (A->val(i, j) - sum) / lower->val(j, j);

            }
        }

    }
    conjugate = lower->largetranspose();
    return Cholesky(lower.mat, conjugate.mat, A.rows);    
}





large_mat solveLx(large_mat L, x){   

    large_mat a;
    a->buildmat(x.cols, 1);
    large_mat x_temp = x;
    //WOKRING VERSION PREVIOUSLY DID NOT SUBTRACT 1, THIS IS A TEST
    for(int j = 0; j <= L.cols - 1; j++){
        a.mat[j] = x_temp.mat[j] / L->val(j, j);

        for(int i = j + 1; i <= L.cols; i++){ 
            x_temp.mat[i] = x_temp.mat[i] - (L->val(i, j) * a.mat[j]);
            
        }
    }
    return a;
}

large_mat solveUx(large_mat U, x){   
    large_mat a;
    a->buildmat(x.cols, 1);
    large_mat x_temp = x;
    //WOKRING VERSION PREVIOUSLY DID NOT SUBTRACT 1, THIS IS A TEST
    for(int j = U.cols - 1; j >= 0; j--){
        a.mat[j] = x_temp.mat[j] / U->val(j, j);

        for(int i = 0; i <= j; i++){ 
            x_temp.mat[i] = x_temp.mat[i] - (U->val(i, j) * a.mat[j]);
            
        }
    }
    return a;
} 


large_mat solveChol(Cholesky A; large_mat b){
    //solve Ax = b by decomposing into LUx = b
    //decompose further into Ly = b where Ux = y

    large_mat upper = A->extractconjugate();
    large_mat lower = A->extractlower();

    large_mat y = solveLx(lower, b);
    y = solveUx(upper, y);

    return y;
}

large_mat solveChol(large_mat L, LT, b){
    //solve Ax = b by decomposing into LUx = b
    //decompose further into Ly = b where Ux = y

    large_mat y = solveLx(L, b);
    y = solveUx(U, y);

    return y;
}


large_mat CholInverse(large_mat A){
    large_mat storage = A;
    LU decomp = LUDecomp(A);

    large_mat ident;
    ident->largeident(A.rows);

    large_mat lower = decomp->extractlower();
    large_mat upper = decomp->extractconjugate();

    
    for(int i = 0; i < A.rows; i++){
        large_mat b;
        b->buildvect(ident->getcol(i));
        large_mat inverse = solveChol(lower, upper, b);
        ident->setcol(i, inverse.mat);
    }

    return ident;
}       