/**
 * Created by mypc on 11/24/2016.
 * not using ; all mongo db interacctions to be placed here
 */

//Insert data to a MongoDB collection//
function insertDocument(db, callback) {
    db.collection('temperature').insertOne({
            "boilername": "boiler1", "temperature": "400 degree", "datetime": Date()
        },
        db.collection('temperature').insertMany([
            {"boilername": "boiler2", "temperature": "300 degree", "datetime": new Date()},
            {"boilername": "boiler2", "temperature": "400 degree", "datetime": new Date()}
        ]), function (err, result) {
            assert.equal(err, null);
            console.log('');
            callback();
        });
};


//Fetch data from MongoDB//
function fetchTempFromDB(db, callback) {

    var cursor = db.collection('temperature').find({"boilername": boilerName},
        {
            "temperature": 1,
            "boilername": 1,
            "datetime": 1,
            "_id": 0
        }).toArray(function (err, queryResult) {
        returnQueryResult = queryResult;
        callback();
    });
};



//unused:

//Delete data from a MongoDB collection //
/*
var deletedocument = function (db, callback) {
    console.log("Called Delete");
    db.collection('temperature').deleteMany({}, function (err, results) {
        callback();
    })
}

//Fetch data from MongoDB for a date range//
var fetchTempRangeFromDB = function (boilerName, startingDate, endingDate, callback) {
    var cursor = mongoose.connection.collection('temperature').find({
            "boilername": boilerName
            , "datetime": {$gte: Date(startingDate)}
            //, "datetime": {$lt: ISODate(endingDate)}
        },
        {
            "temperature": 1,
            "boilername": 1,
            "datetime": 1,
            "_id": 0
        }).toArray(function (err, queryResult) {
        returnQueryResult = queryResult;
        callback();
    });
};*/
