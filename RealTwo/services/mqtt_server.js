// * Created by mypc on 11/9/2016.

var UDP_PORT = require('../config/config').MQTTServerPort;
var UDP_HOST = require('../config/config').edgeIP;

var dgram = require('dgram');
var server = dgram.createSocket('udp4');
var mongoose = require('mongoose');
var mqttHandler = require('../utilities/db_utilities/mqttCollectionHandler');

server.on('listening', function () {
    var address = server.address();
    console.log('UDP Server listening on ' + address.address + ":" + address.port);
});

server.on('message', function (message, remote) {
    console.log(":MQTT:", remote.address + ':' + remote.port + ' - ' + message + message.length);

    var topicID = getTopicId(message);
    var msg = getMessage(message);

    mqttHandler.udpHandler(topicID[0],msg[0]);
});

server.on("error", function (err) {
    console.log("Error: " + err);
});
server.bind(UDP_PORT, UDP_HOST);

//utility
function getMessage(message) {
    var index = message.indexOf(44);
    var output = [];
    if (index < message.length - 1) {
        output= message.subarray(index + 1, message.length);
    }
    for(var index in output)
    {
        output[index] =  output[index] - 48;
    }
    return output;
}

function getTopicId(message) {
    var index = message.indexOf(44);
    var stringData;
    var output = [];
    if (index >= 0)
        output =  message.subarray(0, index);

    for(var index in output)
    {
        output[index] =  output[index] - 48;
        //stringData  = stringData.toString() +  output[index].toString();
    }
    return output;

}





