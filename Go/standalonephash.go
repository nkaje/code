package main
import (
    "fmt"
    "crypto/hmac"
    "crypto/sha256"
    "encoding/hex"
    "hash"
)

// from crypto/tls/prf.go
// pHash implements the P_hash function, as defined in RFC 4346, section 5.
func pHash(result, secret, seed []byte, hash func() hash.Hash) {
	h := hmac.New(hash, secret)
	h.Write(seed)
	a := h.Sum(nil)

	j := 0
	for j < len(result) {
		h.Reset()
		h.Write(a)
		h.Write(seed)
		b := h.Sum(nil)
		todo := len(b)
		if j+todo > len(result) {
			todo = len(result) - j
		}
		copy(result[j:j+todo], b)
		j += todo

		h.Reset()
		h.Write(a)
		a = h.Sum(nil)
	}
}

func encode_str(str []byte) {
   enc := make([]byte, hex.EncodedLen(len(str)))
   hex.Encode(enc, str)
   fmt.Printf("%s\n", str)
   fmt.Printf("%s\n", enc)
}

func main() {
   /* The following set of inputs can come from a long int (Bytes() vs FillBytes()) */
   s := "de7cf220ae0475870236061c75e0ca84d5759fbf479b243fe94a972bf103ba"
   ss := "00de7cf220ae0475870236061c75e0ca84d5759fbf479b243fe94a972bf103ba"
   seed := []byte("gwkey")
   result := make([]byte, 32)

   secret, _ := hex.DecodeString(s)
   fmt.Printf("%s", hex.Dump(seed))
   fmt.Printf("%s", hex.Dump(secret))

   pHash(result, secret, seed, sha256.New)
   fmt.Printf("\nwithout leading zeros, result\n %s", hex.Dump(result))

   secret2, _ := hex.DecodeString(ss)
   pHash(result, secret2, seed, sha256.New)
   fmt.Printf("\nwith leading zeros, result\n %s", hex.Dump(result))
}
