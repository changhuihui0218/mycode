<template>
    <div>
重定向
{{$route.params.id}}
    </div>
</template>

<script>
    export default {
        data(){
           return{
                id:this.$route.params.id
           }
        }
    }
</script>

<style lang="scss" scoped>

</style>