#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>
#include <math.h>
using namespace std;

class Complex
{
	private:
	        float real;
	        float image;
    public:
            Complex(float=0.0,float=0.0);    //构造函数 
            Complex(const Complex &c);       //拷贝构造函数
			//以下为运算函数
			Complex conj(void) const;
			Complex add(const Complex &c) const;  //加运算 
			Complex sub(const Complex &c) const;  //减运算 
			Complex mul(const Complex &c) const;  //乘运算 
			Complex div(const Complex &c) const;  //除运算 
			//以下为普通成员函数
			float abs(void) const;
			float getreal(void) const;            //获取实部 
			float getimage(void) const;           //获取虚部 
			void setComplex(float r,float i);     //重新设定复数值 
			//以下为输出输入函数重载
			friend ostream& operator<<(ostream& out,const Complex& c);  //输出重载 
			friend istream& operator>>(istream& in,Complex& c);         //输入重载 
			//以下为运算符重载
			friend Complex operator+(float r,const Complex& c);   //
			friend Complex operator+(int r,const Complex& c);
			friend Complex operator-(float r,const Complex& c);
			friend Complex operator-(int r,const Complex& c);
			friend Complex operator*(float r,const Complex& c);
			friend Complex operator*(int r,const Complex& c);
			friend Complex operator+(const Complex& c,float r);
			friend Complex operator+(const Complex& c,int r);
			friend Complex operator-(const Complex& c,float r);
			friend Complex operator-(const Complex& c,int r);
			friend Complex operator*(const Complex& c,float r);
			friend Complex operator*(const Complex& c,int r);
			friend Complex operator/(float r,const Complex& c);
			friend Complex operator/(int r,const Complex& c);
			friend Complex operator/(const Complex& c,float r);
			friend Complex operator/(const Complex& c,int r);
			friend Complex operator+(const Complex& c1,const Complex& c2);
			friend Complex operator-(const Complex& c1,const Complex& c2);
			friend Complex operator*(const Complex& c1,const Complex& c2);
			friend Complex operator/(const Complex& c1,const Complex& c2);
};
//定义虚数单位ie 
const Complex ie(0,1);

#endif