import urllib.parse
import base64
import json
import re
from bs4 import BeautifulSoup

from login import Login
from lesson import Lesson
from config import STUID, PASSWORD
from introduce import Introduce
from courserecord import Courserecord
from teachercourse import Teachercourse

# 登录获取cookie
login = Login(STUID, PASSWORD)
session = login.login()

#获取老师信息
intro = Introduce(session)
a = intro.get_introduce()
b = intro.get_name()
if (a):
    print(b + "，" + a[0] + "。")
else:
    print("未找到该老师的信息")



