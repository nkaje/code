import base64
import hashlib
from Crypto import Random
from Crypto.Cipher import AES

import sys
import os
import struct

from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import ed25519

# Add in path to mcuboot.  This is required to pull in keys module from imgtool
sys.path.append(os.path.join(os.getcwd(), "repos", "mcuboot", "scripts", "imgtool"))
import keys as keys

def get_key():
    # base64 encoded
    infile = "./sample_key_file"
    with open(infile, "rb") as f:
        kdata = f.read()
        kdata = base64.decodestring(kdata)
    return kdata

def dump_data(data, fname):
    with open(fname, "wb") as f:
        f.write(data)

def encrypt_decrypt():
    data = "One One Four Two"
    backend = default_backend()
    kdata = get_key()

    print("Data: ", data, len(data))
    print("Key data:", kdata, len(kdata))
    print(kdata)
    print(len(kdata))
    dump_data(kdata, "./keydata")
    # set the ctr here
    ctr = 0x10c00
    iv = bytes(12) + ctr.to_bytes(4, byteorder='big')
    print(iv)
    cipher = Cipher(algorithms.AES(kdata), modes.CTR(iv), backend=backend)
    enc = cipher.encryptor()
    ctext = enc.update(data.encode())
    print(ctext)
    ctext = ctext + enc.finalize()
    print(ctext)
    dump_data(ctext, "./cipher_file")

    decryptor = cipher.decryptor()
    dtext = decryptor.update(ctext) + decryptor.finalize()
    print(dtext)
    dump_data(dtext, "./dec_plaintext.txt")

if __name__ == "__main__":
    encrypt_decrypt()

