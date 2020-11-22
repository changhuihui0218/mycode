<template>
    <div>
        Vuex
        <!-- 取状态方法1 -->
        {{$store.state.count}}
        -----
        <!--取状态方法2  -->
        {{count}}

        <!-- 修改状态的方法1 -->
        <button @click="$store.commit('add',3)">++</button>
        <!-- 修改状态的方法2 -->
        <button @click="add1(3)">+++</button>

        <!-- Getter -->
        <h2>count1的值： {{count}}</h2>
        <h2>count2的值： {{$store.state.count2}}</h2>
        <!--方法1-->
        <h2>sum的值为：{{$store.getters.sum}}</h2>
        <h2>sum的值为：{{sum}}</h2>
    </div>
</template>

<script>
    import {mapState,mapMutations,mapGetters} from 'vuex' 
    export default {
        computed:{
            ...mapState(['count']),
            ...mapGetters(['sum'])
        },
        methods:{
            ...mapMutations(["add1"])
        },
    }
</script>

<style lang="scss" scoped>

</style>