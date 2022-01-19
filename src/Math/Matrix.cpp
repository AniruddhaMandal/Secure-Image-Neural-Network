#include<iostream>
#include<math.h>
#include<fstream>
#include<Matrix.h>
#include<MathCal.h>
#include<ImRead.h>
#include<omp.h>


Matrix::Matrix() {
    this->row = 1;
    this->col = 1;
    this->values = new long double*[1];
    this->values[0] = new long double[1];
}
Matrix::Matrix(int _row, int _col) {
    this->row = _row;
    this->col = _col;
    this->values = new long double*[_row];
    for(int i=0; i<_row;i++) {
        this->values[i] = new long double[_col];
    }
}

/**
 * Converts Image into a Matrix type of grayscale image.
 * And it scales the pixel values down to [0,1].
*/
Matrix::Matrix(const Image &ImageObj) {
    this->row = 1024;
    this->col = 1;
    this->values = new long double*[this->row];
    for(int i=0; i<this->row; i++) {
        this->values[i] = new long double[this->col];
        this->values[i][0] = ((long double)(ImageObj.Blue[i]/3 + ImageObj.Green[i]/3 + ImageObj.Red[i]/3))/255;
    }
}


Matrix::~Matrix() {

	for(int i=0; i<this->row; i++) {
		delete[] this->values[i];
	}
	delete[] this->values;
}


void Matrix::Display() {
    std::cout<<"["<<std::endl;
    for(int i=0; i<this->row; i++) {
            std::cout<<"[";
            for(int j=0; j<this->col; j++) {
                printf("%.20Lf ", this->values[i][j]);
            }
            std::cout<<"]"<<std::endl;
        }
        std::cout<<"]\n";
    printf("Shape:(%d,%d)\n",this->row,this->col);
}


void Matrix::MatrixToCsv(const char* fileName) {
    printf("Writing to: %s\n",fileName);
    FILE* fpt = fopen(fileName,"w");
    if(fpt==NULL) {
        printf("[ERROR]: Failed to open file: %s\n", fileName);
        exit(EXIT_FAILURE);
    }

    for(int row=0;row<this->row;row++) {
        for(int col=0; col<this->col;col++) {
            fprintf(fpt,"%.20Lf,",this->values[row][col]);
        }
        fseek(fpt,-1L,SEEK_CUR);
        fprintf(fpt,"\n");
    }
    fclose(fpt);
}


Matrix Matrix::T() {
	Matrix T_matrix = Matrix(this->col, this->row);
    int i,j;
    #pragma omp parallel shared(T_matrix) private(i,j)
    {
    #pragma omp for schedule(static)
    for(i=0; i<this->row; i++)	{
        for(j=0; j<this->col;j++) {
            T_matrix.values[j][i] = this->values[i][j];
        }
    }
    }
    return T_matrix;
}


Matrix Matrix::operator*(const Matrix &Obj) {
    if(this->col != Obj.row) {
        std::cout<<"Dimensionality Error. Column("<<this->col<<") != Row("<<Obj.row<<")"<<std::endl;
        exit(EXIT_FAILURE);
    }
    Matrix Product = Matrix(this->row, Obj.col);
    long double sum;
    int row,col,i;
    #pragma omp parallel shared(Obj,Product) private(row,col,sum,i)
    {
    #pragma omp for schedule(static)
    for(row=0; row<this->row; row++) {
        for(col=0; col<Obj.col; col++) {
            sum = 0;
            for(i=0; i<this->col; i++) {
                sum += (this->values[row][i])*(Obj.values[i][col]);
            }
            Product.values[row][col] = sum;
        }
    }
    } 
    return Product;
}


Matrix Matrix::operator+(const Matrix &Obj) {
    if((this->row != Obj.row) & (this->col != Obj.col)) {
        std::cout<<"Dimension Not Compatable. ("<<this->row<<","<<this->col<<") != ("<<Obj.row<<", "<<Obj.col<<")"<<std::endl;
        exit(EXIT_FAILURE);
    }
    int i,j;
    Matrix Sum = Matrix(this->row, this->col);
    #pragma omp parallel shared(Obj, Sum) private(i,j) 
    {
    #pragma omp for schedule(static)
    for(i=0; i<this->row; i++) {
        for(j=0; j<this->col; j++) {
            Sum.values[i][j] = this->values[i][j] + Obj.values[i][j];
        }
    }
    }
    return Sum;
}


Matrix Matrix::operator-(const Matrix &Obj) {
    if((this->row != Obj.row) & (this->col != Obj.col)) {
        std::cout<<"Dimension Not Compatable. ("<<this->row<<","<<this->col<<") != ("<<Obj.row<<", "<<Obj.col<<")"<<std::endl;
        exit(EXIT_FAILURE);
    }
    int i,j;
    Matrix Sub = Matrix(this->row, this->col);
    #pragma omp parallel shared(Sub, Obj) private(i,j)
    {
        #pragma omp for schedule(static)
    for(i=0; i<this->row; i++) {
        for(j=0; j<this->col; j++) {
            Sub.values[i][j] = this->values[i][j] - Obj.values[i][j];
        }
    }
    }
    return Sub;
}


void Matrix::operator=(const Matrix &Obj) {
    
    for(int i=0; i<this->row; i++) {
        delete[] this->values[i];
    }
    delete[] this->values;

    this->row = Obj.row;
    this->col = Obj.col;
    this->values = new long double*[Obj.row];
    int i,j;
    #pragma omp parallel shared(Obj) private(i,j)
    {
    #pragma omp for schedule(static)
    for(i=0; i<Obj.row;i++) {
        this->values[i] = new long double[Obj.col];
        for(j=0; j<Obj.col; j++) {
            this->values[i][j] = Obj.values[i][j];
        }
    }
    }
}


Matrix Matrix::Sigmoid() {
    Matrix Sig = Matrix(this->row, this->col);
    for(int i=0; i<this->row; i++) {
        for(int j=0; j<this->col; j++) {
            Sig.values[i][j] = _Sigmoid(this->values[i][j]);
        }
    }
    return Sig;
}

Matrix Matrix::SigmoidPrime() {
    Matrix SigP = Matrix(this->row,this->col);
    long double sig;
    for(int i=0; i<this->row; i++) {
        for(int j=0; j<this->col; j++) {
            sig = _Sigmoid(this->values[i][j]);
            SigP.values[i][j] = sig*(1-sig);
        }
    }
    return SigP;
}


void ZeroMatrix(Matrix* mat) {
    for(int i=0; i<mat->row;i++) {
        for(int j=0; j<mat->col; j++) {
            mat->values[i][j] = 0;
        }
    }
}


Matrix* LoadMatrix(const char* fileName) {
    FILE* fpt;
    fpt = fopen(fileName, "r");
    if(fpt == NULL) {
        printf("[ERROR]: File(%s) does not exits.\n",fileName);
        exit(EXIT_FAILURE);
    }
    int row = 0;
    int col = 1;
    char buf;
    buf = getc(fpt);
    // Blank file is considered as 0x0 matrix
    if(buf == EOF) {
        printf("Blank file: %s\n",fileName);
        return randomMatrix(0,0);
    }
    // Finding the column size
    while(buf != EOF) {
        if(buf=='\n') {
            row++;
        }
        buf = getc(fpt);
    }
    fclose(fpt);
    fpt = fopen(fileName,"r");
    buf = getc(fpt);
    // Finding the row size    
    while(buf != '\n') {
        if(buf == ',') {
            col++;
        }
        buf = getc(fpt);
    }
    fclose(fpt);
    // Finaly creating matrix to fill it with values
    Matrix* matrix = new Matrix(row, col);
    fpt = fopen(fileName, "r");
    for(int r=0;r<row;r++)
    {
        for(int c=0;c<col;c++)
        {    
            buf = getc(fpt);
            
            char numberBuff[100];
            int i = 0;
            while((buf != ',') && (buf != '\n')) {
                numberBuff[i] = buf;
                buf = getc(fpt);
                i++;
            } 
            numberBuff[i] = '\0';
            long double a = strtold(numberBuff,NULL);
            matrix->values[r][c] = a;
        }    
    }
    fclose(fpt);
    return matrix;
}



Matrix* randomMatrix(int row, int col) {
    Matrix* randMat = new Matrix(row, col);
    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            randMat->values[i][j] = randomNumber(-1l,1l);
        }
    }
    return randMat;
}


Matrix operator *(long double I, const Matrix &M) {
    Matrix Product = Matrix(M.row,M.col);
    for(int i=0; i<M.row; i++) {
        for(int j=0; j<M.col; j++) {
            Product.values[i][j] = I*M.values[i][j];
        }
    }
    return Product;
}


Matrix HadamardProduct(const Matrix &A, const Matrix &B) {
    if((A.row != B.row) & (A.col != B.col)) {
        printf("ERROR: Dimensionality Error for HadamrdProduct");
        exit(EXIT_FAILURE);
    }

    Matrix H_prod = Matrix(A.row,A.col);
    for(int i=0; i<A.row;i++) {
        for(int j=0; j<A.col; j++) {
            H_prod.values[i][j] = A.values[i][j]*B.values[i][j];
        }
    }

    return H_prod;
}



int Compare(Matrix* A, Matrix* B) {
    if(A->row != B->row || A->col != 1 || B->col != 1){
        printf("Dimensionality Error: Cannot compare.");
        exit(EXIT_FAILURE);
    }
    int IdMaxA = 0;
    int IdMaxB = 0;
    long double MaxA = -100000;
    long double MaxB = -100000;
    for(int i=0; i<A->row; i++) {
        if(A->values[i][0]>MaxA) {
            IdMaxA = i;
            MaxA = A->values[i][0];
        }
        if(B->values[i][0]>MaxB) {
            IdMaxB = i;
            MaxB = B->values[i][0];
        }
    }
        if (IdMaxA == IdMaxB) return 1;
        else return 0;
}

long double MeanSquare(Matrix* A, Matrix* B) {
    if((A->row != B->row) || (A->col != B->col)) {
        std::cout<<"[ERROR]: RootMeanSquare: Dimensionality Error"<<std::endl;
        exit(EXIT_FAILURE);
    }
    long double sum = 0;
    for(int row = 0; row<A->row;row++) {
        for(int col=0;col<A->col;col++) {
            sum += (A->values[row][col]-B->values[row][col])*(A->values[row][col]-B->values[row][col]);
        }
    }
    sum = sqrt(sum);
    return sum;
}