#ifndef MATFLOAT_H
#define MATFLOAT_H
#include<iostream>
using namespace std;

class MatFloat
{
    private:
        int size1;
        int size2;
        float ** data;
    public:
        // 构造函数
        MatFloat(int h, int w);
        MatFloat(const MatFloat &c);
        // 析构函数
        ~MatFloat();
        // 获取矩阵信息
        int get_size1() const;
        int get_size2() const;
        float ** get_data() const;
        // 矩阵运算
        MatFloat mul(const MatFloat &c) const;
        MatFloat add(const MatFloat &c) const;
        MatFloat sub(const MatFloat &c) const;
        MatFloat t() const;
        MatFloat inv() const;
        MatFloat pad(const int &pad_row, const int &pad_col) const;
        float det() const;
        //重载输出函数
        friend ostream& operator<<(ostream& out,const MatFloat& c);
        //重载运算符
        float& operator [] (int i);
        friend MatFloat operator +(float r,const MatFloat& c);   
        friend MatFloat operator +(int r,const MatFloat& c);
        friend MatFloat operator +(const MatFloat& c,float r);
        friend MatFloat operator +(const MatFloat& c,int r);
        friend MatFloat operator -(const MatFloat& c,float r);
        friend MatFloat operator -(const MatFloat& c,int r);
        friend MatFloat operator -(float r,const MatFloat& c);
        friend MatFloat operator -(int r,const MatFloat& c);
        friend MatFloat operator *(float r,const MatFloat& c);
        friend MatFloat operator *(int r,const MatFloat& c);
        friend MatFloat operator *(const MatFloat& c,float r);
        friend MatFloat operator *(const MatFloat& c,int r);
        friend MatFloat operator /(const MatFloat& c,float r);
        friend MatFloat operator /(const MatFloat& c,int r);
        friend MatFloat operator +(const MatFloat& c1,const MatFloat& c2);
        friend MatFloat operator -(const MatFloat& c1,const MatFloat& c2);
        friend MatFloat operator *(const MatFloat& c1,const MatFloat& c2);
};
#endif