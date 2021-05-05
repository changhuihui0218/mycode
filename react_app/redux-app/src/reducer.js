import {combineReducers} from 'redux'

const num =(preState=0,action)=>{
    console.log(preState,action)
    switch(action.type) {
        case 'ADD': 
            return preState+1;
        default: 
            return preState;
    }
}
let reducer = combineReducers({
    num,

})
export default reducer;