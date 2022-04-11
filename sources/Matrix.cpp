#include "Matrix.hpp"
#include <string>
#include <iostream>
namespace zich{

//ctor using initialization list
Matrix::Matrix(std::vector<double> data, const int row, const int col):row(row),col(col)
{
    if (row <= 0 || col <= 0)
    {
        throw std::runtime_error("row or col can't be negative");
    }
    if(row * col != data.size())
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
    for (int i = 0; i < mat_res.data.size(); i++)
    {
        mat_res.data[size_t(i)] = this->data[size_t(i)] + mat.data[size_t(i)];
    }
    return mat_res;
}

//Insert to *this mat the sum of 2 matrices
Matrix& Matrix::operator+=(const Matrix &mat){
    is_legal(mat);
    for (int i = 0; i < this->data.size(); i++)
    {
        this->data[size_t(i)] += mat.data[size_t(i)];
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
     for(int i = 0; i < this->data.size(); i++)
     {
         this->data[size_t(i)] += 1;
     }
     return *this;
 }

//mat++
Matrix Matrix::operator++(const int num){
    Matrix copy = *this;
    for(int i = 0; i < this->data.size(); i++)
     {
         this->data[size_t(i)] += 1;
     }
     return copy;

}

//mat--
Matrix Matrix::operator--(const int num){
    Matrix copy = *this;
    for(int i = 0; i < this->data.size(); i++)
    {
         this->data[size_t(i)] -= 1;
    }
    return copy;
}

//Insert to new mat the dif of 2 matrices
Matrix Matrix::operator-(const Matrix &mat){
    is_legal(mat);
    Matrix mat_res{this->data,row,col};
    for (int i = 0; i < mat_res.data.size(); i++)
    {
        mat_res.data[size_t(i)] = this->data[size_t(i)] - mat.data[size_t(i)];
    }
    return mat_res;
 }

//Insert to this mat the dif of 2 matrices
Matrix& Matrix::operator-=(const Matrix& mat){
    is_legal(mat);
    for (int i = 0; i < this->data.size(); i++)
    {
        this->data[size_t(i)] -= mat.data[size_t(i)];
    }
    return *this;
 }

//--mat
Matrix& Matrix::operator--(){
    for(int i = 0; i < this->data.size(); i++)
    {
         this->data[size_t(i)] -= 1;
    }
    return *this;
}

//Negative Unary - return new mat. (The function is friend because the left 'char' is not the class object). 
Matrix operator-(Matrix& mat){
    Matrix unary_neg{mat.data,mat.row,mat.col};
    for (int i = 0; i < mat.data.size(); i++)
    {   
        if(mat.data[size_t(i)] == 0){
            continue;
        }
        unary_neg.data[size_t(i)] = (-1)*(mat.data[size_t(i)]);
        
    }
    return unary_neg;
} 


//Help function to calculate the sum of the matrix
double Matrix::sum_mat() const{
    double sum = 0;
    for (int i = 0; i < this->data.size(); i++)
    {
        sum += this->data[size_t(i)];
    }
    return sum;
}

bool Matrix::operator>(const Matrix& mat)const{
    is_legal(mat);
    return this->sum_mat() > mat.sum_mat();
}

bool Matrix::operator>=(const Matrix& mat)const{
    is_legal(mat);
    // return this->sum_mat() >= mat.sum_mat();
    return (*this == mat || *this > mat);
}

bool Matrix::operator<(const Matrix& mat)const{
    is_legal(mat);
    return this->sum_mat() < mat.sum_mat();
}

bool Matrix::operator<=(const Matrix& mat)const{
    is_legal(mat);
    // return this->sum_mat() <= mat.sum_mat();
    return (*this == mat || *this < mat);
}

bool Matrix::operator!=(const Matrix& mat)const{
    is_legal(mat);
    return this->sum_mat() != mat.sum_mat();
}

//mat1==mat2 if each value is equal in the right place
bool Matrix:: operator==(const Matrix& mat)const{
    is_legal(mat);
    for (int i = 0; i < this->data.size(); i++){
        if(this->data[size_t(i)] != mat.data[size_t(i)])
        {
            return false;
        }
    }
    return true;
}

//Multiply each value with the scalar and insert to new mat
Matrix Matrix::operator*(const double scalar){
    Matrix mat_res{this->data,this->row,this->col};
    for (int i = 0; i < mat_res.data.size(); i++)
    {
        mat_res.data[size_t(i)] = this->data[size_t(i)] * scalar;
    }
    return mat_res;
 }

//Multiply each value with the scalar and insert to this mat
Matrix& Matrix::operator*=(const double scalar){
    for (int i = 0; i < this->data.size(); i++){
        this->data[size_t(i)] = this->data[size_t(i)]*scalar; 
    }
    return *this;

}

//Multiply each value with the scalar and insert to this mat
//Friend func - for example: new_mat = 9*mat
Matrix operator*(const double scalar, Matrix &mat){
    Matrix mat_res{mat.data,mat.row,mat.col};
    for (int i = 0; i < mat_res.data.size(); i++)
    {
        mat_res.data[size_t(i)] = mat.data[size_t(i)] * scalar;
    }
    return mat_res;
}

//Multiply matrices
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
std::istream & operator>> (std::istream &input , Matrix& m){
    return input;
}


}
