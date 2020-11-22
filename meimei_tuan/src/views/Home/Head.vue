<template>
    <div class="header">
        <input type="text" placeholder="请输入商家或者商品名称">
    </div>
</template>

<script>
    export default {
        
    }
</script>

<style lang="scss" scoped>
.header{
    // width: 100%;
    // height: 1rem;
    background: black;
    padding: 0.2rem 0;
    text-align: center;
    // 用padding串垂直居中，加padding有盒模型的影响，有一种解决方案是直接求掉高度，让元素直接撑开它
    input{
        width: 90%;
        height: 0.6rem;
        border:none;
        border-radius: 15px; //按照高度来
        text-indent: 20px;
    }
}
</style>