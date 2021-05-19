import myContext from './myContent'
import {useContext} from 'react'
function DoingList() {
    const arrList = useContext(myContext)
    return (
        <div>
            <h3>正在进行</h3>
            {
            arrList.map((item,index)=>{
                return (<div>
                    <input type='checkbox'/>
                    <span key={index}>{item.text} [X]</span>
                </div>)
            })
            }
      </div>
    )
}
export default DoingList