
const char index_html[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Web Development ESP32</title>
    <link rel="stylesheet" type="text/css" href="/css/bootstrap.min.css">
</head>
<style>
    .spinner-border {
        --bs-spinner-width: 6rem;
        --bs-spinner-height: 6rem;
        --bs-spinner-border-width: 0.5rem;
        margin: auto;
        display: flex;
    }
</style>
<body>
    <div class="container">
        <div class="row">
            <div class="col-12">
                <h1 class="my-4">Web Development C++ </h1>
                <p id="rfid"></p>
                <p id="userName"></p>
            </div>
        </div>
        <div id="main-content">
            <div id="login-container">
                <div class="card w-100 mb-3">
                    <h3 class="card-header bg-success" style="color: #fff;">Please enter name</h3>
                    <div class="card-body">
                        <!-- <p class="card-text">Then Login using card</p> -->
                        <input id="userInput" class="form-control" type="text" placeholder="Name" aria-label="User Name">
                        <button id="btn-submit" type="button" class="btn btn-primary mt-3" disabled>Submit</button>
                    </div>
                </div>
                <div class="rfid-ready text-center d-none">
                    <h3 id="readerReadyText" class="card-text"></h3>
                    <div class="d-flex justify-content-center">
                        <div class="spinner-grow text-primary" role="status">
                        <span class="visually-hidden">Loading...</span>
                        </div>
                        <div class="spinner-grow text-secondary" role="status">
                        <span class="visually-hidden">Loading...</span>
                        </div>
                        <div class="spinner-grow text-success" role="status">
                        <span class="visually-hidden">Loading...</span>
                        </div>
                        <div class="spinner-grow text-danger" role="status">
                        <span class="visually-hidden">Loading...</span>
                        </div>
                        <div class="spinner-grow text-warning" role="status">
                        <span class="visually-hidden">Loading...</span>
                        </div>
                        <div class="spinner-grow text-info" role="status">
                        <span class="visually-hidden">Loading...</span>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>

    <script src="/js/bootstrap.min.js"></script>
    <script src="/js/customEvents.js"></script>
    <script src="/js/apiExamples.js"></script>
    <script src="/js/login.js"></script>
</body>
</html>

)=====";