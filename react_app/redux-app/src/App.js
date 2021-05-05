import store from "./store";
import add from './action';
import {connect} from 'react-redux';
function App(props) {
  return (
    <div className="App">
     redux
     <h2>{props.num}</h2>
     <button onClick={()=>{
       store.dispatch(add());
     }}>click +1</button>
    </div>
  );
}
const mapStateToProps = (state)=>(
  {
    num:state.num
  }
)

export default connect(mapStateToProps)(App);
