from pyquery import PyQuery as pq
from collections import deque
import urllib2
import re
import csv

urls = deque([
    "http://www.cs.tsinghua.edu.cn/publish/csen/4922/index.html",
    "http://www.eecs.mit.edu/people/faculty-advisors",
    "https://cs.stanford.edu/directory/faculty",
    "https://www2.eecs.berkeley.edu/Faculty/Lists/faculty.html",
    "https://www.cs.cmu.edu/directory/all",
])

searched_urls = set()


class Teacher:
    def __init__(self, name, university, link):
        self.name = name
        self.university = university
        self.link = link

teachers = []
names = set()

while urls:
    url = urls.popleft()
    searched_urls.add(url)
    try:
        d = pq(url=url)
    except urllib2.HTTPError:
        continue
    d.make_links_absolute()
    if re.search(r"tsinghua", url):
        for a in d("a"):
            link = pq(a).attr("href")
            text = pq(a).html()
            if link:
                if re.match(r"^http://www.cs.tsinghua.edu.cn/publish/csen/[0-9]{4}/index.html$", link) or\
                    (re.match(r"^http://www.cs.tsinghua.edu.cn/publish/csen/[0-9]{4}/[0-9]{4}/[0-9]+/[0-9]+_.html$", link) and\
                         re.search(r"List", text)):
                    if link not in urls and link not in searched_urls:
                        urls.append(link)
                elif re.match(r"^http://www.cs.tsinghua.edu.cn/publish/csen/[0-9]{4}/[0-9]{4}/[0-9]+/[0-9]+_.html$", link)\
                        and re.match(r"^[a-zA-Z]{1,10} [a-zA-Z]{1,10}$", text):
                    if text not in names:
                        names.add(text)
                        teachers.append(Teacher(text, "Tsinghua", link))
    elif re.search(r"mit", url):
        for span in d("span.field-content.card-title"):
            a = pq(span)("a:first")
            link = pq(a).attr("href")
            text = pq(a).html()
            if text:
                text = text.strip("</br>")
            if link and text:
                if text not in names:
                    names.add(text)
                    teachers.append(Teacher(text, "MIT", link))
    elif re.search(r"stanford", url):
        for tr in d("tr.odd, tr.even"):
            td = pq(tr)("td:first")
            a = pq(td)("a:first")
            link = pq(a).attr("href")
            text = pq(a).html()
            if link and text:
                if text not in names:
                    names.add(text)
                    teachers.append(Teacher(text, "Stanford", link))
    elif re.search(r"berkeley", url):
        for h3 in d("h3.media-heading"):
            a = pq(h3)("a:first")
            link = pq(a).attr("href")
            text = pq(a).html()
            if link and text:
                if text not in names:
                    names.add(text)
                    teachers.append(Teacher(text, "Berkeley", link))
    elif re.search(r"cmu", url):
        for a in d("a"):
            title = pq(a).attr("title")
            if title and re.match(r"^Go to", title):
                link = pq(a).attr("href")
                if link not in urls and link not in searched_urls:
                    urls.append(link)
        for tr in d("tr.odd, tr.even"):
            td_lastName = pq(tr)("td:first")
            td_firstName = pq(tr)("td:nth-child(2)")
            firstName = pq(td_firstName).html().strip()
            a = pq(td_lastName)("a:first")
            lastName = pq(a).html().strip()
            link = pq(a).attr("href")
            name = ' '.join((firstName, lastName))
            if name not in names:
                names.add(name)
                teachers.append(Teacher(name, "CMU", link))

with open("result.csv", "wb") as csvFile:
    writer = csv.writer(csvFile)
    for teacher in teachers:
        writer.writerow([teacher.name.encode("utf-8"), teacher.university, teacher.link])
