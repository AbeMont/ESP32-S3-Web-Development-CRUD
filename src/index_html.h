
const char index_html[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Web Development ESP32</title>
</head>
<body>
    <style>
        body {
            background-color: black;
            font-family: 'Courier New', Courier, monospace;
            color: lime;
            margin: 0;
        }

        h1 {
            font-weight: lighter;
            margin-bottom: 8px;
        }

        p {
            margin: 0;
            font-size: 32px;
        }

        span {
            font-size: 25px;
        }

        .cards {
            display: flex;
            justify-content: space-evenly;
        }

        .btn {
            background: none;
            border: 1px solid lime;
            color: lime;
            padding: 0.5rem 1rem;
            margin-top: 8px;
        }
    </style>
    <h1>Web Development C++ </h1>

    <div class="content">
        <button id="btn0" class="btn" onclick="postOperators()">Get Operators</button>
        <button id="btn1" class="btn" onclick="getSnakeData()">Get Snake Data</button>
        <button id="btn2" class="btn" onclick="postData()">Post Data</button>
        <button id="btn3" class="btn" onclick="getOperatorById(2)">Find Operator</button>
        <button id="btn4" class="btn" onclick="deleteOperatorbyId(3)">Delete Operator</button>
        <button id="btn4" class="btn" onclick="updateOperatorById(1)">Update Operator</button>
    </div>

    <script>
        ////////////////
        // GET Requests
        ///////////////

        async function getSnakeData() {
            console.log("Get Snake Data");

            const url = "/getSankeData";

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
                id: 4,
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
    </script>
</body>
</html>

)=====";