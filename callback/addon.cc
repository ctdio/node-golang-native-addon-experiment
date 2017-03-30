#include <node.h>
#include <nan.h>

using v8::Local;
using v8::Object;
using v8::Value;
using Nan::Callback;
using Nan::AsyncWorker;
using Nan::AsyncQueueWorker;
using Nan::FunctionCallbackInfo;

class MyWorker : public AsyncWorker {
public:
  // constructor
  MyWorker (Callback *callback) : AsyncWorker(callback) {}
  // destructor
  ~MyWorker () {}

  void Execute () {
    printf("%s\n", "Hello world");
  }
};

void DoSomethingAsync (const FunctionCallbackInfo<Value> &info) {
  // NOTE: info is something exposed by the macro
  Callback *callback = new Callback(info[0].As<v8::Function>());
  AsyncQueueWorker(new MyWorker(callback));
}

void Init (Local<Object> exports) {
  Nan::SetMethod(exports, "doSomethingAsync", DoSomethingAsync);
}

NODE_MODULE(asyncModule, Init)
