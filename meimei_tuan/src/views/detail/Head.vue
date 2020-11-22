<template>
    <div class="container">
        <div class="top-box">
            <div class="box-msg" @click="$router.go(-1)">
                &lt;
            </div>
        </div>
        <div class="header-box">
            <img :src="element.img">
            <div class="store-info">
                <div class="info-1">
                    <span class='info-1-left'>{{element.minute}}分钟</span>|<span class='info-1-right'>{{element.distance}}km</span>
                </div>
                <div class="info-2">
                    公告：{{element.notice}}
                </div>
                <div class="info-3">
                    <span class="info-3-msg">{{element.full}}</span>
                    <span class="info-3-right">&gt;</span>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
    export default {
        props:["element"]
    }
</script>

<style lang="scss" scoped>
.top-box{
    height: 1rem;
    background-color: rgb(46, 47, 59);
    display: flex;
    line-height: 1rem;;
    .box-msg{
        margin-left: 10px;
        color: rgb(255, 255, 255);
        width: 0.8rem;
        height: 1rem;
        font-size: 20px;
    }
}
.header-box{
    height: 1.6rem;
    background-color: rgb(46, 47, 59);
    padding-top:0.1rem;
    box-sizing: border-box;
    display: flex;
    img{
        width: 1.7rem;
        height: 1.28rem;
        padding:0 0.2rem;
     }
     .store-info{
         flex: 1;
         width: 0;
         color: #ffffff;
         font-size: 12px;
         .info-1{
             font-family: mtsi-font;
             height: 20px;
            .info-1-left{
                padding-right: 5px;
            }
             .info-1-right{
                padding-left: 5px;
            }

         }
         .info-2{
             height:16px;
             line-height: 16px;
             font-size: 12px "PingFangSC-Regular", Hiragino Sans GB, Arial, Helvetica, "\5B8B\4F53", sans-serif;
             overflow: hidden;
             text-overflow: ellipsis;
             white-space: nowrap;
             padding: 5px 0;
         }
         .info-3{
             height: 14.67px;
             line-height: 14.67px;
             .info-3-msg{
                display: inline-block;
                width: 80%;
                overflow: hidden;
                text-overflow: ellipsis;
                white-space: nowrap;
             }
             .info-3-right{
                 float: right;
                 padding-right:10px;
                 font-size: 16px;
             }
         }
     }

}
</style>