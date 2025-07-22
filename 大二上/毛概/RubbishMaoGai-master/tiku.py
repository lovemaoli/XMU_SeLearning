"""
题库生成
Author: F5
Date: 2020-05-12
"""

import matplotlib.pyplot as plt
import os
import sys
import html

if len(sys.argv) != 2:
    print("Usage: python tiku.py [my|mg|sg]")
    exit(0)

course = sys.argv[1]
data_path = "samples_" + course
tiku_path = "tiku_" + course + ".html"


prepend = '''
<head>
    <title>题库</title>
    <meta charset="utf-8">
</head>
<body>
<div>全文搜索时，由于标点符号全半角、空格数量不匹配等问题，不建议复制整个标题搜索，可能会找不到结果！建议仅搜索题目标题的连续文字内容。</div>
<h5>GitHub仓库地址：<a href="https://github.com/F5Soft/RubbishMaoGai">https://github.com/F5Soft/RubbishMaoGai</a>。</h5>
<h5>如果题库使用体验不错，欢迎star!</h5>
<hr>
'''


def unescape(raw: str):
    """
    转换十进制Unicode表示的字符
    """
    ans = raw.strip()
    ans = html.unescape(ans)
    ans = html.unescape(ans)
    ans = ans.replace("<p>", '')
    ans = ans.replace("</p>", '')
    ans = ans.replace("<br>", '')
    ans = ans.replace(' ', '')
    ans = ans.lstrip('>')
    return ans


tiku = open(tiku_path, 'wt', encoding="utf8", errors="replace")
tiku.write(prepend)

questions = set()
question_count = 0
question_count_list = []
total_count = 0
total_count_list = []

for dirname in os.listdir(data_path):
    for filename in os.listdir(os.path.join(data_path, dirname)):
        if "_files" in filename:
            continue

        filename = os.path.join(data_path, dirname, filename)
        f = open(filename, 'rt', encoding='GBK')
        in_context = False
        in_answer_context = False

        for line in f.readlines():
            # 题目标题
            if "_content" in line:
                total_count += 1
                low = line.find('value=') + 7
                high = line.find('><iframe') - 1
                title = unescape(line[low:high])

                if title not in questions:
                    in_context = True
                    questions.add(title)
                    question_count += 1
                    tiku.write("<h3>" + str(question_count) +
                               ". " + title + "</h3>")

                question_count_list.append(question_count)
                total_count_list.append(total_count)

            # 题目选项
            if in_context and "answer" in line and "sogoutip" not in line:
                low = line.find('answer') + 8
                tiku.write("<div>" + unescape(line[low:]) + "</div>")

            # 题目答案区域结束
            if in_answer_context and "</td>" in line:
                in_context = False
                in_answer_context = False
                tiku.write("</div>")

            # 题目答案选项内容（有多选情况）
            if in_answer_context:
                tiku.write("<div>" + unescape(line) + "</div>")

            # 题目答案区域开始
            if in_context and "[参考答案]" in line:
                in_answer_context = True
                tiku.write("<h5>参考答案</h5><div>")
        f.close()

tiku.close()
print("去重后:", question_count)
print("总计:", total_count)

# 预测题库题目数量
plt.plot(total_count_list, question_count_list)
plt.show()
