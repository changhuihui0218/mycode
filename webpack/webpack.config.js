const path = require('path');

module.exports = {
    entry: {
        index: './src/index.js'
    },
    output: {
        // 绝对路径
        path: path.resolve(__dirname, 'dist'),
        filename: '[name].js'
    },
    module: {
        rules: [
            {
                test: /\.css$/,
                use: ['style-loader', 'css-loader','postcss-loader']
            },{
                test:/\.scss$/,
                use:['style-loader','css-loader','sass-loader']
            }
        ]
    }
}

