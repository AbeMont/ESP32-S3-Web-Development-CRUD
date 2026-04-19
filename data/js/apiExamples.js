    ////////////////
    // GET Requests
    ///////////////

    async function getSnakeData() {
        console.log("Get Snake Data");

        const url = "/getSnakeData";

        try {
            const response = await fetch(url);
            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            const data = await response.json();
            console.log(data);
        } catch (error) {
            console.error("Fetch Error: ", error);
        }
    }

    async function postOperators() {
        console.log("Operators");

        const url = "/getOperators";

        try {
            const response = await fetch(url);
            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            const data = await response.json();
            console.log(data);
        } catch (error) {
            console.error("Fetch Error: ", error);
        }
    }

    async function getOperatorById(id) {
        console.log("Find Operator by id");

        const url = `getOperatorById?id=${id}`;

        try {
            const response = await fetch(url);
            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            const data = await response.json();
            console.log(data);
        } catch (error) {
            console.error("Fetch Error: ", error);
        }
    }

    async function getView() {
        const url = `login`;
        try {
            const response = await fetch(url);
            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            const data = await response.text();
            console.log(data);
            const el = document.getElementById('view-test');
            el.innerHTML = data;
            el.style.backgroundColor = 'green';
            el.style.color = 'white';
        } catch (error) {
            console.error("Fetch Error: ", error);
        }
    }
    //////////////////
    // Delete Request
    /////////////////

    async function deleteOperatorbyId(id) {
        const url = `deleteOperatorbyId?id=${id}`;

        try {
            const response = await fetch(url, {
                method: 'DELETE' // Specify the HTTP method
            });

            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            const data = await response.json();
            console.log(data);
        } catch (error) {
            console.error("Fetch Error: ", error);
        }
    }

    ///////////////
    // Post Request
    ///////////////

    async function postData() {
        const url = "/post-json-data";

        const dataToSend = {
            id: 5,
            name: 'Raiden',
            weapon: 'M4A1 Assault Rifle',
            metalGear: 'Metal Gear Ray'
        };

        fetch(url, {
            method: 'POST', // Specify the method
            headers: {
                'Content-Type': 'application/json' // Inform the server that the body is JSON
            },
            body: JSON.stringify(dataToSend) // Convert the JavaScript object to a JSON string
        })
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json(); // Parse the JSON response from the server
        })
        .then(data => {
            console.log('Success:', data); // Handle the successful response data
        })
        .catch(error => {
            console.error('Error:', error); // Handle any errors during the fetch operation
        });

    }

    //////////////
    // Put Request
    //////////////

    async function updateOperatorById(id) {
        const url = `updateOperatorById`;

        const dataToSend = {
            id: id,
            name: 'Lain',
            weapon: 'M4A1 Assault Rifle',
            metalGear: 'Protocol 9'
        };

        try {
            const response = await fetch(url, { 
                method: 'PUT',
                headers: {
                    'Content-Type': 'application/json' 
                },
                body: JSON.stringify(dataToSend)
            });
            if (!response.ok) {
                throw new Error(`HTTP error! status: ${response.status}`);
            }
            const data = await response.json();
            console.log(data);
        } catch (error) {
            console.error("Fetch Error: ", error);
        }
    }