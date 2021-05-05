import { useContext } from 'react';
import myContext from './myContext';

const Child1= ()=>{
    const count = useContext(myContext);
    return (
        <div>
            我是子组件 {count}
        </div>
    )
}
export default Child1;