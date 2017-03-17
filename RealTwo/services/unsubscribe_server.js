/**
 * Created by mypc on 11/26/2016.
 */
/**
 * Created by mypc on 11/26/2016.
 */

var UDP_PORT = require('../config/config').UnsubscribeServerPort;
var dgram = require('dgram');
var server = dgram.createSocket('udp4');
var mongoose = require('mongoose');
var UDP_HOST = require('../config/config').edgeIP;

server.on('listening', function () {
    var address = server.address();
    console.log('UDP unsubscriber Server listening on ' + address.address + ":" + address.port);
});


server.on('message', function (message, remote) {
    console.log(":Unsubscriber Details:", remote.address + ':' + remote.port + ' - ' + message);
    //var topicID = getTopicId(message);
    var topicID = JSON.parse(JSON.stringify(message)).data[0];

    //find and un-subscribe to topics collection in Mongo//
    findTopic(topicID, remote);


});

server.on("error", function (err) {
    console.log("Error: " + err);
});

server.bind(UDP_PORT, UDP_HOST);

//utility not used here?
function getMessage(message) {
    var index = message.indexOf(44);
    if (index < message.length - 1) {
        return message.subarray(index + 1, message.length);
    }
}

function getTopicId(message) {
    var index = message.indexOf(44);
    if (index >= 0)
        return message.subarray(0, index);
    return new Uint8Array(0);
}

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
                    deregisterSubscriber(topicID, remote);
                }
            }
        });
    }
    catch (e) {
        console.log("error in find");
    }

}

//
function deregisterSubscriber(topicID, remote) {

    mongoose.connection.collection('topics').updateOne(
        {"topicID": JSON.stringify(topicID)},
        {$pull: {"subscribers": {"subscriber": {$regex: remote.address}}}}
        , function (err, body) {
            if (err) {
                return err;
            }
            console.log("Successfully un-subscribed ip from the topic :", remote.address, topicID);
        });
}

