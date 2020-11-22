import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)

export default new Vuex.Store({
  /*
      循环：  循环的对象.forEach((参数1  参数2 )=>{
        ......操作
        参数1 :循环的得到的值
        参数2:索引值 不需要的话直接不用写就可以了
      })

      给一个行元素设置宽和高不好使。但是我们给他定位的时候他就会好使了。
  
  
  */
  state: {
    prodList:[]
  },
  mutations: {
    //1.在页面一进来，数据请求回来后，将商品数据存到数组中
    getData(state,list){
      state.prodList=list;
    },

    //添加商品的操作
    add(state,{objIndex,index}){
      // console.log(objIndex,index)
      let pro=state.prodList[objIndex].content[index];
      if(pro.count){
        // 不能直接根据数组中的索引值来修改数组
        // pro.count++;
        Vue.set(pro,'count',pro.count+1);
      }else{
        // pro.count=1;
        Vue.set(pro,'count',1);
      }
    },

    //
    sub(state,{objIndex,index}){
      let pro=pro=state.prodList[objIndex].content[index];
      if(pro.count){
        Vue.set(pro,'count',pro.count-1);
      }else{
        Vue.set(pro,'count',1);
      }
    }
  },
  getters:{
    //计算总数
    total(state){
      let sum=0;
      state.prodList.forEach((type)=>{
        type.content.forEach((obj)=>{
          if(obj.count>0){
            sum+=obj.count;
          }
        })
      })
      return sum;
    },


    //计算总价
    sumTotal(state){
      let sumPrice=0;
      state.prodList.forEach((type)=>{
        type.content.forEach((obj)=>{
          if(obj.count>0){
              sumPrice+=obj.count*obj.price;
          }
        })
      })
        return sumPrice;
    }

  },
  actions: {
  },
  modules: {
  }
})
