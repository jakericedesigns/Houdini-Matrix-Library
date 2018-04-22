struct LU{
   large_mat A;
   large_mat U;
   large_mat L;
}



LU LUDecomp(large_mat A){
    //doolittle's algo
    

    large_mat lower = buildmat(A.cols, A.rows);
    large_mat upper = buildmat(A.cols, A.rows); 
    
    if(A.rows != A.cols){
        printf("ERROR: Matrix is not square, returning UL = 0 \n");
        return LU(A, upper, lower);
    }
    

    int n = A.rows;

    for(int i = 0; i  < n; i++){
        //build upper

        for(int k = i; k < n; k++){
            float sum = 0;
            for(int j = 0; j < i; j++){
                sum += lower->val(i, j) * upper->val(j, k);
            }
            int index = upper->index(i, k);
            upper.mat[index] = A->val(i, k) - sum;

        }
        //set lower
        for (int k = i; k < n; k++) {
            if(i == k){
                int index = lower->index(i, i);
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
    return LU(A, upper, lower);    
}
