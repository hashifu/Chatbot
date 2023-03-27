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

# 获取教师邮箱
lesson = Lesson(session)
email_list = lesson.find_all()
parms = lesson.find_parms()
print(email_list[0])
print(parms[0])
