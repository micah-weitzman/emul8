#!/usr/bin/python2 
import binascii
import codecs

# (OP 1) '6001 6102 1200'#
# (OP 2)
# (OP 3) '6011 3011 1200 6196 3103 1200'
# (OP 4) '6012 4011 1200 6105 4105 1200'
# (OP 5) 
hx = '6245 6445 5240 1200 624F 5240 1200'

# (OP 6) '6001 6102 6203 6304 6405 6506 6607 6708 6809 690A 6A0B 6B0C 6C0D 6D0E 6E0F 6F10'
# (OP 7) '7055 7155 1200'
# (OP 8)
# (OP 9) '6011 6112 9010 1200 6012 9010 1200 61FF'
# (OP A) 'A202 A302 AFFF'
# (OP B) '7002 B200'
# (OP C) 'C012 1200'

new_str = codecs.decode(hx.replace(" ", ""), 'hex')

output_file = open("TEST", "wb")
output_file.write(new_str)

output_file.close()
