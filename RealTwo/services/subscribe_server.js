/**
 * Created by mypc on 11/26/2016.
 */

var UDP_PORT = require('../config/config').SubscribeServerPort;
var dgram = require('dgram');
var server = dgram.createSocket('udp4');
var mongoose = require('mongoose');
var UDP_HOST = require('../config/config').edgeIP;

server.on('listening', function () {
    var address = server.address();
    console.log('UDP Subscriber Server listening on ' + address.address + ":" + address.port);
});


server.on('message', function (message, remote) {
    console.log(":Subscriber Details:", remote.address + ':' + remote.port + ' - ' + message);
    //var topicID = getTopicId(message);
    var topicID = JSON.parse(JSON.stringify(message)).data[0];

    //find and save to topics collection in Mongo//
    findTopic(topicID, remote);


});

server.on("error", function (err) {
    console.log("Error: " + err);
});

server.bind(UDP_PORT, UDP_HOST);



function findTopic(topicID, remote) {
    try {
        mongoose.connection.collection('topics').find({"topicID": JSON.stringify(topicID)},
            {
                "publisher": 1,
                "_id": 0
            }).toArray(function (err, result) {
            if (err) {
                return err;
            }
            else {
                if (result != null && result.length != 0) {
                    registerSubscriber(topicID, remote);
                }
            }
        });
    }
    catch (e) {
        console.log("error in find");
    }

}

function registerSubscriber(topicID, remote) {
    mongoose.connection.collection('topics').updateOne(
        {"topicID": JSON.stringify(topicID)},
        { $push: {"subscribers": { "subscriber": remote.address + ":" + remote.port }}}
        , function (err, body) {
            if (err) {
                return err;
            }
            console.log("successfully subscribed ip to  the topic :", remote.address, topicID);
        });


}

