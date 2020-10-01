var latitude = 0, longitude = 0, 
    userCenter = new google.maps.LatLng(latitude, longitude), map;

var locations = new Object();
locations["Halligan"] = [42.408121, -71.116193];
locations["SEC"] = [42.405903, -71.116702];
locations["Campus Center"] = [42.405594, -71.120017];
locations["Fletcher"] = [42.407984, -71.122318];
locations["574 / Sci-Tech"] = [42.403781, -71.114380];
locations["Davis Square"] = [42.396309, -71.122016];

var locationPreference = "";
var rentPreference = 0;

function loadLandingPage(){
    map = new google.maps.Map(document.getElementById("map"), {
    center: userCenter,
    zoom: 14
    });
    
    navigator.geolocation.getCurrentPosition(function(position){
        latitude = position.coords.latitude;
        longitude = position.coords.longitude;
        userCenter = new google.maps.LatLng(latitude, longitude);
        map.panTo(userCenter);
    });
    initialize_preference();
}

function initialize_preference() {
    preference = document.getElementById('slider');
    var header = document.createElement("P");
    preference.appendChild(header);
}

//TODO: prevent page from reloading when this form submits
function storeLocationPreference() {
    locationPreference = $("input[name=location]:checked").val();
    displayRentPrompt();
}

function displayRentPrompt(){
    $("#prompt").innerHTML = "Enter your preferred rent:";
    $("#locationForm").style.visibility = "hidden";
    //TODO: display rent entry
}