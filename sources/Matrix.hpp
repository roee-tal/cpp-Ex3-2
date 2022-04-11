#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>

namespace zich{
    class Matrix{    
            std::vector<double>data;
            int row;
            int col;

        public :
            //constructor
            Matrix(const std::vector<double> data, const int row, const int col); 

            //Help function to check if the input is legal 
            void is_legal(const Matrix &mat) const;

            //Arithmetic operators
            Matrix operator+(const Matrix &mat);
            Matrix& operator+=(const Matrix& mat);   
            Matrix& operator++();
            Matrix operator++(const int num);
            Matrix operator-(Matrix const &mat);
            Matrix& operator-=(const Matrix& mat);
            Matrix& operator--();
            Matrix operator--(const int num);

            //Unary
            friend Matrix operator+(Matrix& mat);
            friend Matrix operator-(Matrix& mat);

            //Find sum of matrix
            double sum_mat()const;

            //Compare operators
            bool operator>(const Matrix& mat)const;
            bool operator>=(const Matrix& mat)const;
            bool operator<(const Matrix& mat)const;
            bool operator<=(const Matrix& mat)const;
            bool operator==(const Matrix& mat)const;
            bool operator!=(const Matrix& mat)const;

            // Multipication (with other matrix and scalar)
            Matrix operator*(const double scalar);
            Matrix operator*(const Matrix &mat);
            Matrix& operator*=(const double scalar);
            Matrix& operator*=(const Matrix &mat);
            friend Matrix operator*(const double scalar, Matrix &mat);

            // input output
            friend std::ostream & operator << (std::ostream &out, const Matrix &mat);
            friend std::istream & operator>> (std::istream &input , Matrix& m);
    };
}
