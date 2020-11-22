const user={
  namespaced: true,
  state: {
      proList:[
        {
            name:'iphone12'
        },{
            name:'QQ'
        },{
            name:'xx'
        }
      ]
  },
  mutations: {
      addList(state){
            state.proList.push({name:'111'});
      }
  },
  getters:{
  },
  actions: {
  },
  modules: {
  }
}
export default user;
