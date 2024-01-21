<template>
    <word-page id="user-manager">
        <h1 class="header">表单制作的基本套路</h1>
        <p>
            每个表单必定对应一个数据库查询。每个表单正常来说都会拥有以下功能：
        <ol>
            <li>1. 一个添加按钮，但如果这个实体是由系统自动维护的，则没有此按钮。比如日志功能；</li>
            <li>2. 一个筛选器，可以是一个文本框加一个筛选按钮，也可以是一组筛选；</li>
            <li>3. 一个table表示的表格，在表格里有操作字段，用以修改和删除功能；</li>
            <li>4. 一个分页。</li>
        </ol>
        </p>
        <p>
            筛选器一般而言都会拥有 page和pageSize 两个字段，用以分页。
        </p>
        <p>
            对应的后台接口一般而言至少有以下内容：
        <ol>
            <li>1. 一个获取列表的接口 getXXXs；</li>
            <li>2. 一个保存内容的接口 saveXXX。在这个接口里需要区别修改和新建两种方法；</li>
            <li>3. 一个获取单个实体的接口 getXXX；</li>
            <li>4. 一个用以删除实体的接口 removeXXX。</li>
        </ol>
        </p>
        <div class="sample">
            <a-row>
                <a-space>
                    <a-button type="primary">新增</a-button>
                    <a-divider type="vertical" />
                    <a-input v-model:value="name"></a-input>
                    <a-button type="primary" @click="loadPage">搜索</a-button>
                </a-space>
            </a-row>
            <a-table class="data-table" :columns="columns" :data-source="data" :pagination="pagination">
                <template #bodyCell="{ column, text, record }">
                    <template v-if="column.key === 'operation'">
                        <a-space>
                            <a href="javascript:;">[编辑]</a>
                            <a href="javascript:;">[删除]</a>
                        </a-space>
                    </template>
                </template>
            </a-table>
        </div>
    </word-page>
</template>

<script setup>
import { axios } from '@/axios';
import ensureLogin from '@v/login/ensureLogin';
import { ref, reactive, computed } from 'vue';

let currentUser = await ensureLogin();

let page = ref(1), pageSize = ref(10), totalRows = ref(1);
let name = ref("");

async function loadPage() {
    let searcher = {
        page: page.value,
        pageSize: pageSize.value,
        name: name.value
    }

    // console.log(searcher);
    let msg = await axios.post("/api/user/GetUsers", searcher);
    console.log(msg);
    data.value = msg.data;
    page.value = msg.page;
    pageSize.value = msg.pageSize;
    totalRows.value = msg.totalRows;
}
loadPage();

let columns = [
    {
        title: "姓名", // 显示在界面上的标签
        dataIndex: "userName", // 在data里的索引
    },
    {
        title: "密码", // 显示在界面上的标签
        dataIndex: "password", // 在data里的索引
    },
    {
        title: "头像", // 显示在界面上的标签
        dataIndex: "avatar", // 在data里的索引
    },
    {
        title: "操作",
        key: 'operation'
    }
];
let data = ref([]);
const pagination = computed(() => ({
    total: totalRows.value,
    current: page.value,
    pageSize: pageSize.value,
}));
</script>

<style lang="less">
@import "@/assets/word-like.less";
@import "@/assets/paper.less";

#user-manager {
    width: 1000px;
    margin: 60px auto;

    .page-div {
        padding: 60px 10px;
    }

    .sample {
        background: #fff;
        padding: 10px;

        .data-table {
            margin-bottom: 10px;
            td {
                border: none;
            }
        }
    }
}
</style>
