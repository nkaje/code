package main
import "fmt"
import "time"
import "container/list"
import "sync"

type Txfn func() error

func run_thread() error {

    fmt.Println("processing done ")

    return nil
}

func main() {
    queue := list.New()
    var mutex = &sync.Mutex{}
    const sample = "abcdefghij"

    var sem = make(chan int, 5)
    fmt.Println("run main()")

    for i:= 0; i<10; i++ {
        fmt.Printf("queue %c\n", sample[i])
        queue.PushBack(sample[i])
        sem <- 1
        go func(queue *list.List) {
           mutex.Lock()
           if (queue.Len() > 0) {
                e := queue.Front()
                queue.Remove(e)
                fmt.Printf("dequeue %c %c\n", e.Value, ch_v)
           }
           mutex.Unlock()
           run_thread()
            <-sem
        } (queue)
    }

    fmt.Println("Waiting for 10 seconds")
    time.Sleep(10 * time.Second)
}
