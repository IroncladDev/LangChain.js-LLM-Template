/**
 * hnswlib-node provides Node.js bindings for Hnswlib.
 *
 * Copyright (c) 2022-2023 Atsushi Tatsuma
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fstream>
#include <memory>
#include <new>
#include <string>
#include <vector>

#include <napi.h>

#include "hnswlib/hnswlib.h"

class L2Space : public Napi::ObjectWrap<L2Space> {
public:
  uint32_t dim_;
  std::unique_ptr<hnswlib::L2Space> l2space_;

  L2Space(const Napi::CallbackInfo& info) : Napi::ObjectWrap<L2Space>(info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
      Napi::Error::New(env, "Expected 1 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return;
    }
    if (!info[0].IsNumber()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a number.").ThrowAsJavaScriptException();
      return;
    }

    dim_ = info[0].As<Napi::Number>().Uint32Value();
    l2space_ = std::unique_ptr<hnswlib::L2Space>(new hnswlib::L2Space(static_cast<size_t>(dim_)));
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // clang-format off
    Napi::Function func = DefineClass(env, "L2Space", {
      InstanceMethod("distance", &L2Space::distance),
      InstanceMethod("getNumDimensions", &L2Space::getNumDimensions)
    });
    // clang-format on

    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);

    exports.Set("L2Space", func);
    return exports;
  }

private:
  Napi::Value distance(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 2) {
      Napi::Error::New(env, "Expected 2 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsArray()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be an Array.").ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[1].IsArray()) {
      Napi::TypeError::New(env, "Invalid the second argument type, must be an Array.").ThrowAsJavaScriptException();
      return env.Null();
    }

    Napi::Array arr_a = info[0].As<Napi::Array>();
    Napi::Array arr_b = info[1].As<Napi::Array>();

    if (arr_a.Length() != dim_) {
      Napi::Error::New(env, "Invalid the first array length (expected " + std::to_string(dim_) + ", but got " +
                              std::to_string(arr_a.Length()) + ").")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (arr_b.Length() != dim_) {
      Napi::Error::New(env, "Invalid the second array length (expected " + std::to_string(dim_) + ", but got " +
                              std::to_string(arr_b.Length()) + ").")
        .ThrowAsJavaScriptException();
      return env.Null();
    }

    std::vector<float> vec_a(dim_, 0.0);
    std::vector<float> vec_b(dim_, 0.0);

    for (uint32_t i = 0; i < dim_; i++) {
      Napi::Value val_a = arr_a[i];
      Napi::Value val_b = arr_b[i];
      vec_a[i] = val_a.As<Napi::Number>().FloatValue();
      vec_b[i] = val_b.As<Napi::Number>().FloatValue();
    }

    hnswlib::DISTFUNC<float> df = l2space_->get_dist_func();
    const float d = df(vec_a.data(), vec_b.data(), l2space_->get_dist_func_param());
    return Napi::Number::New(info.Env(), d);
  }

  Napi::Value getNumDimensions(const Napi::CallbackInfo& info) { return Napi::Number::New(info.Env(), dim_); }
};

class InnerProductSpace : public Napi::ObjectWrap<InnerProductSpace> {
public:
  uint32_t dim_;
  std::unique_ptr<hnswlib::InnerProductSpace> ipspace_;

  InnerProductSpace(const Napi::CallbackInfo& info) : Napi::ObjectWrap<InnerProductSpace>(info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
      Napi::Error::New(env, "Expected 1 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return;
    }
    if (!info[0].IsNumber()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a number.").ThrowAsJavaScriptException();
      return;
    }

    dim_ = info[0].As<Napi::Number>().Uint32Value();
    ipspace_ = std::unique_ptr<hnswlib::InnerProductSpace>(new hnswlib::InnerProductSpace(static_cast<size_t>(dim_)));
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // clang-format off
    Napi::Function func = DefineClass(env, "InnerProductSpace", {
      InstanceMethod("distance", &InnerProductSpace::distance),
      InstanceMethod("getNumDimensions", &InnerProductSpace::getNumDimensions)
    });
    // clang-format on

    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData(constructor);

    exports.Set("InnerProductSpace", func);
    return exports;
  }

private:
  Napi::Value distance(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 2) {
      Napi::Error::New(env, "Expected 2 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsArray()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be an Array.").ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[1].IsArray()) {
      Napi::TypeError::New(env, "Invalid the second argument type, must be an Array.").ThrowAsJavaScriptException();
      return env.Null();
    }

    Napi::Array arr_a = info[0].As<Napi::Array>();
    Napi::Array arr_b = info[1].As<Napi::Array>();

    if (arr_a.Length() != dim_) {
      Napi::Error::New(env, "Invalid the first array length (expected " + std::to_string(dim_) + ", but got " +
                              std::to_string(arr_a.Length()) + ").")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (arr_b.Length() != dim_) {
      Napi::Error::New(env, "Invalid the second array length (expected " + std::to_string(dim_) + ", but got " +
                              std::to_string(arr_b.Length()) + ").")
        .ThrowAsJavaScriptException();
      return env.Null();
    }

    std::vector<float> vec_a(dim_, 0.0);
    std::vector<float> vec_b(dim_, 0.0);

    for (uint32_t i = 0; i < dim_; i++) {
      Napi::Value val_a = arr_a[i];
      Napi::Value val_b = arr_b[i];
      vec_a[i] = val_a.As<Napi::Number>().FloatValue();
      vec_b[i] = val_b.As<Napi::Number>().FloatValue();
    }

    hnswlib::DISTFUNC<float> df = ipspace_->get_dist_func();
    const float d = df(vec_a.data(), vec_b.data(), ipspace_->get_dist_func_param());
    return Napi::Number::New(info.Env(), d);
  }

  Napi::Value getNumDimensions(const Napi::CallbackInfo& info) { return Napi::Number::New(info.Env(), dim_); }
};

class CustomFilterFunctor : public hnswlib::BaseFilterFunctor {
public:
  CustomFilterFunctor(const Napi::Env& env, const Napi::Function& callback) : env_(env), callback_(callback) {}

  bool operator()(hnswlib::labeltype id) { return callback_.Call({Napi::Number::New(env_, id)}).ToBoolean().Value(); }

private:
  Napi::Env env_;
  Napi::Function callback_;
};

class LoadBruteforceSearchIndexWorker : public Napi::AsyncWorker {
public:
  LoadBruteforceSearchIndexWorker(const std::string& filename, hnswlib::BruteforceSearch<float>** index,
                                  hnswlib::SpaceInterface<float>** space, Napi::Promise::Deferred deferred,
                                  Napi::Function& callback)
      : Napi::AsyncWorker(callback), deferred(deferred), filename_(filename), result_(false), index_(index), space_(space) {}

  ~LoadBruteforceSearchIndexWorker() {}

  void Execute() {
    try {
      std::ifstream ifs(filename_);
      if (ifs.is_open()) {
        ifs.close();
      } else {
        throw std::runtime_error("failed to open file: " + filename_);
      }
      if (*index_) delete *index_;
      *index_ = new hnswlib::BruteforceSearch<float>(*space_, filename_);
      result_ = true;
    } catch (const std::exception& e) {
      result_ = false;
      SetError("Hnswlib Error: " + std::string(e.what()));
    }
  }

  void OnOK() {
    Napi::HandleScope scope(Env());
    Napi::Boolean result = Napi::Boolean::New(Env(), result_);
    deferred.Resolve(result);
  }

  void OnError(const Napi::Error& e) { deferred.Reject(e.Value()); }

  Napi::Promise::Deferred deferred;

private:
  std::string filename_;
  bool result_;
  hnswlib::BruteforceSearch<float>** index_;
  hnswlib::SpaceInterface<float>** space_;
};

class SaveBruteforceSearchIndexWorker : public Napi::AsyncWorker {
public:
  SaveBruteforceSearchIndexWorker(const std::string& filename, hnswlib::BruteforceSearch<float>** index,
                                  Napi::Promise::Deferred deferred, Napi::Function& callback)
      : Napi::AsyncWorker(callback), deferred(deferred), filename_(filename), result_(false), index_(index) {}

  ~SaveBruteforceSearchIndexWorker() {}

  void Execute() {
    try {
      if (*index_ == nullptr) throw std::runtime_error("search index is not constructed.");
      (*index_)->saveIndex(filename_);
      result_ = true;
    } catch (const std::exception& e) {
      result_ = false;
      SetError("Hnswlib Error: " + std::string(e.what()));
    }
  }

  void OnOK() {
    Napi::HandleScope scope(Env());
    Napi::Boolean result = Napi::Boolean::New(Env(), result_);
    deferred.Resolve(result);
  }

  void OnError(const Napi::Error& e) { deferred.Reject(e.Value()); }

  Napi::Promise::Deferred deferred;

private:
  std::string filename_;
  bool result_;
  hnswlib::BruteforceSearch<float>** index_;
};

class BruteforceSearch : public Napi::ObjectWrap<BruteforceSearch> {
public:
  uint32_t dim_;
  hnswlib::BruteforceSearch<float>* index_;
  hnswlib::SpaceInterface<float>* space_;

  BruteforceSearch(const Napi::CallbackInfo& info)
      : Napi::ObjectWrap<BruteforceSearch>(info), index_(nullptr), space_(nullptr) {
    Napi::Env env = info.Env();

    if (info.Length() != 2) {
      Napi::Error::New(env, "Expected 2 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return;
    }
    if (!info[0].IsString()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a string.").ThrowAsJavaScriptException();
      return;
    }
    if (!info[1].IsNumber()) {
      Napi::TypeError::New(env, "Invalid the second argument type, must be a number.").ThrowAsJavaScriptException();
      return;
    }

    const std::string space_name = info[0].As<Napi::String>().ToString();
    if (space_name != "l2" && space_name != "ip") {
      Napi::Error::New(env, "Wrong space name, expected \"l2\" or \"ip\".").ThrowAsJavaScriptException();
      return;
    }

    dim_ = info[1].As<Napi::Number>().Uint32Value();

    try {
      if (space_name == "l2") {
        space_ = new hnswlib::L2Space(static_cast<size_t>(dim_));
      } else {
        space_ = new hnswlib::InnerProductSpace(static_cast<size_t>(dim_));
      }
    } catch (const std::bad_alloc& err) {
      Napi::Error::New(env, err.what()).ThrowAsJavaScriptException();
      return;
    }
  }

  ~BruteforceSearch() {
    if (space_) delete space_;
    if (index_) delete index_;
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // clang-format off
    Napi::Function func = DefineClass(env, "BruteforceSearch", {
      InstanceMethod("initIndex", &BruteforceSearch::initIndex),
      InstanceMethod("readIndex", &BruteforceSearch::readIndex),
      InstanceMethod("readIndexSync", &BruteforceSearch::readIndexSync),
      InstanceMethod("writeIndex", &BruteforceSearch::writeIndex),
      InstanceMethod("writeIndexSync", &BruteforceSearch::writeIndexSync),
      InstanceMethod("addPoint", &BruteforceSearch::addPoint),
      InstanceMethod("removePoint", &BruteforceSearch::removePoint),
      InstanceMethod("searchKnn", &BruteforceSearch::searchKnn),
      InstanceMethod("getMaxElements", &BruteforceSearch::getMaxElements),
      InstanceMethod("getCurrentCount", &BruteforceSearch::getCurrentCount),
      InstanceMethod("getNumDimensions", &BruteforceSearch::getNumDimensions)
    });
    // clang-format on

    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData<Napi::FunctionReference>(constructor);

    exports.Set("BruteforceSearch", func);
    return exports;
  }

private:
  Napi::Value initIndex(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
      Napi::Error::New(env, "Expected 1 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsNumber()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a number.").ThrowAsJavaScriptException();
      return env.Null();
    }

    const uint32_t max_elements = info[0].As<Napi::Number>().Uint32Value();

    if (index_) delete index_;

    try {
      index_ = new hnswlib::BruteforceSearch<float>(space_, static_cast<size_t>(max_elements));
    } catch (const std::bad_alloc& err) {
      index_ = nullptr;
      Napi::Error::New(env, err.what()).ThrowAsJavaScriptException();
      return env.Null();
    }

    return env.Null();
  }

  Napi::Value readIndex(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
      Napi::Error::New(env, "Expected 1 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsString()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a string.").ThrowAsJavaScriptException();
      return env.Null();
    }

    const std::string filename = info[0].As<Napi::String>().ToString();
    Napi::Function callback = Napi::Function::New(env, [](const Napi::CallbackInfo& info) { return info.Env().Undefined(); });
    Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());
    LoadBruteforceSearchIndexWorker* worker =
      new LoadBruteforceSearchIndexWorker(filename, &index_, &space_, deferred, callback);

    worker->Queue();

    return worker->deferred.Promise();
  }

  Napi::Value readIndexSync(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
      Napi::Error::New(env, "Expected 1 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsString()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a string.").ThrowAsJavaScriptException();
      return env.Null();
    }

    const std::string filename = info[0].As<Napi::String>().ToString();

    try {
      std::ifstream ifs(filename);
      if (ifs.is_open()) {
        ifs.close();
      } else {
        throw std::runtime_error("failed to open file: " + filename);
      }
      if (index_) delete index_;
      index_ = new hnswlib::BruteforceSearch<float>(space_, filename);
    } catch (const std::exception& e) {
      Napi::Error::New(env, "Hnswlib Error: " + std::string(e.what())).ThrowAsJavaScriptException();
      return env.Null();
    }

    return env.Null();
  }

  Napi::Value writeIndex(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
      Napi::Error::New(env, "Expected 1 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsString()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a string.").ThrowAsJavaScriptException();
      return env.Null();
    }

    const std::string filename = info[0].As<Napi::String>().ToString();
    Napi::Function callback = Napi::Function::New(env, [](const Napi::CallbackInfo& info) { return info.Env().Undefined(); });
    Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());
    SaveBruteforceSearchIndexWorker* worker = new SaveBruteforceSearchIndexWorker(filename, &index_, deferred, callback);

    worker->Queue();

    return worker->deferred.Promise();
  }

  Napi::Value writeIndexSync(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
      Napi::Error::New(env, "Expected 1 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsString()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a string.").ThrowAsJavaScriptException();
      return env.Null();
    }

    const std::string filename = info[0].As<Napi::String>().ToString();

    if (index_ == nullptr) {
      Napi::Error::New(env, "Search index is not constructed.").ThrowAsJavaScriptException();
      return env.Null();
    }

    index_->saveIndex(filename);

    return env.Null();
  }

  Napi::Value addPoint(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 2) {
      Napi::Error::New(env, "Expected 2 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsArray()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be an Array.").ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[1].IsNumber()) {
      Napi::TypeError::New(env, "Invalid the second argument type, must be a number.").ThrowAsJavaScriptException();
      return env.Null();
    }

    if (index_ == nullptr) {
      Napi::Error::New(env, "Search index has not been initialized, call `initIndex` in advance.").ThrowAsJavaScriptException();
      return env.Null();
    }

    Napi::Array arr = info[0].As<Napi::Array>();
    if (arr.Length() != dim_) {
      Napi::Error::New(env, "Invalid the given array length (expected " + std::to_string(dim_) + ", but got " +
                              std::to_string(arr.Length()) + ").")
        .ThrowAsJavaScriptException();
      return env.Null();
    }

    std::vector<float> vec(dim_, 0.0);
    for (uint32_t i = 0; i < dim_; i++) {
      Napi::Value val = arr[i];
      vec[i] = val.As<Napi::Number>().FloatValue();
    }

    const uint32_t idx = info[1].As<Napi::Number>().Uint32Value();

    try {
      index_->addPoint(reinterpret_cast<void*>(vec.data()), static_cast<hnswlib::labeltype>(idx));
    } catch (const std::runtime_error& e) {
      Napi::Error::New(env, "Hnswlib Error: " + std::string(e.what())).ThrowAsJavaScriptException();
      return env.Null();
    }

    return env.Null();
  }

  Napi::Value removePoint(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
      Napi::Error::New(env, "Expected 1 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsNumber()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a number.").ThrowAsJavaScriptException();
      return env.Null();
    }

    if (index_ == nullptr) {
      Napi::Error::New(env, "Search index has not been initialized, call `initIndex` in advance.").ThrowAsJavaScriptException();
      return env.Null();
    }

    const uint32_t idx = info[0].As<Napi::Number>().Uint32Value();

    index_->removePoint(static_cast<hnswlib::labeltype>(idx));

    return env.Null();
  }

  Napi::Value searchKnn(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 2) {
      Napi::Error::New(env, "Expected 2-3 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsArray()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be an Array.").ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[1].IsNumber()) {
      Napi::TypeError::New(env, "Invalid the second argument type, must be a number.").ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[2].IsUndefined() && !info[2].IsFunction()) {
      Napi::TypeError::New(env, "Invalid the third argument type, must be a function.").ThrowAsJavaScriptException();
      return env.Null();
    }

    if (index_ == nullptr) {
      Napi::Error::New(env, "Search index has not been initialized, call `initIndex` in advance.").ThrowAsJavaScriptException();
      return env.Null();
    }

    CustomFilterFunctor* filterFn = nullptr;
    if (info[2].IsFunction()) {
      try {
        filterFn = new CustomFilterFunctor(env, info[2].As<Napi::Function>());
      } catch (const std::bad_alloc& err) {
        Napi::Error::New(env, err.what()).ThrowAsJavaScriptException();
        return env.Null();
      }
    }

    Napi::Array arr = info[0].As<Napi::Array>();
    if (arr.Length() != dim_) {
      Napi::Error::New(env, "Invalid the given array length (expected " + std::to_string(dim_) + ", but got " +
                              std::to_string(arr.Length()) + ").")
        .ThrowAsJavaScriptException();
      return env.Null();
    }

    const uint32_t k = info[1].As<Napi::Number>().Uint32Value();
    if (k > index_->maxelements_) {
      Napi::Error::New(env, "Invalid the number of k-nearest neighbors (cannot be given a value greater than `maxElements`: " +
                              std::to_string(index_->maxelements_) + ").")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (k <= 0) {
      Napi::Error::New(env, "Invalid the number of k-nearest neighbors (must be a positive number).")
        .ThrowAsJavaScriptException();
      return env.Null();
    }

    std::vector<float> vec(dim_, 0.0);
    for (uint32_t i = 0; i < dim_; i++) {
      Napi::Value val = arr[i];
      vec[i] = val.As<Napi::Number>().FloatValue();
    }
    std::priority_queue<std::pair<float, size_t>> knn =
      index_->searchKnn(reinterpret_cast<void*>(vec.data()), static_cast<size_t>(k), filterFn);
    const size_t n_results = knn.size();
    Napi::Array arr_distances = Napi::Array::New(env, n_results);
    Napi::Array arr_neighbors = Napi::Array::New(env, n_results);
    for (int32_t i = static_cast<int32_t>(n_results) - 1; i >= 0; i--) {
      const std::pair<float, size_t>& nn = knn.top();
      arr_distances[i] = Napi::Number::New(env, nn.first);
      arr_neighbors[i] = Napi::Number::New(env, nn.second);
      knn.pop();
    }

    if (filterFn) delete filterFn;

    Napi::Object results = Napi::Object::New(env);
    results.Set("distances", arr_distances);
    results.Set("neighbors", arr_neighbors);
    return results;
  }

  Napi::Value getMaxElements(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (index_ == nullptr) return Napi::Number::New(env, 0);
    return Napi::Number::New(env, index_->maxelements_);
  }

  Napi::Value getCurrentCount(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (index_ == nullptr) return Napi::Number::New(env, 0);
    return Napi::Number::New(env, index_->cur_element_count);
  }

  Napi::Value getNumDimensions(const Napi::CallbackInfo& info) { return Napi::Number::New(info.Env(), dim_); }
};

class LoadHierarchicalNSWIndexWorker : public Napi::AsyncWorker {
public:
  LoadHierarchicalNSWIndexWorker(const std::string& filename, const bool allow_replace_deleted,
                                 hnswlib::HierarchicalNSW<float>** index, hnswlib::SpaceInterface<float>** space,
                                 Napi::Promise::Deferred deferred, Napi::Function& callback)
      : Napi::AsyncWorker(callback), deferred(deferred), filename_(filename), allow_replace_deleted_(allow_replace_deleted),
        result_(false), index_(index), space_(space) {}

  ~LoadHierarchicalNSWIndexWorker() {}

  void Execute() {
    try {
      std::ifstream ifs(filename_);
      if (ifs.is_open()) {
        ifs.close();
      } else {
        throw std::runtime_error("failed to open file: " + filename_);
      }
      if (*index_) delete *index_;
      *index_ = new hnswlib::HierarchicalNSW<float>(*space_, filename_, false, 0, allow_replace_deleted_);
      result_ = true;
    } catch (const std::exception& e) {
      result_ = false;
      SetError("Hnswlib Error: " + std::string(e.what()));
    }
  }

  void OnOK() {
    Napi::HandleScope scope(Env());
    Napi::Boolean result = Napi::Boolean::New(Env(), result_);
    deferred.Resolve(result);
  }

  void OnError(const Napi::Error& e) { deferred.Reject(e.Value()); }

  Napi::Promise::Deferred deferred;

private:
  std::string filename_;
  bool allow_replace_deleted_;
  bool result_;
  hnswlib::HierarchicalNSW<float>** index_;
  hnswlib::SpaceInterface<float>** space_;
};

class SaveHierarchicalNSWIndexWorker : public Napi::AsyncWorker {
public:
  SaveHierarchicalNSWIndexWorker(const std::string& filename, hnswlib::HierarchicalNSW<float>** index,
                                 Napi::Promise::Deferred deferred, Napi::Function& callback)
      : Napi::AsyncWorker(callback), deferred(deferred), filename_(filename), result_(false), index_(index) {}

  ~SaveHierarchicalNSWIndexWorker() {}

  void Execute() {
    try {
      if (*index_ == nullptr) throw std::runtime_error("search index is not constructed.");
      (*index_)->saveIndex(filename_);
      result_ = true;
    } catch (const std::exception& e) {
      result_ = false;
      SetError("Hnswlib Error: " + std::string(e.what()));
    }
  }

  void OnOK() {
    Napi::HandleScope scope(Env());
    Napi::Boolean result = Napi::Boolean::New(Env(), result_);
    deferred.Resolve(result);
  }

  void OnError(const Napi::Error& e) { deferred.Reject(e.Value()); }

  Napi::Promise::Deferred deferred;

private:
  std::string filename_;
  bool result_;
  hnswlib::HierarchicalNSW<float>** index_;
};

class HierarchicalNSW : public Napi::ObjectWrap<HierarchicalNSW> {
public:
  uint32_t dim_;
  hnswlib::HierarchicalNSW<float>* index_;
  hnswlib::SpaceInterface<float>* space_;

  HierarchicalNSW(const Napi::CallbackInfo& info) : Napi::ObjectWrap<HierarchicalNSW>(info), index_(nullptr), space_(nullptr) {
    Napi::Env env = info.Env();

    if (info.Length() != 2) {
      Napi::Error::New(env, "Expected 2 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return;
    }
    if (!info[0].IsString()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a string.").ThrowAsJavaScriptException();
      return;
    }
    if (!info[1].IsNumber()) {
      Napi::TypeError::New(env, "Invalid the second argument type, must be a number.").ThrowAsJavaScriptException();
      return;
    }

    const std::string space_name = info[0].As<Napi::String>().ToString();
    if (space_name != "l2" && space_name != "ip") {
      Napi::Error::New(env, "Wrong space name, expected \"l2\" or \"ip\".").ThrowAsJavaScriptException();
      return;
    }

    dim_ = info[1].As<Napi::Number>().Uint32Value();

    try {
      if (space_name == "l2") {
        space_ = new hnswlib::L2Space(static_cast<size_t>(dim_));
      } else {
        space_ = new hnswlib::InnerProductSpace(static_cast<size_t>(dim_));
      }
    } catch (const std::bad_alloc& err) {
      Napi::Error::New(env, err.what()).ThrowAsJavaScriptException();
      return;
    }
  }

  ~HierarchicalNSW() {
    if (space_) delete space_;
    if (index_) delete index_;
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // clang-format off
    Napi::Function func = DefineClass(env, "HierarchicalNSW", {
      InstanceMethod("initIndex", &HierarchicalNSW::initIndex),
      InstanceMethod("readIndex", &HierarchicalNSW::readIndex),
      InstanceMethod("readIndexSync", &HierarchicalNSW::readIndexSync),
      InstanceMethod("writeIndex", &HierarchicalNSW::writeIndex),
      InstanceMethod("writeIndexSync", &HierarchicalNSW::writeIndexSync),
      InstanceMethod("resizeIndex", &HierarchicalNSW::resizeIndex),
      InstanceMethod("addPoint", &HierarchicalNSW::addPoint),
      InstanceMethod("markDelete", &HierarchicalNSW::markDelete),
      InstanceMethod("unmarkDelete", &HierarchicalNSW::unmarkDelete),
      InstanceMethod("searchKnn", &HierarchicalNSW::searchKnn),
      InstanceMethod("getIdsList", &HierarchicalNSW::getIdsList),
      InstanceMethod("getMaxElements", &HierarchicalNSW::getMaxElements),
      InstanceMethod("getCurrentCount", &HierarchicalNSW::getCurrentCount),
      InstanceMethod("getNumDimensions", &HierarchicalNSW::getNumDimensions),
      InstanceMethod("getEf", &HierarchicalNSW::getEf),
      InstanceMethod("setEf", &HierarchicalNSW::setEf)
    });
    // clang-format on

    Napi::FunctionReference* constructor = new Napi::FunctionReference();
    *constructor = Napi::Persistent(func);
    env.SetInstanceData<Napi::FunctionReference>(constructor);

    exports.Set("HierarchicalNSW", func);
    return exports;
  }

private:
  Napi::Value initIndex(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
      Napi::Error::New(env, "Expected 1-5 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }

    const bool given_named_args = info.Length() == 1 && info[0].IsObject();
    const Napi::Object named_args = given_named_args ? info[0].As<Napi::Object>() : Napi::Object::New(env);

    if (given_named_args) {
      if (!named_args.Has("maxElements")) {
        Napi::TypeError::New(env, "Missing named argument `maxElements`, must be specified.").ThrowAsJavaScriptException();
        return env.Null();
      }
      if (!named_args.Get("maxElements").IsNumber()) {
        Napi::TypeError::New(env, "Invalid the named argument type `maxElements`, must be a number.")
          .ThrowAsJavaScriptException();
        return env.Null();
      }
      if (named_args.Has("m") && !named_args.Get("m").IsNumber()) {
        Napi::TypeError::New(env, "Invalid the named argument type `m`, must be a number.").ThrowAsJavaScriptException();
        return env.Null();
      }
      if (named_args.Has("efConstruction") && !named_args.Get("efConstruction").IsNumber()) {
        Napi::TypeError::New(env, "Invalid the named argument type `efConstruction`, must be a number.")
          .ThrowAsJavaScriptException();
        return env.Null();
      }
      if (named_args.Has("randomSeed") && !named_args.Get("randomSeed").IsNumber()) {
        Napi::TypeError::New(env, "Invalid the named argument type `randomSeed`, must be a number.")
          .ThrowAsJavaScriptException();
        return env.Null();
      }
      if (named_args.Has("allowReplaceDeleted") && !named_args.Get("allowReplaceDeleted").IsBoolean()) {
        Napi::TypeError::New(env, "Invalid the named argument type `allowRepalceDeleted`, must be a boolean.")
          .ThrowAsJavaScriptException();
        return env.Null();
      }
    } else {
      if (!info[0].IsNumber()) {
        Napi::TypeError::New(env, "Invalid the first argument type, must be a number.").ThrowAsJavaScriptException();
        return env.Null();
      }
      if (!info[1].IsUndefined() && !info[1].IsNumber()) {
        Napi::TypeError::New(env, "Invalid the sencond argument type, must be a number.").ThrowAsJavaScriptException();
        return env.Null();
      }
      if (!info[2].IsUndefined() && !info[2].IsNumber()) {
        Napi::TypeError::New(env, "Invalid the third argument type, must be a number.").ThrowAsJavaScriptException();
        return env.Null();
      }
      if (!info[3].IsUndefined() && !info[3].IsNumber()) {
        Napi::TypeError::New(env, "Invalid the fourth argument type, must be a number.").ThrowAsJavaScriptException();
        return env.Null();
      }
      if (!info[4].IsUndefined() && !info[4].IsBoolean()) {
        Napi::TypeError::New(env, "Invalid the fifth argument type, must be a boolean.").ThrowAsJavaScriptException();
        return env.Null();
      }
    }

    const uint32_t max_elements_ = given_named_args ? named_args.Get("maxElements").As<Napi::Number>().Uint32Value()
                                                    : info[0].As<Napi::Number>().Uint32Value();
    const uint32_t m_ = given_named_args ? (!named_args.Has("m") ? 16 : named_args.Get("m").As<Napi::Number>().Uint32Value())
                                         : (info[1].IsUndefined() ? 16 : info[1].As<Napi::Number>().Uint32Value());
    const uint32_t ef_construction_ =
      given_named_args
        ? (!named_args.Has("efConstruction") ? 200 : named_args.Get("efConstruction").As<Napi::Number>().Uint32Value())
        : (info[2].IsUndefined() ? 200 : info[2].As<Napi::Number>().Uint32Value());
    const uint32_t random_seed_ =
      given_named_args ? (!named_args.Has("randomSeed") ? 100 : named_args.Get("randomSeed").As<Napi::Number>().Uint32Value())
                       : (info[3].IsUndefined() ? 100 : info[3].As<Napi::Number>().Uint32Value());
    const bool allow_replace_deleted_ =
      given_named_args
        ? (!named_args.Has("allowReplaceDeleted") ? false : named_args.Get("allowReplaceDeleted").As<Napi::Boolean>().Value())
        : (info[4].IsUndefined() ? false : info[4].As<Napi::Boolean>().Value());

    if (index_) delete index_;

    try {
      index_ = new hnswlib::HierarchicalNSW<float>(space_, static_cast<size_t>(max_elements_), static_cast<size_t>(m_),
                                                   static_cast<size_t>(ef_construction_), static_cast<size_t>(random_seed_),
                                                   allow_replace_deleted_);
    } catch (const std::bad_alloc& err) {
      index_ = nullptr;
      Napi::Error::New(env, err.what()).ThrowAsJavaScriptException();
      return env.Null();
    }

    return env.Null();
  }

  Napi::Value readIndex(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
      Napi::Error::New(env, "Expected 1-2 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsString()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a string.").ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[1].IsUndefined() && !info[1].IsBoolean()) {
      Napi::TypeError::New(env, "Invalid the second argument type, must be a boolean.").ThrowAsJavaScriptException();
      return env.Null();
    }

    const std::string filename = info[0].As<Napi::String>().ToString();
    const bool allow_replace_deleted = info[1].IsUndefined() ? false : info[1].As<Napi::Boolean>().Value();
    Napi::Function callback = Napi::Function::New(env, [](const Napi::CallbackInfo& info) { return info.Env().Undefined(); });
    Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());
    LoadHierarchicalNSWIndexWorker* worker =
      new LoadHierarchicalNSWIndexWorker(filename, allow_replace_deleted, &index_, &space_, deferred, callback);

    worker->Queue();

    return worker->deferred.Promise();
  }

  Napi::Value readIndexSync(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
      Napi::Error::New(env, "Expected 1-2 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsString()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a string.").ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[1].IsUndefined() && !info[1].IsBoolean()) {
      Napi::TypeError::New(env, "Invalid the second argument type, must be a boolean.").ThrowAsJavaScriptException();
      return env.Null();
    }

    const std::string filename = info[0].As<Napi::String>().ToString();
    const bool replace_deleted = info[1].IsUndefined() ? false : info[1].As<Napi::Boolean>().Value();

    if (index_) delete index_;

    try {
      std::ifstream ifs(filename);
      if (ifs.is_open()) {
        ifs.close();
      } else {
        throw std::runtime_error("failed to open file: " + filename);
      }
      index_ = new hnswlib::HierarchicalNSW<float>(space_, filename, false, 0, replace_deleted);
    } catch (const std::runtime_error& e) {
      Napi::Error::New(env, "Hnswlib Error: " + std::string(e.what())).ThrowAsJavaScriptException();
      return env.Null();
    } catch (const std::bad_alloc& err) {
      Napi::Error::New(env, "Hnswlib Error: " + std::string(err.what())).ThrowAsJavaScriptException();
      return env.Null();
    }

    return env.Null();
  }

  Napi::Value writeIndex(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
      Napi::Error::New(env, "Expected 1 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsString()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a string.").ThrowAsJavaScriptException();
      return env.Null();
    }

    const std::string filename = info[0].As<Napi::String>().ToString();
    Napi::Function callback = Napi::Function::New(env, [](const Napi::CallbackInfo& info) { return info.Env().Undefined(); });
    Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());
    SaveHierarchicalNSWIndexWorker* worker = new SaveHierarchicalNSWIndexWorker(filename, &index_, deferred, callback);

    worker->Queue();

    return worker->deferred.Promise();
  }

  Napi::Value writeIndexSync(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
      Napi::Error::New(env, "Expected 1 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsString()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a string.").ThrowAsJavaScriptException();
      return env.Null();
    }

    const std::string filename = info[0].As<Napi::String>().ToString();

    if (index_ == nullptr) {
      Napi::Error::New(env, "Search index is not constructed.").ThrowAsJavaScriptException();
      return env.Null();
    }

    index_->saveIndex(filename);

    return env.Null();
  }

  Napi::Value resizeIndex(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
      Napi::Error::New(env, "Expected 1 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsNumber()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a number.").ThrowAsJavaScriptException();
      return env.Null();
    }

    if (index_ == nullptr) {
      Napi::Error::New(env, "Search index has not been initialized, call `initIndex` in advance.").ThrowAsJavaScriptException();
      return env.Null();
    }

    const uint32_t new_max_elements = info[0].As<Napi::Number>().Uint32Value();

    try {
      index_->resizeIndex(static_cast<size_t>(new_max_elements));
    } catch (const std::runtime_error& e) {
      Napi::Error::New(env, "Hnswlib Error: " + std::string(e.what())).ThrowAsJavaScriptException();
      return env.Null();
    } catch (const std::bad_alloc& err) {
      Napi::Error::New(env, err.what()).ThrowAsJavaScriptException();
      return env.Null();
    }

    return env.Null();
  }

  Napi::Value addPoint(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 2) {
      Napi::Error::New(env, "Expected 2-3 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsArray()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be an Array.").ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[1].IsNumber()) {
      Napi::TypeError::New(env, "Invalid the second argument type, must be a number.").ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[2].IsUndefined() && !info[2].IsBoolean()) {
      Napi::TypeError::New(env, "Invalid the third argument type, must be a boolean.").ThrowAsJavaScriptException();
      return env.Null();
    }

    if (index_ == nullptr) {
      Napi::Error::New(env, "Search index has not been initialized, call `initIndex` in advance.").ThrowAsJavaScriptException();
      return env.Null();
    }

    Napi::Array arr = info[0].As<Napi::Array>();
    if (arr.Length() != dim_) {
      Napi::Error::New(env, "Invalid the given array length (expected " + std::to_string(dim_) + ", but got " +
                              std::to_string(arr.Length()) + ").")
        .ThrowAsJavaScriptException();
      return env.Null();
    }

    std::vector<float> vec(dim_, 0.0);
    for (uint32_t i = 0; i < dim_; i++) {
      Napi::Value val = arr[i];
      vec[i] = val.As<Napi::Number>().FloatValue();
    }

    const uint32_t idx = info[1].As<Napi::Number>().Uint32Value();
    const bool replace_deleted = info[2].IsUndefined() ? false : info[2].As<Napi::Boolean>().Value();

    try {
      index_->addPoint(reinterpret_cast<void*>(vec.data()), static_cast<hnswlib::labeltype>(idx), replace_deleted);
    } catch (const std::runtime_error& e) {
      Napi::Error::New(env, "Hnswlib Error: " + std::string(e.what())).ThrowAsJavaScriptException();
      return env.Null();
    }

    return env.Null();
  }

  Napi::Value markDelete(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
      Napi::Error::New(env, "Expected 1 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsNumber()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a number.").ThrowAsJavaScriptException();
      return env.Null();
    }

    if (index_ == nullptr) {
      Napi::Error::New(env, "Search index has not been initialized, call `initIndex` in advance.").ThrowAsJavaScriptException();
      return env.Null();
    }

    const uint32_t idx = info[0].As<Napi::Number>().Uint32Value();

    try {
      index_->markDelete(static_cast<hnswlib::labeltype>(idx));
    } catch (const std::runtime_error& e) {
      Napi::Error::New(env, "Hnswlib Error: " + std::string(e.what())).ThrowAsJavaScriptException();
      return env.Null();
    }

    return env.Null();
  }

  Napi::Value unmarkDelete(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
      Napi::Error::New(env, "Expected 1 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsNumber()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a number.").ThrowAsJavaScriptException();
      return env.Null();
    }

    if (index_ == nullptr) {
      Napi::Error::New(env, "Search index has not been initialized, call `initIndex` in advance.").ThrowAsJavaScriptException();
      return env.Null();
    }

    const uint32_t idx = info[0].As<Napi::Number>().Uint32Value();

    try {
      index_->unmarkDelete(static_cast<hnswlib::labeltype>(idx));
    } catch (const std::runtime_error& e) {
      Napi::Error::New(env, "Hnswlib Error: " + std::string(e.what())).ThrowAsJavaScriptException();
      return env.Null();
    }

    return env.Null();
  }

  Napi::Value searchKnn(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 2) {
      Napi::Error::New(env, "Expected 2-3 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsArray()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be an Array.").ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[1].IsNumber()) {
      Napi::TypeError::New(env, "Invalid the second argument type, must be a number.").ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[2].IsUndefined() && !info[2].IsFunction()) {
      Napi::TypeError::New(env, "Invalid the third argument type, must be a function.").ThrowAsJavaScriptException();
      return env.Null();
    }

    if (index_ == nullptr) {
      Napi::Error::New(env, "Search index has not been initialized, call `initIndex` in advance.").ThrowAsJavaScriptException();
      return env.Null();
    }

    Napi::Array arr = info[0].As<Napi::Array>();
    if (arr.Length() != dim_) {
      Napi::Error::New(env, "Invalid the given array length (expected " + std::to_string(dim_) + ", but got " +
                              std::to_string(arr.Length()) + ").")
        .ThrowAsJavaScriptException();
      return env.Null();
    }

    CustomFilterFunctor* filterFn = nullptr;
    if (info[2].IsFunction()) {
      try {
        filterFn = new CustomFilterFunctor(env, info[2].As<Napi::Function>());
      } catch (const std::bad_alloc& err) {
        Napi::Error::New(env, err.what()).ThrowAsJavaScriptException();
        return env.Null();
      }
    }

    const uint32_t k = info[1].As<Napi::Number>().Uint32Value();
    if (k > index_->max_elements_) {
      Napi::Error::New(env, "Invalid the number of k-nearest neighbors (cannot be given a value greater than `maxElements`: " +
                              std::to_string(index_->max_elements_) + ").")
        .ThrowAsJavaScriptException();
      return env.Null();
    }

    std::vector<float> vec(dim_, 0.0);
    for (uint32_t i = 0; i < dim_; i++) {
      Napi::Value val = arr[i];
      vec[i] = val.As<Napi::Number>().FloatValue();
    }
    std::priority_queue<std::pair<float, size_t>> knn =
      index_->searchKnn(reinterpret_cast<void*>(vec.data()), static_cast<size_t>(k), filterFn);
    const size_t n_results = knn.size();
    Napi::Array arr_distances = Napi::Array::New(env, n_results);
    Napi::Array arr_neighbors = Napi::Array::New(env, n_results);
    for (int32_t i = static_cast<int32_t>(n_results) - 1; i >= 0; i--) {
      const std::pair<float, size_t>& nn = knn.top();
      arr_distances[i] = Napi::Number::New(env, nn.first);
      arr_neighbors[i] = Napi::Number::New(env, nn.second);
      knn.pop();
    }

    if (filterFn) delete filterFn;

    Napi::Object results = Napi::Object::New(env);
    results.Set("distances", arr_distances);
    results.Set("neighbors", arr_neighbors);
    return results;
  }

  Napi::Value getIdsList(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (index_ == nullptr) return Napi::Array::New(env, 0);
    uint32_t n_elements = index_->label_lookup_.size();
    Napi::Array ids = Napi::Array::New(env, n_elements);
    uint32_t counter = 0;
    for (auto kv : index_->label_lookup_) {
      ids[counter] = Napi::Number::New(env, kv.first);
      counter++;
    }
    return ids;
  }

  Napi::Value getMaxElements(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (index_ == nullptr) return Napi::Number::New(env, 0);
    return Napi::Number::New(env, index_->max_elements_);
  }

  Napi::Value getCurrentCount(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (index_ == nullptr) return Napi::Number::New(env, 0);
    return Napi::Number::New(env, index_->cur_element_count);
  }

  Napi::Value getNumDimensions(const Napi::CallbackInfo& info) { return Napi::Number::New(info.Env(), dim_); }

  Napi::Value getEf(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if (index_ == nullptr) {
      Napi::Error::New(env, "Search index has not been initialized, call `initIndex` in advance.").ThrowAsJavaScriptException();
      return env.Null();
    }
    return Napi::Number::New(env, index_->ef_);
  }

  Napi::Value setEf(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
      Napi::Error::New(env, "Expected 1 arguments, but got " + std::to_string(info.Length()) + ".")
        .ThrowAsJavaScriptException();
      return env.Null();
    }
    if (!info[0].IsNumber()) {
      Napi::TypeError::New(env, "Invalid the first argument type, must be a number.").ThrowAsJavaScriptException();
      return env.Null();
    }

    if (index_ == nullptr) {
      Napi::Error::New(env, "Search index has not been initialized, call `initIndex` in advance.").ThrowAsJavaScriptException();
      return env.Null();
    }

    const uint32_t ef = info[0].As<Napi::Number>().Uint32Value();
    index_->setEf(static_cast<size_t>(ef));

    return env.Null();
  }
};

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  L2Space::Init(env, exports);
  InnerProductSpace::Init(env, exports);
  BruteforceSearch::Init(env, exports);
  HierarchicalNSW::Init(env, exports);
  return exports;
}

NODE_API_MODULE(addon, Init)
