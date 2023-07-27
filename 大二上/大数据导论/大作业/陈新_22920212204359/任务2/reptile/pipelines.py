# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# useful for handling different item types with a single interface
from itemadapter import ItemAdapter


class ReptilePipeline:
    fp1 = None
    fp2 = None

    def open_spider(self, spider):
        print('************开始爬虫程序***********')
        self.fp1 = open('./1.txt', 'w', encoding='utf-8')
        self.fp2 = open('./2.txt', 'w', encoding='utf-8')

    def process_item(self, item, spider):
        title = item['title']
        content=item['content']
        self.fp1.write(title)
        self.fp2.write(title)
        self.fp2.write(content)

        return item

    def close_spider(self, spider):
        print('**********爬虫结束*****************')
        self.fp1.close()
        self.fp2.close()
