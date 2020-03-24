#ifndef MATCOMPLEX_H
#define MATCOMPLEX_H
#include<iostream>
using namespace std;
#include"complex.h"

class MatComplex
{
    private:
        int size1;
        int size2;
        Complex ** data;
    public:
        // 构造函数
        MatComplex(int h, int w);
        MatComplex(const MatComplex &c);
        // 析构函数
        ~MatComplex();
        // 获取矩阵信息
        int get_size1() const;
        int get_size2() const;
        Complex ** get_data() const;
        // 矩阵运算
        MatComplex mul(const MatComplex &c) const;
        MatComplex add(const MatComplex &c) const;
        MatComplex sub(const MatComplex &c) const;
        MatComplex t() const;
        MatComplex inv() const;
        MatComplex pad(const int &pad_row, const int &pad_col) const;
        Complex det() const;
        //重载输出函数
        friend ostream& operator<<(ostream& out,const MatComplex& c);
        //重载运算符
        Complex& operator [] (int i);
        friend MatComplex operator +(float r,const MatComplex& c);   
        friend MatComplex operator +(int r,const MatComplex& c);
        friend MatComplex operator +(const MatComplex& c,float r);
        friend MatComplex operator +(const MatComplex& c,int r);
        friend MatComplex operator -(const MatComplex& c,float r);
        friend MatComplex operator -(const MatComplex& c,int r);
        friend MatComplex operator -(float r,const MatComplex& c);
        friend MatComplex operator -(int r,const MatComplex& c);
        friend MatComplex operator *(float r,const MatComplex& c);
        friend MatComplex operator *(int r,const MatComplex& c);
        friend MatComplex operator *(const MatComplex& c,float r);
        friend MatComplex operator *(const MatComplex& c,int r);
        friend MatComplex operator /(const MatComplex& c,float r);
        friend MatComplex operator /(const MatComplex& c,int r);
        friend MatComplex operator +(const MatComplex& c1,const MatComplex& c2);
        friend MatComplex operator -(const MatComplex& c1,const MatComplex& c2);
        friend MatComplex operator *(const MatComplex& c1,const MatComplex& c2);
};

#endif