import React from 'react';
import ReactDOM from 'react-dom';
import App from './App';
import reportWebVitals from './reportWebVitals';
import {BrowserRouter as Router} from 'react-router-dom';

ReactDOM.render(
  // 严格模式-----去掉
  // <React.StrictMode>
  //   <App />
  // </React.StrictMode>,

  // 路由的使用   
  // hash（路径前带有#） BrowseRouter（路径无） memoryRouter （刷新的时候，虽然路径没有改变，但是页面会回到最原始的界面）
  // 在<App/>的外部用<Router>包裹起来，这样App以及App下的文件都可以使用路由  
  // link是模糊匹配 /不管是什么路径都会匹配到这个/代表的路径 exact
  <Router>
    <App />
  </Router>,
  document.getElementById('root')
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();
