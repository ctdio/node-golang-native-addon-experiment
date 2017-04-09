# Promise example

This another example that shows how Go can be used to perform the bulk of whatever operation
you plan on performing needs to be performed asynchronously.

In this example, we use `cgo` to share a struct between Go and C++. The struct's definition is
located in `lib/types.h` We can use `cgo`'s preamble feature to include the header file and
get access to the data type.

The majority of the plumbing needs to still be done in C++ land, this time with the help of
[Nan](https://github.com/nodejs/nan). However once the input can be coerced into something
simple enough to pass to Go, we can simply call the exported Go function to perform the more
complex work.

### Todo:
- Add more details about how this all works
