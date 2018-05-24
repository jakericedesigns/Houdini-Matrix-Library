
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
		if(i > len(A.mat) * 5){
			printf("DID NOT CONVERGE, num iterations: %g", i);
			break;
		} 
	}	
	return curr_v;
}


SVD SVDecomp(large_mat A){

	SVD current_svd;
	large_mat U, V, Sigma;

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
			
			u_temp->vect_outer(v_temp);
			u_temp->matrixmultconst(Sigma.mat[j]);
			
			matrix_for_decomp->matrixsub(u_temp->largetranspose());
		}
		large_mat v = Singular_Value(matrix_for_decomp, 1e-6);
		large_mat u = matrixproduct(A->largetranspose(), v);

		//Singular Value
		float sigma = vect_norm(u); 

		u->matrixdivconst(sigma);
		u->largetranspose();

		//U needs to be set column wise since theyre transposed in their current form
		U->setcol(i, u.mat);

		//since V is going to be square, we can use normal appending
		append(V.mat, v.mat);
		append(Sigma.mat, sigma);
	}

	Sigma.cols = len(Sigma.mat);

	return SVD(U, Sigma, V);

}