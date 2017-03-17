/**
 * Created by mypc on 11/24/2016.
 */
var chokidar = require('chokidar');
var path = require('path');
var ddlHandler = require('../utilities/db_utilities/ddlHandler');

console.log(__dirname);

var watcher = chokidar.watch(__dirname, {
    ignored: /[\/\\]\./, persistent: true
});

var log = console.log.bind(console);

watcher
    .on('add', function (path) {
        console.log("new file added");
        log('File', path, 'has been added');
    })
    .on('unlink', function (path) {
        log('File', path, 'has been removed');
    })
    .on('error', function (error) {
        log('Error happened', error);
    })

watcher.close();

require('chokidar').watch(__dirname, {ignored: /[\/\\]\./}).on('all', function (event, path) {
    if (event === "add") {
        if (checkifXML(path)) {
            // console.log("path:  ",path);
            ddlHandler.readDDL(path);
        }
    }
    else {
        console.log(event, path);
    }
});

function checkifXML(path) {
    var a = path.split('.').pop();
    if (a.toLowerCase() == "xml" ? true : false) {
        //console.log("is xml");
        return true;
    }
    else {
        //console.log("not an xml file");
        return false;
    }
}

/*
 .on('addDir', function (path) {
 log('Directory', path, 'has been added');
 })
 .on('change', function (path) {
 log('File', path, 'has been changed');
 })
 .on('unlinkDir', function (path) {
 log('Directory', path, 'has been removed');
 })

 .on('ready', function () {
 log('Initial scan complete. Ready for changes.');
 })
 .on('raw', function (event, path, details) {
 log('Raw event info:', event, path, details);
 })*/
