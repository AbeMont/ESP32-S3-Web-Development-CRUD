const char mainMenu[] PROGMEM = R"=====(
<div class="mb-3">
    <div class="row">
        <div class="col-md-4">
            <button id="btn0" class="btn btn-primary w-100" onclick="postOperators()">Get Operators</button>
        </div>
        <div class="col-md-4">
            <button id="btn1" class="btn btn-primary w-100" onclick="getSnakeData()">Get Snake Data</button>
        </div>
        <div class="col-md-4">
            <button id="btn3" class="btn btn-primary w-100" onclick="getOperatorById(2)">Find Operator</button>
        </div>
    </div>
</div>
<div class="mb-3">
    <div class="row">
        <div class="col-md-4">
            <button id="btn2" class="btn btn-success w-100" onclick="postData()">Post Data</button>
        </div>
        <div class="col-md-4">
            <button id="btn4" class="btn btn-warning w-100" onclick="updateOperatorById(1)">Update Operator</button>
        </div>
        <div class="col-md-4">
            <button id="btn4" class="btn btn-danger w-100" onclick="deleteOperatorbyId(3)">Delete Operator</button>
        </div>
    </div>
</div>
<div class="row">
    <div class="col-md-4 offset-md-4">
        <button type="button" class="btn btn-primary w-100" data-bs-toggle="modal" data-bs-target="#exampleModal">
            Launch demo modal
        </button>
        <!-- Modal -->
        <div class="modal fade" id="exampleModal" tabindex="-1" aria-labelledby="exampleModalLabel" aria-hidden="true">
            <div class="modal-dialog">
                <div class="modal-content">
                <div class="modal-header">
                    <h1 class="modal-title fs-5" id="exampleModalLabel">Modal title</h1>
                    <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                </div>
                <div class="modal-body">
                    Operator Data can go here
                </div>
                <div class="modal-footer">
                    <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Close</button>
                    <button type="button" class="btn btn-primary">Save changes</button>
                </div>
                </div>
            </div>
        </div>
    </div>
    <div class="col-md-4">
        <button id="view-btn" class="btn btn-success w-100" onclick="getView()">Get View</button>
    </div>
</div>

<div id="view-test"></div>

)=====";