import scrapy
from reptile.items import ReptileItem


class SpidersSpider(scrapy.Spider):
    name = 'spiders'
    allowed_domains = ['hongloumeng.5000yan.com']
    start_urls = ['http://hongloumeng.5000yan.com/']

    def parse(self, response):
        li_list = response.xpath('//div[@class="sidamingzhu-list-mulu"]/ul/li')
        all_data = []
        for li in li_list:
            title = li.xpath('./a/text()')[0].extract()
            url = li.xpath('./a//@href')[0].get()
            item = ReptileItem()
            item['title'] = title.replace(u'\xa0', '') + '\n'
            item['url'] = url
            yield scrapy.Request(url=url, meta={'item': item}, callback=self.parse_detail)

    def parse_detail(self, response):
        item = response.meta['item']
        content=''
        div_list = response.xpath('//div[@class="grap"]/div')
        for div in div_list:
            content+=div.xpath('./text()')[0].extract().strip()+'\n'
        item['content']=content.replace(u'\xa0', '')+'\n'
        print(item['title'].strip()+' 已完成')
        yield item

