
struct SVD{
	large_mat U;
	large_mat Sigma;
	large_mat V;
}

large_mat Singular_Value(large_mat A; float k){
	large_mat v;
	v->resizemat(A.cols, 1);
	v->fillrandom(100);
	v->matrixdivconst(v->vect_norm());

	large_mat B = A;
	large_mat transpose = B->largetranspose();
	B->matrixproduct(transpose);



	large_mat last_v, curr_v = v;
	int i = 0;
	float epsilon = k;
	if(epsilon == 0.){
		epsilon = 1e-5;
	}
	while(i >= 0){
		i++;
		last_v = curr_v;
		curr_v = matrixproduct(B, curr_v);
		
		
		float norm = curr_v->vect_norm();
		curr_v = curr_v->matrixdivconst(norm);

		float test = dotproduct(curr_v, last_v);
		if(test > 1 - epsilon){
			//printf("Converged in %g iterations!", i);
			break;
		}
	}	
	return curr_v;
}


SVD SVDecomposition(large_mat A){
	SVD current_svd;
	large_mat U, V, Sigma;
	//U->buildmat(A.cols, A.rows);
	//V->buildmat(A.cols, A.cols);
	V.rows = A.cols;
	V.cols = A.cols;

	U.rows = A.rows;
	U.cols = A.cols;

	for(int i = 0; i < A.cols; i++){
		
		large_mat matrix_for_decomp = A;

		for(int j = 0; j < i; j++){
			large_mat u_temp;
			u_temp->buildvect(U->getrow(j));
			

			large_mat v_temp;
			v_temp->buildvect(V->getcol(j));
			
			v_temp->vect_outer(u_temp);
			large_mat temp_outer = v_temp;

			//large_mat temp_outer = matrixproduct_debug(u_temp, v_temp, "temp_outer \n");
			
			temp_outer->matrixmultconst(Sigma.mat[j]);
			//printf("J VAL %g \n", j);
			
			
			matrix_for_decomp->matrixsub(temp_outer);
			//matrix_for_decomp->printAsRows();
		}
		large_mat v = Singular_Value(matrix_for_decomp, 1e-6);
	    //printf("%g \n", v.mat);
		large_mat u = matrixproduct_debug(A->largetranspose(), v, "u_creation bug \n");
		float sigma = vect_norm(u); 
		//printf("SIGMA: %g \n", sigma);
		u->matrixdivconst(sigma);


		append(U.mat, u.mat);
		append(V.mat, v.mat);
		append(Sigma.mat, sigma);
	}

	Sigma.cols = len(Sigma.mat);

	return SVD(U, Sigma, V);

}