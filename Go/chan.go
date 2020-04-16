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

func run_thread(cb Txfn) error {
    c := make(chan string, 2)

    go fill_messages(c)

    fmt.Println("In run_thread, waiting 5s")
    time.Sleep(5 * time.Second)

    fmt.Println("looking to read c")
    for val := range c {
        fmt.Println(val)
    }
    fmt.Println("all read")
    err := cb()

    return err
}

func main() {
    fmt.Println("run main()")

    txCb := func() error {
        rt.PrintStack()
        fmt.Println("in callback func()")
        return nil
    }

    go run_thread(txCb)

    fmt.Println("Continuing main()...")

    fmt.Println("Waiting for 10 seconds")
    time.Sleep(10 * time.Second)
}
