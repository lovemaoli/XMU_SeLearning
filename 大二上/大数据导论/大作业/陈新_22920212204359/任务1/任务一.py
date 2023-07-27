import requests
from bs4 import BeautifulSoup

headers = {
    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.'
                  '0.0.0 Safari/537.36 Edg/108.0.1462.42'
}
fp1 = open('./1.txt', 'w', encoding='utf-8')
fp2 = open('./2.txt', 'w', encoding='utf-8')


def request_page(url):
    page = requests.get(url=url, headers=headers)
    page.encoding = 'utf-8'
    return page.text


def parse_page(page):
    soup = BeautifulSoup(page, 'lxml')
    data_list = soup.select('.sidamingzhu-list-mulu>ul>li')
    for data in data_list:
        title = data.a.string
        title_url = data.a['href']
        yw_page = yw_page_requests(title_url)
        yw_page_parse(yw_page, title)
        print(title)
        fp1.write(title.replace(u'\xa0', '') + '\n')


def yw_page_requests(url):
    yw_page = requests.get(url=url, headers=headers)
    yw_page.encoding = yw_page.apparent_encoding
    return yw_page.text


def yw_page_parse(page, title):
    fp2.write(title + '\n')
    soup2 = BeautifulSoup(page, 'lxml')
    content = soup2.find('div', class_='grap')
    cons = content.find_all('div')
    text = ''
    for con in cons:
        text += con.text.replace(u'\xa0', '').strip()
    fp2.write(text)
    fp2.write('\n\n')  # 分隔用


if __name__ == '__main__':
    print('************开始爬虫程序***********')
    url = 'https://hongloumeng.5000yan.com/'
    page = request_page(url)
    parse_page(page)
    print('**********爬虫结束*****************')
