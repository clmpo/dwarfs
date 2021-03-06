/* vim:set ts=2 sw=2 sts=2 et: */
/**
 * \author     Marcus Holland-Moritz (github@mhxnet.de)
 * \copyright  Copyright (c) Marcus Holland-Moritz
 *
 * This file is part of dwarfs.
 *
 * dwarfs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dwarfs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dwarfs.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <string>

#include <boost/noncopyable.hpp>

#include <folly/Range.h>

namespace dwarfs {

class mmif : public boost::noncopyable {
 public:
  virtual ~mmif() = default;

  const void* get() const { return addr_; }

  template <typename T>
  const T* as(size_t offset = 0) const {
    return reinterpret_cast<const T*>(
        reinterpret_cast<const char*>(const_cast<const void*>(addr_)) + offset);
  }

  size_t size() const { return size_; }

  folly::ByteRange range(size_t start, size_t size) const {
    return folly::ByteRange(as<uint8_t>(start), size);
  }

 protected:
  void assign(const void* addr, size_t size) {
    addr_ = addr;
    size_ = size;
  }

 private:
  const void* addr_;
  size_t size_;
};
} // namespace dwarfs
