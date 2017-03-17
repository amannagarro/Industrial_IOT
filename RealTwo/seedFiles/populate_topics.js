/**
 * Created by mypc on 11/26/2016.
 */
var mongoose = require('mongoose');

mongoose.connection.collection('topics').deleteMany({});
mongoose.connection.collection('topics').insertMany([
     { "topicID": "1","topicname": "temp_threshold", "publisher": null, "subscribers": [],"data":null }
    ,{ "topicID": "2","topicname": "proximity_achieved", "publisher": null, "subscribers": [],"data":null }
    ,{ "topicID": "3","topicname": "reserved1", "publisher": null, "subscribers": [],"data":null }
    ,{ "topicID": "4","topicname": "reserved2", "publisher": null, "subscribers": [],"data":null }
    ]);
