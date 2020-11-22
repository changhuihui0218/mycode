<template>
<!-- 行元素 行级块元素 当多个高度不一样的时候 用vertical-align:middele 默认是靠下对齐
元素定位后元素的宽度是内容撑的，可以写死
fixed遇到transform就不好使了

提到content之外，wrapper以内
 -->
    <div>
       <div class="top-box">
           <div class="top-address">
               <div class="add-1">
                   <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABwAAAAgCAMAAAA2a+hwAAAAV1BMVEUAAACrq6uqqqqrq6uvr6+qqqqsrKysrKyqqqqsrKyurq6tra2qqqqrq6urq6usrKyxsbGqqqqrq6urq6urq6uqqqqqqqqrq6urq6urq6urq6uqqqqqqqptythVAAAAHHRSTlMA9dHCCYNBTN4vGSPsj2hFD6lgd3Tly7Z6VDyiLLeTfQAAASlJREFUKM91UlGWgyAMJICAqK1WrdrO/c+5aXhK2WXnJy8ZMkwC6oR1gwlEwQzOqhJ27nGhnwvaM6Ub11nbuUYz7TM3AOae07sBhszRogosdLIz6GzLzYT5EzvCIYWx0US6SWYOUMdhw1tSFyAITtI3Nm4EReEA42P0BhA2Ejq1Y5JBAxolaBBEecKuDI5UMqcZk44dXAnczdC45vbQYhRBEUSEEE8yguQiDj3GOjmiZ722LtviyaYedUMPHsOn6vhnFMNadkVbW0KLlc/c8Kytz+D2Cc8UlM2Lzy0tEQtnlLUFeiy5UeN6/gmbLcgN0/fB4ZsbCqm4Ys/ZjLUrDSTLyehvgy+SNcrayFX+20M4+YsV9iaaXlXgCPtS7ZN7e6B/qX/Qal34/AGEtRT7yCXlzQAAAABJRU5ErkJggg==" alt="">
               </div>
               <div class="add-2">{{data.address}}</div>
               <div class="add-3">
                   <div class="add-3-img"></div>
               </div>
           </div>
           <div class="top-label">
               <div class="add-1">
                   <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAAe1BMVEUAAACsrKyrq6u8vLyrq6uqqqqurq6rq6uqqqqurq6rq6uqqqqrq6urq6urq6urq6urq6utra2qqqqrq6urq6urq6usrKyvr6+qqqqrq6urq6urq6uurq6rq6uqqqqqqqqqqqqrq6urq6uqqqqurq6rq6utra2tra2qqqpQWWHrAAAAKHRSTlMAa5UFpvkR9vIJxu3ey2FaSyrmiHNELxy1f2Y3INfQvq+ajHolUT0Y1wVGwAAAAV5JREFUOMt9k+l6gyAQRTGAu8bdqM2+nfd/whZJ22hMzg/9Zu6dEYQRE/K+Sr/EO77OWwxh7y6obh8CkTodfNCbdTBRg+tBg6cyaYL1RoOvavkrt8d50d0JgaJ0bfMCEucuply6LSRjk4rwIpYYYjLzXuEs6laZGzLVfDS0mlh+MqyA9IPh4tERu8sGd5X4oMQWorBbMHRAlOTiuvOA7NVQQ2k7yw1+u7CGHs6jrvBvz584mbwhhfzntcYfbELZHVWoR2tNIFwxsBOWnV3Kja2Nc+Jmo485WtpL4HEfCwvqMbHGA8zDHp5DaCsr9g8D+jQoIB8LzWHaVoVdjDyVZnfNqhrTJYl4kOI1Yk6Gvv0FR+J2pjcR1X8kQ+LpOAwRanLpE4r8Ka59DsF0LPZ4/V/DTqOkmBIoOLh2wkIoxSuOpqjN7/CJrmKJZgeq3sP+3fzKswdEqXhPe0zK2Wh/A7mFImCuxPBKAAAAAElFTkSuQmCC" alt="">
               </div>
               <div class="add-2">查看食品安全档案</div>
               <div class="add-3"></div>
           </div>
       </div>
       <div class="time-box">
           <div class="serve-box">
               <div class="serve-img">
                   <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABoAAAAcCAYAAAEIFJ9FAAAABGdBTUEAALGPC/xhBQAAAeZJREFUSA3VVr1OAkEQZpetsNNGJfoEPoJEa1/B0hgIHQ0PQQEVBLD2EbTW+Ao+gcSfRgoSqWDP+fa4zbjZYxcUEi+Bm/l2Zr6Z2dnNiQI9g8EgwXs2m1WsAmBICxJCZgEZgK5WqwIK/ARfBfjz8a/60ZRSZQEco7HBHTCzNcmKfr//IoQ4smgqaEePUE15LhfKNg1hAcZZLxjmiJ1O58CBjJql+0whLnwGHEOQnVLpTaE+cjjGopsgdyAZue3RLhZsS2EQTjgN41aaooH/7TmpJEnOMKKBjMwyjOinRbfbPVVKPZIeTJUIRrVa7ViA5Ws6PWw0Gu8hNtqSe3I8MQMZMubr2Eu7T6R80uIuN+Ay30PrhN3mRsvkYPE+Z8u08fSWMvHieZrWaeONWKt7MmpSFwW1Wq19EjVq0hgNcyHxanNkTadC3PR6FV0sPpCTYY11zolpYVSAWDhKcj4/VyAhXcaeDrKNfnDjlejGAwcaLsEccwSjGRaGiLnokLQzxIOExp3bemRzDbu4l2iVwXUD5uleon9d0VqnL689y/DftM676XlkXqJNDMPWWrc1InwGjPBNRN9+d5PJ5KrZbH7k9XkVvN1ul+n6GcLHcEDAxTqX8pYIy6T+VZV0aSevRa0vr+v1p288mc50UpNwRAAAAABJRU5ErkJggg==" alt="">
               </div>
               <div class="serve-info">
                  <div class="info-1">配送服务：</div>
                  <div class="info-2"></div>
                  <div class="info-3">{{data.server}}</div>
               </div>
           </div>
           <div class="time-box">
                   <div class="time-img">
                       <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAB4AAAAeCAMAAAAM7l6QAAAAS1BMVEUAAACsrKy1tbWqqqqrq6v///+rq6urq6urq6urq6urq6uurq6qqqqrq6usrKyqqqqrq6uqqqqqqqqrq6urq6uqqqqsrKywsLCqqqqPxk2bAAAAGHRSTlMAZQfy5wKLvamAUCrhcjmUQtbZokbKJg4RvoWNAAAA8ElEQVQoz4WTWZLDIAxEBWIxxgtekvT9TzqumQFFSRz3DxSvqiW0UJOfQlyZ1xgmT6+yo0OTG62m/QBwZ0rOxXQMDD2JfAKcsc3JOCD5RjsgKDs7A1vlCTD0IgOk/7hCNe9/jQaE9hhju84Y7HGMcBIXkPgO45GXO6wVFnvnaQLbz9gyJgroSGFRh0AR5gwbRFpRzvCOhRj5DGfwG75rrM1vQHg8m+vUHhvAxrfU6sfE8TBYSv1YK4uod0CpZWlFFdl0u9eitpaIpCV/DZ01kIZejcP1MJHfgPl9FL8P8oc12HPeZQ2ul0iv4MK8qBX8Aa70EZDD+3G4AAAAAElFTkSuQmCC" alt="">
                   </div>
                   <div class="time-info">配送时间：{{data.delivery_time}}</div>
            </div>
       </div>
       <div class="shop-box">
           <div class="msg">
               <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAB4AAAAeCAMAAAAM7l6QAAAATlBMVEUAAACYmJiYmJibm5uYmJiXl5ezs7OXl5eXl5eYmJiYmJiYmJiZmZmgoKCYmJiYmJiZmZmZmZmbm5ufn5+Xl5eYmJiZmZmYmJiampqXl5fFk318AAAAGXRSTlMAVKso+bYG6tzTS346FuW+cGgcEJKHW5sw6MqDlgAAAMFJREFUKM9909sSgyAMRdGDRGxFtF7b8/8/2po6iuPE/URYb2HAtfRqYNdUlGRqLRTWN/ou6AxdhBNM7skZJr/ICJMj2cPkmbLg4Djo4OdC6ygOBzs+0qrCLamR8fhkqedycdoHOWPQ7Ty5X58Zkd3K3uCREm4YLYc7rphu2LMFOjqD35x0z49/RThxQ/EAJuFWGTIeWkadgtea6ucH9+wC8vzqO6MfgatbD3q4su3KtivbXiqbTtawvaUk2I3ZF/wCwVMN845HN1gAAAAASUVORK5CYII=" alt="">
               <div class="thank-msg">
                   {{data.notice}}
               </div>
               <div class="thank-arr"></div>
            </div>
            <div class="shop-serve">
                <div class="info-1">
                    <img src="//s3plus.meituan.net/v1/mss_e2821d7f0cfe4ac1bf9202ecf9590e67/cdn-prod/file:9096d347/bc2175e8adc4beec375977e424b1f542.png" alt="">
                </div>
                <div class="info-2">商家服务</div>
                <div class="info-3">
                    <div class="info-3-1">
                        <div class="img1"></div>
                        该商户为品牌商户
                    </div>
                    <div class="info-3-2">
                         <div class="img2"></div>
                            该商户支持在线支付
                        <div class="img3"></div>
                    </div>
                </div>
            </div>
           <div class="cheapper-box">
               <div class="full-down">
                   <div class="info-img"></div>
                   <div class="info-msg">
                      {{data.full}}
                   </div>
               </div>
               <div class="discount">
                    <div class="info-img">
                       <img src="" alt="">
                   </div>
                   <div class="info-msg">
                       {{data.sales}}
                   </div>
               </div>
               <div class="pay">
                   <div class="info-img">
                       <img src="" alt="">
                   </div>
                   <div class="info-msg">
                       该商家支持在线支付
                   </div>
               </div>
           </div>
       </div>
    </div>
</template>

<script>
import axios from 'axios'
    export default {
        data(){
            return{
                data:[]
            }
        },
        created(){
            axios.get('http://admin.gxxmglzx.com/tender/test/get_store_id?id='+this.$route.query.id)
            .then((res)=>{
                console.log(res.data.data);
                this.data=res.data.data
            })
            .catch((error)=>{
                console.loh(error);
            })
        }
    }
</script>

<style lang="scss" scoped>
.top-box{
    width: 305px;
    height: 100px;
    margin:0 15px;
    box-sizing: border-box;

    .top-address{
        width: 290px;
        height: 40px;
        margin: 18px 0;
        box-sizing: border-box;
        padding: 0 50px 0 24px;
        position: relative;
        display: flex;
        .add-1{
            img{
                position: absolute;
                top: 0;
                left: 0;
                width: 14px;
                height: 16px;
            }
        }
        .add-2{
            width: 216px;
            font-family: mtsi-font;
            font-size: 14px;
        }
         .add-3{
             width: 50px;
             height: 40px;
             .add-3-img{
                width: 20px;
                height: 20px;
                display: inline-block;
                background-image: url(//s3plus.meituan.net/v1/mss_e2821d7f0cfe4ac1bf9202ecf9590e67/cdn-prod/file:9096d347/25e14d800434e9a9d3ee9148dd6b033f.png);
                background-size: 100% 100%;
                margin: 0 auto;
                margin: 10px 0 0 25px;
                position: absolute;
                right: 0;
             }
        } 
        .add-3::before{
            content: "";
            display: inline-block;
            height: 30px;
            width: 1px;
            background-color: #e4e4e4;
            transform: scale(0.5);
            position: absolute;
            top: 50%;
            right: 35px;
            margin-top: -15px;
            //问题：发现伪元素跟着元素跑 怎么要他俩分开一点距离
        }
    }

    .top-label{
        width: 290px;
        height: 20px;
        margin: 18px 0;
        box-sizing: border-box;
        padding-left: 24px;
        display: flex;
        position: relative;
        .add-1{
            img{
                width: 16px;
                height: 16px;
                position: absolute;
                top: 0;
                left: 0;
            }
        } 
        .add-2{
            font-family: "PingFangSC-Regular", Hiragino Sans GB, Arial, Helvetica, "宋体", sans-serif;
            font-size: 14px;
        }
        .add-3{
            content: "";
            background-image: url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAwAAAAWBAMAAAAGFmApAAAAG1BMVEUAAACvr6+np6eurq6srKyurq6urq6np6evr6+aZHW7AAAACHRSTlMAzhHbG8S8HSeiSm4AAAAwSURBVAjXY0gsYACBDBMwpdjsAKKYJMjhNoIp51YQyWIhBOY0KhDPYZAAcxhCwRwAI1kNBzm+faIAAAAASUVORK5CYII=);
            height: 11px;
            width: 6px;
            background-size: 100% 100%;
            position: absolute;
            right: 0;
            top: 5px
        }
    }
}
.time-box{
    width: 305px;
    height: 94px;
    margin: 0 15px;
    box-sizing: border-box;
    .serve-box{
        display: flex;
        width: 290px;
        height: 20px;
        box-sizing: border-box;
        margin: 18px 0;
        padding-left: 24px;
        position: relative;
        .serve-img{
            img{
                width: 13.93px;
                height: 15px;
                position: absolute;
                top: 0;
                left: 0;
            }
        }
        .serve-info{
            display: flex;
            font-size: 14px;
            font-family: "PingFangSC-Regular", Hiragino Sans GB, Arial, Helvetica, "宋体", sans-serif;
            .info-1{
                height: 23px;
            }
            .info-2{
                background-image: url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGQAAAAeCAMAAADthUvBAAAAk1BMVEUAAAD/0mL/1WL/0WEzMzPrwVyiiUzDolTXsljPrFbov1u+nlKmjE3zx17fuFlHQjc3NjNPSDlLRTjbtVnHpVSLdkZVTTpCPjbku1p0ZUH7zmCqj05gVj0/PDX2yl9oXD9bUjzvxF3LqFWehUs7OTSVfkmBb0Sukk58a0OzlVBwYkC3mVBtX0DTrleEcUV/bkT4yl88Dmb6AAAAA3RSTlMA8zzqiAonAAACdklEQVRIx73U7XKiMBSA4d2eI8qXiQpBaAQUEEFte/9Xt0lIIdDSnemMvj8ITss8JGeGP7qXv/C4nmHAMwx4hgHPMGBqLFxfLsfGgf9V2/C17jF7AWbTfeypJxcP96BKrUkp6FIszOf4Si4r2sg/RSGYmUbiivKNvDImr4nYGZKNEUH5jh++KEDX75KufysDEF2io9gj3Y8RYx9HnHSUyBK6fHkSS4WccVSu3vBNbcInYn/sMpkJfC3LhvsBsaIe2QWinAW6O6jeQthnWZ5lHFkWzyMLFefdOoPoDuE3Yw9FEROXah4p0SzpECdWMRrHgUJsWYOV3QdmG6XPIzsV590KGjnLCKXns60QipMoQFPXtd5kKabyu5lcSdgf11rG8vWQmHUU4Qlqy7IKjC3RaQa5bLso1TeXHrHL03gmDlow7igQTgg5IJFVM4jrdVmezv1E7lExGbyF7krnDIjsRpLfHFdS0XeYIDn2hSPExcoNf0Cc166S6xtHIeuc1jBF9p+dy7uJLLab1C3bdBY5HVQUsezugg5h6rNUkQEZsvAKBnKNyE5MMGLOz8e1KmOe+6PjEo+xnF5GSPAhLklIPXPw78jUV2u9JaufEJewdEGYPSD6Y3xNTWRJy7hZ8cMSdGmMbeoViX6sXcwiyZIj34v/yTBeJh3irYy8fifH+kbR+NpnkbVhO/iuvwaSFrcSt/qIrzlGbeELZJw5E79muLG6ky3QhjTELb+1bRy3t4wnvfFi7mSTV/fhl13xXO6kcYyayeBPLe3e/rWS1921CN/O7xdRZRgmouxpydxPnQ8zDYZAHtRgPA4ZjMchg/E4ZDAejQzGP/NOULq7WWqcAAAAAElFTkSuQmCC);
                width: 50px;
                height: 15px;
               background-size: 100% 100%;
               margin: 0 10px 0 0;
            }
        }
    }
    .time-box{
         display: flex;
         width: 290px;
         height: 20px;
         box-sizing: border-box;
         margin: 18px 0;
         padding-left: 24px;
         position: relative;

         .time-img{
             img{
                 width: 15px;
                 height: 15px;
                 position:absolute;
                 top: 0;
                 left: 0;
             }
         }
         .time-info{
            font-family: mtsi-font;
            font-size: 14px;
         }

    }
}
.shop-box{
    width: 305px;
    height: 300px;
    box-sizing: border-box;
    padding: 0 15px;
    .msg{
        width: 290px;
        height: 20px;
        margin: 18px 0;
        padding-left: 24px;
        position: relative;
        display: flex;
        img{
            width: 14px;
            height: 14px;
            position:absolute;
            top: 0;
            left: 0;
        }
    .thank-msg{
        box-sizing: border-box;
        width: 266px;
        height: 20px;
        overflow: hidden;
        text-overflow: ellipsis;
        white-space: nowrap; 
        padding-right: 15px;
        font-family: "PingFangSC-Regular", Hiragino Sans GB, Arial, Helvetica, "宋体", sans-serif;
        font-size: 14px;
    }
    .thank-arr{
            content: "";
            background-image: url(data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAwAAAAWBAMAAAAGFmApAAAAG1BMVEUAAACvr6+np6eurq6srKyurq6urq6np6evr6+aZHW7AAAACHRSTlMAzhHbG8S8HSeiSm4AAAAwSURBVAjXY0gsYACBDBMwpdjsAKKYJMjhNoIp51YQyWIhBOY0KhDPYZAAcxhCwRwAI1kNBzm+faIAAAAASUVORK5CYII=);
            height: 11px;
            width: 6px;
            background-size: 100% 100%;
            position: absolute;
            right: 24px;
            top: 5px
    }
  }
  .shop-serve{
      width: 290px;
      height: 40px;
      position: relative;
      box-sizing: border-box;
    //   margin: 18px 0;
      padding-left: 24px;
      display: flex;
      .info-1{
          img{
              width: 14px;
              height: 14px;
              position: absolute;
              top:0;
              left: 0;
          }
      }
      .info-2{
          width: 56px;
          height: 20px;
          font-family: "PingFangSC-Regular", Hiragino Sans GB, Arial, Helvetica, "宋体", sans-serif;
          font-size: 14px;
      }
      .info-3{
          width: 210px;
          height: 40px;
          padding-left: 15px;
          box-sizing: border-box;
          font-family: "PingFangSC-Regular", Hiragino Sans GB, Arial, Helvetica, "宋体", sans-serif;
          font-size: 12px;
          .info-3-1{
               .img1{
                    display: inline-block;
                    vertical-align: middle;
                    margin-right:6px;
                    width: 15px;
                    height: 15px;
                    box-sizing: border-box;
                    background-size: 100% 100%;
                    background-image:url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAB4AAAAeCAMAAAAM7l6QAAAAPFBMVEUAAAAArv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv+7rjL9AAAAE3RSTlMAQMCA75TQG7IwEGBwUAbgoN+J9CeHAQAAANBJREFUKM+tk42KxDAIhB2j5q/d7l7e/13PbOG4a9KWgx2QoB+jGJAeKu1Eog/SFOlEMX2ROD3lQo0u1P6N1zjBCyNz6PNeUkYcpIBrybSk1dMcD7gRGPHVmJOvbGGGqS0A98Acg/Y4wc8Q1GNwa2OXGpv6O2CGKxtIN5o2p71sz/7W0R1QhJuyL8bHxaQPLMBmMAPi0b0PDJaJefjU1HHFmhhvN/IfbMkTbm+p9um/cZHws82keU3rFd6kXLq9d+a6F23Agz6Cb87g5ohuTvAbKZUOJe5EpDUAAAAASUVORK5CYII=");
                }
          }
          .info-3-2{
              margin-top: 5px;
               .img2{
                    display: inline-block;
                    vertical-align: middle;
                    width: 15px;
                    height: 15px;
                    box-sizing: border-box;
                    margin-right:6px;
                    background-size: 100% 100%;
                    background-image:url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAB4AAAAeCAMAAAAM7l6QAAAAP1BMVEUAAAAArv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arf8Arv8Arf8Arv9dh4GPAAAAFHRSTlMAQL+A8Q6ub6AmUOAwIJHQYM+GX0YPCd8AAACvSURBVCjPpdNBDsMgDARAg21wICRNyv/f2kbQqhEGDt0LkocVFwywOMpqyC1vJc+ghj0t4Dx04x0Q95kJMgySfzikT2nVOMc6NkdsOTiByhZblpgGzCQwYDxxNSV+E2PSjZkQbc22PK3FG7sTr3bQ2w+JiAB2Z/VtoofgdcupzKHMZPMKfyscj7XH5dhHDBK6XPInB9fntFuypuVcK5Kth4aVzHnykSdrMFmiyQq+AJ+LC5MukzlBAAAAAElFTkSuQmCC");
               }
               .img3{
                    margin-left:10px;
                    display: inline-block;
                    vertical-align: middle;
                    width: 15px;
                    height: 15px;
                    box-sizing: border-box;
                    margin-right:6px;
                    background-size: 100% 100%;
                    background-image:url("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAB4AAAAeCAMAAAAM7l6QAAAAOVBMVEUAAAAArv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv8Arv99/esyAAAAEnRSTlMAwECA8Q5woK4k0JIw4GBSf59v48E4AAAAxklEQVQoz62TW46DMAxFff2Ik1Cgk/0vdjygkSChRZV6fvI4UhxbNlHJ2i7RXMJqMrrEkhbKiV6SMqm91qbU6A3tK5pbz0kb/+FgTlPa9t3ji4jgKeKLx4772FBgnoC6VmCSQYNI4sDguB51PcTGqNsR+bQs7QBGzQcenX4gcNnJAKZRB/VZAXR6Z8l71tnL+DXLPzNv2udZrIvtqinWNTQVh64n7dWNKAlCB6x+0ral4vjP2OyiasYfNtNNI9+Mwc0Q3YzgL1P/DZPg4w9EAAAAAElFTkSuQmCC");
               }
          }
      }
  }
  .cheapper-box{
      width: 290px;
      height: 90px;
      padding: 18px 0;
      font-family: mtsi-font;
      font-size: 14px;
      .full-down{
          width: 261px;
          height: 40px;
          box-sizing: border-box;
          padding: 0 0 5px;
          display: flex;
          .info-img{
              display: inline-block;
              background-image: url("https://p0.meituan.net/activityconfig/6087b33fd42d14fd94e899084aaef56d1720.png");
              width: 15px;
              height: 15px;
              background-size: 100% 100%;
          }
          .info-msg{
              width: 234.9px;
              display: inline-block;
              margin: 0 0 5px 7px;
          }
      }
      .discount{
          display: flex;
          box-sizing: border-box;
          .info-img{
              display: inline-block;
              background-image: url("https://p0.meituan.net/activityconfig/3da2d9c7a4ddf89e4e71cfdfff168c391088.png");
              width: 29px;
              height: 15px;
              background-size: 100% 100%;

          }
          .info-msg{
               margin: 0 0 5px 7px;
               overflow: hidden;
               text-overflow: ellipsis;
            //    white-space: nowrap;
          }
      }
      .pay{
          display: flex;
          .info-img{
              display: inline-block;
              background-image:url("https://p1.meituan.net/xianfu/32200c3060be7903f62c9076308619ee734.png");
              width: 15px;
              height: 15px;
              background-size: 100% 100%;
          }
          .info-msg{
              margin: 0 0 5px 7px;
          }
      }

  }
}

</style>