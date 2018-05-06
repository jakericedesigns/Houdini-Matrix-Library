struct LU{
    float L[];
    float U[];
    int n;

    large_mat extractlower(){
        return large_mat(L, n, n);
    }
    large_mat extractupper(){
        return large_mat(U, n, n);
    }

}



LU LUDecomp(large_mat A){
    //doolittle's algo
    
    //SOMETHING FUCKY IS HAPPENING
    large_mat lower, upper;
    lower->buildmat(A.cols, A.rows);
    upper->buildmat(A.cols, A.rows); 
    
    if(A.rows != A.cols){
        printf("ERROR: Matrix is not square, returning UL = 0 \n");
        return LU(lower.mat, upper.mat, A.rows);
    }
    

    int n = A.rows;

    for(int i = 0; i  < n; i++){
        
        //build upper
        for(int k = i; k < n; k++){
            float sum = 0.;
            for(int j = 0; j < i; j++){
                sum += lower->val(i, j) * upper->val(j, k);

            }
           // printf("%g", sum);
            int index = upper->index(i, k);
            upper.mat[index] = A->val(i, k) - sum;

        }
        //set lower
        for (int k = i; k < n; k++) {
            if(i == k){
                int index = lower->index(i, k);
                lower.mat[index] = 1.; //diag == 1
            }else{

                float sum = 0.;
                for(int j = 0; j < i; j++){
                    sum += lower->val(k, j) * upper->val(j, i);
                }
                int index = lower->index(k, i);
                lower.mat[index] = (A->val(k, i) - sum) / upper->val(i,i);

            }

        }    

    }
    return LU(lower.mat, upper.mat, A.rows);    
}


float LUDeterminant(LU LUP){
    //determinant of a triangular matrix is the product of the diagonals

    float detU = 1.;
    float detL = 1.;

    large_mat L = large_mat(LUP.L, LUP.n, LUP.n);
    large_mat U = large_mat(LUP.U, LUP.n, LUP.n);

    for(int i = 0; i < LUP.n; i++){
        detL *= L->val(i, i);
        detU *= U->val(i, i);
    }
    return detU * detL;    
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


large_mat solveLU(LU A; large_mat b){
    //solve Ax = b by decomposing into LUx = b
    //decompose further into Ly = b where Ux = y

    large_mat upper = A->extractupper();
    large_mat lower = A->extractlower();

    large_mat y = solveLx(lower, b);
    y = solveUx(upper, y);

    return y;
}

large_mat solveLU(large_mat L, U, b){
    //solve Ax = b by decomposing into LUx = b
    //decompose further into Ly = b where Ux = y

    large_mat y = solveLx(L, b);
    y = solveUx(U, y);

    return y;
}


large_mat LUInverse(large_mat A){
    large_mat storage = A;
    LU decomp = LUDecomp(A);

    large_mat ident;
    ident->largeident(A.rows);

    large_mat lower = decomp->extractlower();
    large_mat upper = decomp->extractupper();

    
    for(int i = 0; i < A.rows; i++){
        large_mat b;
        b->buildvect(ident->getcol(i));
        large_mat inverse = solveLU(lower, upper, b);
        ident->setcol(i, inverse.mat);
    }

    return ident;
}       