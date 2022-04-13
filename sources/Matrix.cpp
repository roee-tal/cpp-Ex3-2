#include "Matrix.hpp"
#include <string>
#include <iostream>
namespace zich{

//ctor using initialization list
Matrix::Matrix(std::vector<double> data, const int row, const int col):row(row),col(col)
{
    if (row <= 0 || col <= 0) //cant be negative
    {
        throw std::runtime_error("row or col can't be negative");
    }
    if(row * col != data.size()) // the size should be match to number of values
    {
         throw std::runtime_error("row*col should be same to the matrix size");
    }
    this->data = std::move(data);
}

//Check if the input is legal(row==row,col==col)
void Matrix:: is_legal(const Matrix &mat)const{
    if(this->row != mat.row || this->col != mat.col){
        throw std::invalid_argument("row and col must be equal");
    }
}

//Insert to new mat the sum of 2 matrices
Matrix Matrix::operator+(const Matrix &mat){
    is_legal(mat);
    Matrix mat_res{this->data,row,col};
    for (unsigned long i = 0; i < mat_res.data.size(); i++)
    {
        mat_res.data.at(i) = this->data.at(i) + mat.data.at(i);
    }
    return mat_res;
}

//Insert to *this mat the sum of 2 matrices
Matrix& Matrix::operator+=(const Matrix &mat){
    is_legal(mat);
    for (unsigned long i = 0; i < this->data.size(); i++)
    {
        this->data.at(i) += mat.data.at(i);
    }
    return *this;
 }

//Positive Unary - return new mat. (The function is friend because the left 'char' is not the class object). 
 Matrix operator+(Matrix& mat){
     Matrix unary_mat{mat.data,mat.row,mat.col};
     return unary_mat;
 }

//++mat
Matrix& Matrix::operator++(){
     for(unsigned long i = 0; i < this->data.size(); i++)
     {
         this->data.at(i) += 1;
     }
     return *this;
 }

//mat++
Matrix Matrix::operator++(const int num){
    Matrix copy = *this;
    for(unsigned long i = 0; i < this->data.size(); i++)
     {
         this->data.at(i)+= 1;
     }
     return copy;

}

//mat--
Matrix Matrix::operator--(const int num){
    Matrix copy = *this;
    for(unsigned long i = 0; i < this->data.size(); i++)
    {
         this->data.at(i) -= 1;
    }
    return copy;
}

//Insert to new mat the dif of 2 matrices
Matrix Matrix::operator-(const Matrix &mat){
    is_legal(mat);
    Matrix mat_res{this->data,row,col};
    for (unsigned long i = 0; i < mat_res.data.size(); i++)
    {
        mat_res.data.at(i) = this->data.at(i)- mat.data.at(i);
    }
    return mat_res;
 }

//Insert to this mat the dif of 2 matrices
Matrix& Matrix::operator-=(const Matrix& mat){
    is_legal(mat);
    for (unsigned long i = 0; i < this->data.size(); i++)
    {
        this->data.at(i) -= mat.data.at(i);
    }
    return *this;
 }

//--mat
Matrix& Matrix::operator--(){
    for(unsigned long i = 0; i < this->data.size(); i++)
    {
         this->data.at(i) -= 1;
    }
    return *this;
}

//Negative Unary - return new mat. (The function is friend because the left 'char' is not the class object). 
Matrix operator-(Matrix& mat){
    Matrix unary_neg{mat.data,mat.row,mat.col};
    for (unsigned long i = 0; i < mat.data.size(); i++)
    {   
        if(mat.data.at(i) == 0){
            continue;
        }
        unary_neg.data.at(i) = (-1)*(mat.data.at(i));
        
    }
    return unary_neg;
} 


//Help function to calculate the sum of the matrix
double Matrix::sum_mat() const{
    double sum = 0;
    for (unsigned long i = 0; i < this->data.size(); i++)
    {
        sum += this->data.at(i);
    }
    return sum;
}

bool Matrix::operator>(const Matrix& mat)const{
    is_legal(mat);
    return this->sum_mat() > mat.sum_mat();
}

bool Matrix::operator>=(const Matrix& mat)const{
    is_legal(mat);
    return (*this == mat || *this > mat);
}

bool Matrix::operator<(const Matrix& mat)const{
    is_legal(mat);
    return this->sum_mat() < mat.sum_mat();
}

bool Matrix::operator<=(const Matrix& mat)const{
    is_legal(mat);
    return (*this == mat || *this < mat);
}

//Use of !(==)
bool Matrix::operator!=(const Matrix& mat)const{
    is_legal(mat);
    return !(*this == mat);
}

//mat1==mat2 if each value is equal in the right place
bool Matrix:: operator==(const Matrix& mat)const{
    is_legal(mat);
    for (unsigned long i = 0; i < this->data.size(); i++){
        if(this->data.at(i) != mat.data.at(i))
        {
            return false;
        }
    }
    return true;
}

//Multiply each value with the scalar and insert to new mat
Matrix Matrix::operator*(const double scalar){
    Matrix mat_res{this->data,this->row,this->col};
    for (unsigned long i = 0; i < mat_res.data.size(); i++)
    {
        mat_res.data.at(i) = this->data.at(i) * scalar;
    }
    return mat_res;
 }

//Multiply each value with the scalar and insert to this mat
Matrix& Matrix::operator*=(const double scalar){
    for (unsigned long i = 0; i < this->data.size(); i++){
        this->data.at(i) = this->data.at(i)*scalar; 
    }
    return *this;

}

//Multiply each value with the scalar and insert to this mat
//Friend func - for example: new_mat = 9*mat
Matrix operator*(const double scalar, Matrix &mat){
    Matrix mat_res{mat.data,mat.row,mat.col};
    for (unsigned long i = 0; i < mat_res.data.size(); i++)
    {
        mat_res.data.at(i) = mat.data.at(i) * scalar;
    }
    return mat_res;
}

//Multiply matrices into new mat
Matrix Matrix::operator*(const Matrix &mat){
    if(this->col != mat.row){
        throw std::runtime_error("left matrix's col has to be same to right matrix row");
    }
    int idx=0;
    int ind_this=0;
    int ind_mat=0;
    std::vector<double> vector1;
    vector1.resize((unsigned int)(this->row * mat.col));
    for (int i = 0; i < this->row; i++)
    {
        for (int j = 0; j < mat.col; j++)
        {
            for (int k = 0; k < this->col; k++)
            {
                idx = mat.col*i+j;
                ind_this = this->col*i+k;
                ind_mat = mat.col*k+j;
                vector1[size_t(idx)] += this->data[size_t(ind_this)]*mat.data[size_t(ind_mat)];
            }
        }
    }
    Matrix mat_res(vector1, this->row, mat.col);
    return mat_res;
}

//Multiply matrices into *this mat
Matrix& Matrix::operator*=(const Matrix &mat){
    if(this->col != mat.row){
        throw std::runtime_error("left matrix's col has to be same to right matrix row");
    }
    int idx=0;
    int ind_this=0;
    int ind_mat=0;
    std::vector<double> vector1;
    vector1.resize((unsigned int)(this->row * mat.col));
    for (int i = 0; i < this->row; i++)
    {
        for (int j = 0; j < mat.col; j++)
        {
            for (int k = 0; k < this->col; k++)
            {
                idx = mat.col*i+j;
                ind_this = this->col*i+k;
                ind_mat = mat.col*k+j;
                vector1[size_t(idx)] += this->data[size_t(ind_this)]*mat.data[size_t(ind_mat)];
            }
        }
    }
    this->data = vector1;
    this->col = mat.col;
    return *this;
}

//Should print: [6 0 0]
//              [0 6 0]
//              [0 0 6]*/
std::ostream& operator << (std::ostream &out, const Matrix &mat){
    for (int i = 0; i < mat.row; i++)
    {
        out << '[';
        for (int j = 0; j < mat.col; j++)
        {
            if (j != mat.col -1 )
            {
                out << mat.data[(unsigned int)(i * mat.col + j)] << ' ';
            }
            else{
                out <<mat.data[(unsigned int)(i * mat.col + j)];
            }
        }
        if (i != mat.row - 1)
            {
                out << ']' << '\n';
            }
        else
            {
                out << ']';
            }
    }
    return out;
}


// Should be in this format :[1 1], [1 1]
std::istream& operator >>(std::istream& input,Matrix &mat){
    std::vector<double> vector1;
    int row=1;
    int col = 1;
    int col_size = 1;
    int row_size=mat.data.size();
    bool first = false;
    std::string str;
    for(char tmp=0; input.get(tmp) && tmp!='\n';){
        if(tmp==','){
            row++;
            if((first && col!=col_size) || row >= row_size){
                throw std::invalid_argument("wrong col\row num for mat");
            }
            if(!first) {
                col = col_size;
                first= true;
                col_size=0;
            }   
        }
        else if(tmp==' '){
            vector1.push_back(stod(str));
            str="";
            col_size++;
        }
        else if(tmp != '[' && tmp != ']') {
                str += tmp;
        }
    }
    mat.data = vector1;
    return input;
}
}



    // string str;
    // double num=0;
    // input.fill('f');
    // int rowSize=matrix.mat.size();
    // int columnSize=matrix.mat.at(0).size ();
    // unsigned long row=0;
    // unsigned long column=0;
    // input.get();
    // for(char c=0; input.get(c)&&c!='\n';){
    //     if (c=='['){
    //         column=0;
    //         row++;
    //         if (row>=rowSize){
    //             throw invalid_argument( "\nthe input have more rows than the matrix" );
    //         }
    //     }
    //     else if((c==' '|| c==']')&&str.length()!=0){
    //         if (column>=columnSize){
    //             throw invalid_argument( "\nthe input have more columns than the matrix" );
    //         }
    //         num= stod(str);
    //         matrix.mat.at(row).at(column)=num;
    //         cout<<row<<","<<column<<","<<num <<endl;
    //         column++;
    //         str="";
    //     }
    //     else if (isdigit(c)!=0){

    //         str+=c;
    //     }
    // }

    // return input;