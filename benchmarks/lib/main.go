package main

import "C"
import "time"
import "fmt"

func getTimestamp () int64 {
  return (time.Now().UnixNano() / int64(time.Millisecond))
}

//export Add
func Add (a, b float64) float64 {
  return a + b
}

//export Increment
func Increment () int {
  start := getTimestamp()
  v := 0

  for i := 0; i < 2147483600; i++ {
    v = i
  }

  fmt.Printf("go: Time in ms to complete loop %v ms\n", getTimestamp() - start)
  return v
}

func main () {}
