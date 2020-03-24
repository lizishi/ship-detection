#include<iostream>
#include"mat_uint8.h"

//构造函数
MatUint8::MatUint8(int h, int w)
{
    size1 = h;
    size2 = w;
    data = new uint8*[size1];
    for (int i = 0; i <= size1 - 1; i++)
    {
        data[i] = new uint8[size2]();
    }
}
//拷贝构造函数
MatUint8::MatUint8(const MatUint8 &c)
{
    size1=c.get_size1();
    size2=c.get_size2();
    data=new uint8*[size1];
    uint8 **c_data = c.get_data();
    for(int i=0;i<=size1-1;i++)
    {
        data[i]=new uint8[size2];
        for(int j=0;j<=size2-1;j++)
        {
            data[i][j] = c_data[i][j];
        }
    }
}
//转换构造函数
MatUint8::MatUint8(const MatFloat &c)
{
    size1=c.get_size1();
    size2=c.get_size2();
    data=new uint8*[size1];
    float **c_data = c.get_data();
    float max_c = -1000000;
    for(int i=0;i<=size1-1;i++)
        for(int j=0;j<=size2-1;j++)
            max_c = c_data[i][j]>max_c?c_data[i][j]:max_c;
    for(int i=0;i<=size1-1;i++)
    {
        data[i]=new uint8[size2];
        for(int j=0;j<=size2-1;j++)
        {
            data[i][j] = (uint8)(c_data[i][j] / max_c * 255);
        }
    }
}
//析构函数
MatUint8::~MatUint8()
{
    for(int i=0;i<size1;i++)
    {
        delete []data[i];
    }
    delete []data;
}
//获取长度size1
int MatUint8::get_size1() const
{
    return size1;
}
//获取宽度size2
int MatUint8::get_size2() const
{
    return size2;
}
//获取数据指针data
uint8 ** MatUint8::get_data() const
{
    return data;
}
//矩阵乘法
MatUint8 MatUint8::mul(const MatUint8 &c) const
{
    if (size2 == c.get_size1())
    {
        MatUint8 res(size1, c.get_size2());
        uint8 **res_data = res.get_data();
        uint8 **c_data = c.get_data();
        for (int i=0; i<size1; i++)
        {
            for (int j=0; j<c.get_size2(); j++)
            {
                uint8 num = 0;
                for (int k=0; k<size2; k++)
                {
                    num = num + data[i][k] * c_data[k][j];
                }
                res_data[i][j] = num;
            }
        }
        return res;
    }
    else
    {
        cout<<"the size of multiplying Matrix are not match"<<endl;
        cout<<size1<<' '<<size2<<endl;
        cout<<c.get_size1()<<' '<<c.get_size2();
        return MatUint8(1, 1);
    }
}
//矩阵加法
MatUint8 MatUint8::add(const MatUint8 &c) const
{
    if ((size1 == c.get_size1()) and (size2 == c.get_size2()))
    {
        MatUint8 res(size1, size2);
        uint8 **res_data = res.get_data();
        uint8 **c_data = c.get_data();
         for (int i=0; i<size1; i++)
        {
            for (int j=0; j<size2; j++)
            {
                res_data[i][j] = data[i][j] + c_data[i][j];
            }
        }
        return res;
    }
    else
    {
        cout<<"the size of adding Matrix are not match"<<endl;
        cout<<size1<<' '<<size2<<endl;
        cout<<c.get_size1()<<' '<<c.get_size2();
        return MatUint8(1, 1);
    }
}
//矩阵减法
MatUint8 MatUint8::sub(const MatUint8 &c) const
{
    if ((size1 == c.get_size1()) and (size2 == c.get_size2()))
    {
        MatUint8 res(size1, size2);
        uint8 **res_data = res.get_data();
        uint8 **c_data = c.get_data();
         for (int i=0; i<size1; i++)
        {
            for (int j=0; j<size2; j++)
            {
                res_data[i][j] = data[i][j] - c_data[i][j];
            }
        }
        return res;
    }
    else
    {
        cout<<"the size of substracting Matrix are not match"<<endl;
        cout<<size1<<' '<<size2<<endl;
        cout<<c.get_size1()<<' '<<c.get_size2();
        return MatUint8(1, 1);
    }
}
//矩阵求转置
MatUint8 MatUint8::t() const
{
    MatUint8 res(size2, size1);
    uint8 ** res_data = res.get_data();
    for (int i=0; i<size1; i++)
    {
        for (int j=0; j<size2; j++)
        {
            res_data[j][i] = data[i][j];
        }
    }
    return res;
}
//矩阵求逆
MatUint8 MatUint8::inv() const
{
    if (size1==size2)
    {
        MatUint8 res(size1, size2);
        uint8 **res_data = res.get_data();
        if(size1==1)
        {
            res_data[0][0] = 1;
            return res;
        }
        uint8 mat_det = det();
        if ((mat_det <= 1e-5) and (mat_det >= -1e-5))
        {
            cout<<"the matrix is strange"<<endl;
            return res;
        }
        MatUint8 temp(size1-1, size1-1);
        uint8 ** temp_data = temp.get_data();
        for(int i=0;i<size1;i++)
        {
            for(int j=0;j<size1;j++)
            {
                for(int k=0;k<size1-1;k++)
                {
                    for(int t=0;t<size1-1;t++)
                    {
                        temp_data[k][t] = data[k>=i?k+1:k][t>=j?t+1:t];
                    }
                }
                res_data[j][i]  = temp.det() / mat_det;
                if((i+j)%2 == 1)
                {
                    res_data[j][i] = res_data[j][i] * (-1);
                }
            }
        }
        return res;
    }
    else
    {
        cout<<"the size of inv Matrix are not match"<<endl;
        cout<<size1<<' '<<size2<<endl;
        return MatUint8(1, 1);
    }
}
//矩阵填充
MatUint8 MatUint8::pad(const int &pad_row, const int &pad_col) const
{
    MatUint8 res(size1+2*pad_row, size2+2*pad_col);
    uint8 ** res_data = res.get_data();
    for (int i=pad_row;i<size1+pad_row;i++)
    {
        for (int j=pad_col;j<size2+pad_col;j++)
        {
            res_data[i][j] = data[i-pad_row][j-pad_col];
        }
    }
    for (int i=0;i<pad_row;i++)
    {
        for (int j=pad_col;j<size2+pad_col;j++)
        {
            res_data[i][j] = res_data[2*pad_row-1-i][j];
            res_data[size1+pad_row+i][j] = res_data[size1+pad_row-1-i][j];
        }
    }
    for (int i=0;i<size2+2*pad_row;i++)
    {
        for (int j=0;j<pad_col;j++)
        {
            res_data[i][j] = res_data[i][2*pad_row-1-j];
            res_data[i][size2+pad_col+j] = res_data[i][size2+pad_col-1-j];
        }
    }
    return res;
}
//矩阵求行列式
uint8 MatUint8::det() const
{  
    if (size1!=size2)
    {
        cout<<"det require size of matrix equal"<<endl;
        cout<<size1<<' '<<size2;
        return 0;
    }
    if(size1==1)
    {
        return data[0][0];
    }
    uint8 ans = 0;
    MatUint8 temp(size1-1, size1-1);
    uint8 **temp_data = temp.get_data();
    for(int i=0;i<size1;i++)
    {
        for(int j=0;j<size1-1;j++)
        {
            for(int k=0;k<size1-1;k++)
            {
                temp_data[j][k] = data[j+1][(k>=i)?k+1:k];

            }
        }
        uint8 t = temp.det();
        if(i%2==0)
        {
            ans = ans + data[0][i]*t;
        }
        else
        {
            ans = ans - data[0][i]*t;
        }
    }
    return ans;
}
//重载输出
ostream& operator<<(ostream& out, const MatUint8&c)
{
    uint8 **c_data=c.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            out<<c_data[i][j]<<'\t';
        }
        out<<'\n';
    }
    return out;
}
//重载运算符
uint8& MatUint8::operator [](int i)
{
    if (i <= size1 * size2)
    {
        int h = i / size2;
        int w = i % size2;
        return data[h][w];
    }
    else
    {
        std::cout<<"overflow"<<endl;
        return data[0][0];
    }
}
MatUint8 operator+(float r,const MatUint8& c)
{
    MatUint8 res(c);
    uint8 **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] + r;
        }
    }
    return res;
}

MatUint8 operator+(int r,const MatUint8& c)
{
    MatUint8 res(c);
    uint8 **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] + r;
        }
    }
    return res;
}

MatUint8 operator+(const MatUint8& c,float r)
{
    MatUint8 res(c);
    uint8 **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] + r;
        }
    }
    return res;
}

MatUint8 operator+(const MatUint8& c,int r)
{
    MatUint8 res(c);
    uint8 **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] + r;
        }
    }
    return res;
}

MatUint8 operator-(const MatUint8& c,float r)
{
    MatUint8 res(c);
    uint8 **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] - r;
        }
    }
    return res;
}

MatUint8 operator-(const MatUint8& c,int r)
{
    MatUint8 res(c);
    uint8 **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] - r;
        }
    }
    return res;
}

MatUint8 operator-(float r,const MatUint8& c)
{
    MatUint8 res(c);
    uint8 **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = r - res_data[i][j];
        }
    }
    return res;
}

MatUint8 operator-(int r,const MatUint8& c)
{
    MatUint8 res(c);
    uint8 **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = r - res_data[i][j];
        }
    }
    return res;
}

MatUint8 operator*(float r,const MatUint8& c)
{
    MatUint8 res(c);
    uint8 **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] * r;
        }
    }
    return res;
}

MatUint8 operator*(int r,const MatUint8& c)
{
    MatUint8 res(c);
    uint8 **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] * r;
        }
    }
    return res;
}

MatUint8 operator*(const MatUint8& c,float r)
{
    MatUint8 res(c);
    uint8 **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] * r;
        }
    }
    return res;
}

MatUint8 operator*(const MatUint8& c,int r)
{
    MatUint8 res(c);
    uint8 **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] * r;
        }
    }
    return res;
}

MatUint8 operator/(const MatUint8& c,float r)
{
    MatUint8 res(c);
    uint8 **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] / r;
        }
    }
    return res;
}

MatUint8 operator/(const MatUint8& c,int r)
{
    MatUint8 res(c);
    uint8 **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] / r;
        }
    }
    return res;
}

MatUint8 operator*(const MatUint8& c1,const MatUint8& c2)
{
    return c1.mul(c2);
}

MatUint8 operator+(const MatUint8& c1,const MatUint8& c2)
{
    return c1.add(c2);
}

MatUint8 operator-(const MatUint8& c1,const MatUint8& c2)
{
    return c1.sub(c2);
}