import urllib.parse
import base64
import json
import re
from bs4 import BeautifulSoup


class Introduce:
    def __init__(self, session):
        self.session = session
        print("")
        print("请输入老师姓名,二字名字中间用空格隔开")
        self.teacher_name =  input()
        self.header = {
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.51 Safari/537.36"
        }

    def get_page(self):
        ss = urllib.parse.quote(self.teacher_name)
        self.session.get("http://cs.ustc.edu.cn", headers=self.header)
        self.session.post("http://cs.ustc.edu.cn/_web/search/doSearch.do?locale=zh_CN&request_locale=zh_CN&_p=YXM9NTYmdD0yMTYzJmQ9MTM0MzkmcD0xJm09U04m&keyword={}".format(ss), headers=self.header)

        header = {
            "Referer": "http://cs.ustc.edu.cn/_web/search/doSearch.do?locale=zh_CN&request_locale=zh_CN&_p=YXM9NTYmdD0yMTYzJmQ9MTM0MzkmcD0xJm09U04m&keyword={}".format(
                ss),
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.51 Safari/537.36"
        }

        t = '[{"field":"pageIndex","value":1},{"field":"group","value":0},{"field":"searchType","value":"1"},{"field":"keyword","value":"' + self.teacher_name + '"},{"field":"recommend","value":"1"},{"field":4,"value":""},{"field":5,"value":""},{"field":6,"value":""},{"field":7,"value":""},{"field":8,"value":""},{"field":9,"value":""},{"field":10,"value":""}]'
        t = base64.b64encode(t.encode('utf-8'))

        j = json.loads((self.session.post("http://cs.ustc.edu.cn/_web/search/packageCons.do?_p=YXM9NTYmdD0yMTYzJmQ9MTM0MzkmcD0xJm09U04m&tt=0.2615115796874672&searchInfo={}".format(t.decode()), headers=header).content.decode('utf-8')))

        soup = BeautifulSoup(j["data"], "html.parser")

        aa = soup.find_all("a")
        result = [_.get("href") for _ in aa]
        return result

    def get_introduce(self):
        tin = self.get_page()

        if (tin):
            sn = re.findall(r'，(.*?)。</', self.session.get(tin[0], headers=self.header).content.decode('utf-8'))
            countain = re.search('宋体',sn[0])
            if (countain):
                return 0
            else:
                return sn
        else:
            return 0

    def get_name(self):
        return self.teacher_name