import Vue from 'vue'
import VueRouter from 'vue-router'
import Home from './../views/Home.vue'
import Test from './../views/Test.vue'
import Test1 from './../views/Test1.vue'
import Test3 from './../views/Test3.vue'
import Alias from './../views/Alias.vue'
import A from './../views/A.vue'
import B from './../views/B.vue'
import IVue from './../views/Vuex.vue'

Vue.use(VueRouter)

const routes = [
  {
    path:'/home',
    name:'myHome',
    component:Home,
    children:[
      {
        path:'/home/a',
        component:A
      },{
        path:'/home/b',
        component:B
      }

    ]
  },
  {
    path:'/test/:id',
    component:Test,
  },
  {
    path:'test3',
    component:Test3
  },
  {
    path:'/alias',
    component:Alias,
    alias:'/aa'
  },
  {
    path:'/test1/:id',
    component:Test1
  },{
    path:'/vuex',
    component:IVue
  },
  {
    path:'/:id',
    redirect:'/test1/:id',
  }
]

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes
})

export default router
