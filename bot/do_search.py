import urllib.parse
import base64
import json
import re
from bs4 import BeautifulSoup

from searchinternet import Search

def my_search(s):
      a = Search(s)
      s = a.search_inter()
      return s


