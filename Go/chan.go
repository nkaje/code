package main
import "fmt"
import "time"
import rt "runtime/debug"

type Txfn func() error

func fill_messages(c chan string) {
    for i := 0;  i <= 3; i++ {
        if (i == 0) {
            c <- "buffered"
        }  else if (i == 1) {
            c <- "channel"
        } else {
            c <- "done"
        }

    }
    close(c)
}

func run_thread(cb Txfn, i int) error {
    c := make(chan string, 2)

    go fill_messages(c)

    fmt.Println("In run_thread, waiting 5s", i)
    time.Sleep(5 * time.Second)

    fmt.Println("looking to read c", i)
    for val := range c {
        fmt.Println(val)
    }
    fmt.Println("all read", i)
    err := cb()

    return err
}

func main() {
    var sem = make(chan int, 5)
    fmt.Println("run main()")

    txCb := func() error {
        rt.PrintStack()
        fmt.Println("in callback func()")
        return nil
    }

    for i:= 0; i<10; i++ {
        sem <- 1
        go func(i int) {
            run_thread(txCb, i)
            <-sem
        } (i)
    }

    fmt.Println("Continuing main()...")

    fmt.Println("Waiting for 10 seconds")
    time.Sleep(10 * time.Second)
}
