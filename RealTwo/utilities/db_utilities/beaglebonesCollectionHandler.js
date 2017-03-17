/**
 * Created by mypc on 11/24/2016.
 */
/*
var mongoose = require('mongoose');

function fetchDataForUDP(db) {

    var cursor = db.collection('BeagleBones').find({"BeagleBoneName": BeagleBone2},
        {}).find({"ConnectedDevices.devicename": postLedRed}, {
            "ConnectedDevices.devicenumber": 1
        }, function (err, data) {
            if (err) {
                console.log(err);
                return;
            }
            console.log(data);
        }
    )
}


//Delete data from a MongoDB collection //
//Parameters: db,boilername,collection_name
function delete_document(db) {
    console.log("Called Delete");
    db.collection('temperature').removeOne({"boilername": ""}, function (err, results) {
            if (err) {
                console.log(err);
                return;
            }
            console.log("Deletion successsful");
        }
    )
}
*/
var mongoose = require('mongoose');
var udpServerForUI = require('../../services/udp_server_forUI');
var bbbHandler ={};

module.exports.fetchDataForUDP = function(boilerName, res, url) {
    var returnRes = null;
    var cursor = mongoose.connection.collection('BeagleBones').find({"BeagleBoneName": boilerName},
        {
            "_id": 0,
            "IP": 1,
            "Port": 1
        }).toArray(function (err, queryResult) {
            if (err) {
                console.log(err);
                return;
            }
            else {
                console.log("fetchDataForUDP", queryResult);
                findNested(boilerName, url, queryResult, boilerName, res);
            }
        }
    );
    console.log("inside returnRes data from udp:", returnRes);
}

function findNested(boilerName, url_measures, lastQuery, boilerName, res) {
    var cursor = mongoose.connection.collection('BeagleBones').find({'BeagleBoneName': boilerName},
        {
            "ConnectedDevices": 1
        }).toArray(function (err, data) {
        console.log('found data', data);

        if (data != null && data.length > 0) {
            var key = getdevicenum(data[0].ConnectedDevices, url_measures);
            //console.log('key', key);
            //console.log('lastquery:', lastQuery);
            udpServerForUI.sendMessage(lastQuery[0].IP, lastQuery[0].Port, key, boilerName, res, url_measures);
        }
        else {
            res.send(null);
        }
    });
}

// (Parameters required:The Array of connected devices,devicename)
function getdevicenum(p, url_measures) {
    for (var key in p) {
        if (p.hasOwnProperty(key)) {
            if (p[key].Measures == url_measures) {
                //console.log(key + " -> " + p[key].DeviceNumber); //+ p[key].devicename +
                return p[key].DeviceNumber;
            }
        }
    }
}
