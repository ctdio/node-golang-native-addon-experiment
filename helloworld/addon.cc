#include <node.h>
#include "lib/libgo.h"

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void HelloMethod  (const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();
  char *c = Hello();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, c));
  // this pointer MUST be explictly freed
  delete c;
}

void Init (Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", HelloMethod);
}

NODE_MODULE(myGoAddon, Init)
