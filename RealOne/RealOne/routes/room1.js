var express = require('express');
var request = require('request');
var router = express.Router();

var edgeConnectionUrl =  "http://localhost:3002";

/* GET users listing. */
router.get('/', function (req, res, next) {
    res.render('room1', {name: "Boiler Room", title: "Boiler Room 1" });
});

router.get('/getTemp', function (req, res, next) {
    var edgeUrl = edgeConnectionUrl + "/getTemperature?boilerName="+req.query.data;
    console.log(edgeUrl);
    request({uri: edgeUrl, method: "GET"}, function (err, response, body) {
        if (err){
            console.log(err);
        }
        else
        {
            console.log("Response received:",body);
            res.send({temperatureValue: JSON.parse(body)});
        }
    });
});

router.get('/postLedGreen', function (req, res, body) {

    var edgeUrl = edgeConnectionUrl + "/postLedGreen?boilerName="+req.query.data;
    console.log(edgeUrl);
    request({uri: edgeUrl, method: "GET"}, function (err, response, body) {
        if (err){
            console.log(err);
        }
        else
        {
            console.log("Response received:",body);
        }
    });
});

router.get('/postLedRed', function (req, res, body) {

    var edgeUrl = edgeConnectionUrl + "/postLedRed?boilerName="+req.query.data;
    console.log(edgeUrl);
    request({uri: edgeUrl, method: "GET"}, function (err, response, body) {
        if (err){
            console.log(err);
        }
        else
        {
            console.log("Response received:",body);
        }
    });
});

router.get('/postLedBlue', function (req, res, body) {

    var edgeUrl = edgeConnectionUrl + "/postLedBlue?boilerName="+req.query.data;
    console.log(edgeUrl);
    request({uri: edgeUrl, method: "GET"}, function (err, response, body) {
        if (err){
            console.log(err);
        }
        else
        {
            console.log("Response received:",body);
        }
    });
});

router.get('/getTempGraph', function (req, res, body) {
    var edgeUrl = edgeConnectionUrl + "/getTempGraph?boilerName="+req.query.data;
    request({uri: edgeUrl, method: "GET"}, function (err, response, body) {
        if (err){
            console.log(err);
        }
        else
        {
            console.log("Response received:",body);

            var output=[];
            for(var i in JSON.parse(body))
            {
                output.push(((JSON.parse(body))[i])['temperature']);
            }
            res.send({temperatureRangeValue: output});
        }
    });
});

router.get('/getProximity', function (req, res, next) {
    var edgeUrl = edgeConnectionUrl + "/getProximity?boilerName="+req.query.data;
    console.log(edgeUrl);
    request({uri: edgeUrl, method: "GET"}, function (err, response, body) {
        if (err){
            console.log(err);
        }
        else
        {
            console.log("Response received:",body);
            res.send({ProximityValue: JSON.parse(body)});
        }
    });
});

router.get('/getConveyorData', function (req, res, next) {
    var edgeUrl = edgeConnectionUrl + "/getConveyorData?boilerName="+req.query.data;
    request({uri: edgeUrl, method: "GET"}, function (err, response, body) {
        if (err){
            console.log(err);
        }
        else
        {
            console.log("Response received:",body);
            res.send({EnergyConsumption: ((JSON.parse(body))[0])['conveyor_belt_on_time']});
        }
    });

});

module.exports = router;
