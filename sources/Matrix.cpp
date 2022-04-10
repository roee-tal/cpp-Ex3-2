#include "Matrix.hpp"
#include <string>
namespace zich{

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

void Matrix:: is_legal(Matrix const &mat)const{
    if(this->row != mat.row || this->col != mat.col){
        throw std::invalid_argument("row and col must be equal");
    }
}

Matrix Matrix::operator+(Matrix const &mat){
    is_legal(mat);
    Matrix mat_res{this->data,row,col};
    for (int i = 0; i < mat_res.data.size(); i++)
    {
        mat_res.data[size_t(i)] = this->data[size_t(i)] + mat.data[size_t(i)];
    }
    return mat_res;
}

Matrix& Matrix::operator+=(Matrix const &mat){
    is_legal(mat);
    for (int i = 0; i < this->data.size(); i++)
    {
        this->data[size_t(i)] += mat.data[size_t(i)];
    }
    return *this;
 }

 Matrix operator+(Matrix& mat){
     Matrix unary_mat{mat.data,mat.row,mat.col};
     return unary_mat;
 }

Matrix& Matrix::operator++(){
     for(int i = 0; i < this->data.size(); i++)
     {
         this->data[size_t(i)] += 1;
     }
     return *this;
 }

Matrix Matrix::operator++(const int num){
    Matrix copy = *this;
    for(int i = 0; i < this->data.size(); i++)
     {
         this->data[size_t(i)] += 1;
     }
     return copy;

}

Matrix Matrix::operator--(const int num){
    Matrix copy = *this;
    for(int i = 0; i < this->data.size(); i++)
    {
         this->data[size_t(i)] -= 1;
    }
    return copy;
}

Matrix Matrix::operator-(Matrix const &mat){
    is_legal(mat);
    Matrix mat_res{this->data,row,col};
    for (int i = 0; i < mat_res.data.size(); i++)
    {
        mat_res.data[size_t(i)] = this->data[size_t(i)] - mat.data[size_t(i)];
    }
    return mat_res;
 }

Matrix& Matrix::operator-=(const Matrix& mat){
    is_legal(mat);
    for (int i = 0; i < this->data.size(); i++)
    {
        this->data[size_t(i)] -= mat.data[size_t(i)];
    }
    return *this;
 }

Matrix& Matrix::operator--(){
    for(int i = 0; i < this->data.size(); i++)
    {
         this->data[size_t(i)] -= 1;
    }
    return *this;
}

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
    return this->sum_mat() >= mat.sum_mat();
}

bool Matrix::operator<(const Matrix& mat)const{
    is_legal(mat);
    return this->sum_mat() < mat.sum_mat();
}

bool Matrix::operator<=(const Matrix& mat)const{
    is_legal(mat);
    return this->sum_mat() <= mat.sum_mat();
}

bool Matrix::operator!=(const Matrix& mat)const{
    is_legal(mat);
    return this->sum_mat() != mat.sum_mat();
}

bool Matrix:: operator==(const Matrix& mat)const{
    is_legal(mat);
    double sum1 = 0;
    double sum2 = 0;
    for (int i = 0; i < this->data.size(); i++){
        if(this->data[size_t(i)] != mat.data[size_t(i)])
        {
            return false;
        }
    }
    return true;
}

Matrix Matrix::operator*(const double scalar){
    Matrix mat_res{this->data,this->row,this->col};
    for (int i = 0; i < mat_res.data.size(); i++)
    {
        mat_res.data[size_t(i)] = this->data[size_t(i)] * scalar;
    }
    return mat_res;
 }

Matrix& Matrix::operator*=(const double scalar){
    for (int i = 0; i < this->data.size(); i++){
        this->data[size_t(i)] = this->data[size_t(i)]*scalar; 
    }
    return *this;

}

Matrix operator*(const double scalar, Matrix &mat){
    Matrix mat_res{mat.data,mat.row,mat.col};
    for (int i = 0; i < mat_res.data.size(); i++)
    {
        mat_res.data[size_t(i)] = mat.data[size_t(i)] * scalar;
    }
    return mat_res;
}

Matrix Matrix::operator*(const Matrix &mat){
    if(this->col != mat.row){
        throw std::runtime_error("left matrix's col has to be same to right matrix row");
    }
    std::vector<double> vector1;
    vector1.resize((unsigned int)(this->row * mat.col));
    for (int i = 0; i < this->row; i++)
    {
        for (int j = 0; j < mat.col; j++)
        {
            for (int k = 0; k < this->col; k++)
            {
                int idx = mat.col*i+j;
                vector1[size_t(idx)] += this->data[size_t(this->col*i+k)]*mat.data[size_t(mat.col*k+j)];
            }
        }
    }
    Matrix mat3(vector1, this->row, mat.col);
    return mat3;
}

Matrix& Matrix::operator*=(const Matrix &mat){
    if(this->col != mat.row){
        throw std::runtime_error("left matrix's col has to be same to right matrix row");
    }
    std::vector<double> vector1;
    vector1.resize((unsigned int)(this->row * mat.col));
    for (int i = 0; i < this->row; i++)
    {
        for (int j = 0; j < mat.col; j++)
        {
            for (int k = 0; k < this->col; k++)
            {
                vector1[size_t(mat.col*i+j)] += this->data[size_t(this->col*i+k)]*mat.data[size_t(mat.col*k+j)];
            }
        }
    }
    this->data = vector1;
    this->col = mat.col;
    return *this;
}

std::ostream& operator << (std::ostream &out, const Matrix &mat){
    for (int i = 0; i < mat.row; i++){
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
        out << ']' << '\n';
    }
    return out;
}

// std::istream& operator>> (std::istream &os ,Matrix& mat);
// std::istream & operator >> (std::istream & is, Matrix & self){
//         string element;
//         string matend;
//         int columns = -2;
//         int lines = 0;
//         std::vector<double> matrix;
//         while(!is.eof()){
//             is >> element;
//             matend+=" "+element;
//         }

//         lines = (int)count(matend.begin(), matend.end(), '[');

//         for(unsigned long i=0; i < matend.size(); i++){
//             if(matend[i] == ' '){
//                 columns++;
//             }
//             if(matend[i] == ']'){
//                 break;
//             }
//         }

//         // matrix_input_exeption(&matend,lines,columns);

//         int sum_spaces = lines*(columns+2);
//         int sum_psiks = lines-1;
//         if(lines != (int)count(matend.begin(), matend.end(), ']')){
//             throw std::out_of_range{"not in format"};
//         }
//         int sum_spaces_between = 0;
//         for(unsigned long i=0; i < matend.size(); i++){
//             if(matend[i] == ' '){
//                 sum_spaces--;
//                 sum_spaces_between++;
//             }
//             if(matend[i] == ','){
//                 sum_psiks--;
//             }
//             if(i != matend.size()-1 && matend[i] == ']' && matend[i+1] != ','){
//                 throw std::out_of_range{"not in format"};
//             }
//             if(matend[i] == ']'){
//                 if(sum_spaces_between != (columns+2)){
//                     throw std::out_of_range{"not in format"};
//                 }
//                 sum_spaces_between = 0;
//             }  
//         }
//         if(sum_spaces != 0 || sum_psiks !=0){
//             throw std::out_of_range{"not in format"};
//         }

//         replace(matend.begin(),matend.end(),'[', ' ');
//         replace(matend.begin(),matend.end(),']', ' ');
//         replace(matend.begin(),matend.end(),',', ' ');

//         string num_in_matrix;
//         stringstream stream_matrix(matend);
//         while (getline(stream_matrix, num_in_matrix,' ')) {
//             if( num_in_matrix != "\0"){
//                 try{
//                     double num_double =stod(num_in_matrix);
//                     matrix.push_back(num_double);
//                 }
//                 catch (exception& ex) {
//                     throw std::out_of_range{"not number"};
//                 }
//             }
//         }
//         self.columns = columns;
//         self.lines = lines;
//         self.matrix = matrix;
//         return is;
//     }   


}