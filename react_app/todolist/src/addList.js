import {useState,useContext, useRef} from 'react'
import myContext from './myContent'
const AddList=()=>{
    const inputEl = useRef(null)
    const {arrList,setList} = useContext(myContext)
    return (
        <div>
            <input type='text' ref={inputEl} placeholder='请输入想要添加的信息'></input>
            <button onClick = {()=>{
                var arr = [...arrList]
                arr.push(inputEl.current.value)
                console.log(arr)
                setList([...arr])
                console.log(arrList)
                inputEl.current.value = ''

            }}>添加</button>
        </div>
    )
}
export default AddList