#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

class Operation;
class Variable {
public:
  Variable(std::string expr) : expr_(expr) {}
  std::string expr() const { return expr_; }
  void operator=(const Operation &oth) const;

private:
  std::string expr_;
};
class Operation {
public:
  Operation(const Variable &a, std::string op, const Variable &b)
      : expr_(a.expr() + " " + op + " " + b.expr()) {}
  Operation(const Variable &a, std::string op, long long b)
      : expr_(a.expr() + " " + op + " " + std::to_string(b)) {}
  Operation(long long a, std::string op, const Variable &b)
      : expr_(std::to_string(a) + " " + op + " " + b.expr()) {}
  std::string expr() const { return expr_; }

private:
  std::string expr_;
};

void Variable::operator=(const Operation &oth) const {
  std::cout << expr_ + " = " + oth.expr() + "\n";
}

class Array {
  class ArrayImpl {
  public:
    ArrayImpl() {}
    ArrayImpl(std::string name, size_t size) : name_(name), size_(size) {}
    virtual Variable operator[](size_t index) {
      assert(index < size_);
      return Variable(name_ + "[" + std::to_string(index) + "]");
    }
    virtual size_t size() const { return size_; }

  private:
    std::string name_;
    size_t size_;
  };

  class SlicedArray : public ArrayImpl {
  public:
    SlicedArray(ArrayImpl *impl, size_t start, size_t stop)
        : impl_(impl), start_(start), stop_(stop) {}
    Variable operator[](size_t index) override {
      assert(index + start_ < stop_);
      return (*impl_)[start_ + index];
    }
    size_t size() const override { return stop_ - start_; }

  private:
    ArrayImpl *impl_;
    size_t start_;
    size_t stop_;
  };

  class ReversedArray : public ArrayImpl {
  public:
    ReversedArray(ArrayImpl *impl) : impl_(impl) {}
    virtual Variable operator[](size_t index) override {
      assert(index < impl_->size());
      return (*impl_)[impl_->size() - index - 1];
    }
    size_t size() const override { return impl_->size(); }

  private:
    ArrayImpl *impl_;
    size_t start_;
    size_t stop_;
  };

public:
  Array(std::string name, size_t size)
      : impl_(std::make_shared<ArrayImpl>(name, size)) {}
  Array(std::shared_ptr<ArrayImpl> impl) : impl_(std::move(impl)) {}
  Variable operator[](size_t index) { return (*impl_)[index]; }
  size_t size() const { return impl_->size(); }
  Array reverse() const {
    return Array(std::make_shared<ReversedArray>(impl_.get()));
  }
  Array slice(size_t start, size_t stop) const {
    return Array(std::make_shared<SlicedArray>(impl_.get(), start, stop));
  }

private:
  std::shared_ptr<ArrayImpl> impl_;
};

void reduce(Array last_layer, Array output, std::string mid, std::string op,
            long long neutral) {
  int N = last_layer.size();
  if (N == 1) {
    output[0] = Operation(last_layer[0], op, neutral);
    return;
  }
  int layer_size = N;
  int count = 1;
  for (; (layer_size + 1) >> 1 > 1; layer_size = (layer_size + 1) >> 1) {
    Array layer(mid + std::to_string(count++), (layer_size + 1) >> 1);
    for (int i = 0; i<layer_size>> 1; i++) {
      layer[i] = Operation(last_layer[2 * i], op, last_layer[2 * i + 1]);
    }
    if (layer_size & 1) {
      layer[layer_size >> 1] =
          Operation(last_layer[layer_size - 1], op, neutral);
    }
    last_layer = layer;
  }
  output[0] = Operation(last_layer[0], op, last_layer[1]);
}

void reduce(int N, std::string in, std::string out, std::string mid,
            std::string op, long long neutral) {
  Array last_layer = Array(in, N);
  Array output = Array(out, 1);
  reduce(last_layer, output, mid, op, neutral);
}

// Can be improved.
void scan(Array in, Array out, std::string mid, std::string op,
          long long neutral, int depth) {
  int N = in.size();
  out[0] = Operation(in[0], op, neutral);
  if (N == 1)
    return;
  if (N == 2) {
    out[1] = Operation(in[0], op, in[1]);
    return;
  }
  Array merged_in = Array(mid + "_in_" + std::to_string(depth), N / 2);
  Array merged_out = Array(mid + "_out_" + std::to_string(depth), N / 2);
  for (int i = 0; i < N / 2; i++) {
    merged_in[i] = Operation(in[2 * i], op, in[2 * i + 1]);
  }
  scan(merged_in, merged_out, mid, op, neutral, depth + 1);
  for (int i = 0; i < N / 2; i++) {
    out[2 * i + 1] = Operation(merged_out[i], op, neutral);
    if (2 * i + 2 < N) {
      out[2 * i + 2] = Operation(merged_out[i], op, in[2 * i + 2]);
    }
  }
}

void scan(Array input, Array output, std::string mid, std::string op,
          long long neutral) {
  scan(input, output, mid, op, neutral, 0);
}

void scan(int N, std::string in, std::string out, std::string mid,
          std::string op, long long neutral) {
  Array input = Array(in, N);
  Array output = Array(out, N);
  scan(input, output, mid, op, neutral);
}
