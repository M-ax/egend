var dataLoop;

function sendDataToEgend(){
  var dat = roundToString(controller.getLStickY())
    + " " + roundToString(controller.getRStickX()) + " ";

  req = $.ajax({
    method: "POST",
    url: "egend",
    data: dat
  });

  dataLoop = setTimeout(sendDataToEgend, 50);
}

function roundToString(num){
  return parseFloat(Math.round(num * 100) / 100).toFixed(3);
}
