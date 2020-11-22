import Vue from 'vue'
import Vuex from 'vuex'
import axios from 'axios'

Vue.use(Vuex)

export default new Vuex.Store({
  //存储状态
  state: {
    count:0,
    count2:1,
    list:[]
  },

  mutations: {
    add(state,num){
      state.count+=num;
    },
    add1(state,num){
      state.count+=num;
    },
    addList(state,arr){
      state.list=arr
    }
  },
  getters:{
    sum(state){
      return state.count+state.count2
    }
  },
  actions: {
    getMovieList({commit}){
    /*
      豆瓣电影的接口
      `https://frodo.douban.com/api/v2/subject_collection/movie_showing/items?start=${event.start}&count=${event.count}&apiKey=054022eaeae0b00e0fc068c0c0a2102a`
        start和count是分页的参数
    */
      axios.get('https://bird.ioliu.cn/v1?url=https://frodo.douban.com/api/v2/subject_collection/movie_showing/items?start=0&count=10&apiKey=054022eaeae0b00e0fc068c0c0a2102a')
      .then((res)=>{
          console.log(res.data.subject_collection_items);
          commit('addList',res.data.subject_collection_items);
      }).catch((error)=>{
        console.log(error);
      })
    }
  },
  modules: {
  }
})
