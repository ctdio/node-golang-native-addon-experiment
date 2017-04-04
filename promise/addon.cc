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
using v8::Promise;
using Nan::Maybe;
using Nan::Callback;
using Nan::AsyncWorker;
using Nan::AsyncQueueWorker;
using Nan::Persistent;
using Nan::FunctionCallbackInfo;

// TODO: move away from async worker that needs a callback arg
class MyWorker : public AsyncWorker {
public:
  // constructor
  MyWorker (GoArgs args, Persistent<Promise::Resolver> *persistentResolver, Callback *callback) :
    AsyncWorker(callback),
    args(args),
    persistentResolver(persistentResolver) {}

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

    // resolve promise
    auto resolver = Nan::New(*persistentResolver);
    resolver->Resolve(res);

    // delete persisted resolver
    persistentResolver->Reset();
    delete persistentResolver;
  }
private:
  GoArgs args;
  GoArgs result;
  Persistent<Promise::Resolver> *persistentResolver;
};

void DoSomethingAsync (const FunctionCallbackInfo<Value> &info) {
  Local<Object> obj = info[0]->ToObject();
  Local<Value> value = Nan::Get(obj, Nan::New<String>("num").ToLocalChecked()).ToLocalChecked();
  auto resolver = Promise::Resolver::New(info.GetIsolate());
  auto persistientResolver = new Persistent<Promise::Resolver>(resolver);
  auto promise = resolver->GetPromise();

  if (!value->IsNumber()) {
    // if nothing, invoke callback with error
    Local<Value> err = Nan::Error("A number value for 'num' must be supplied");
    resolver->Reject(err);
  } else {
    // otherwise perform work
    GoArgs args;
    args.num = value->NumberValue();
    std::cout << args.num << " is the value\n";
    AsyncQueueWorker(new MyWorker(args, persistientResolver, 0));
  }

  // return the promise
  info.GetReturnValue().Set(promise);
}

void Init (Local<Object> exports) {
  Nan::SetMethod(exports, "doSomethingAsync", DoSomethingAsync);
}

NODE_MODULE(asyncModule, Init)
