#ifndef ITERATOR_H
#define ITERATOR_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <Eigen/Dense>
#pragma GCC diagnostic pop

#include "range.hpp"

namespace Eigen
{
    template<typename _Scalar, int _Rows, int _Cols>
    class Iterator
    {
        Matrix<_Scalar, _Rows, _Cols>& data;
        int position;
    public:
        explicit Iterator(Matrix<_Scalar, _Rows, _Cols>& data, int position): data(data), position(position) {}

        Eigen::Block<Eigen::Matrix<_Scalar, _Rows, _Cols>,1,_Cols, false > operator*()
        {
            return data.row(position);
        }

        Iterator& operator++()
        {
            position++;
            return *this;
        }

        bool operator!=(const Iterator& it) const
        {
            return position != it.position;
        }
    };

    template<typename _Scalar, int _Rows>
    class Iterator<_Scalar,_Rows, 1>
    {
        Matrix<_Scalar, _Rows, 1>& data;
        int position;
    public:
        explicit Iterator(Matrix<_Scalar, _Rows, 1>& data, int position): data(data), position(position) {}

        _Scalar& operator*()
        {
            return data[position];
        }

        Iterator& operator++()
        {
            position++;
            return *this;
        }

        bool operator!=(const Iterator& it) const
        {
            return position != it.position;
        }
    };

    template<typename _Scalar, int _Rows, int _Cols> Iterator<_Scalar, _Rows, _Cols> begin(Eigen::Matrix<_Scalar, _Rows, _Cols>& mat)
    {
        return Iterator<_Scalar, _Rows, _Cols>(mat,0);
    }

    template<typename _Scalar, int _Rows, int _Cols> Iterator<_Scalar, _Rows, _Cols> end(Eigen::Matrix<_Scalar, _Rows, _Cols>& mat)
    {
        return Iterator<_Scalar, _Rows, _Cols>(mat,mat.rows());
    }

    template<typename _Scalar, int _Rows, int _Cols>
    class IteratorRow
    {
        Eigen::Block<Eigen::Matrix<_Scalar, _Rows, _Cols>,1,_Cols, false > data;
        int position;
    public:
        explicit IteratorRow(Eigen::Block<Eigen::Matrix<_Scalar, _Rows, _Cols>,1,_Cols, false > data, int position): data(data), position(position) {}

        _Scalar& operator*()
        {
            return data[position];//(0,position);
        }

        IteratorRow& operator++()
        {
            position++;
            return *this;
        }

        bool operator!=(const IteratorRow& it) const
        {
            return position != it.position;
        }
    };

    template<typename _Scalar, int _Rows, int _Cols> IteratorRow<_Scalar, _Rows, _Cols> begin(Eigen::Block<Eigen::Matrix<_Scalar, _Rows, _Cols>,1,_Cols, false > mat)
    {
        return IteratorRow<_Scalar, _Rows, _Cols>(mat,0);
    }

    template<typename _Scalar, int _Rows, int _Cols> IteratorRow<_Scalar, _Rows, _Cols> end(Eigen::Block<Eigen::Matrix<_Scalar, _Rows, _Cols>,1,_Cols, false > mat)
    {
        return IteratorRow<_Scalar, _Rows, _Cols>(mat,mat.cols());
    }

    template<typename _Scalar, int _Rows, int _Cols>
    class ConstIterator {
        const Matrix<_Scalar, _Rows, _Cols>& data;
        int position;
    public:
        explicit ConstIterator(const Matrix<_Scalar, _Rows, _Cols>& data, int position): data(data), position(position) {}

        const Eigen::Block<const Eigen::Matrix<_Scalar, _Rows, _Cols>,1,_Cols, false > operator*()
        {
            return data.row(position);
        }

        ConstIterator& operator++()
        {
            position++;
            return *this;
        }

        bool operator!=(const ConstIterator& it) const
        {
            return it.position != position;
        }
    };

    template<typename _Scalar, int _Rows>
    class ConstIterator<_Scalar,_Rows, 1>
    {
        const Matrix<_Scalar, _Rows, 1>& data;
        int position;
    public:
        explicit ConstIterator(const Matrix<_Scalar, _Rows, 1>& data, int position): data(data), position(position) {}

        const _Scalar& operator*()
        {
            return data[position];
        }

        ConstIterator& operator++()
        {
            position++;
            return *this;
        }

        bool operator!=(const ConstIterator& it) const
        {
            return position != it.position;
        }
    };

    template<typename _Scalar, int _Rows, int _Cols> ConstIterator<_Scalar, _Rows, _Cols> begin(const Eigen::Matrix<_Scalar, _Rows, _Cols>& mat)
    {
        return ConstIterator<_Scalar, _Rows, _Cols>(mat,0);
    }

    template<typename _Scalar, int _Rows, int _Cols> ConstIterator<_Scalar, _Rows, _Cols> end(const Eigen::Matrix<_Scalar, _Rows, _Cols>& mat)
    {
        return ConstIterator<_Scalar, _Rows, _Cols>(mat,mat.rows());
    }
}

namespace util
{
namespace lang
{

template<typename _Scalar, int _Rows, int _Cols>
int len(const Eigen::Matrix<_Scalar,_Rows,_Cols>& mat)
{
    return mat.rows();
}

template<typename _Scalar, int _Cols>
int len(const Eigen::Matrix<_Scalar, 1,_Cols>& mat)
{
    return mat.cols();
}

template<typename _Scalar, int _Rows, int _Cols, int _Rows2, int _Cols2>
int len(const Eigen::Block<const Eigen::Matrix<_Scalar, _Rows, _Cols>, _Rows2, _Cols2, false>& mat)
{
    return mat.rows();
}

template<typename _Scalar, int _Rows, int _Cols, int _Cols2>
int len(const Eigen::Block<const Eigen::Matrix<_Scalar, _Rows, _Cols>, 1, _Cols2, false>& mat)
{
    return mat.cols();
}

template<typename _Scalar, int _Rows, int _Cols, int _Rows2, int _Cols2>
int len(const Eigen::Block<Eigen::Matrix<_Scalar, _Rows, _Cols>, _Rows2, _Cols2, false>& mat)
{
    return mat.rows();
}

template<typename _Scalar, int _Rows, int _Cols, int _Cols2>
int len(const Eigen::Block<Eigen::Matrix<_Scalar, _Rows, _Cols>, 1, _Cols2, false>& mat)
{
    return mat.cols();
}

template<typename _Scalar, int _Rows, int _Cols>
const Eigen::Block<const Eigen::Matrix<_Scalar, _Rows, _Cols>, 1, _Cols, false> elementAt(const Eigen::Matrix<_Scalar, _Rows, _Cols>& mat, int pos)
{
    return mat.row(pos);
}

template<typename _Scalar, int _Rows>
const _Scalar& elementAt(const Eigen::Matrix<_Scalar, _Rows, 1>& mat, int pos)
{
    return mat[pos];
}

template<typename _Scalar, int _Rows, int _Cols>
void setElementAt(Eigen::Block<Eigen::Matrix<_Scalar, _Rows, _Cols>, 1, _Cols, false> mat, int pos, const _Scalar& elem)
{
    mat[pos] = elem;
}

template<typename _Scalar, int _Rows>
void setElementAt(Eigen::Matrix<_Scalar, _Rows, 1>& mat, int pos, const _Scalar& elem)
{
    mat[pos] = elem;
}

template<typename _Scalar, int _Rows, int _Cols>
range_proxy<int> indices(const Eigen::Matrix<_Scalar,_Rows,_Cols>& mat)
{
    return {0, len(mat)};
}

template<typename _Scalar, int _Cols>
void resizeOuter(Eigen::Matrix<_Scalar, -1, _Cols>& mat, int size)
{
    mat.resize(size,std::max(1,(int)mat.cols()));
}

#if 0
template<typename _Scalar, int _Cols>
//const Eigen::Block<const Eigen::Matrix<_Scalar, 1, _Cols>, 1, 1, false > elementAt(const Eigen::Matrix<_Scalar,1,_Cols>& mat, int pos)
const _Scalar& elementAt(const Eigen::Matrix<_Scalar,1,_Cols>& mat, int pos)
{
    return mat[pos];
}
#endif

#if 0
template<typename Matrix, int _Rows, int _Cols>
const Eigen::Block<const Eigen::Block<Matrix, _Rows, _Cols, false>, 1, _Cols, false> elementAt(const Eigen::Block<Matrix, _Rows, _Cols, false>& mat, int pos)
{
    return mat.row(pos);
}

template<typename Matrix, int _Cols>
const Eigen::Block<const Eigen::Block<Matrix, 1, _Cols, false>, 1, 1, false> elementAt(const Eigen::Block<Matrix, 1, _Cols, false>& mat, int pos)
{
    return mat.col(pos);
}
#endif

}
}

#endif // ITERATOR_H
