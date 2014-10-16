#include "iterator.h"

#include <iostream>

#include <eigen3/Eigen/Dense>

using util::lang::range;
using util::lang::indices;
using util::lang::len;
using util::lang::elementAt;

typedef Eigen::VectorXd VecDd;
typedef Eigen::MatrixXd MatDd;

typedef Eigen::VectorXi VecDi;
typedef Eigen::MatrixXi MatDi;

//typedef Eigen::SparseMatrix<double> MatSd;
//typedef Eigen::SparseMatrix<int> MatSi;

typedef Eigen::Vector2d Vec2d;
typedef Eigen::Vector3d Vec3d;
//typedef Eigen::Vector4d Vec4d;

typedef Eigen::Matrix2d Mat2d;
typedef Eigen::Matrix3d Mat3d;
//typedef Eigen::Matrix4d Mat4d;

typedef Eigen::Vector2i Vec2i;
typedef Eigen::Vector3i Vec3i;
//typedef Eigen::Vector4i Vec4i;

typedef Eigen::Matrix2i Mat2i;
typedef Eigen::Matrix3i Mat3i;
//typedef Eigen::Matrix4i Mat4i;

void vectorTests()
{
    Vec2d t2(0.0,1.0);

    int i = 0;
    for (double t:t2)
    {
        assert(int(t) == i);
        i++;
    }

    i = 0;
    for (double& t:t2)
    {
        assert(int(t) == i);
        i++;
    }

    i = 0;
    for (const double& t:t2)
    {
        assert(int(t) == i);
        i++;
    }

    std::cout << "non-const tests done" << std::endl;

    const Vec2d& t3 = t2;

    i = 0;
    for (double t:t3)
    {
        assert(int(t) == i);
        i++;
    }

    i = 0;
    for (const double& t:t3)
    {
        assert(int(t) == i);
        i++;
    }
    std::cout << "vector tests done!" << std::endl;
}

void matTests()
{
    MatDi mat;
    mat.resize(2,2);
    mat << 0, 1, 2, 3;

    int i = 0;
    for (const Vec2i& vec: mat)
    {
        for (const int& t: vec)
        {
            assert(t == i);
            i++;
        }
    }

    i = 0;
    for (auto vec: mat)
    {
        for (int& t: vec)
        {
            assert(t == i);
            i++;
        }
    }

    i = 0;
    for (Vec2i vec: mat)
    {
        for (int t: vec)
        {
            assert(t == i);
            i++;
        }
    }

    std::cout << "non-const tests done" << std::endl;

    const MatDi& cmat = mat;

    i = 0;
    for (const Vec2i& vec: cmat)
    {
        for (const int& t: vec)
        {
            assert(t == i);
            i++;
        }
    }

    i = 0;
    for (Vec2i vec: cmat)
    {
        for (int t: vec)
        {
            assert(t == i);
            i++;
        }
    }

    std::cout << "dynamic matrix tests done" << std::endl;

    Mat3d mat2;
    i = 0;
    for (auto vec: mat2)
    {
        for (double& val: vec)
        {
            val = i;
            i++;
        }
    }

    i = 0;
    for (const Vec3d& vec: mat2)
    {
        for (double val: vec)
        {
            assert(i == int(val));
            i++;
        }
    }

    i = 0;
    for (Vec3d vec: mat2)
    {
        for (double val: vec)
        {
            assert(i == int(val));
            i++;
        }
    }

    std::cout << "non-const tests done" << std::endl;

    const Mat3d& cmat2 = mat2;

    i = 0;
    for (const Vec3d& vec: cmat2)
    {
        for (double val: vec)
        {
            assert(i == int(val));
            i++;
        }
    }

    i = 0;
    for (Vec3d vec: cmat2)
    {
        for (double val: vec)
        {
            assert(i == int(val));
            i++;
        }
    }

    std::cout << "static matrix tests done" << std::endl;
    i = 0;
    for (int j:indices(mat2))
    {
        assert(i == j);
        i++;
    }
    assert(i == 3);

    i = 0;
    for (int j:indices(cmat2))
    {
        assert(i == j);
        i++;
    }
    assert(i == 3);

    i = 0;
    for (int j:indices(mat))
    {
        assert(i == j);
        i++;
    }
    assert(i == 2);

    i = 0;
    for (int j:indices(cmat))
    {
        assert(i == j);
        i++;
    }
    assert(i == 2);
}

void otherTests()
{
    Mat2i mat1;
    mat1 << 0,1,2,3;
    MatDi mat2;
    mat2.resize(2,2);
    mat2 << 0,1,2,3;

    int l;
    l = len(mat1);
    assert(l == 2);
    l = len(mat1.row(0));
    assert(l == 2);
    l = len(mat2);
    assert(l == 2);
    l = len(mat2.row(0));
    assert(l == 2);

    Vec2i testvec;
    int testint;
    testvec = elementAt(mat1,1);
    assert(testvec[0] == 2);
    assert(testvec[1] == 3);
    testvec = elementAt(mat2,1);
    assert(testvec[0] == 2);
    assert(testvec[1] == 3);
    const Vec2i& mat1row0 = mat1.row(0);
    testint = elementAt(mat1row0,1);
    assert(testint == 1);
    const VecDi& mat2row0 = mat2.row(0);
    testint = elementAt(mat2row0,1);
    assert(testint == 1);

    Vec3i vec1;
    vec1 << 0,1,2;
    VecDi vec2;
    vec2.resize(3);
    vec2 << 0,1,2;
    assert(len(vec1) == 3);
    assert(len(vec2) == 3);

    testint = elementAt(vec1,1);
    assert(testint == 1);
    testint = elementAt(vec2,1);
    assert(testint == 1);
}

int main()
{
    vectorTests();
    matTests();
    otherTests();
}
