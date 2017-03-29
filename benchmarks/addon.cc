#include <node.h>
#include <iostream>
#include <chrono>
#include "lib/libgo.h"

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Number;
using v8::Value;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;
using std::cout;

bool validateArgs (Isolate *isolate, const FunctionCallbackInfo<Value> &args) {
  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    return false;
  }
  return true;
}

void CppAdd(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();
  bool valid = validateArgs(isolate, args);
  if (!valid) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong args")));
    return;
  }

  double sum = args[0]->NumberValue() + args[1]->NumberValue();
  Local<Number> value = Number::New(isolate, sum);
  args.GetReturnValue().Set(value);
}

void GoAdd(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();
  bool valid = validateArgs(isolate, args);
  if (!valid) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong args")));
    return;
  }

  GoFloat64 sum = Add(args[0]->NumberValue(), args[1]->NumberValue());
  Local<Number> value = Number::New(isolate, sum);
  args.GetReturnValue().Set(value);
}

void CppIncrement(const FunctionCallbackInfo<Value> &args) {

  Isolate *isolate = args.GetIsolate();
  high_resolution_clock::time_point start = high_resolution_clock::now();

  int value = 0;

  for (int i = 0; i < 2147483600; i++) {
    value = i;
  }

  high_resolution_clock::time_point end = high_resolution_clock::now();

  auto diff = duration_cast<milliseconds>(end - start);

  cout << "cpp: Time in ms to complete loop " << diff.count() << "ms\n";

  args.GetReturnValue().Set(Number::New(isolate, value));
}

void GoIncrement(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();

  args.GetReturnValue().Set(Number::New(isolate, Increment()));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "cppAdd", CppAdd);
  NODE_SET_METHOD(exports, "goAdd", GoAdd);
  NODE_SET_METHOD(exports, "cppIncrement", CppIncrement);
  NODE_SET_METHOD(exports, "goIncrement", GoIncrement);
}

NODE_MODULE(addon, init)
