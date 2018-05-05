struct large_mat{
	float mat[];

	int cols = 1;
	int rows = 1;

	int rowsize(){ return len(mat) / cols; }
	int colsize(){ return len(mat) / rows; }

	//int index(int colIdx, rowIdx){ return colIdx * cols + rowIdx; }
	int index(int colIdx, rowIdx){ return colIdx + rowIdx * this.cols;}
	float val(int colIdx, rowIdx){ return mat[ this->index(colIdx, rowIdx) ]; }


/*------------------------MATRIX HELPER FUNCTIONS-------------------------------*/

	//convert these into array slices for speed 
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


	void setcol(int row_i; float vals[]){
		if(len(vals) != cols){
			printf("ERROR: Col Size Missmatch");
			return;
		} 
		for(int i = 0; i < this.cols; i++){
				this.mat[this->index(i, row_i)] = vals[i];
		}
	}

	void resizemat(int columns, rows){
			if(columns == 0 || rows == 0){
				printf("ERROR: Matrix cannot have 0 Rows or Columns");
				return;
			}
			this.cols = columns;
			this.rows = rows;
			resize(this.mat, columns * rows);
	}
	void buildvect(float A[]){
		if(len(A) <= 0){
			printf("ERROR: Array Must be Larger than len 0");
			return;
		}
		this.mat = A;
		this.cols = len(A);
		this.rows = 1;
	}

	void setrow(int col_i; float vals[]){
		if(len(vals) != rows){
			printf("ERROR: Row Size Missmatch");
			return;
		} 
		for(int i = 0; i < this.rows; i++){
				this.mat[this->index(col_i, i)] = vals[i];
		}
	}

	void swaprows(int row_A, row_B){
		float B[] = this->getrow(row_B);
		this->setrow(row_B, this->getrow(row_A));
		this->setrow(row_A, B);
	}

	void swapcols(int col_A, col_B){
		float B[] = this->getrow(col_B);
		this->setcol(col_B, this->getrow(col_A));
		this->setcol(col_A, B);
	}
	//

	void flatten(){
		this.cols = this.cols * this.rows;
		this.rows = 1;
	}

	void fillrandom(){
		foreach(int index; float val; this.mat){
			mat[index] = (rand(index + val) - .5) * 2.;
		}
	}
	
	void fillrandom(int seed){
		foreach(int index; float val; this.mat){
			mat[index] = (rand(index + val + seed) - .5) * 2.;
		}
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


/*------------------------VECTOR CONSTRUCTORS-------------------------------*/
	//vectors by default are column vectors
	void largevect(float x[]){
	        this.mat = x;
	        this.cols = len(x);
	        this.rows = 1;
	}

	void largevect(vector2 x){
	        float array[] = array(x[0], x[1]);
	       	
	       	this.mat = array;
	        this.cols = 2;
	        this.rows = 1;
	}

	void largevect(vector x){
	        float array[] = array(x[0], x[1], x[2]);

	        this.mat = array;
	        this.cols = 3;
	        this.rows = 1;
	}

	//i dont support quaternion rotations yet cuz fuck off.
	void largevect(vector4 x){
	        float array[] = array(x[0], x[1], x[2], x[3]);
	        this.mat = array;
	        this.cols = 4;
	        this.rows = 1;
	}	



/*------------------------Matrix CONSTRUCTORS-------------------------------*/

	void buildmat(int new_col, new_row){
		this.rows = new_row;
		this.cols = new_col;
		resize(this.mat, new_col * new_row);
	}

	void buildmat(matrix3 m){
		this.rows = 3;
		this.cols = 3;
		this.mat = set(m);
	}

	void buildmat(matrix m){
		this.rows = 4;
		this.cols = 4;
		this.mat = set(m);
	}

	void buildmat(matrix2 m){
		this.rows = 2;
		this.cols = 2;
		this.mat = array(m.xx, m.xy, m.yx, m.yy);
	}


	void largeident(int size){
		this.rows = size;
		this.cols = size;
		resize(this.mat, rows * rows);
		for(int i = 0; i < rows; i++){
			int index = this->index(i, i);
			this.mat[index] = 1;
		}
	}




/*------------------------MATRIX OPERATORS-------------------------------*/
	void largetranspose(){
		large_mat A = this;
		A.rows = this.cols;
		A.cols = this.rows;

		for(int i = 0; i < this.cols; i++){
			for(int j = 0; j < this.rows; j++){
				A.mat[A->index(j, i)] = this->val(i, j);
			}
		}
		this = A;
	}
	
	void matrixproduct(large_mat B){
		if(this.rows != B.cols){
			printf("ERROR: Matrix Size Mismatch");
			return;
		} 
		large_mat C;
		C->buildmat(this.cols, B.rows);

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
	
	void matrixmultconst(float b){
	
		foreach(int i; float val; this.mat){
		    this.mat[i] = val * b;
		}
	}
	void matrixdivconst(float b){
	
		foreach(int i; float val; this.mat){
		    this.mat[i] = val / b;
		}
	}


	float vect_norm(){
		float sum = 0;	
		foreach(float a; this.mat){
			sum += a * a;
		}
		return sqrt(sum);
	}
	/*
	void reordermat(){
		int order[];
		for(int i = 0; i < this.rows; i++){
			for(int j = 0; j < this.cols; j++){
				int idx = this->index(j, i);
				append(order, idx);
				
			
			}
		}
		printf("%g \n", order);
		this.mat = reorder(this.mat, order);
	}
	*/
}




float dotproduct(large_mat A, B){
	if(len(A.mat) != len(B.mat)){
		printf("what the fuck are you even trying rn tho \n");
		return 0.0;
	} 

	float sum = 0.0;
	foreach(int i; float currVal; A.mat){
		sum += currVal * B.mat[i];
	}
	return sum;
}





large_mat matrixproduct(large_mat A, B){
	if(A.rows != B.cols){
			printf("ERROR: Matrix Size Mismatch");
			return A;
	}


	large_mat C;
	C->buildmat(A.cols, B.rows);

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
	large_mat B;
	B->buildmat(A.rows, A.cols);

	for(int i = 0; i < A.cols; i++){
		for(int j = 0; j < A.rows; j++){
			B.mat[B->index(j, i)] = A->val(i, j);

		}
	}

		return B;
}

large_mat matrixmultconst(large_mat A; float b){

	foreach(int i; float val; A.mat){
	    A.mat[i] = val * b;
	}
	return A;
}
large_mat matrixdivconst(large_mat A; float b){

	foreach(int i; float val; A.mat){
	    A.mat[i] = val / b;
	}
	return A;
}

large_mat mataugment(large_mat A, B){
	large_mat OUT;
	OUT->buildmat(A.cols * 2, A.rows);
	for(int i = 0; i < OUT.cols; i++){
			for(int j = 0; j < OUT.rows; j++){
				if(i < A.cols){
					OUT.mat[OUT->index(i, j)] = A->val(i, j);
				}else{
					OUT.mat[OUT->index(i, j)] = B->val(i % A.cols, j);
				}
			}
	}
	return OUT;
}

