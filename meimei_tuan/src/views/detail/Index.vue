<template>
  <div class="my-wrapper">
    <div class="my-content">
      <Head :element="obj"></Head>
      <van-tabs
        v-model="active"
        animated
        color="#fbb000"
        sticky
        font-weight="bolder"
        line-width="20px"
        line-height="2px"
      >
        <van-tab :title="'点餐'">
          <Oder></Oder>
        </van-tab>
        <van-tab :title="'评论'">
          <Comments></Comments>
        </van-tab>
        <van-tab :title="'商家'">
          <Store></Store>
        </van-tab>
      </van-tabs>
    </div>
    <!-- 购物车 -->
    <cart v-if="active == 0" :element="obj"></cart>
  </div>
  <!-- 有两个问题
        1《显示不了
        2.怎么传参让不同的商家显示不同的信息
     -->
</template>

<script>
import Head from "./Head";
import Oder from "./Oder";
import Comments from "@/views/comment/Index.vue";
import Store from "./Store";
import BetterScroll from "better-scroll";
import Cart from './Cart.vue';
import axios from 'axios';
export default {
  data() {
    return {
      active: 0,
      obj:[]
    };
  },
  components: {
    Head,
    Oder,
    Comments,
    Store,
    Cart
  },
  mounted() {
    setTimeout(() => {
      let bs = new BetterScroll(".my-wrapper", {
        // movable: true,
        // zoom: true
         bounce:false,
        click: true,
      });
    },1000);
  },
  created(){
    axios.get('http://admin.gxxmglzx.com/tender/test/get_store_id?id='+this.$route.query.id)
    .then((res)=>{
      console.log("hahha");
      // console.log(res.data.data);
      this.obj=res.data.data;
    })
    .catch((error)=>{
      console.log(error);
    })
  }
};
</script>

<style lang="scss" scoped>
.my-wrapper {
  height: 100vh;
 
}
</style>