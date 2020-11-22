<template>
<!-- 问题

    1.宽度问题
    一般当标题的长度比较短一点的时候不会出现左边的的宽度被挤压到了。
    发现只要把overflow的三句话的最后一句就删掉好使了
    原因 给父 flex子元素的加一个width=0;
    是父元素分为1，3部分
    然后子元素是撑开的，所以他会占用挤压掉
    2.出现了两次
    将scroll中的click改为false就好使了
    因为出现了两个scrolll 里面一个外面一个 将外面的scroll给click给false
    只需要第一个就好
 -->
    <div class="order-box">
        <div class="box-left">
            <div>
                <ul>
                    <li class="left-list" :class="{active: index ==currentIndex}" v-for="(obj,index) in nav" @click.prevent="change(index)"  :key="index">{{obj.name}}</li>
                </ul>
           </div>
        </div>
        <div class="box-right">
        <div>
            <ul>
                <li  class="cate" v-for="(obj,objIndex) in goods" :key="objIndex"> 
                    <ul>
                        <div class="title">{{obj.name}}</div>
                        <li v-for="(pro,index) in obj.content" :key="pro.id">
                            <div class="pro-info">     
                                <img class="info-img" :src="pro.img" alt="">
                                <div class="info-box">
                                    <div class="info-name">{{pro.name}}</div>
                                    <div class="info">{{pro.info}}</div>
                                    <div class="info-num">
                                        <span class="num-1">月售{{pro.num}}</span>
                                        <span class="num-2">赞{{pro.up}}</span>
                                    </div>
                                    <div class="info-price">
                                        <span class="price-1">¥ {{pro.price}}</span>
                                        <span class="price-2">/约2斤</span>
                                        <div class="price-add">
                                            <div class="price-add1"  v-if= "pro.count>0" @click="$store.commit('sub',{objIndex,index})" ></div>
                                            <div class="price-add2" v-if= "pro.count>0">{{pro.count}}</div>
                                            <div class="price-add3" @click="$store.commit('add',{objIndex,index})"></div>
                                        </div>
                                    </div>
                                    <div class="price-border">6.8折</div>
                                </div>
                            </div>
                        </li>
                    </ul>
                </li>
            </ul>
        </div>
        </div>
        <!-- <div class="cart"></div> -->
    </div>
</template>

<script>
    import axios from 'axios'
    import BetterScoll from 'better-scroll'
    export default {
        data(){
           return{
                nav:[],
                goods:[],
                currentIndex:0,
                scrollY:0,
                position:[],
                num:0,
                isShow:true
           }
        },
        methods:{
            change(index){
                //点击左边的标签，右边的商品滑动到相应的位置

                //1.先获取到这个点击的标签(类名是右边的类名)
                let cateList =document.getElementsByClassName("cate");
                // console.log(cateList[index]);

                //2.将右边的滑动到相应的位置scrollToElement
                this.proScoll.scrollToElement(cateList[index]);
                this.currentIndex=index;
            },
            //右边滑动的时候，知道滑动是哪一个分类
            getPosition(){
                 let cateList =document.getElementsByClassName("cate");
                 let h=0;
                 for(let i=0;i<cateList.length;i++){
                     if(i==0){
                         this.position.push(0)
                     }else{
                         h +=cateList[i-1].offsetHeight;
                         this.position.push(h)
                     }
                 }
                 console.log(this.position);
            },
            add(){
                this.num++;
            },
            sub(){
                // if(num>0){
                //      this.num--;
                // }
                 this.num--;
            }

        },
      created(){
          axios.get('http://admin.gxxmglzx.com/tender/test/get_nav?id='+this.$route.query.id)
          .then((res)=>{
            //   console.log(res.data.data);
              this.nav=res.data.data.nav;
              this.goods=res.data.data.goods;
            //   console.log(this.goods);
              this.$store.commit("getData",this.goods)
              this.$nextTick(()=>{
                this.catScoll = new BetterScoll(".box-left",{
                    click:false,
                    bounce:false
                });
                this.proScoll = new BetterScoll(".box-right",{
                    click:false,
                    bounce:false,
                    probeType:3
                });
                //得到滚动条的滑动的长度以及位置on
                //若不出现位置信息则添加一个配置项probeType为3
                this.proScoll.on("scroll",position=>{
                    // console.log(position.x,position.y);
                    this.scrollY=Math.abs(position.y);
                    // if(scrollY)
                    // console.log(this.scrollY);
                })
                this.getPosition();//放到里面就好使了
              })

          })
          .catch((error)=>{
              console.log(error);
          });




        //想要点餐页滑动时超出自己的高度则不动
        // setTimeout(()=>{
        //      let catScoll = new BetterScoll(".box-left",{
        //          click:true,
        //          bounce:false
        //     });
        //     let proScoll = new BetterScoll(".box-right",{
        //         click:true,
        //         bounce:false
        //     });
        // },1000)
      },

      //右侧滑动时，左侧也滑动
      //监听属性 当scrollY发生变化的时候则监听
      watch:{
          //监听属性的写法:属性(变化的值)
          scrollY(value){
              let cateList = document.getElementsByClassName("left-list")
              for(let index=0;index<this.position.length;index++){
                  let pos1 =this.position[index];
                  let pos2 =this.position[index+1];

                  if(value>pos1 && value <pos2){
                    //   console.log(i);
                      this.currentIndex=index;
                    //   console.log(cateList[index])
                      this.catScoll.scrollToElement(cateList[index],300)
                  }
              }

          }

      }
    }
</script>

<style lang="scss" scoped>
.order-box{
     display: flex;
      padding-bottom: 50px;
      box-sizing: border-box;
    .box-left{
        height: calc( 100vh - 94px);
        flex:1;
        color: #666666;
        background: #f5f5f5;
        .left-list{
        //    height: 60px;
           padding: 9px 10px 22px;
           line-height: 18px;
           font-size: 13px;
           font-family: "PingFangSC-Regular", Hiragino Sans GB, Arial, Helvetica, "\5B8B\4F53", sans-serif;
           text-align: left;
           color: #666666;
           &.active{
               color: red;
               background: white;
           }
          
        }
    }
    .box-right{
        flex:3;
        // margin-left: 10px;
         height: calc( 100vh - 94px);
        .title{
            height: 36px;
            font-size: 12px;
            color: #333333;
            padding-left: 10px;
            line-height: 36px;
        }
        .pro-info{
            display: flex;
            box-sizing:content-box;
            .info-img{
                margin-left: 10px;
                width: 75px;
                height: 75px;
                margin-right: 10px;
            }
            .info-box{
                flex:1;
                width:0;
            }
            .info-name{
                font-size: 16px;
                color: #333333;
                font-weight: bold;
                font-family: "PingFangSC-Medium", "Hiragino Sans GB", Arial, Helvetica, "\5B8B\4F53", sans-serif;
                overflow: hidden;
                text-overflow: ellipsis;
                white-space: nowrap;
                height: 22px;
                margin-bottom: 2px;
            }
            .info{
                width: 137px;
                overflow: hidden;
                text-overflow: ellipsis;
                white-space: nowrap;
                line-height: 15px;
                font-size: 11px;
                color: #666666;
                margin-bottom:3px;
            }
            .info-num{
                height: 15px;
                font-size: 11px;
                margin-bottom: 3px;
                font-family: mtsi-font;
                color: #666;;
                .num-1{
                    margin-right: 10px;
                }
            }
            .info-price{
                 padding-right: 5px;
                 position:relative;
                display: flex;
                .price-1{
                    display: inline-block;
                    height: 21.5px;
                    line-height: 21.5px;
                    color: #fb4e44;
                    font-size: 18px;
                    font-family: "PingFangSC-Medium", "Hiragino Sans GB", Arial, Helvetica, "\5B8B\4F53", sans-serif;
                    vertical-align: middle;
                }
                .price-2{
                    display: inline-block;
                    align-items: end;
                    color: #999;
                    font-size: 12px;
                    font-family: "PingFangSC-Medium", "Hiragino Sans GB", Arial, Helvetica, "\5B8B\4F53", sans-serif;
                }
                .price-add{
                    position: absolute;
                    right:10px;
                    bottom: 0;
                    display: flex;
                    .price-add1{
                        display: inline-block;
                        margin-right: 5px;
                        height: 22px;
                        width: 22px;
                        background-size: 100% 100%;
                        background-image: url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADQAAAA0CAMAAADypuvZAAAAM1BMVEX////Z296wsLD6+vvo6evi5Obe3+Lr7O709fb5+fr3+Pjb3eDw8fLu7/Hl5+nk5ui5ubmS1nTyAAABG0lEQVRIx52WWXLEIAxEeUGSGeNl7n/aME6lUmQWm+5f+5l2A5LSC+XFPCrUcFtyuqDbFHSK6XaCzE7TvpZ8LFnWnSafPyB5g2oldSpWYXvrcgKmkQdNDpbfWDDwVwEE8cH6HMRTIAX8Y7rZofxbByydyKBfKx7MORV9Bn4CPL82EfkKlOMv+QxzuqQZfr++YemijK3Dz9Sb8mb0sib8Z4tqGlDldrA2AtnhKygjUCGOX0tDesS2sI9BO0vzuI5BK5acMgYVPAV5DMpEy71P9P71pHu/J9REDzXmBdVDSJBkTwpCilzaXOkYSQdWuRrSJZSuu1JYpBKmFEupLCsNQGk1SlOT2qfSqJWRQBg+lDFHG6j00U0fEqVx9BvALAkNabHL3QAAAABJRU5ErkJggg==);
                    }
                    .price-add2{
                        height: 22px;
                        line-height: 22px;

                    }
                    .price-add3{
                        display: inline-block;
                        margin-left: 5px;
                        background-image:url(//s3plus.meituan.net/v1/mss_e2821d7f0cfe4ac1bf9202ecf9590e67/cdn-prod/file:9096d347/318c525df8eba9c557594305c44b2ddf.png);
                        height: 22px;
                        width: 22px;
                        background-size: 100% 100%;
                    }
                }
            }
            .price-border{
                color: #fb4e44;
                font-size: 10px;
                border:1px solid #fb4e44;
                width: 30px;
                height: 15px;
                margin-bottom:21.5px;
            }

        }
    }
    
}
</style>