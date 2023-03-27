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

#查询课程评分
teacherpoint = Teachercourse(session)
a = teacherpoint.get_higest()
c = re.search("/course/", a)
if c:
    b = teacherpoint.get_teach()
    if b == -1:
        print("您所找的教师暂未教授该学科")
    else:
        if b > 8:
            print("该教师这门课评分为%.1f,评分良好" % b)
        elif b > 5:
            print("该教师这门课评分为%.1f,褒贬不一" % b)
        elif b > 0:
            print("该教师这门课评分为%.1f,建议换课" % b)
        else:
            print("该课程暂无评分")
else:
    print("未找到该教师")
