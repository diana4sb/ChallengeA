var http = require('http'),
  fs = require('fs');

var express = require('express');
var SerialPort = require("serialport").SerialPort;

var app = module.exports = express.createServer();

var server = http.createServer(function (req, res) {
  fs.readFile('./index.html', function(error, data) {
    res.writeHead(200, { 'Content-Type': 'text/html' });
    res.end(data, 'utf-8');
  });
}).listen(3000, "127.0.0.1");
console.log('Server running at http://127.0.0.1:3000/');

var io = require('socket.io').listen(app);

var serialport = new SerialPort("COM11"); // replace this address with your port address
serialport.on('open', function(){
io.sockets.on('connection', function (socket) {
  socket.on('data', function (data) {
    //console.log('Received PING. Sending PONG..');
    socket.emit('data', { text: 'data' });
  });
 // socket.on('data', function (data) {
   // console.log('Received data!');
  //});
  //setInterval(function() {
    //console.log('Sending PING to client..');
   // socket.emit('ping', { text: 'PING' });
 // }, 10000);
//});
