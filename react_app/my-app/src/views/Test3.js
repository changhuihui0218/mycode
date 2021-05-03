import React, { Component } from 'react';
import {withRouter} from 'react-router-dom'

class Test3 extends Component {
    render() {
        // console.log(this.props)
        return (
            <div>
                hhh
                <button onClick={()=>{
                    this.props.history.goBack();
                }}>返回</button>
            </div>
        );
    }
}

export default withRouter(Test3);