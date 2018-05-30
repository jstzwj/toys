import sys
import os
import base64
import re
import tkinter
import tkinter.filedialog
from pyDes import *

global list_files

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

def center_window(root, width, height):  
    screenwidth = root.winfo_screenwidth()  
    screenheight = root.winfo_screenheight()  
    size = '%dx%d+%d+%d' % (width, height, (screenwidth - width)/2, (screenheight - height)/2)  
    print(size)
    root.geometry(size) 

def onGetAnswer():
    cur_idx = list_files.curselection()
    if len(cur_idx) != 0:
        each_path = list_files.get(cur_idx[0])
        matchObj = re.match(r'.*\\([a-zA-Z0-9]*)\\mooctest\\[a-zA-Z0-9+]*=', each_path)
        if matchObj:
            print('Decryting "%s"...' % matchObj.group(1))
            out_name = tkinter.filedialog.asksaveasfilename(title='Save As', filetypes=[('TXT', '*.txt'), ('All Files', '*')])
            if not out_name.endswith(".txt"):
                out_name += ".txt"
            if out_name != '':
                read_and_write(each_path, out_name, True)
            

root = tkinter.Tk()
center_window(root, 300, 240)
list_files = tkinter.Listbox(root, selectmode = tkinter.BROWSE)
tkinter.Button(root, text='get answer', command=onGetAnswer).pack(fill=tkinter.X)
path_list = search_all_file("C:\\mooctest\\projects\\")
for item in path_list:
    list_files.insert(0,item)

list_files.pack(fill=tkinter.X)
root.mainloop()


