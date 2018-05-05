
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
			printf("Converged in %g iterations!", i);
			break;
		}
	}	
	return curr_v;
}