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

#获取课程最高评分
coursepoint = Courserecord(session)
a = coursepoint.get_higest()
if a:
    c = coursepoint.get_higestcourse()
    if c:
        d = re.search("暂无评价", c)
        if d:
            print("您所选课程均暂无评价")
        else:
            b = coursepoint.get_teach()
            print("所选学科最高评分为" + c)
            print("授课教师为" + b)
    else:
        print("未找到您所选的学科")
else:
    print("未找到您所选的学科")


