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
        fmt.Println("in func()")
        return nil
    }

    err := run_thread(txCb)
    if err != nil {
        fmt.Println("Error")
    } else {
        fmt.Println("no Error")
    }

    fmt.Println("Continuing main()...")

    fmt.Println("Waiting for 30 seconds")
    time.Sleep(15 * time.Second)
}
