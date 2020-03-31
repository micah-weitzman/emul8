#!/bin/pyton 
import binascii

hx = '60126112621263121200'

new_str = hx.decode("hex")

output_file = open("TEST", "wb")
output_file.write(new_str)

output_file.close()
