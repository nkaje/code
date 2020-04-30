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
        sem <- 1

        mutex.Lock()
        fmt.Printf("queue %c, length of queue %d\n", sample[i], len(sem))
        queue.PushBack(sample[i])
        mutex.Unlock()

        go func(queue *list.List) {
           mutex.Lock()
           if (queue.Len() > 0) {
                e := queue.Front()
                queue.Remove(e)
                fmt.Printf("dequeue %c length of queue %d\n", e.Value, len(sem)-1)
           }
           mutex.Unlock()
           run_thread()
            <-sem
        } (queue)
    }

    fmt.Println("Waiting for 10 seconds")
    time.Sleep(10 * time.Second)
}
