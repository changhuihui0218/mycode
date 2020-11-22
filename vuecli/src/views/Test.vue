<template>
    <div>
        <h2>我是测试页</h2>
        {{$route.params.id}}
    </div>
</template>

<script>
    export default {
        
    }
</script>

<style lang="scss" scoped>
// scoped 表示css的作用域，默认值只在这个组件中显示，其他组件不好使
    h2{
        background: blue;
    }
</style>