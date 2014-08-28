import os
lst = [['lucy','25','beijing'],['lilei','32','hongkong'],['hanmeimei','9','sichuan'],['tom','13','shanghai']]

lst.sort(key=lambda i:str(i[2]))
print lst