#include<iostream>
#include"mat_float.h"
//构造函数
MatFloat::MatFloat(int h, int w)
{
    size1 = h;
    size2 = w;
    data = new float*[size1];
    for (int i = 0; i <= size1 - 1; i++)
    {
        data[i] = new float[size2]();
    }
}
//拷贝构造函数
MatFloat::MatFloat(const MatFloat &c)
{
    size1=c.get_size1();
    size2=c.get_size2();
    data=new float*[size1];
    float **c_data = c.get_data();
    for(int i=0;i<=size1-1;i++)
    {
        data[i]=new float[size2];
        for(int j=0;j<=size2-1;j++)
        {
            data[i * size2 + j] = c_data[i * size2 + j];
        }
    }
}
//析构函数
MatFloat::~MatFloat()
{
    for(int i=0;i<size1;i++)
    {
        delete []data[i];
    }
    delete []data;
}
//获取长度size1
int MatFloat::get_size1() const
{
    return size1;
}
//获取宽度size2
int MatFloat::get_size2() const
{
    return size2;
}
//获取数据指针data
float ** MatFloat::get_data() const
{
    return data;
}
//矩阵乘法
MatFloat MatFloat::mul(const MatFloat &c) const
{
    if (size2 == c.get_size1())
    {
        MatFloat res(size1, c.get_size2());
        float **res_data = res.get_data();
        float **c_data = c.get_data();
        for (int i=0; i<size1; i++)
        {
            for (int j=0; j<c.get_size2(); j++)
            {
                float num = 0;
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
        return MatFloat(1, 1);
    }
}
//矩阵加法
MatFloat MatFloat::add(const MatFloat &c) const
{
    if ((size1 == c.get_size1()) and (size2 == c.get_size2()))
    {
        MatFloat res(size1, size2);
        float **res_data = res.get_data();
        float **c_data = c.get_data();
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
        return MatFloat(1, 1);
    }
}
//矩阵减法
MatFloat MatFloat::sub(const MatFloat &c) const
{
    if ((size1 == c.get_size1()) and (size2 == c.get_size2()))
    {
        MatFloat res(size1, size2);
        float **res_data = res.get_data();
        float **c_data = c.get_data();
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
        return MatFloat(1, 1);
    }
}
//矩阵求转置
MatFloat MatFloat::t() const
{
    MatFloat res(size2, size1);
    float ** res_data = res.get_data();
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
MatFloat MatFloat::inv() const
{
    if (size1==size2)
    {
        MatFloat res(size1, size2);
        float **res_data = res.get_data();
        if(size1==1)
        {
            res_data[0][0] = 1;
            return res;
        }
        float mat_det = det();
        if ((mat_det <= 1e-5) and (mat_det >= -1e-5))
        {
            cout<<"the matrix is strange"<<endl;
            return res;
        }
        MatFloat temp(size1-1, size1-1);
        float ** temp_data = temp.get_data();
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
        return MatFloat(1, 1);
    }
}
//矩阵填充
MatFloat MatFloat::pad(const int &pad_row, const int &pad_col) const
{
    MatFloat res(size1+2*pad_row, size2+2*pad_col);
    float ** res_data = res.get_data();
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
float MatFloat::det() const
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
    float ans = 0;
    MatFloat temp(size1-1, size1-1);
    float **temp_data = temp.get_data();
    for(int i=0;i<size1;i++)
    {
        for(int j=0;j<size1-1;j++)
        {
            for(int k=0;k<size1-1;k++)
            {
                temp_data[j][k] = data[j+1][(k>=i)?k+1:k];

            }
        }
        float t = temp.det();
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
ostream& operator<<(ostream& out, const MatFloat&c)
{
    float **c_data=c.get_data();
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
float& MatFloat::operator [](int i)
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
MatFloat operator+(float r,const MatFloat& c)
{
    MatFloat res(c);
    float **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] + r;
        }
    }
    return res;
}

MatFloat operator+(int r,const MatFloat& c)
{
    MatFloat res(c);
    float **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] + r;
        }
    }
    return res;
}

MatFloat operator+(const MatFloat& c,float r)
{
    MatFloat res(c);
    float **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] + r;
        }
    }
    return res;
}

MatFloat operator+(const MatFloat& c,int r)
{
    MatFloat res(c);
    float **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] + r;
        }
    }
    return res;
}

MatFloat operator-(const MatFloat& c,float r)
{
    MatFloat res(c);
    float **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] - r;
        }
    }
    return res;
}

MatFloat operator-(const MatFloat& c,int r)
{
    MatFloat res(c);
    float **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] - r;
        }
    }
    return res;
}

MatFloat operator-(float r,const MatFloat& c)
{
    MatFloat res(c);
    float **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = r - res_data[i][j];
        }
    }
    return res;
}

MatFloat operator-(int r,const MatFloat& c)
{
    MatFloat res(c);
    float **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = r - res_data[i][j];
        }
    }
    return res;
}

MatFloat operator*(float r,const MatFloat& c)
{
    MatFloat res(c);
    float **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] * r;
        }
    }
    return res;
}

MatFloat operator*(int r,const MatFloat& c)
{
    MatFloat res(c);
    float **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] * r;
        }
    }
    return res;
}

MatFloat operator*(const MatFloat& c,float r)
{
    MatFloat res(c);
    float **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] * r;
        }
    }
    return res;
}

MatFloat operator*(const MatFloat& c,int r)
{
    MatFloat res(c);
    float **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] * r;
        }
    }
    return res;
}

MatFloat operator/(const MatFloat& c,float r)
{
    MatFloat res(c);
    float **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] / r;
        }
    }
    return res;
}

MatFloat operator/(const MatFloat& c,int r)
{
    MatFloat res(c);
    float **res_data = res.get_data();
    for (int i=0;i<c.get_size1();i++)
    {
        for (int j=0;j<c.get_size2();j++)
        {
            res_data[i][j] = res_data[i][j] / r;
        }
    }
    return res;
}

MatFloat operator*(const MatFloat& c1,const MatFloat& c2)
{
    return c1.mul(c2);
}

MatFloat operator+(const MatFloat& c1,const MatFloat& c2)
{
    return c1.add(c2);
}

MatFloat operator-(const MatFloat& c1,const MatFloat& c2)
{
    return c1.sub(c2);
}