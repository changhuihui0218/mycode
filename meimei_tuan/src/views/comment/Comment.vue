<template>
<!-- 问题：
1.为什么会出现星星在前面的情况；
2.星星和文字怎么调水平对齐的情况
 -->
    <div class="comment-box">
           <div class="comment-info-1">
               <div class="info-1-num">{{obj.score}}</div>
               <div class="info-1-msg">商家评价</div>   
           </div>
           <div class="comment-info-2">
               <div class="info-first">
                   <span class="info-2">口味</span>
                   <!-- <div style="display:inline-block"> -->
                    <Star :num='parseFloat(obj.flavor)'></Star>
                    <!-- </div>     -->
                   <span class="info-score">{{obj.flavor}}</span>
               </div>
               <div>
                   <span class="info-2">包装</span>
                   <Star :num='parseFloat(obj.packing)'></Star>
                   <span class="info-score">{{obj.packing}}</span>
               </div>
           </div>
           <div class="comment-info-3">
               <div  class="info-1-num">{{obj.delivery}}</div>
               <div class="info-1-msg">配送评分</div>
           </div>
    </div>
</template>

<script>
    import Star from '../../components/Star'
    import axios from 'axios'
    export default {
        components:{
            Star
        },
        props:["obj"]
    }
</script>

<style lang="scss" scoped>
    .comment-box{
        height: 1.4rem;
        // box-sizing: content-box;
        display: flex;
        padding-top: 0.3rem;
        // margin-bottom: 0.2rem;
        .comment-info-1,.comment-info-3{
            text-align: center;
            width: 1.728rem;
            height: 1rem;
             .info-1-msg{
                font-size: 0.24rem;
                color: #999;
            }
        }
        .comment-info-1{
            .info-1-num{
                color: #FFB000;
                font-size: 0.54rem;
            }
        }
        .comment-info-2{
            height: 1rem;
            flex:1;
            .info-score{
                font-size: 0.28rem;
                color: #FFB000;
            }
            .info-first{
                display:inline-block;
                margin: 0.06rem 0 0.2rem;
            }
            .info-2,.info-3{
                font-size: 0.26rem;
                margin-right: 0.3rem;
                color: #666;
            }
        }
        .comment-info-3{
            border-left: 0.02rem solid #e4e4e4;;
             .info-1-num{
                color: #999;
                font-size: 0.54rem;
            }
        }
    }

</style>