struct large_mat{
	float mat[];

	int cols;
	int rows;

	int rowsize(){ return len(mat) / cols; }
	int colsize(){ return len(mat) / rows; }

	int index(int colIdx, rowIdx){ return colIdx * cols + rowIdx; }
	float val(int colIdx, rowIdx){ return mat[ this->index(colIdx, rowIdx) ]; }

	
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

	void initmat(int columns, rows){

		
		this.cols = columns;
		this.rows = rows;
		this.mat = {0};

		for(int i = 0; i < (rows * columns) - 1; i++){
			append(this.mat, 0);
		}

	}
	

	void largetranspose(){
		large_mat A;
		A->initmat(this.cols, this.rows);
		for(int i = 0; i < this.cols; i++){
			for(int j = 0; j < this.rows; j++){
				A.mat[A->index(j, i)] = this->val(i, j);
			}
		}
		this = A;
	}


	void matrixproduct(large_mat B){
		if(this.cols != B.rows) return;
		large_mat C;
		
		C->initmat(B.cols, this.rows);

		for(int i = 0; i <= this.cols + 1; i++){
			for(int j = 0; j <= this.rows + 1; j++){
				
				int indexij = C->index(i, j);
				
				if(indexij >= B.cols * this.rows) continue;

				for(int k = 0; k <= C.cols; k++){
					C.mat[indexij] += this->val(i, k) * B->val(k, j);
				}
			}
		}
		this = C;
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

large_mat largetranspose(large_mat A){
	large_mat B;
	B->initmat(A.cols, A.rows);
	for(int i = 0; i < A.cols; i++){
		for(int j = 0; j < A.rows; j++){
			B.mat[B->index(j, i)] = A->val(i, j);
		}
	}
	return B;
}

large_mat buildmat(int rows, columns){
	large_mat A;
	A.rows = rows;
	A.cols = columns;

	int i = 0;
	while(i < rows * columns){
		append(A.mat, 0);
		i++;
	}
	return A;

}

large_mat buildmat(matrix3 m){
	large_mat A;
	A.rows = 3;
	A.cols = 3;
	A.mat = set(m);
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

}

//vectors by default are column vectors

large_mat largevect(float x[]){
        return large_mat(x, 1, len(x));
}

large_mat largevect(vector2 x){
        float array[] = array(x[0], x[1]);
        return large_mat(array, 1, 2);
}

large_mat largevect(vector x){
        float array[] = array(x[0], x[1], x[2]);
        return large_mat(array, 1, 3);
}

//i dont support quaternion rotations yet cuz fuck off.
large_mat largevect(vector4 x){
        float array[] = array(x[0], x[1], x[2], x[3]);
        return large_mat(array, 1, 4);
}
