package main

import "C"

//export Hello
func Hello () *C.char {
  return C.CString("Hello World")
}

// required to build
func main () {}
