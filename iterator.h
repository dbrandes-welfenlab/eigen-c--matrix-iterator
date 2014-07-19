#ifndef ITERATOR_H
#define ITERATOR_H

#include <eigen3/Eigen/Dense>

#include <cpp11-range/range.hpp>

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
range_proxy<long int> indices(const Eigen::Matrix<_Scalar,_Rows,_Cols>& mat)
{
    if (mat.rows() > 1)
    {
        return {0, mat.rows()};
    }
    else
    {
        return {0, mat.cols()};
    }
}

}
}

#endif // ITERATOR_H
