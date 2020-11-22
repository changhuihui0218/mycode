<template>
    <div class="comment-wrapper">
        <!-- 遇到单词的大写改为中划线-小写
            因为Html标签不区分大小写，只识别小写，大写了也会识别为小写
         -->
         <div>
              <Comment :obj="data"></Comment>
              <Detail :data="data" @changeType="fn"></Detail>
         </div>
    </div>
    <!-- 亮点：
        发现子组件的两个都用到了某个接口的数据
        我们在父组件中请求，然后传参数
     -->
     <!-- 调用子向父亲传值时，一定要加‘’，且调用方法时用户this.  -->
</template>

<script>
    import Comment from './Comment'
    import Detail from './Detail'
    import axios from 'axios'
    import BetterScoll from 'better-scroll'
    export default {
        components:{
            Comment,
            Detail
        },
        data(){
            return{
                 data:[]
            }
        },
        methods:{
            fn(typeId){
                // console.log(typeId);
                this.getData(typeId);  
            },
            getData(id){
                axios.get('http://admin.gxxmglzx.com/tender/test/get_info?id='+this.$route.query.id+'&type='+id)
                .then((res)=>{
                    console.log(res.data);
                    this.data=res.data.data;
                    this.$nextTick(()=>{
                    let myScoll = new BetterScoll(".comment-wrapper",{
                        click:true,
                        bounce:false
                    })
                 })
                })
                .catch((error)=>{
                    console.log(error);
                })
            }
        },
        created(){
           this.getData(1)
        },
        
    }
</script>

<style lang="scss" scoped>
.comment-wrapper{
    height:calc(100vh - 44px)
}
</style>