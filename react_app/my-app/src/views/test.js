import React, { Component } from 'react';

class test extends Component {
    render() {
        let id =this.props.match.params;
        console.log(id)
        return (
            <div>
                我是测试测试页面呀
                <button onClick={()=>{
                    // this.props.history.goBack();
                    this.props.history.goForward();
                }}>返回上一页</button>
            </div>
        );
    }
}

export default test;