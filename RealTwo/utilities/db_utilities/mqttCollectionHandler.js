/**
 * Created by mypc on 11/26/2016.
 */
var mongoose = require('mongoose');
var mqttHandler={};

//UDP Handler & Send Message not required as its present in MQTT server.
// But we need to export this file anyways for storeConveyorData so might as well have these here too and remove from mqtt server.

module.exports.udpHandler=function(topicID,message) {
    console.log("Sending data to subscribers"+message);
    mongoose.connection.collection("topics").find({"topicID": JSON.stringify(topicID)},
        {
            "subscribers": 1,
            "_id": 0
        }).toArray(function (err, returnData) {
        //for each subscriber , send message
        if (returnData != null && returnData.length > 0 && returnData[0].subscribers != null && returnData[0].subscribers.length > 0)
        {
            var subList = returnData[0].subscribers;
            for (var data in subList) {
                //if (returnData.hasOwnProperty(key)) {
                    var array = subList[data].subscriber.split(":");
                    sendMessage(array[0], array[1], message);
                //}
            }
        }
    });
    //Store ConveyorData in DB for analytics
    storeConveyorData(topicID);
}

function storeConveyorData(topicID) {
    //Create new entry while sending ON request to LED (temp_threshold)
    if(topicID==1)
    {
    mongoose.connection.collection('Conveyor').insertOne({
        "boilername": "Boiler1"
        ,"conveyor_start_time": new Date()
        ,"conveyor_end_time": null
        , "conveyor_belt_on_time" : null
    })
    }
    //Update end time while sending OFF request to LED(proximity_acheived)
    if(topicID==2){
        mongoose.connection.collection('Conveyor').updateOne(
            {"boilername": "Boiler1", "conveyor_end_time": null},
            {
                $set: {
                    "conveyor_end_time": new Date(),
                    "conveyor_belt_on_time": "10"
                }
            }
        )
    }
}


function sendMessage(ip, port, message) {
    var msg = new Buffer(JSON.stringify(message));
    var dgram = require('dgram');
    var client = dgram.createSocket('udp4');

    client.send(msg, 0, msg.length, port, ip, function (err, bytes) {
        if (err)
            throw err;
        console.log('UDP message sent to ' + ip + ':' + port);
    });
}
