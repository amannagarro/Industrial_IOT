/**
 * Created by mypc on 11/27/2016.
 */
/**
 * Created by mypc on 11/26/2016.
 */
/**
 * Created by mypc on 11/26/2016.
 */

var UDP_PORT =  require('../config/config').TemperatureAnalysisServerPort;
var dgram = require('dgram');
var server = dgram.createSocket('udp4');
var mongoose = require('mongoose');
var UDP_HOST = require('../config/config').edgeIP;

server.on('listening', function () {
    var address = server.address();
    console.log('UDP temperature_analysis server listening on ' + address.address + ":" + address.port);
});

server.on('message', function (message, remote) {
    console.log(":Temperature received from :", remote.address + ':' + remote.port + ' as - ' + message);
    var msg = JSON.parse(JSON.stringify(message)).data[0];

    //call function to insert temperature into collection temperature_graph//
    temperature_graph(msg);
    console.log("Temperature successfully inserted into collection temperature_graph");
});

server.on("error", function (err) {
    console.log("Error: " + err);
});

server.bind(UDP_PORT, UDP_HOST);

// function to store temperature into collection temperature_graph
function temperature_graph(msg) {
    mongoose.connection.collection("temperature_graph").insertOne({
        "boilername":"Boiler1"
        ,"temperature": msg
        ,"recordeddate": new Date()

    }), function (err, result) {
        if (err) {
            console.log(err);
            return;
        }
    }
}

