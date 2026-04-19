////////////////////////////////////////////////////
// Client-Side Scripting
////////////////////////////////////////////////////

const userInput = document.getElementById('userInput');
const btnSubmit = document.getElementById('btn-submit');

window.onload = function() {
    const url = "/rfid-ready-to-read";
    rfidReady(url, "false");
    userInput.value = "";
    btnSubmit.disabled = true;
}

userInput.addEventListener('input',(e)=>{
    console.log(e.target.value);
    console.log((e.target.value).length);

    if ((e.target.value).length > 2) {
        btnSubmit.disabled = false;
    } else {
        btnSubmit.disabled = true;
    }
});

async function rfidReady(url, value) {
    try {
        const response = fetch(url, {
            method: 'POST', // Specify the method
            headers: {
                'Content-Type': 'text/plain' // Inform the server that the body is JSON
            },
            body: value
        }).then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
                return response.text(); // Parse the JSON response from the server
            })
        .then(data => {
            console.log(data); // Handle the successful response data
            const rfidReadySection = document.querySelector(".rfid-ready");
            
            if(value === "true") {
                const readerReadyText = document.getElementById("readerReadyText");
                rfidReadySection.classList.remove('d-none');
                readerReadyText.textContent = data;
            }
        });
    } catch (error) {
        console.error("Fetch Error: ", error);
    }
}

btnSubmit.addEventListener('click', () => {
    const url = "/rfid-ready-to-read";
    rfidReady(url, "true");
});