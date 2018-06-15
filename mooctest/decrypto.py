import sys
import os
import base64
import re
from pyDes import *

def decode(str):
    k = des(b"witest.n", ECB, b"\0\0\0\0\0\0\0\0", pad=None, padmode=PAD_PKCS5)
    decode_str = base64.b64decode(str)
    out_str = k.decrypt(decode_str)
    return out_str.decode("utf-8")

def read_and_write(in_file, out_file, is_code=False):
    f_in = open(in_file)
    f_out = open(out_file, "w")
    for line in f_in:
        l = line.strip()
        l = decode(l)
        matchIDObj = re.match(r'([a-z.]+:id/[a-zA-Z0-9_]+)\*[a-zA-Z]+Activity', l)
        matchXPathObj = re.match(r'(//android\.widget\.[a-zA-Z0-9_]+\[@text=\'.*\'\])\*[a-zA-Z]+Activity', l)
        if matchIDObj and is_code:
            f_out.write("driver.findElementById(\""+matchIDObj.group(1)+"\").click();\r\n")
        elif matchXPathObj and is_code:
            f_out.write("driver.findElementByXPath(\""+ matchXPathObj.group(1) +"\").click();\r\n")
        else:
            f_out.write(l+"\r\n")
    f_in.close()
    f_out.close()

def search_all_file(path):
    retval = []
    for filename in os.listdir(path):
        deeper_dir = os.path.join(path, filename)
        if os.path.isfile(deeper_dir):
            matchObj = re.match(r'.*\\([a-zA-Z0-9]*)\\mooctest\\[a-zA-Z0-9+]*=', deeper_dir)
            if matchObj:
                print('find file "%s"' % deeper_dir)
                retval.append(deeper_dir)
        if os.path.isdir(deeper_dir):
            retval += search_all_file(deeper_dir)
    return retval

if len(sys.argv) <= 1:
    in_file = "in.txt"
    out_file = "out.txt"
    list = search_all_file("C:\\mooctest\\projects\\")
    name = input("Please intput project name:")

    for each_path in list:
        matchObj = re.match(r'.*\\([a-zA-Z0-9]*)\\mooctest\\[a-zA-Z0-9+]*=', each_path)
        if matchObj and matchObj.group(1) == name.strip():
            print('Decryting "%s"...' % name.strip())
            out_name = input("Please type output file name:")
            is_code = input("Generate code(Y/N):")
            if is_code=="Y" or is_code == "y":
                read_and_write(each_path, out_name, True)
            else:
                read_and_write(each_path, out_name, False)
            

elif len(sys.argv) == 2:
    in_file = sys.argv[1]
    out_file = "out.txt"
    read_and_write(in_file, out_file)
elif len(sys.argv) == 3:
    in_file = sys.argv[1]
    out_file = sys.argv[2]
    read_and_write(in_file, out_file)
else:
    print("TOO MUCH ARGUEMENTS!")

