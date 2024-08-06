
#include "Matrix.h"

#include <algorithm>
#include <vector>


using namespace std;

vector<vector<double>> operator_add(vector<vector<double>> arrA, vector<vector<double>> arrB)
{
    //����ӷ�
    // ����arrA������
    int rowA = arrA.size();
    //����arrA������  
    int colA = arrA[0].size();
    //����arrB������  
    int rowB = arrB.size();
    //����arrB������  
    int colB = arrB[0].size();

    vector<vector<double>>  res;
    if ((colA != colB) || (rowA != rowB))//�жϾ��������Ƿ�һ��  
    {
        printf("���󲻿�����");
    }
    else
    {
        //���ý������Ĵ�С����ʼ��ΪΪ0  
        res.resize(rowA);
        for (int i = 0; i < rowA; ++i)
        {
            res[i].resize(colB);
        }

        //�������  
        for (int i = 0; i < rowA; ++i)
        {
            for (int j = 0; j < colB; ++j)
            {

                res[i][j] = arrA[i][j] + arrB[i][j];

            }
        }
    }
    return res;
}

vector<vector<double>> operator_multiply(vector<vector<double>> arrA, vector<vector<double>> arrB)
{
    //����˷�
    //����arrA������  
    int rowA = arrA.size();
    //����arrA������  
    int colA = arrA[0].size();
    //����arrB������  
    int rowB = arrB.size();
    //����arrB������  
    int colB = arrB[0].size();
    vector<vector<double>>  res;

    if (colA != rowB)//�������arrA�����������ھ���arrB��������
    {
        printf("���󲻿�����");
    }
    else
    {
        //���ý������Ĵ�С����ʼ��ΪΪ0  
        res.resize(rowA);
        for (int i = 0; i < rowA; ++i)
        {
            res[i].resize(colB);
        }

        //�������  
        for (int i = 0; i < rowA; ++i)
        {
            for (int j = 0; j < colB; ++j)
            {
                for (int k = 0; k < colA; ++k)
                {
                    res[i][j] += arrA[i][k] * arrB[k][j];
                }
            }
        }
    }
    return res;
}


vector<vector<double>> operator_number(vector<vector<double>> arr, double m)
{
    //����˷�
    //����arrA������  
    int row = arr.size();
    //����arrA������  
    int col = arr[0].size();

    vector<vector<double>>  res;
    //���ý������Ĵ�С����ʼ��ΪΪ0  
    res.resize(row);
    for (int i = 0; i < row; ++i)
    {
        res[i].resize(col);
    }

    //�������  
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {

            res[i][j] = arr[i][j] * m;
        }
    }

    return res;

}

vector<vector<double>> operator_inv(vector<vector<double>> arrA)
{
    //�������
    //����arrA������  
    int row = arrA.size();
    //����arrA������  
    int col = arrA[0].size();
    if (row != col)
    {
        printf("���󲻿�����");
    }

    vector<vector<double>>  res;
    res.resize(row);
    for (int i = 0; i < row; ++i)
    {
        res[i].resize(col);
        res[i][i] = 1;//��ʼ����λ��
    }
    int temp_row = 0;
    double max = 0;
    double ratio = 0;
    for (int i = 0; i < row; i++)
    {
        //��ѡ��Ԫ��
        max = arrA[i][i];
        temp_row = i;
        for (int i_change = i; i_change < row; i_change++)
        {
            if (i_change == i)
                continue;
            if (max < arrA[i][i_change])
            {
                max = arrA[i][i_change];
                temp_row = i_change;
            }
        }
        if (temp_row != i)
        {
            swap(arrA[i], arrA[temp_row]);
            swap(res[i], res[temp_row]);
        }

        //��Ԫ
        for (int i_change = 0; i_change < row; i_change++)
        {
            if (i_change == i)
                continue;
            ratio = arrA[i][i] / arrA[i_change][i];

            for (int j = 0; j < col; j++)
            {
                if (j >= i)
                {
                    arrA[i_change][j] = (arrA[i_change][j] - arrA[i][j] / ratio);
                }
                res[i_change][j] = (res[i_change][j] - res[i][j] / ratio);
            }

        }


    }
    //��һ
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            res[i][j] = res[i][j] / arrA[i][i];
        }
    }

    return res;
}

vector<vector<double>> operator_converse(vector<vector<double>> arrA)
{
    //ת�þ���
    //����arrA������  
    int row = arrA.size();
    //����arrA������  
    int col = arrA[0].size();

    vector<vector<double>>  res;
    //��ʼ������
    res.resize(col);
    for (int i = 0; i < col; ++i)
    {
        res[i].resize(row);
    }

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            res[i][j] = arrA[j][i];
        }
    }

    return res;
}