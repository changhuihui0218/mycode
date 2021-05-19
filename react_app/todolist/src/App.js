import {useRef, useState} from 'react'
import myContext from './myContent'
import AddList from './addList'
import DoingList from './doingList'
function App() {
  const [arrList, setList] = useState([
    {text:'hhhh',},
    {text:'heee',}
  ]);
  const inputEl = useRef(null)
  return (
    <div className="App">
      <h1>todoList</h1>
      <myContext.Provider value={{arrList,setList}}>
          <AddList />
      </myContext.Provider>
      <myContext.Provider value={arrList}>
          <DoingList />
      </myContext.Provider>
    </div>
  );
}

export default App;
