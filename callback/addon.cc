#include <node.h>
#include <nan.h>
#include <iostream>
#include "lib/libgo.h"
#include "lib/types.h"

using v8::Local;
using v8::Object;
using v8::Value;
using v8::String;
using v8::Number;
using v8::Isolate;
using Nan::Maybe;
using Nan::Callback;
using Nan::AsyncWorker;
using Nan::AsyncQueueWorker;
using Nan::FunctionCallbackInfo;

class MyWorker : public AsyncWorker {
public:
  // constructor
  MyWorker (GoArgs args, Callback *callback) :
    AsyncWorker(callback),
    args(args) {}

  // destructor
  ~MyWorker () {
    delete callback;
    callback = 0;
  }

  void Execute () {
    result = doSomething(args);
  }

  void HandleOKCallback () {
    Local<Object> res = Nan::New<Object>();

    Nan::Set(res, Nan::New<String>("num").ToLocalChecked(), Nan::New<Number>(result.num));

    Local<Value> callbackRes[] = {
      Nan::Null(),
      res
    };
    callback->Call(2, callbackRes);
  }
private:
  GoArgs args;
  GoArgs result;
};

void DoSomethingAsync (const FunctionCallbackInfo<Value> &info) {
  Local<Object> obj = info[0]->ToObject();
  Callback *callback = new Callback(info[1].As<v8::Function>());

  Local<Value> value = Nan::Get(obj, Nan::New<String>("num").ToLocalChecked()).ToLocalChecked();

  if (!value->IsNumber()) {
    // if nothing, invoke callback with error
    Local<Value> err = Nan::Error("A number value for 'num' must be supplied");
    Local<Value> callbackRes[] = { err };
    callback->Call(1, callbackRes);
  } else {
    // otherwise perform work
    GoArgs args;
    args.num = value->NumberValue();
    std::cout << args.num << " is the value\n";
    AsyncQueueWorker(new MyWorker(args, callback));
  }
}

void Init (Local<Object> exports) {
  Nan::SetMethod(exports, "doSomethingAsync", DoSomethingAsync);
}

NODE_MODULE(asyncModule, Init)
