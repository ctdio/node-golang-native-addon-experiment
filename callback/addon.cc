#include <node.h>
#include <nan.h>
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
  MyWorker (GoArgs *args, Callback *callback) :
    AsyncWorker(callback),
    args(args) {}

  // destructor
  ~MyWorker () {}

  void Execute () {
    result = doSomething(*args);
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
  GoArgs *args;
  GoArgs result;
};

void DoSomethingAsync (const FunctionCallbackInfo<Value> &info) {
  Local<Object> obj = info[0]->ToObject();
  Callback *callback = new Callback(info[1].As<v8::Function>());

  auto value = Nan::Get(obj, Nan::New<String>("num").ToLocalChecked()).ToLocalChecked();
  Maybe<double> dVal = Nan::To<double>(value);

  if (dVal.IsNothing()) {
    // if nothing, invoke callback with error
    Local<Value> err = Nan::Error("Value for 'num' must be supplied");
    Local<Value> callbackRes[] = { err };
    callback->Call(1, callbackRes);
  } else {
    // otherwise perform work
    GoArgs *args = new GoArgs();
    args->num = dVal.FromJust();
    AsyncQueueWorker(new MyWorker(args, callback));
  }
}

void Init (Local<Object> exports) {
  Nan::SetMethod(exports, "doSomethingAsync", DoSomethingAsync);
}

NODE_MODULE(asyncModule, Init)
