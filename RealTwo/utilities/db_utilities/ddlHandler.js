/**
 * Created by mypc on 11/24/2016.
 */
var fs = require("fs");
var xml2js = require('xml2js');
var exportObject = {};
var mongoose = require('mongoose');

exportObject.readDDL = function (fileURL) {
    console.log("read ddl", fileURL);
    //fetch file name
    fs.readFile(fileURL, function (err, data) {
        if (err) {
            console.log(err);
            return;
        }
        parseDDL(data)
    });
};

function parseDDL(data) {
    //xml logging
    console.log("parsing DDL");
    var parser = new xml2js.Parser({explicitArray: false});
    parser.parseString(data, function (err, result_to_use) {
        if (err) {
            console.log("Error reading from XML:" + error);
            return;
        }
        findBBBData(result_to_use, function () {
            deleteBBBData(result_to_use, function () {
                insertBBBData(result_to_use);
            });
        }, function () {
            insertBBBData(result_to_use);
        });
    });
}

function deleteBBBData(result_to_use, callback2) {
    console.log("Called Delete Record from DDL");
    mongoose.connection.collection('BeagleBones').removeMany({BeagleBoneName: result_to_use.DDL.BBB.Name},
        function (err, result) {
            if (err) {
                console.log(err);
                return;
            }
            else {
                callback2();
                //console.log("deletion request result", result);
                console.log("Deletion successsful");
            }
        }
    )
}

function insertBBBData(result_to_use) {
    // console.log("insert from DDl");
    //console.log("result to use: ", result_to_use);
    mongoose.connection.collection('BeagleBones').insertOne(
        {
            "BeagleBoneName": result_to_use.DDL.BBB.Name,
            "IP": result_to_use.DDL.BBB.IP,
            "Port": result_to_use.DDL.BBB.Port,
            "ConnectedDevices": result_to_use.DDL.BBB.ConnectedDevices.ConnectedDevice
        },
        function (err, result) {
            if (err) {
                console.log(err);
                return;
            }
            //console.log("after insert", result);
            console.log("Insert Status complete");
        }
    );
}

function findBBBData(result_to_use, callback1, callback2) {
    // console.log("XML Data::", Date.now() + "   \n", result_to_use.DDL.BBB);
    try {
        var cursor = mongoose.connection.collection('BeagleBones').find(
            {BeagleBoneName: {$eq: result_to_use.DDL.BBB.Name}}
        ).toArray(function (err, returnResult) {
            if (err) {
                console.log(err);
                return;
            }
            else {
                console.log('found record in data: ', returnResult.length);
                if (returnResult.length != null && returnResult.length != 0) {
                    callback1();
                }
                else {
                    callback2();
                }
            }
        });
    }
    catch (e) {
        console.log('error is:', e);
    }
}

module.exports = exportObject;
