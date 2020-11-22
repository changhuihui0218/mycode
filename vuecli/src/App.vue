<template>
  <div id="app">
    <!-- <Home></Home>
    <test></test> -->

    <!-- 路由传参
        1.query传参
        2.params传参
        3.路由路径传参
     -->
    <!-- <router-link to="/home">首页</router-link> -->

    <!-- <router-link :to="{path:'/home',query:{id:6666}}">首页</router-link> -->
    <!-- <router-link :to="{name:'myHome',params:{name:'zs'}}">首页</router-link> -->

    <router-link to="/home">首页</router-link>
    <router-link to="/test/3">测试页</router-link>
    |
    <router-link :to="{path:'/test3',query:{name:'zs'}}">Test3</router-link>
    <!-- 配置别名 -->
    <router-link to="/aa">test_alias</router-link>
    <!-- 重定向 -->
     <router-link to='/4'>/</router-link>
     <!-- 路由过渡动画 -->
     <transition name='fade'>
       <router-view></router-view>
     </transition>
     <!-- 编程方式导航 -->
     <button @click="goHome()">click-home</button>
    <button @click="goTest()">click-test</button>
    <button @click="goTest1()">click-test1</button>
    <button @click="goBack()">&lt;</button>

  </div>
</template>

<script>
  import Test from './views/Test'
  import Home from './views/Home'
  export default {
    components:{
      Test,
      Home
    },
    methods:{
      //编程式导航 路由参数
      goHome(){
        this.$router.push('/home')
      },
      goTest(){
        this.$router.push('/test/5')
      },
      goTest1(){
        this.$router.push({path:'/test3',query:{name:'zs'}})
      },
      goBack(){
        this.$router.go(-1)
      }
    }
  }
</script>>
<style lang="scss">
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}

#nav {
  padding: 30px;

  a {
    font-weight: bold;
    color: #2c3e50;

    &.router-link-exact-active {
      color: #42b983;
    }
  }
}
// 动画
.fade-enter{
  opacity: 0;  
}
.fade-enter-active{
  transition: opacity 2s ease;
}
.fade-enter-to{
  opacity: 1;
}
.fade-leave{
  transform: translateX(0);
}
.fade-leave-active{
  transition: transform 2s ease;
}
.fade-leave-to{
  transform: translateX(100%);
}

</style>
