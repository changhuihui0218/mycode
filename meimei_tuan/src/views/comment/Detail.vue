<template>
<!-- 为什么会报错？
    1.key---obj.
    2.使用索引怎么用
 -->
 <!-- 
     type是干嘛的参数 ----用来标记标签不同
     为什么没有图片呢？
  -->
    <div class="detail-box">
        <div class="detail-label">
            <ul class="label-box">
                <!-- 可以不用list循环，直接span v-for也可以 -->
                <li v-for="obj in data.label" :key="obj.id">
                    <span :class="{active:obj.id ==typeId }" @click="change(obj.id)" class="label-list">{{obj.name}}({{obj.count}})</span>
                </li>
            </ul>
        </div>
        <div class="comment-box">
            <ul>
                <li class="info-box" v-for="obj in data.rate" :key="obj.id">
                    <img  class="info-img" :src="obj.portrait">
                    <div class="info-msg">
                        <div class="info-1">
                            <span class="info-1-name">{{obj.name}}</span>
                            <span class="info-1-time">{{obj.time}}</span>
                        </div>
                        <div class="info-2">{{obj.duration}}分钟送达</div>
                        <div class="info-3">{{obj.content}}</div>
                    </div>
                </li>
            </ul>
        </div>
    </div>
</template>

<script>
    import axios from 'axios'
    export default {
        props:["data"],
        data(){
            return{
                typeId:1
            }
        },
        methods:{
            change(typeId){
                this.$emit('changeType',typeId);
                this.typeId=typeId;
            }
        }
    }
</script>

<style lang="scss" scoped>
 .detail-box{
     border-top:10px solid #eee;
     .label-box{
         display: flex;
         flex-wrap: wrap;
     }
     .detail-label{
        // height: 128px;
        padding: 15px 14px 5px;
        .label-list{
            display: inline-block;
            height: 26px;
            padding: 0 12px;
            border:1px solid #bbb;
            border-radius: 26px;
            line-height: 27px;
            margin: 0 10px 10px 0;
            font-size: 13px;
            color: #666;
            text-align: center;
            // &退回上一级
            &.active{
                border-color: #ffb000 ;
                background: #fffbf1;
                color: #FFB000;

             }
        }
    }
 }
 .comment-box{
     padding: 15px;
     border-top:1px solid #eee;
     .info-box{
        display: flex;
        padding-bottom:15px;;
        .info-img{
            height: 40px;
            width: 40px;
            border-radius: 50%;
        }
        .info-msg{
            margin-left: 5px;
            .info-1{
                height: 15.33px;
                .info-1-name{
                    line-height: 15px;
                    color: #2f2f2f;
                    font-size: 16px;
                    font-family: "PingFangSC-Regular", Hiragino Sans GB, Arial, Helvetica, "\5B8B\4F53", sans-serif;
                }
                .info-1-time{
                    font-size: 12px;
                    color: #898989;
                    float: right;
                }
            }
            .info-2{
                margin-top: 10px;
                height: 12.67px;
                color: #666;
                font-size: 12px;
                line-height: 12px;

            }
            .info-3{
                font-size: 14px;
                line-height: 20px;
                color: #2f2f2f;
                padding-top: 14px;
                padding-bottom: 8px;    
            }
        }
    }
 }

</style>