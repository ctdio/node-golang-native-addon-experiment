package main

import "C"

//export Hello
func Hello () *C.char {
  return C.CString("Hello world!")
}

// required to build
func main () {}
