#ifndef MATUINT8_H
#define MATUINT8_H
#include<iostream>
#include"mat_float.h"
using namespace std;

typedef unsigned char uint8;

class MatUint8
{
    private:
        int size1;
        int size2;
        uint8 ** data;
    public:
        // 构造函数
        MatUint8(int h, int w);
        MatUint8(const MatUint8 &c);
        MatUint8(const MatFloat &c);
        // 析构函数
        ~MatUint8();
        // 获取矩阵信息
        int get_size1() const;
        int get_size2() const;
        uint8 ** get_data() const;
        // 矩阵运算
        MatUint8 mul(const MatUint8 &c) const;
        MatUint8 add(const MatUint8 &c) const;
        MatUint8 sub(const MatUint8 &c) const;
        MatUint8 t() const;
        MatUint8 inv() const;
        MatUint8 pad(const int &pad_row, const int &pad_col) const;
        uint8 det() const;
        //重载输出函数
        friend ostream& operator<<(ostream& out,const MatUint8& c);
        //重载运算符
        uint8& operator [] (int i);
        friend MatUint8 operator +(float r,const MatUint8& c);   
        friend MatUint8 operator +(int r,const MatUint8& c);
        friend MatUint8 operator +(const MatUint8& c,float r);
        friend MatUint8 operator +(const MatUint8& c,int r);
        friend MatUint8 operator -(const MatUint8& c,float r);
        friend MatUint8 operator -(const MatUint8& c,int r);
        friend MatUint8 operator -(float r,const MatUint8& c);
        friend MatUint8 operator -(int r,const MatUint8& c);
        friend MatUint8 operator *(float r,const MatUint8& c);
        friend MatUint8 operator *(int r,const MatUint8& c);
        friend MatUint8 operator *(const MatUint8& c,float r);
        friend MatUint8 operator *(const MatUint8& c,int r);
        friend MatUint8 operator /(const MatUint8& c,float r);
        friend MatUint8 operator /(const MatUint8& c,int r);
        friend MatUint8 operator +(const MatUint8& c1,const MatUint8& c2);
        friend MatUint8 operator -(const MatUint8& c1,const MatUint8& c2);
        friend MatUint8 operator *(const MatUint8& c1,const MatUint8& c2);
};

#endif