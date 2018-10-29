var dataLoop = null;
var socketCon = null;

var loopDelay = 20;

function initConnection(){
  socketCon = new WebSocket("ws://" + window.location.hostname + ":8000/");

  socketCon.onopen = function () {
    console.log("Connected to websocket server.");
  };

  socketCon.onerror = function (error) {
    console.log('WebSocket Error ' + error);
  };

  socketCon.onmessage = function (e) {
    //console.log('Server: ' + e.data);
  };
}

function startDataLoop(){
  dataLoop = setInterval(sendDataToEgend, loopDelay);
}

function stopDataLoop(){
  clearInterval(dataLoop);
}

function sendDataToEgend(){
  if (socketCon === null){
    initConnection();
  }

  var dat = roundToString(controller.getLStickY())
    + " " + roundToString(-controller.getRStickY());

  socketCon.send(dat);
}

function roundToString(num){
  return parseFloat(Math.round(num * 100) / 100).toFixed(3);
}
