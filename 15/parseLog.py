#!/usr/bin/env python3
# -*-coding:gb2312-*-
import re
import os
from collections import OrderedDict
from copy import copy
from decimal import Decimal


def loginfos(filename):
    fn = open(filename, 'r', encoding="gb2312", errors="ignore")
    list = fn.readlines()
    flist = str.split(filename, '/')
    return flist.pop(), list


'''
'NOTICE: 05-31 20:00:00:  ztcadapter * 40869 search_id=00091638b611a864 cp=nuomi_train_category pn=2 psuid=0 BD=A5CF8985C0284CF9BAF8EEC9A8F0927B|0 cn=SE_ztcnuomijson_v27171a7 uip=211.97.128.77 gps=13149013.420000_2795776.950000_0_194_1527768000612 err=0 ads=0 ft=1 sdx=3 all=(47508 250 [47084,0,20,4,0,1,3] [47154,0,11,41,24,47021,25] 0) up_ip=10.205.144.26 asp_ip= tm=(47508 47084 47154) rt_ip=10.194.165.50 lost=0 '
'''

filter = r'.*cp=ztc_wise_daoliu_vtype.*ads=([\d]+).*tm=\(([\d\s]+)\).*';
filterlog = r'.*(logid:5555).*'


def paseLinst(logname, lines):
    size = len(lines)
    if size == 0:
        print(logname + "\tis null")
    size = 0
    allnum = 0
    alltime = 0
    for line in lines:
        if line is None:
            continue
        fret = re.search(filterlog, line)
        if fret is not None:
            continue
        searchRet = re.search(filter, line)
        if searchRet is None:
            # print(line)
            list = None
        else:
            list = searchRet.groups()
        if list is None:
            continue
        else:
            size = size + 1
            allnum = allnum + int(list[0])
            times = re.split(r'\s', list[1])
            alltime = alltime + int(times[0])
    return allnum, alltime, size


def listdir(path):
    pathdirs = []
    if os.path.isdir(path):
        dirs = os.listdir(path)
        for name in dirs:
            pathname = path + "/" + name
            if os.path.isdir(pathname):
                pathdirs = pathdirs + listdir(pathname)
            else:
                pathdirs.append(pathname)
    else:
        pathdirs.append(path)
    return pathdirs


dirs = listdir('C:/Users/qinhan/Desktop/diff')
# dirs = [dirs[0], dirs[1], dirs.pop(), dirs.pop()]
filenum = "文件数量"
reqnum = "有效请求数量"
ads = "广告数量"
perads = "平均广告数/请求"
reqtime = "有效请求时长"
pertime = "平均时间/请求"
A = OrderedDict([
    (filenum, 0),
    (reqnum, 0),
    (ads, 0),
    (perads, 0),
    (reqtime, 0),
    (pertime, 0),
])
result = OrderedDict()
for file in dirs:
    ret = loginfos(file)
    logname = ret[0]
    list = ret[1]
    lineinfo = paseLinst(logname, list)
    num = lineinfo[0]
    time = lineinfo[1]
    size = lineinfo[2]
    # ztcadapter.log.201806031130
    date = logname[15:23]
    if date in result:
        pass
    else:
        result[date] = copy(A)
    result[date][filenum] = result[date][filenum] + 1
    result[date][reqnum] = result[date][reqnum] + size
    result[date][ads] = result[date][ads] + num
    result[date][reqtime] = result[date][reqtime] + time

keys = A.keys()
keystr = "日期\t\t" + "\t\t".join(keys) + '\r\n'
restr = keystr
for key, retLine in result.items():
    if retLine[reqnum] > 0:
        retLine[perads] = round(Decimal(retLine[ads] / retLine[reqnum]), 4)
        retLine[pertime] = round(Decimal(retLine[reqtime] / retLine[reqnum]), 4)
    retLineVal = retLine.values()
    valstr = "\t\t".join([str(v) for v in retLineVal])
    restr = restr + key + "\t\t" + valstr + '\r\n'

file = './ab.text'
fn = open(file, 'w')
ret = fn.write(restr)
if ret:
    print("success")
else:
    print("fail")
