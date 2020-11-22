<template>
  <div>
    <h2>我是首页</h2>

    <!-- 配置子路由
      1.先link 写路径
      2.占位
      3.进行配置
     -->
      <!-- 接收参数 -->
    <!-- {{$route.query.id}} -->

    <!-- {{$route.params.name}} -->
    <!-- {{name}} -->
    <router-link to="/home/a">A</router-link>
    <router-link to="/home/b">B</router-link>

    <router-view></router-view>
    {{$store.state.count}}

    <!-- module模板 -->
    {{$store.state.a.list}}
    <ul>
      <li v-for=" (obj,index) in $store.state.b.proList" :key="index">{{obj.name}}</li>
    </ul>
    <button @click="$store.commit('b/addList')">add</button>

  </div>
</template>

<script>
import axios from 'axios'
export default {
  data(){
   return{
      name:this.$route.params.name
   }
  },
  created(){
    this.$store.dispatch('getMovieList')  
  }
}
</script>

<style lang="scss" scoped>
// scoped 表示css的作用域，默认值只在这个组件中显示，其他组件不好使
    h2{
        background: red;
    }
</style>
