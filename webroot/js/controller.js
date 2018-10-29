//Controller class, built to handle xbox one controller.
var controller = {
  gamepad: null,

  getLStickY: function(){
    if (controller.gamepad === null)
      return 0;
    return clampDeadZone(controller.gamepad.axes[1], 0.12);
  },
  getRStickY: function(){
    if (controller.gamepad === null)
      return 0;
    return clampDeadZone(controller.gamepad.axes[3], 0.05);
  },

  connected: function(ev){
    var gp = navigator.getGamepads()[ev.gamepad.index];
    if (gp.index != 0)
      return;

    console.log("Gamepad connected at index %d: %s. %d buttons, %d axes.",
      gp.index, gp.id,
      gp.buttons.length, gp.axes.length);

    controller.gamepad = gp;

    $("#connected").html("True");
  },
  disconnected: function(ev){
    if (ev.gamepad !== controller.gamepad)
      return;
    else {
      controller.gamepad = null;
      console.log("Gamepad disconnected.");

      $("#connected").html("False");

      //TODO: poll egend with no post to stop motors.
    }
  }
};

$(document).ready(function() {
  window.addEventListener("gamepadconnected", controller.connected);
  window.addEventListener("gamepaddisconnected", controller.disconnected);
});

function clampDeadZone(number, deadZone){
  if (number > -deadZone && number < deadZone)
    return 0;

  return number;
}
