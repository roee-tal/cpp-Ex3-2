#include "doctest.h"
#include "Matrix.hpp"
#include <stdexcept>
#include <string>

using namespace zich;
using namespace std;


TEST_CASE("good input"){
    SUBCASE("+(2 matrices)"){
        vector<double> identity = {-1.5, 0, 0, 0, 1, 0, 0, 0, -2};
        vector<double> arr = {-1.5, 0, 0, 0, 3, 0, 0, 0, 1};
        vector<double> v_res = {-3, 0, 0, 0, 4, 0, 0, 0, -1};
        vector<double> v_res2 = {-4.5, 0, 0, 0, 7, 0, 0, 0, 0};
        Matrix a{identity, 3, 3};
        Matrix b{arr, 3, 3};
        Matrix c{v_res, 3, 3};
        Matrix d{v_res2, 3, 3};
        CHECK((a+b==c));
        CHECK((c+b==d));

    }

    SUBCASE("+="){
        vector<double> identity = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        vector<double> v_res = {12, 0, 0, 0, 12, 0, 0, 0, 12};
        Matrix a{identity, 3, 3};
        Matrix b{arr, 3, 3};
        Matrix c{v_res, 3, 3};
        CHECK_EQ((a == b), true);
        CHECK_EQ(((a+=b) == b), false);    
        CHECK(((a+=a) == c));     
    }
    SUBCASE("+(unary"){
        vector<double> identity = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        Matrix a{identity, 3, 3};
        Matrix b = +a;
        CHECK((a==b));    
    }

    SUBCASE("++"){
        vector<double> identity = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        vector<double> arr = {4, 1, 1, 1, 4, 1, 1, 1, 4};
        Matrix a{identity, 3, 3};
        Matrix b{arr, 3, 3};
        CHECK_EQ((a == b), false);
        a = ++a;
        CHECK_EQ((a == b), true);
    }

    SUBCASE("operator++() after"){
        std::vector<double> b ={2, 1,1, 1, 2, 1, 1, 1, 2};
        std::vector<double> c ={3, 2, 2, 2, 3, 2, 2, 2, 3};
        Matrix mat2{b,3,3};
        Matrix mat3{c,3,3};
        CHECK_EQ((mat2++ == mat3),false);//The increment happens after, so in this point its false
        CHECK_EQ((mat2 == mat3),true);//Now its true   
    }

    SUBCASE("-="){
        vector<double> v1 = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        vector<double> v2 = {9, 0, 0, 0, 9, 0, 0, 0, 9};
        vector<double> v3 = {12, 0, 0, 0, 12, 0, 0, 0, 12};
        vector<double> v4 = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        Matrix a{v1, 3, 3};
        Matrix b{v2, 3, 3};
        Matrix c{v3, 3, 3};
        Matrix zero{v4, 3, 3};
        CHECK(((c-=a) == b));
        CHECK(((c-=b) == zero));    
        CHECK(((a-=a) == zero));   
    }

    SUBCASE("-(2 matrices)"){
        vector<double> v1 = {1, 2, 3, 4};
        vector<double> v2 = {1, 2, 3, 4};
        vector<double> v3 = {0,0,0,0};
        vector<double> v4 =  {-1,-1,-1,-1};
        Matrix a{v1, 2, 2};
        Matrix b{v2, 2, 2};
        Matrix zero{v3, 2, 2};
        Matrix d{v4, 2, 2};
        CHECK((a-b==zero));
        CHECK((a-zero==a));
        CHECK((a-a==zero));
    }

    SUBCASE("-(unary)"){
        vector<double> identity = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        vector<double> arr = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        Matrix a{identity, 3, 3};
        Matrix zero{arr, 3, 3};
        Matrix b = -a;
        CHECK(((b+=a) == zero)); // should be zero matrix
    }

    SUBCASE("--"){
        vector<double> identity = {3.2, 0, 0, 0, 3.8, 0, 0, 0, 3.9};
        vector<double> arr = {2.2, -1, -1, -1, 2.8, -1, -1, -1, 2.9};
        Matrix a{identity, 3, 3};
        Matrix b{arr, 3, 3};
        CHECK_EQ((a == b), false);
        a = --a;
        CHECK_EQ((a == b), true);
    }

    SUBCASE("operator--() after"){
        std::vector<double> b ={2, 1,1, 1, 2, 1, 1, 1, 2};
        std::vector<double> c ={3, 2, 2, 2, 3, 2, 2, 2, 3};
        Matrix mat2{b,3,3};
        Matrix mat3{c,3,3};
        CHECK_EQ((mat3-- == mat2),false);//The increment happens after, so in this point its false
        CHECK_EQ((mat3 == mat2),true);//Now its true   
    }

    SUBCASE("*=(matrix)"){
        std::vector<double> a = {1,2,3};
        std::vector<double> b = {1,1,1, 1,1,1, 1,1,1};
        std::vector<double> c = {6,6,6};
        std::vector<double> d = {1,2,3,4};
        std::vector<double> e = {6,6,6, 12,12,12, 18,18,18, 24,24,24};
        Matrix mat1{a,1,3};
        Matrix mat2{b,3,3};
        Matrix mat3{d,4,1}; 
        // Matrix mat4{d,2,2};
        Matrix mat_good{c,1,3};
        mat1*=mat2;
        CHECK((mat1==mat_good));
        mat3*=mat1;
        Matrix mat_good2{e,4,3};
        CHECK((mat3==mat_good2));
        vector<double> v1 = {1, 2, 3, 4, 5, 6}; // matrix 2*3
        vector<double> v2 = {1, 2, 3, 4, 5, 6};
        vector<double> v3 = {22,28,49,64}; // matrix 2*2
        vector<double> unit = {1,0,0,1}; //unit matrix
        Matrix mat7(v1,2,3);
        Matrix mat4(v2,3,2);
        Matrix mat3_4(v3,2,2);
        Matrix mat3_5(unit,2,2);
        CHECK((mat7 * mat4 == mat3_4));
        mat7 *= mat4;
        CHECK((mat7 == mat3_4));
        CHECK(((mat3_4*=mat3_5)==mat3_4)); //mat*unit mat == mat

}
    SUBCASE("operator--() after"){   
        std::vector<double> b ={2, 1,1, 1, 2, 1, 1, 1, 2};
        std::vector<double> c ={3, 2, 2, 2, 3, 2, 2, 2, 3};
        Matrix mat2{b,3,3};
        Matrix mat3{c,3,3};
        CHECK_EQ((mat3-- == mat2),false);
        CHECK_EQ((mat3 == mat2),true);    
}

    SUBCASE("*=(scalar),*(mat*scalar),*(scalar*mat)"){
        vector<double> v1 = {1,2,3,4}; 
        vector<double> v2 = {1,2,3,4}; 
        vector<double> v3 = {2,4,6,8}; 
        Matrix mat1(v1,2,2);
        Matrix mat2(v2,2,2);
        Matrix mat3(v3,2,2);
        Matrix mat_res1 = mat1*2; //(mat*scalar)
        Matrix mat_res2 = 2*mat1; //scalar*mat(the friend function)
        CHECK((mat_res1 == mat3));
        CHECK((mat_res1 == mat_res2));//Check if they are same
        CHECK((mat_res1* 3> mat3));
        mat2 *= 2;
        CHECK((mat2 == mat3));
        CHECK((mat2 == mat_res1));

        //Check on large matrix
        vector<double> v4;
        for(int i=50;i<80;i++){
            v4.push_back(i);
        }
        Matrix mat4(v4,10,3);
        vector<double> v5;
        for(int i=50;i<80;i++){
            v5.push_back(i*2);
        }
        Matrix mat5(v5,10,3);
        CHECK_EQ((mat4 == mat5),false);
        CHECK_EQ(((mat4*=2) == mat5),true);
        Matrix m6 = mat4;
        CHECK_EQ((m6 == mat5),true);
        m6 = mat4*2;
        CHECK_EQ((m6 == mat5),false);
    }

    
    SUBCASE("compare same matrix"){
        vector<double> v1 = {3, 0, 0, 0, -3, 0, 0, 0, 3};
        vector<double> v2 = {3, 0, 0, 0, -3, 0, 0, 0, 3};
        
        Matrix m1{v1, 3, 3};
        Matrix m2{v2, 3, 3};

        CHECK_EQ(m1 == m2,true);
        CHECK_EQ(m1 >= m2,true);
        CHECK_EQ(m1 > m2,false);
        CHECK_EQ(m1 <= m2,true);
        CHECK_EQ(m1 < m2,false);
        CHECK_EQ(m1 != m2,false);
    }

    SUBCASE("compare matrix with same size but different values"){
        vector<double> v2 = {3, 0, 0, 0, -3, 0, 0, 0, 3};
        vector<double> v3 = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        Matrix m3{v3, 3, 3}; //m3 is bigger
        Matrix m2{v2, 3, 3};

        CHECK_EQ(m2 == m3,false);
        CHECK_EQ(m2 >= m3,false);
        CHECK_EQ(m2 > m3,false);
        CHECK_EQ(m2 <= m3,true);
        CHECK_EQ(m2 < m3,true);
        CHECK_EQ(m2 != m3,true);
    }

}


TEST_CASE("bad matrix building"){
    vector<double>v1;
    for (double i = 0; i < 12; i++){
        v1.push_back(i);
    }
    CHECK_THROWS(Matrix(v1,3,5));

    vector<double>v2;
    for (double i = 0; i < 9; i++){
        v2.push_back(i);
    }
    CHECK_THROWS(Matrix(v1,3,2));
    CHECK_THROWS(Matrix(v1,3,-3));
    CHECK_THROWS(Matrix(v1,-3,-3));
    CHECK_THROWS(Matrix(v1,-3,3));
    CHECK_THROWS(Matrix(v1,0,3));
    CHECK_THROWS(Matrix(v1,3,0));
}

TEST_CASE("bad input"){
    vector<double>v1;
    for (double i = 0; i < 12; i++){
        v1.push_back(i);
    }
    vector<double>v2;
    for (double i = 0; i < 9; i++){
        v2.push_back(i);
    }
    vector<double>v3;
    for (double i = 0; i < 8; i++){
        v3.push_back(i);
    }
    Matrix m1{v1,3,4};
    Matrix m2{v2,3,3};
    Matrix m3{v3,4,2};

    CHECK_THROWS(if(m1 == m2));
    CHECK_THROWS(if(m1 >= m2));
    CHECK_THROWS(if(m1 != m3));
    CHECK_THROWS(if(m3 == m2));
    CHECK_THROWS(if(m3 < m2));
    CHECK_THROWS(m1 += m3);
    CHECK_THROWS(m2 - m3);
    CHECK_THROWS(m1 -= m2);
    CHECK_THROWS(m1 - m2);
    CHECK_THROWS(m3 + m2);
    CHECK_THROWS(m2 -= m1);
    CHECK_THROWS(m2 += m3);    
}