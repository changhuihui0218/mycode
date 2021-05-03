
import {Link,Route,NavLink,Redirect,Prompt} from 'react-router-dom'
import Home from './views/home'
import Test from './views/test'
import Hui from './views/hui'
import Test3 from './views/Test3'
import './app.css'
let flag=true;
function App() {
  return (
    <div>
      哈哈哈哈
      <Test3></Test3>
      {/* <Link to='/home'>首页</Link>
      <Link to='/test/5'>测试页面</Link>
      <Link to='/render'>render方式渲染页面</Link>
      <Link to='/children'>children方式渲染页面</Link> */}

      <Route path='/' exact component={Hui}></Route>
      <Route path='/home' component={Home}></Route>
       {/*传参数的写法  param的写法  
          this.props下有三个参数match中有参数
        */}
      <Route path='/test/:id' component={Test}></Route>

       {/* render的写法 */}
      <Route path='/render' render={()=>{
        return (
          <div>
            <h2>我是render渲染的页面</h2>
          </div>
        )
      }}></Route>

      {/* children函数得写法 不管路径有没有被匹配到的时候，他一直都渲染存在任何页面
          有些不一样----当匹配到xxxxx，，有一点点不一样
                        当匹配到其他的  没有
      */}
      <Route path='/children' children={()=>{
        return (
          <div>
            <h2>我是children渲染的页面</h2>
          </div>
        )
      }}></Route>



      {/* 路由的重定向 
        当路径想要重定向到xxx 
        在render函数中写一个<Redirect></Redirect>重定向到
        虽然重定向到其他的页面
      */}
      {/* <Route path='/test' render={()=>(
        <Redirect to='/home'></Redirect>
      )}></Route> */}


        {/* 编程式导航
            this.props.history.goBack();返回上一页 goForward()
            this.props.history.go(-1);  //返回上一页 （2，3，4，5）

        */}

        {/* 
          通过路由跳进来创建页面
            history、match、location
          通过子组件嵌入进来
            在子组件中this.props的对象----空对象--没有传入值
            可以通过 withRouter包裹的组件
            1、首先 在子组件中：引入 withRouter 在 react-dom-router
            2、在导出子组件的页面中用withRouter包裹它
            3、就有this.props进行
        */}
        {/* 
            在主页面中演示
            Prompt 在react-dom-router中引用进来的
              when 条件为真， 离开页面的时候会提示  在每回页面就要跳转的时候触发
            刚开始的标识是true,
            <Prompt when ={flag} message={()=>("提示字（是否确定跳转）")></Prompt>
        */}
          {/* <Prompt when={flag} message={()=>('确定是否离开？')}></Prompt> */}
        {/* 
            NavLink
            Link---被解析为a标签  不管有没有激活都长一样  当激活的时候 样式长得不一样使用NavLink
            当前及的时候 会增加一个 class='active',对应的样式不一样
             可以修改 针对于每一个页面的NavLink中的 activeClassName='xxx'
            activeStyle(对象)
        */}
      <NavLink to='/home' activeClassName='xx'>首页</NavLink>
      <NavLink to='/test/5'>测试页面</NavLink>
      <NavLink to='/render'>render方式渲染页面</NavLink>
      <NavLink to='/children'>children方式渲染页面</NavLink>
    </div>
  );
}

export default App;
