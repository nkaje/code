#!/usr/bin/env python3
import base64
import struct
import click


def decode(filename):
    contents = bytes()

    try:
        with open(filename, "rb") as f:
            contents = f.read()
    except FileNotFoundError as e:
        raise SystemExit("File Not Found")

    dec = base64.decodestring(contents)
    return dec


@click.option("-i", "--inp", required=True, help="Input file")
@click.option("-o", "--outp", required=True, help="Output path, file will be creaed")
@click.command(help="read and decode a base64 encodede file")
def decbase64(inp, outp):
    dec = decode(inp)
    try:
        with open(outp, mode="wb") as f:
            f.write(dec)
    except IOError as e:
        raise SystemExit("Unable to write to %s" % outp)


@click.group()
def cli():
    pass


cli.add_command(decbase64)


if __name__ == "__main__":
    cli()
