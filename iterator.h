#ifndef ITERATOR_H
#define ITERATOR_H

#include <eigen3/Eigen/Dense>

template<class T>
class Iterator
{
    T* data;
    int position;
public:
    explicit Iterator(T* data);
    auto& operator*();
    Iterator& operator++();
    bool operator!=(const Iterator& it) const;
};

template<class T, typename _Scalar, int _Rows, int _Cols> Iterator<T> begin(Eigen::Matrix<_Scalar, _Rows, _Cols>& mat);
template<class T, typename _Scalar, int _Rows, int _Cols> Iterator<T> end(Eigen::Matrix<_Scalar, _Rows, _Cols>& mat);

template<class T>
class ConstIterator {
    const T& data;
    int position;
public:
    explicit ConstIterator(const T& data);
    const auto& operator*();
    ConstIterator& operator++();
    bool operator!=(const ConstIterator& it) const;
};

template<class T, typename _Scalar, int _Rows, int _Cols> ConstIterator<T> begin(const Eigen::Matrix<_Scalar, _Rows, _Cols>& mat);
template<class T, typename _Scalar, int _Rows, int _Cols> ConstIterator<T> end(const Eigen::Matrix<_Scalar, _Rows, _Cols>& mat);

#endif // ITERATOR_H
