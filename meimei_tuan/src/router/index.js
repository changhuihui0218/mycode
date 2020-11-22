import Vue from 'vue'
import VueRouter from 'vue-router'
import Home from '@/views/Home/index'
import Detail from '@/views/detail/Index'

Vue.use(VueRouter)

const routes = [
 {
   path:'/',
   component:Home
 },
 {
   path:'/detail',
   component:Detail
 }
]

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes
})

export default router
