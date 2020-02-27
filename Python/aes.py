import base64
import hashlib
from Crypto import Random
from Crypto.Cipher import AES

import sys
import os
import struct
import click

from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import ed25519

# Add in path to mcuboot.  This is required to pull in keys module from imgtool
sys.path.append(os.path.join(os.getcwd(), "repos", "mcuboot", "scripts", "imgtool"))
import keys as keys

def get_key(filename):
    # base64 encoded
    with open(filename, "rb") as f:
        kdata = f.read()
        kdata = base64.decodestring(kdata)
    return kdata

def dump_data(data, fname):
    with open(fname, "wb") as f:
        f.write(data)

@click.option("-i", "--inp", required=True, help="Input file")
@click.option("-e", "--encfile", required=True, help="Encrypted file")
@click.option("-d", "--decfile", required=True, help="Decrypted file")
@click.option("-k", "--key", required=True, help="Key file")
@click.command(help="encrypt/decrypt with keys")
def encrypt_decrypt(inp, encfile, decfile, key):
    data = "Hello World!!!!!"
    backend = default_backend()
    kdata = get_key(key)

    print(inp)
    print(decfile)
    print(encfile)

    print("Data: ", data, len(data))
    print("Key data:", kdata, len(kdata))
    ctr = 0 #0x10c00
    iv = bytes(12) + ctr.to_bytes(4, byteorder='big')
    print("iv", iv)
    cipher = Cipher(algorithms.AES(kdata), modes.CTR(iv), backend=backend)
    enc = cipher.encryptor()
    ctext = enc.update(data.encode())
    print(ctext)
    ctext = ctext + enc.finalize()
    print(ctext)
    dump_data(ctext, encfile)

    decryptor = cipher.decryptor()
    dtext = decryptor.update(ctext) + decryptor.finalize()
    dump_data(dtext, decfile)


@click.group()
def cli():
    pass

if __name__ == "__main__":
    encrypt_decrypt()

