//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// p0_starter.h
//
// Identification: src/include/primer/p0_starter.h
//
// Copyright (c) 2015-2020, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <memory>

namespace bustub {

/*
 * The base class defining a Matrix
 * 
 * Matrix is an interface(pure virtual class)
 */
template <typename T>
class Matrix {
 protected:
  // TODO(P0): Add implementation
  Matrix(int r, int c) {
    rows = r;
    cols = c;
    linear = new T[rows*cols];
  }

  // # of rows in the matrix
  int rows;
  // # of Columns in the matrix
  int cols;
  // Flattened array containing the elements of the matrix
  // TODO(P0) : Allocate the array in the constructor. Don't forget to free up
  // the array in the destructor.
  T *linear;

 public:
  // Return the # of rows in the matrix
  virtual int GetRows() = 0;

  // Return the # of columns in the matrix
  virtual int GetColumns() = 0;

  // Return the (i,j)th  matrix element
  virtual T GetElem(int i, int j) = 0;

  // Sets the (i,j)th  matrix element to val
  virtual void SetElem(int i, int j, T val) = 0;

  // Sets the matrix elements based on the array arr
  virtual void MatImport(T *arr) = 0;

  // TODO(P0): Add implementation
  virtual ~Matrix() {
    // De-allocates a dynamic array.
    delete[] linear;
  };
};

template <typename T>
class RowMatrix : public Matrix<T> {
 public:
  // TODO(P0): Add implementation
  RowMatrix(int r, int c) : Matrix<T>(r, c) {
    data_ = new T*[r];
    for (int i=0; i < r; i++) {
      data_[i] = this->linear + (i * c);
    }
  }

  // TODO(P0): Add implementation
  int GetRows() override {
    return this->rows;
  }

  // TODO(P0): Add implementation
  int GetColumns() override {
    return this->cols;
  }

  // TODO(P0): Add implementation
  T GetElem(int i, int j) override {
    return data_[i][j];
  }

  // TODO(P0): Add implementation
  void SetElem(int i, int j, T val) override {
    data_[i][j] = val;
  }

  // TODO(P0): Add implementation
  void MatImport(T *arr) override {
    int total_elements = this->rows * this->cols;
    for (int i=0; i<total_elements; i++) {
      int ri = i / this->cols;
      int ci = i % this->cols;
      data_[ri][ci] = arr[i];
    }
  }

  // TODO(P0): Add implementation
  ~RowMatrix() override {
    // for (int i=0; i<this->rows; i++) {
    //   delete[] data_[i];
    // }
    delete[] data_;
  };

 private:
  // 2D array containing the elements of the matrix in row-major format
  // TODO(P0): Allocate the array of row pointers in the constructor. Use these pointers
  // to point to corresponding elements of the 'linear' array.
  // Don't forget to free up the array in the destructor.
  T **data_;
};

template <typename T>
class RowMatrixOperations {
 public:
  // Compute (mat1 + mat2) and return the result.
  // Return nullptr if dimensions mismatch for input matrices.
  static std::unique_ptr<RowMatrix<T>> AddMatrices(std::unique_ptr<RowMatrix<T>> mat1,
                                                   std::unique_ptr<RowMatrix<T>> mat2) {
    // TODO(P0): Add code
    if (mat1->GetColumns() != mat2->GetColumns() || mat1->GetRows() != mat2->GetRows()) {
      return nullptr;
    }

    int cols = mat1->GetColumns();
    int rows = mat1->GetRows();
    // Allocate memory for result matrix.
    RowMatrix<int>* res{new RowMatrix<int>(rows, cols)};

    for (int i=0; i<rows; i++)
      for (int j=0; j<cols; j++) {
        int e1 = mat1->GetElem(i, j);
        int e2 = mat2->GetElem(i, j);
        res->SetElem(i, j, e1+e2);
      }

    return std::unique_ptr<RowMatrix<T>>(res);
  }

  // Compute matrix multiplication (mat1 * mat2) and return the result.
  // Return nullptr if dimensions mismatch for input matrices.
  static std::unique_ptr<RowMatrix<T>> MultiplyMatrices(std::unique_ptr<RowMatrix<T>> mat1,
                                                        std::unique_ptr<RowMatrix<T>> mat2) {
    // TODO(P0): Add code
    int m1r = mat1->GetRows();
    int m1c = mat1->GetColumns();
    int m2r = mat2->GetRows();
    int m2c = mat2->GetColumns();

    if (m1c != m2r) {
      return nullptr;
    }
    // Allocate memory for result matrix.
    RowMatrix<int>* res{new RowMatrix<int>(m1r, m2c)};
    for (int i=0; i<m1r; i++) {
      for (int j=0; j<m2c; j++) {
        res->SetElem(i, j, 0);
        int val = 0;
        for (int k=0; k<m1c; k++) {
          val += mat1->GetElem(i, k) * mat2->GetElem(k, j);
          res->SetElem(i, j, val);
        }
      }
    }

    return std::unique_ptr<RowMatrix<T>>(res);
  }

  // Simplified GEMM (general matrix multiply) operation
  // Compute (matA * matB + matC). Return nullptr if dimensions mismatch for input matrices
  static std::unique_ptr<RowMatrix<T>> GemmMatrices(std::unique_ptr<RowMatrix<T>> matA,
                                                    std::unique_ptr<RowMatrix<T>> matB,
                                                    std::unique_ptr<RowMatrix<T>> matC) {
    // TODO(P0): Add code

    return std::unique_ptr<RowMatrix<T>>(nullptr);
  }
};
}  // namespace bustub
