package main

import (
    "os"
    "net"
    "log"
    "time"
    "io"
)

func main() {
    l, err := net.Listen("tcp", "localhost:4242")
    if err != nil {
        log.Fatal(err)
    }

    for {
        conn, err := l.Accept()
        if err != nil {
            log.Fatal(err)
        }

        go proxy(conn)
   }
}

func proxy(conn net.Conn) {
    defer conn.Close()

    remote, err := net.Dial("tcp", "localhost:80")
    if err != nil {
        log.Println(err)
        return
    }

    defer remote.Close()

    go io.Copy(remote, conn)
    io.Copy(conn, remote)
}

func copyToStderr(conn net.Conn) {
    defer conn.Close()
    for {
        conn.SetReadDeadline(time.Now().Add(5 * time.Second))
        var buf [128]byte
        n, err := conn.Read(buf[:])
        if err != nil {
            log.Printf("Finished with err %v", err)
            return
        }
        os.Stderr.Write(buf[:n])
    }
}

