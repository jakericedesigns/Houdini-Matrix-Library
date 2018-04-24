struct large_mat{
	float mat[];

	int cols;
	int rows;

	int rowsize(){ return len(mat) / cols; }
	int colsize(){ return len(mat) / rows; }

	//int index(int colIdx, rowIdx){ return colIdx * cols + rowIdx; }
	int index(int colIdx, rowIdx){ return colIdx + rowIdx * rows; }
	float val(int colIdx, rowIdx){ return mat[ this->index(colIdx, rowIdx) ]; }

	//convert these into array slices for speec 
	function float[] getcol(int row_i){
		float vect[];
		for(int i = 0; i < this.cols; i++){
			append(vect, this->val(i, row_i));
		}
		return vect;
	}

	
	function float[] getrow(int col_i){
		float vect[];
		for(int i = 0; i < this.rows; i++){
			append(vect, this->val(col_i, i));
		}
		return vect;
	}
	//




	void flatten(){
		this.cols = this.cols * this.rows;
		this.rows = 1;
	}

	
	void largetranspose(){
		large_mat A = this;

		for(int i = 0; i < this.cols; i++){
			for(int j = 0; j < this.rows; j++){
				A.mat[A->index(j, i)] = this->val(i, j);
			}
		}
		this = A;
	}
	

	void printAsRows(){
		for(int i = 0; i < this.cols; i++){
			printf("%g \n", this->getrow(i));
		}
	}

	void printAsCols(){
		for(int i = 0; i < this.rows; i++){
			printf("%g \n", this->getcol(i));
		}
	}


	void matrixproduct(large_mat B){
		if(this.cols != B.rows){
			printf("ERROR: Matrix Size Mismatch");
			return;
		} 
		large_mat C;

		resize(C.mat, this.cols * B.rows);
		C.cols = this.cols;
		C.rows = B.rows;

		for(int i = 0; i < this.cols; i++){
			for(int j = 0; j < B.rows ; j++){
				int indexij = C->index(i, j);
				C.mat[indexij] = 0; 

				for(int k = 0; k <= B.cols; k++){
					C.mat[indexij] += this->val(i, k) * B->val(k, j);				
				}
				
			}
		}

		this = C;
	}

	void matrixadd(large_mat B){
		if(this.cols !=  B.cols || this.rows != B.rows){
			printf("ERROR: Matrix Size Mismatch");
			return;
		}
		foreach(int index; float val; this.mat){
			this.mat[index] += B.mat[index];
		}
	}

	void matrixsub(large_mat B){
		if(this.cols !=  B.cols || this.rows != B.rows){
			printf("ERROR: Matrix Size Mismatch");
			return;
		}
		foreach(int index; float val; this.mat){
			this.mat[index] -= B.mat[index];
		}
	}



}




float dotproduct(float a[], b[]){
	if(len(a) != len(b)){
		printf("what the fuck are you even trying rn tho \n");
		return 0.0;
	} 

	float sum = 0.0;
	foreach(int i; float currVal; a){
		sum += currVal * b[i];
	}
	return sum;
}


large_mat buildmat(int columns, rows){
	large_mat A;
	A.rows = rows;
	A.cols = columns;
	resize(A.mat, rows * columns);

	return A;
}

large_mat buildmat(matrix3 m){
	large_mat A;
	A.rows = 3;
	A.cols = 3;
	A.mat = set(m);
	return A;
}

large_mat buildmat(matrix m){
	large_mat A;
	A.rows = 4;
	A.cols = 4;
	A.mat = set(m);
	return A;
}

large_mat buildmat(matrix2 m){
	large_mat A;
	A.rows = 2;
	A.cols = 2;
	A.mat = array(m.xx, m.xy, m.yx, m.yy);
	return A;
}


large_mat largeident(int rows, columns){
	large_mat A;
	A.rows = rows;
	A.cols = columns;

	int i = 0;
	while(i < rows * columns){
		append(A.mat, 0);
		i++;
	}

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			if(i = j){
				int index = A->index(i, j);
				A.mat[index] = 1;
			} 
		}

	}

	return A;

}

//vectors by default are column vectors
large_mat largevect(float x[]){
        return large_mat(x, len(x), 1);
}

large_mat largevect(vector2 x){
        float array[] = array(x[0], x[1]);
        return large_mat(array, 2, 1);
}

large_mat largevect(vector x){
        float array[] = array(x[0], x[1], x[2]);
        return large_mat(array, 3, 1);
}

//i dont support quaternion rotations yet cuz fuck off.
large_mat largevect(vector4 x){
        float array[] = array(x[0], x[1], x[2], x[3]);
        return large_mat(array, 4, 1);
}

large_mat matrixproduct(large_mat A, B){
	if(A.cols != B.rows){
			printf("ERROR: Matrix Size Mismatch");
			return A;
	}
	large_mat C;

	resize(C.mat, A.cols * B.rows);
	C.cols = A.cols;
	C.rows = B.rows;

	for(int i = 0; i < A.cols; i++){
		for(int j = 0; j < B.rows ; j++){
			int indexij = C->index(i, j);
			C.mat[indexij] = 0; 

			for(int k = 0; k <= B.cols; k++){
				C.mat[indexij] += A->val(i, k) * B->val(k, j);				
			}
			
		}
	}

	return C;
}

large_mat matrixadd(large_mat A, B){
	large_mat C = A;

	if(C.cols !=  B.cols || C.rows != B.rows){
		printf("ERROR: Matrix Size Mismatch");
		return C;
	}

	foreach(int index; float val; C.mat){
		C.mat[index] += B.mat[index];
	}
	return C;
}

large_mat matrixsub(large_mat A, B){
	large_mat C = A;

	if(C.cols !=  B.cols || C.rows != B.rows){
		printf("ERROR: Matrix Size Mismatch");
		return C;
	}

	foreach(int index; float val; C.mat){
		C.mat[index] -= B.mat[index];
	}
	return C;
}

large_mat largetranspose(large_mat A){
	large_mat B = buildmat(A.rows, A.cols);
	for(int i = 0; i < A.cols; i++){
		for(int j = 0; j < A.rows; j++){

			B.mat[B->index(j, i)] = A->val(i, j);

		}
	}
	return B;
}