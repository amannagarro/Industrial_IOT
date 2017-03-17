/**
 * Created by mypc on 11/23/2016.
 */
var ip = require('ip');
var Configuration = {};

//Mongo DB URL
Configuration.databaseURL ='mongodb://127.0.0.1/local';
// 'mongodb://akashgore:gaurav123@ds159237.mlab.com:59237/iot_db';

//Local IP
Configuration.edgeIP = ip.address();

//Port numbers of all Servers//
Configuration.MQTTServerPort ="48569";
Configuration.SubscribeServerPort = "4444";
Configuration.UnsubscribeServerPort ="5555";
Configuration.TemperatureAnalysisServerPort ="6666";
Configuration.UDPServerUIPort ="3333";

console.log("My IP address is", ip.address());
module.exports = Configuration;
