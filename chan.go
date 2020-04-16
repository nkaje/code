package main
import "fmt"
import "time"

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

func run_thread() error {
    c := make(chan string, 2)

    go fill_messages(c)

    fmt.Println("looking to read c")
    for val := range c {
        fmt.Println(val)
    }
    fmt.Println("all read")

    return nil
}

func main() {

    fmt.Println("run run_thread")

    err := run_thread()
    if err != nil {
        fmt.Println("Error")
    } else {
        fmt.Println("no Error")
    }

    fmt.Println("Waiting for 15 seconds")
    time.Sleep(15 * time.Second)
}
