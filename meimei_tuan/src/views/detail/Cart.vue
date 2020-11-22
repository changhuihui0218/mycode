<template>
<!-- 1.cart单独领出来写
    2.请求在主页面中请求，在子组件中只需要传参数即可。

    3.在Vue中当通过索引修改数组中的值得时候 不能直接改，在页面中不好使
    但是vue中自己修改了，但是页面中不修改
    需要通过set来修改Vue.set(修改那哪个数组，索引值，修改的值)
 -->
    <div class="cart">
      <div :class="{'cart-img':true,'active':$store.getters.total>0}" >
          <div :class="{'total':$store.getters.total>0}" v-if="$store.getters.total>0">{{$store.getters.total}}</div>
      </div>
      <div :class="{'cart-sum':true,'active':$store.getters.total==0}">
          <span class="default" v-if="$store.getters.total==0">另需配送费¥{{element.fee}}元</span>
          总价¥{{$store.getters.sumTotal}}
       </div>
      <div :class="{'cart-computer':true,'active':$store.getters.sumTotal>0}" v-if="$store.getters.total==0">¥{{element.price}}起送</div>
       <div :class="{'cart-computer':true,'active':$store.getters.sumTotal>0}" v-if="$store.getters.total>0">去结算</div>
    </div>
</template>

<script>
    export default {
        props:["element"],
        
    }
</script>

<style lang="scss" scoped>
 .cart{
        width: 320px;
        height: 50px;
        position: fixed;
        bottom: 0;
        left: 0;
        background: #3b3b3c;
        display: flex;
        .cart-img{
            background: url(//s3plus.meituan.net/v1/mss_e2821d7f0cfe4ac1bf9202ecf9590e67/cdn-prod/file:9096d347/c6896f9806bdcb2399cb680fb5dec8c0.png);
            height: 50pxx;
            width: 50px;
            border-radius: 50%;
            background-size: 100% 100%;
            box-sizing: border-box;
            padding:0 10px;
            position: relative;
            bottom: 10px;
            left: 10px;
          &.active{
            background: url(//s3plus.meituan.net/v1/mss_e2821d7f0cfe4ac1bf9202ecf9590e67/cdn-prod/file:9096d347/03098cb323a0263fdbbb102c696433c5.png);
            height: 50pxx;
            width: 50px;
            border-radius: 50%;
            background-size: 100% 100%;
            box-sizing: border-box;
            padding:0 10px;
            position: relative;
            bottom: 10px;
            left: 10px;
          }
          .total{
              width: 15px;
              height: 15px;
              background: red;
              border-radius: 50%;
              position: absolute;
              right: 0;
              top: 0;
              color: #fff;
              font-size: 12px;
              line-height: 15px;
              text-align: center;
          }
        }
        .cart-sum{
          flex:3;
          font-family: Hiragino Sans GB, Arial, Helvetica, "宋体", sans-serif;
          font-size: 20px;
          color: #fff;
          margin-left: 20px;
          height: 50px;
          text-align: center;
          line-height: 50px;
          .default{
                flex:3;
                font-family: "PingFangSC-Regular", Hiragino Sans GB, Arial, Helvetica, "宋体", sans-serif;
                font-size: 16px;
                color: #999;
                margin-left: 20px;
                height: 50px;
                text-align: center;
                line-height: 50px;
          }
        }
        .cart-computer{
          flex:1.5;
          height: 50px;
          text-align: center;
          line-height: 50px;
          font-family: "PingFangSC-Regular", Hiragino Sans GB, Arial, Helvetica, "宋体", sans-serif;
          font-size: 16px;
          color: #999;
          box-sizing: border-box;
          padding: 0 18px;
          &.active{
              background: #f8c74e;
              color: #333;
              font-family: Hiragino Sans GB, Arial, Helvetica, "宋体", sans-serif;
          }
        }
    }

</style>