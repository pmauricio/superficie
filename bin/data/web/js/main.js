var socket;

var messageDiv;
var statusDiv;
var button;
var textField;

$(document).ready( function() {
	setupSocket();
	
	document.getElementById("brow").textContent = " " + BrowserDetect.browser + " "
		+ BrowserDetect.version +" " + BrowserDetect.OS +" ";

	messageDiv = document.getElementById("messages");
	statusDiv = document.getElementById("status");

	//setup message sending button
	message = document.getElementById("message");
	button = document.getElementById("button");

	// send the form when you press enter 
	// or when you press the button
	button.onclick = function(e){
		sendMessageForm();
	};
	$("#message").keyup(function(event){
    	if(event.keyCode == 13){
    		sendMessageForm()
    	}
    })

    


	function devOrientHandler(event) {
  var absolute = event.absolute;
  var alpha    = event.alpha;
  var beta     = event.beta;
  var gamma    = event.gamma;
socket.send(alpha+";"+beta+";"+gamma);
  
  // Do stuff with the new orientation data
}
if (window.DeviceOrientationEvent) {
  // Listen for the event and handle DeviceOrientationEvent object
  window.addEventListener('deviceorientation', devOrientHandler, false);
console.log('SIIIIIIIIIIII');
}else{  console.log('NAAAAOOO');}


});

// send value from text input
function sendMessageForm(){
	socket.send(message.value);
	message.value = "";
}



// setup web socket
function setupSocket(){

	// setup websocket
	// get_appropriate_ws_url is a nifty function by the libwebsockets people
	// it decides what the websocket url is based on the broswer url
	// e.g. https://mygreathost:9099 = wss://mygreathost:9099

	
	// setup!
	socket = new WebSocket( get_appropriate_ws_url());
	
	// open
	try {
		socket.onopen = function() {
			statusDiv.style.backgroundColor = "#40ff40";
			statusDiv.textContent = " websocket connection opened ";
		} 

		// received message
		socket.onmessage =function got_packet(msg) {
			messageDiv.innerHTML = msg.data + "<br />" + messageDiv.innerHTML;
		}

		socket.onclose = function(){
			statusDiv.style.backgroundColor = "#ff4040";
			statusDiv.textContent = " websocket connection CLOSED ";
		}
	} catch(exception) {
		alert('<p>Error' + exception);  
	}

}
	function devOrientHandler(event) {
  var absolute = event.absolute;
  var alpha    = event.alpha;
  var beta     = event.beta;
  var gamma    = event.gamma;
socket.send('a');
  
  // Do stuff with the new orientation data
}