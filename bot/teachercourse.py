import urllib.parse
import re
from bs4 import BeautifulSoup


class Teachercourse:
    def __init__(self, session):
        self.session = session
        print(" ")
        print("请输入课程名字")
        self.classname = input()
        self.header = {
            'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.51 Safari/537.36'
        }
        print(" ")
        print("请输入教师姓名")
        self.teachername = input()

    def get_higest(self):
        ss = urllib.parse.quote(self.teachername)
        self.session.get("https://icourse.club/", headers=self.header)
        self.session.post("https://icourse.club/search/?q={}".format(ss), headers=self.header)

        header = {
            "Referer": "https://icourse.club/search/?q={}".format(ss),
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.51 Safari/537.36"
        }

        rsp = self.session.get("https://icourse.club/search/?q={}".format(ss), headers=header)

        j = rsp.content.decode("utf-8")

        soup = BeautifulSoup(j, "html.parser")
        aa = soup.find_all("a")
        result = [_.get("href") for _ in aa]
        if result:
            return result[12]
        else:
            return 0

    def get_teach(self):
        ss = urllib.parse.quote(self.teachername)
        gt = self.get_higest()
        header = {
            "Referer": "https://icourse.club/search/?q={}".format(ss),
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.51 Safari/537.36"
        }
        rsp2 = self.session.get("https://icourse.club{}".format(gt), headers=header)

        j2 = rsp2.content.decode("utf-8")

        soup = BeautifulSoup(j2, "html.parser")
        aa = soup.find_all("a")
        result = [_.get("href") for _ in aa]

        for i in result:
            result2 = re.search("/teacher/", str(i))
            if result2:
                tectag = i
                break
            else:
                continue

        sn = re.findall(r'class="px16\"(.*?)</a>', self.session.get("https://icourse.club{}".format(tectag), headers=header).content.decode('utf-8'))
        sn2 = re.findall(r'class="rl-pd-sm h4\">(.*?)</span>', self.session.get("https://icourse.club{}".format(tectag), headers=header).content.decode('utf-8'))
        a = 0
        for i in sn:
            result3 = re.search(self.classname, str(i))
            if result3:
                result4 = re.search("暂无评价", sn2[a])
                if result4:
                    return 0
                else:
                    return float(sn2[a])
            else:
                a = a + 1
                continue

        return -1