/* Copyright (c) 2021 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#pragma once

#include <memory>
#include <vector>
#include "paddle/fluid/extension/include/dtype.h"
#include "paddle/fluid/extension/include/place.h"

namespace paddle {
namespace framework {
class CustomTensorUtils;
}  // namespace framework
class Tensor {
 public:
  /// \brief Construct a Tensor on None Place for CustomOp.
  /// Generally it's only used for user to create Tensor.
  explicit Tensor(const PlaceType& place);
  /// \brief Reset the shape of the tensor.
  /// Generally it's only used for the input tensor.
  /// Reshape must be called before calling
  /// mutable_data() or copy_from_cpu()
  /// \param shape The shape to set.
  void reshape(const std::vector<int>& shape);

  /// \brief Get the memory pointer in CPU or GPU with
  /// specific data type.
  /// Please Reshape the tensor first before call this.
  /// It's usually used to get input data pointer.
  /// \param place The place of the tensor this will
  /// override the original place of current tensor.
  template <typename T>
  T* mutable_data(const PlaceType& place);

  /// \brief Get the memory pointer in CPU or GPU with
  /// specific data type. Please Reshape the tensor
  /// first before call this.It's usually used to get
  /// input data pointer.
  template <typename T>
  T* mutable_data();

  /// \brief Get the memory pointer directly.
  /// It's usually used to get the output data pointer.
  /// \return The tensor data buffer pointer.
  template <typename T>
  T* data() const;

  /// \brief Copy the host memory to tensor data.
  /// It's usually used to set the input tensor data.
  /// \param PlaceType of target place, from which
  /// the tensor will copy.

  template <typename T>
  Tensor copy_to(const PlaceType& place);

  /// \brief Return the shape of the Tensor.
  std::vector<int> shape() const;

  /// \brief Return the data type of the tensor.
  /// It's usually used to get the output tensor data type.
  /// \return The data type of the tensor.
  DataType type() const;

  /// \brief Get the size of current tensor.
  /// Use this method to get the size of tensor
  /// \return int64_t.
  int64_t size() const;

  /// \brief Get the place of current tensor.
  /// Use this method to get the place of tensor
  /// \return Place.
  const PlaceType& place() const;

  /// \brief Cast datatype from one to another
  Tensor cast(const DataType& target_type);

 private:
  friend class framework::CustomTensorUtils;
  mutable std::shared_ptr<void> tensor_;
  mutable PlaceType place_;
};

}  // namespace paddle
