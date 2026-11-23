#
#   @ Author:       Eric / Sky__White
#   @ Filename:     [ABC446A].py
#   @ Time:         02/21/2026
#   @ Email:        acwing@foxmail.com
#

s = input()

s = "Of" + chr(ord(s[0]) + 32) + s[1:]

print(s)