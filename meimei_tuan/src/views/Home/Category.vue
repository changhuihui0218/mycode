<template>
    <div>
       <ul>
           <li v-for="obj in List" :key="obj.id" class="list">
               <img :src="obj.img" alt="">
               <p>{{obj.name}}</p>
           </li>
       </ul>
    </div>
</template>

<script>
    import axios from 'axios'
    export default {
        data(){
            return{
                List:[]
            }
        },
        created(){
            axios.get('http://admin.gxxmglzx.com/tender/test/get_type')
            .then((res)=>{
                console.log(res.data)
                if(res.data.errcode==200){
                    this.List=res.data.data
                }
            })
            .catch((error)=>{
                console.log(error)
            })
        }    
    }
</script>

<style lang="scss" scoped>
ul{
    display: flex;
    flex-wrap: wrap;
    padding: 0 0.1rem;
    .list{
        width: 20%;
        margin-top: 0.3rem;
        color: black;
        font-size: 11px;
        text-align: center;
        img{
            // margin-top: 10px;
            width: 75% ;
        }
        ;
    }
}


</style>