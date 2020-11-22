<template>
    <div>
       <div>

       </div>
       <div>
           <ul class="store-list-box">
                <li class="store-list clearfix" v-for=" obj in List" :key="obj.id"
                 @click="$router.push({path:'/detail',query:{id:obj.id}})"
                 >
                    <img :src="obj.img" alt="">
                    <div class="store-info">
                        <h2>{{obj.name}}</h2> 
                        <div class="store-info1 clearfix">
                            <Star :num="parseFloat(obj.score)"></Star>
                            <div class="info2-left">
                                <span>{{obj.score}}</span>
                                <span class="sale">月售{{obj.num}}</span>
                            </div>
                            <div class="info2-right">
                                 <span class="info2-1">{{obj.minute}}分钟</span>
                                 <span class="info2-2">{{obj.distance}}</span>
                            </div>
                        </div>
                        <div class="store-info2">起送￥{{obj.price}}</div>
                    </div>
                </li>
            </ul>
            <img src="@/assets/image/loading1.gif" class="loading" v-show="isShow" alt="">
       </div>
    </div>
</template>

<script>
    import axios from 'axios'
    import Star from './../../components/Star'
    export default {
        components:{
            Star
        },
        data(){
            return{
                List:[],
                pageNum:0,
                isShow:false,
                isFinish:false
            }
        },
        methods:{
            getData(){
                 axios.get('http://admin.gxxmglzx.com/tender/test/get_store?current='+this.pageNum+'&size=10')
                .then((res)=>{
                    // console.log(res.data.data);
                    if(res.data.errcode==200){
                        // this.List=res.data.data.list
                        this.List=[...this.List,...res.data.data.list]
                        this.pageNum++;
                        this.isShow=false;
                        if(res.data.data.total==this.List.length){
                            this.isFinish=true;
                        }
                    }
                }).catch((err)=>{
                    console.log(err);
                })
                }
        },
        created(){
            this.getData();
            this.isShow=true;
            // <!-- 判断滚动条滚动的高度+可视区的高度 =整个页面的高度 -->

            window.onscroll=()=>{
                let scollerTop=document.documentElement.scrollTop;  //获取滚动条上滑的高度
                let clientHeight=document.documentElement.clientHeight; //获取可视区的高度
                let scollerHeight=document.documentElement.scrollHeight;//获取整个页面的高度
                // console.log(scollerTop,clientHeight,scollerHeight);

                if((Math.ceil(scollerTop) + clientHeight == scollerHeight) && (!this.isFinish)){
                    this.isShow=true;
                    this.getData();
                }
                
            }

        }    
    }
</script>

<style lang="scss" scoped>
.store-list-box{
    padding: 0.2rem;
    .store-list{
        display: flex;
        margin-top:10px;
        img{
            width:1.52rem;
            height: 1.14rem;
        }
        .store-info{
            margin-left: 0.2rem;
            flex: 1;
            font-size: 16px;
            h2{
                font-size: 16px;
                font-weight: 600;
                overflow: hidden;
                text-overflow: ellipsis;
                white-space: nowrap;
                width: 80%;
                color: #333;
                font-family: "PingFangSC-Regular", Hiragino Sans GB, Arial, Helvetica, "\5B8B\4F53", sans-serif;
            }
            .store-info1{
                font-size: 11px;
                .info2-left{
                    float: left;
                    .sale{
                        margin-left: 10px;
                    }
                }
                .info2-right{
                    float: right;
                    .info2-2{
                        margin-left:5px;
                    }
                }
            }
            .store-info2{
                font-size: 11px;
                color: #333;
            }
        }
    }   
}
.loading{
    width: 30px;
    height: 30px;
    position: fixed;
    top:50%;
    left:50%;
    transform: translate(-50%,-50%);
    opacity: 0.5;
}
</style>