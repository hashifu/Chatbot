import re
import urllib.parse
import requests
import urllib.error
from bs4 import BeautifulSoup

class Search:
    def __init__(self,s):
        self.header = {
            'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.51 Safari/537.36'
        }
        self.word = s
    def search_inter(self):
        ss = urllib.parse.quote(self.word)
        rsp2 = requests.get("http://cn.bing.com/search?q={}".format(ss), headers=self.header)
        j2 = rsp2.content.decode("utf-8")

        soup = BeautifulSoup(j2, "html.parser")
        td = soup.find_all("h2")
        #print("")
        #print("虽然我听不懂，但你可能想找这些：")
        s2 = ""

        for t in td:
            pattern = re.compile(r'href="([^"]*)"')
            h = re.search(pattern, str(t))
            if h:
                if "http" in str(h):
                    print("")
                    print(t.get_text())
                    for x in h.groups():
                        print(x)
                        s2 = s2 + x + ','

        return s2