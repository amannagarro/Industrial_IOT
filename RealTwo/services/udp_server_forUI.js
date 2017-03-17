/**
 * Created by mypc on 11/23/2016.
 */
/**
 * Created by mypc on 11/23/2016.
 */
/*var PORT = 48570;
 var IP = '192.168.2.4';//2.4*/
/*var message = new Buffer('d');*/


module.exports.sendMessage = function (ip, port, message, boilerName, res, url_measures) {
    console.log("came in message");
    console.log("ip:", ip);
    var msg = new Buffer(message);
    var dgram = require('dgram');
    var client = dgram.createSocket('udp4');
    var mongoose = require('mongoose');

    var UDP_PORT = require('../config/config').UDPServerUIPort;
    var UDP_HOST = require('../config/config').edgeIP;
    var server = dgram.createSocket('udp4');
    server.bind(UDP_PORT, UDP_HOST);

    client.send(msg, 0, msg.length, port, ip, function (err, bytes) {
        if (err)
            throw err;

        if (url_measures.toLowerCase().startsWith("g")) {
            console.log('UDP message sent to ' + ip + ':' + port);
        }
        else {
            console.log('UDP message sent to ' + ip + ':' + port);
            client.close();
            server.close();
            res.send("1"); //OK
        }
    });


    server.on('message', function (message, remote) {
        console.log(remote.address + ':' + remote.port + ' - ' + message + "--" + message.length);

        var temp = JSON.stringify(JSON.parse(message[0]));
        console.log("message is", temp);

        try {
            mongoose.connection.collection('temperature').insert({
                "boilername": boilerName, "temperature": temp, "datetime": Date()
            }), function (err) {
                if (err) {
                    console.log("error while saving", err);
                    client.close();
                    server.close();
                    res.send(null);
                }
                res.send(temp);
                console.log("data saved to ");
            };
        }
        catch (e) {
            console.log("caught error");
        }
        client.close();
        server.close();
        res.send(temp);
    });

    client.on('error', function (err) {
        console.log("UDP receive err:", err);
    });
}

