import {useRef,useState,useEffect,useMemo,memo, useCallback,useReducer} from 'react'
import Child1 from './child1';
import myContext from './myContext'

const Child= memo(({data,change})=>{
  console.log('render',data)
  return (
    <div>
      子组件 {data.title}
      <button onClick={()=>{
         change();
      }}>change click</button>
    </div>
  )
})

function reducer(preState=0,action) {
  switch(action.type){
    case 'add':
      return preState+1;
    case 'reduce':
      return preState-1;
    default: 
      return preState;
  }
}
function App() {

  // 1、使用userState
  let [count,setCount] = useState(0);
  let [list,setList] = useState([{name: 'zs'},{name: 'lisi'}]);
  let [title,setTitle] = useState('title1');

  // 2、使用userEffect
  useEffect(()=>{
    console.log('userEffect'); // 更新和初始化
    // return ()=>{
    //   console.log('jjj'); // 更新和挂载
    // }
  }, []) //[]限制

  // 3、userRef
  const InputEl = useRef(null);

  // 4、缓存
  // const data = {
  //   title: '111',
  // };
  const data = useMemo(()=>{
    return {
      title
    }
  },[title]);

  //5、缓存方法
  // const change= function(){
  //   console.log(1)
  // }
  const change= useCallback(function(){
    console.log(1)
  },[])

  // 6、reducer
 const [num,dispatch]=useReducer(reducer,0);

  return (
    <div className="App">

      {/* 修改简单的值 */}
      {count}
      <button onClick={()=>{
        setCount(count++);
      }}>++</button>

      {/* 修改数组 */}
      <ul>
        {
          list.map((val,index)=>{
            return <li key={index}>{val.name}</li>
          })
        }
      </ul>
        <button onClick={()=>{
          let arr =[...list];
          arr.push({name:'ccc'});
          setList(arr);
        }}>修改数组</button>

        {/* 生命周期 */}

        {/* 获取dom元素 */}
      <input type='name' ref={InputEl}/>
      <button onClick={()=>{
        console.log(InputEl.current.value)
      }}>获取当前元素</button>


      {/* 引入子组件 */}
      <Child data={data} change={change}></Child>
      <button onClick={()=>{
        setTitle('title2')
      }}>修改title</button>

      {/* redux */}
      <button onClick={()=>{
          dispatch({type:'reduce'})
      }}>{num}</button>
      <myContext.Provider value={count}>
        <Child1></Child1>
      </myContext.Provider>
    </div>
  );
}

export default App;
