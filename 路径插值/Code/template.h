#ifndef TEMPLATE_H
#define TEMPLATE_H

template<class T> class mat
{
public:
    mat(unsigned row, unsigned cow) //指定行列构造
    {
        setDim(row, cow);
    }
    ~mat()
    {
        for (unsigned i = 0; i < elem.size(); i++)
        {
            elem[i].clear();
            elem[i].shrink_to_fit();
        }
        elem.clear();
        elem.shrink_to_fit();
    }

    void setDim(unsigned row,unsigned cow)
    {
        elem.resize(row);
        for (unsigned i = 0; i < row; i++)
        {
            elem[i].resize(cow);
        }
    }

    friend mat<T>  operator*(const mat<T>&A, const mat< T>&B)   //矩阵乘法
    {
        unsigned i, j, k;
        mat<T> C(A.getRow(), B.getCow());
        for (i = 0; i <A.getRow(); i++)
        {
            for (j = 0; j < B.getCow(); j++)
            {
                for (k = 0; k < A.getCow(); k++)
                {
                    C[i][j]+=A[i][k] * B[k][j];
                }
            }
        }
        return C;
    }
    friend mat<T>  operator*(const T& e,const mat<T>&A)     //矩阵数乘
    {
        mat<T> C(A.getRow(), A.getCow());

        for (unsigned i = 0; i < C.getRow(); i++)
        {
            for (unsigned j = 0; j < C.getCow(); j++)
            {
                C[i][j] = A[i][j]*e;
            }
        }
        return C;
    }
    friend mat<T>  operator/(const mat<T>&A,const T& e)     //矩阵除以一个数
    {
        mat<T> C(A.getRow(), A.getCow());

        for (unsigned i = 0; i < C.getRow(); i++)
        {
            for (unsigned j = 0; j < C.getCow(); j++)
            {
                C[i][j]= A[i][j]/e;
            }
        }
        return C;
    }

private:
    vector<vector <T>> elem;
};
#endif // TEMPLATE_H
