#include<iostream>
#include"complex.h"

//构造函数 
Complex::Complex(float r,float i)
{
	real=r;
	image=i;
}
//拷贝构造函数 
Complex::Complex(const Complex &c)
{
	real=c.real;
	image=c.image;
}
//共轭运算
Complex Complex::conj(void) const
{
	Complex t(real, -image);
	return t;
}
//加运算 
Complex Complex::add(const Complex &c) const
{
	Complex t;
	t.real=real+c.real;
	t.image=image+c.image;
	return t;
}
//减运算 
Complex Complex::sub(const Complex &c) const
{
    Complex t;
	t.real=real-c.real;
	t.image=image-c.image;
	return t;	
}
//乘运算 
Complex Complex::mul(const Complex &c) const
{
	Complex t;
	t.real=real*c.real-image*c.image;
	t.image=image*c.real+real*c.image;
	return t;
}
//除运算 
Complex Complex::div(const Complex &c) const
{
	if(!(c.real||c.image))
	   {
   		 std::cout<<"分母不能为零"<<endl;
   		 return Complex(0, 0);
   	   }
    Complex t;
    t.real=(real*c.real+image*c.image)/(c.real*c.real+c.image*c.image);
    t.image=(c.real*image-c.image*real)/(c.real*c.real+c.image*c.image);
    return t;
}
//获取幅度
float Complex::abs(void) const
{
	return sqrt((float)(pow(real,2) + pow(image, 2)));
}
//获取实部 
float Complex::getreal(void) const
{
	return real;
}
//获取虚部 
float Complex::getimage(void) const
{
	return image;
}
//设定复数值 
void Complex::setComplex(float r,float i)
{
	real=r;image=i;
}
//输出重载 
ostream& operator<<(ostream& out,const Complex& c)
{
	if(c.image>0)
	  out<<c.real<<'+'<<c.image<<'i';
    if(c.image<0)
      out<<c.real<<c.image<<'i';
    if(c.image==0)
      out<<c.real;
    return out;
}
//输入重载 
istream& operator>>(istream& in,Complex& c)
{
	in>>c.real>>c.image;
	return in;
}
//以下为运算符重载 
Complex operator+(float r,const Complex& c)
{
	Complex t;
	t.real=r+c.real;
	t.image=c.image;
	return t; 
}
Complex operator+(int r,const Complex& c)
{
	Complex t;
	t.real=r+c.real;
	t.image=c.image;
	return t; 
}
Complex operator-(float r,const Complex& c)
{
	Complex t;
	t.real=r-c.real;
	t.image=c.image;
	return t; 
}
Complex operator-(int r,const Complex& c)
{
	Complex t;
	t.real=r-c.real;
	t.image=c.image;
	return t; 
}
Complex operator*(float r,const Complex& c)
{
	Complex t;
	t.real=r*c.real;
	t.image=r*c.image;
	return t; 
}
Complex operator*(int r,const Complex& c)
{
	Complex t;
	t.real=r*c.real;
	t.image=r*c.image;
	return t; 
}
Complex operator+(const Complex& c,float r)
{
	Complex t;
	t.real=r+c.real;
	t.image=c.image;
	return t; 
}
Complex operator+(const Complex& c,int r)
{
	Complex t;
	t.real=r+c.real;
	t.image=c.image;
	return t; 
}
Complex operator-(const Complex& c,float r)
{
	Complex t;
	t.real=r-c.real;
	t.image=c.image;
	return t; 
}
Complex operator-(const Complex& c,int r)
{
	Complex t;
	t.real=r-c.real;
	t.image=c.image;
	return t; 
}
Complex operator*(const Complex& c,float r)
{
	Complex t;
	t.real=r*c.real;
	t.image=r*c.image;
	return t; 
}
Complex operator*(const Complex& c,int r)
{
	Complex t;
	t.real=r*c.real;
	t.image=r*c.image;
	return t; 
}
Complex operator/(float r,const Complex& c)
{
	Complex t(r,0);
	return t.div(c);
}
Complex operator/(int r,const Complex& c)
{
	Complex t((float)r,0);
	return t.div(c);
}
Complex operator/(const Complex& c,float r)
{
	Complex t;
	t.real=c.real/r;
	t.image=c.image/r;
	return t;
}
Complex operator/(const Complex& c,int r)
{
	Complex t;
	t.real=c.real/(float)r;
	t.image=c.image/(float)r;
	return t;
}
Complex operator+(const Complex& c1,const Complex& c2)
{
	return c1.add(c2);
}
Complex operator-(const Complex& c1,const Complex& c2)
{
	return c1.sub(c2);
}
Complex operator*(const Complex& c1,const Complex& c2)
{
	return c1.mul(c2);
}
Complex operator/(const Complex& c1,const Complex& c2)
{
	return c1.div(c2);
}
