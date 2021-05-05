import {createStore} from 'redux'
import reducer from './reducer'

let initStore ={
    num:0
}
//  createStore()的第一个参数是reduce  第二个参数是初始化
let store = createStore(reducer,initStore);

export default store;