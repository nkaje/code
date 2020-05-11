package main

import (
	"fmt"
)

func main() {
	ch := make(chan int, 4)

	go func() {
		for i := 0; i < 4; i++ {
			ch <- i
		}
		close(ch)
	}()

	for {
		_, ok := <-ch
		if ok {
			fmt.Println("read")
		} else {
			fmt.Println("all read")
			break
		}
	}
}

