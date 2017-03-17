var express = require('express');
var router = express.Router();
var mongodb = require('mongodb');
var mongoose = require('mongoose');

//Global variable to get query data from MongoDB
global.returnQueryResult = null;
var udp_server = require('../services/mqtt_server');
var udp_client = require('../services/udp_server_forUI');
var ddlHandler = require('../utilities/db_utilities/ddlHandler');
var readDDLService = require('../DDL_files/readDDLService');
var subscriber_server = require('../services/subscribe_server');
var unsubscriber_server = require('../services/unsubscribe_server');
var bbbHandler = require('../utilities/db_utilities/beaglebonesCollectionHandler');
var temperature_analysis = require('../services/temperature_analysis_server');

//to create topics collection on start-up//This allows subscribers to subscribe//
var populate_topics = require('../seedFiles/populate_topics');

router.get('/', function (req, res, next) {
    //start udp server
    //read ddl server
    console.log("Inside Edge");
    res.render('index', {title: 'Express hain yeh!'});
});

router.get('/postLedRed', function (req, res) {
    boilerName = req.query.boilerName;
    bbbHandler.fetchDataForUDP(boilerName, res, "postLedRed");
});

router.get('/postLedGreen', function (req, res) {
    boilerName = req.query.boilerName;
    bbbHandler.fetchDataForUDP(boilerName, res, "postLedGreen");
});

router.get('/postLedBlue', function (req, res) {
    boilerName = req.query.boilerName;
    bbbHandler.fetchDataForUDP(boilerName, res, "postLedBlue");
});



//added for proximity start
router.get('/getProximity', function (req, res) {
    boilerName = req.query.boilerName;
    bbbHandler.fetchDataForUDP(boilerName, res, "getProximity");
});

//added for proximity end
router.get('/getTemperature', function (req, res) {
    //query to fetch sensor no,IP,PORT from DB ON BASIS OF BB/BOILER NAME
    boilerName = req.query.boilerName;
    console.log("boilerName:", boilerName);

    //fetch ip and port
    bbbHandler.fetchDataForUDP(boilerName, res, "getTemperature");
});

router.get('/getConveyorData', function (req, res) {
        console.log("Fetching conveyor data");
        fetchConveyorData(res);
        //res.send(returnQueryResult);
    }
);

//new
router.get('/getTempGraph', function (req, res) {
    boilerName = req.query.boilerName;
    console.log("boilerName:", boilerName);
    fetchTempGraph(boilerName, res);

});


//Fetch data from graph from MongoDB//
var fetchTempGraph = function (boilerName, res) {
    var cursor = mongoose.connection.collection('temperature_graph').find({"boilername": boilerName},
        {
            "temperature": 1,
            //"boilername": 1,
            //"recordeddate": 1,
            "_id": 0
        }).toArray(function (err, queryResult) {
        res.send(queryResult);
    });
};

//Fetch data from MongoDB//
function fetchConveyorData(res) {
    var cursor = mongoose.connection.collection('Conveyor').find({"conveyor_belt_on_time":10},
            {    "_id":0
                , "conveyor_belt_on_time":1

            }
        ) .toArray(function (err, queryResult) {
        //returnQueryResult = queryResult;
        res.send(queryResult);
    });
};


module.exports = router;


