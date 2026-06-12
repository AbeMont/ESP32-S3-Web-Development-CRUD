var rfid = new EventSource('/rfidEvent');

//////////////////////////
// INITIALIZE RFID EVENTS
//////////////////////////

// The open event fires when a connection to an event source is opened.
rfid.addEventListener('open', function(e) {
    console.log("Open RFID Custom Events");
}, false);

rfid.addEventListener('error', function(e) {
    if (e.target.readyState != EventSource.OPEN) {
        console.log("Events Disconnected");
    }
}, false);

// This message comes from rfid.onConnect([](AsyncEventSourceClient
rfid.addEventListener('message', function(e) {
    console.log("message", e.data);
}, false);

rfid.addEventListener('rfidUID', function(e) {
    const rfid = document.getElementById("rfid");
    rfid.innerHTML = `RFID: ${e.data}`;
    console.log("RFID Code: ", e.data);
}, false);

rfid.addEventListener('loadLoggedIn', function(e) {
    const mainContent = document.getElementById("main-content");
    const userInput = document.getElementById("userInput").value;
    const userName = document.getElementById("userName");

    mainContent.innerHTML = `
    <div class="spinner-border text-success" role="status">
        <span class="visually-hidden">Loading...</span>
    </div>`;

    setTimeout(()=>{
        userName.innerHTML = `<h3> Welcome! ${userInput} </h3>`;
        mainContent.innerHTML = e.data;
    },4000);

}, false);