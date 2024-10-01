const mysql = require('mysql2')

const mysqlConnection = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: 'admin',
    database: 'ARQUI2'
})

mysqlConnection.connect(function(err) {
    if(err) return console.log(err)
    console.log('Database is connected')
})

module.exports = mysqlConnection