/* global google */
/* global _ */
/**
 * scripts.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Global JavaScript.
 */

// Google Map
var map;

// markers for map
var markers = [];

// info window
var info = new google.maps.InfoWindow();

// Выполнить, когда DOM полностью загружен
$(function() {

    // styles for map
    // https://developers.google.com/maps/documentation/javascript/styling
    var styles = [

        // hide Google's labels
        {
            featureType: "all",
            elementType: "labels",
            stylers: [
                {visibility: "off"}
            ]
        },

        // hide roads
        {
            featureType: "road",
            elementType: "geometry",
            stylers: [
                {visibility: "off"}
            ]
        }

    ];

    // options for map
    // https://developers.google.com/maps/documentation/javascript/reference#MapOptions
    var options = {
        center: {lat: 41.3184, lng: -72.9318},
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 20,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true
    };

    // Получить узел DOM, в котором будет создан экземпляр карты
    var canvas = $("#map-canvas").get(0);

    // копировать map
    map = new google.maps.Map(canvas, options);

    // configure UI once Google Map is idle (i.e., loaded)
    google.maps.event.addListenerOnce(map, "idle", configure);

});

/**
 * Adds marker for place to map.
 */
function addMarker(place)
{
    var myLatlng = new google.maps.LatLng(place.latitude, place.longitude);
    
    var marker = new MarkerWithLabel({
        position: myLatlng,
        map: map,
        draggable: false,
        animation: google.maps.Animation.DROP,
        labelContent: place.place_name + ", " + place.admin_name1,
        labelAnchor: new google.maps.Point(1, 2),
        labelClass: "labels",
        labelStyle: {opacity: 0.8},
        labelInBackground: true,
        labelVisible: true,
        clickable: true,
        zIndex: 11
    });
    
    google.maps.event.addListener(marker, "click", function() { loadInfoWindow(place, marker) });
    
    // додати маркер до масиву глобальних маркерів
    markers.push(marker);
}
   
/**
 * Configures application.
 */
function configure()
{
    // Обновить интерфейс после перетаскивания карты
    google.maps.event.addListener(map, "dragend", function() {
        update();
    });

    // Обновить интерфейс после изменения уровня масштабирования
    google.maps.event.addListener(map, "zoom_changed", function() {
        update();
    });

    // Удалять маркеры при перетаскивании
    google.maps.event.addListener(map, "dragstart", function() {
        removeMarkers();
    });

    // configure typeahead
    // https://github.com/twitter/typeahead.js/blob/master/doc/jquery_typeahead.md
    $("#q").typeahead({
        autoselect: true,
        highlight: true,
        minLength: 1
    },
    {
        source: search,
        templates: {
            empty: "no places found yet",
            suggestion: _.template("<p><%- place_name %>, <%- admin_name1 %>, <%- postal_code %></p> ")
        }
    });

    // re-center map after place is selected from drop-down
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {

        // ensure coordinates are numbers
        var latitude = (_.isNumber(suggestion.latitude)) ? suggestion.latitude : parseFloat(suggestion.latitude);
        var longitude = (_.isNumber(suggestion.longitude)) ? suggestion.longitude : parseFloat(suggestion.longitude);

        // set map's center
        map.setCenter({lat: latitude, lng: longitude});

        // update UI
        update();
    });

    // hide info window when text box has focus
    $("#q").focus(function(eventData) {
        hideInfo();
    });

    // re-enable ctrl- and right-clicking (and thus Inspect Element) on Google Map
    // https://chrome.google.com/webstore/detail/allow-right-click/hompjdfbfmmmgflfjdlnkohcplmboaeo?hl=en
    document.addEventListener("contextmenu", function(event) {
        event.returnValue = true; 
        event.stopPropagation && event.stopPropagation(); 
        event.cancelBubble && event.cancelBubble();
    }, true);

    // update UI
    update();

    // give focus to text box
    $("#q").focus();
}

/**
 * Hides info window.
 */
function hideInfo()
{
    info.close();
}

function htmlInfoWindow(data)
{
    var ul = "<ul>";

    var template = _.template("<li><a href='<%- link %>' target='_blank'><%- title %></a></li>");

    var len_data = data.length;
    for (var i = 0; i < len_data; i++)
    {
        ul += template({
            link: data[i].link,
            title: data[i].title
        }); 
    }
    
    ul += "</ul>";

    return ul;
}

function loadInfoWindow(place, marker)
{
    showInfo(marker);

    $.getJSON("articles.php", "geo=" + place.postal_code)
    .done(function(data, textStatus, jqXHR) 
    {
        // Якщо новини немає 
    	if (data.length === 0)
    	{
    	    $.getJSON("articles.php", "geo=" + place.place_name)
                .done(function(data, textStatus, jqXHR) 
                {
                    if (data.length === 0)
                	{
                	    showInfo(marker, "No news for this area.");
                	}
                });
    	}
        else
        {
            ul = htmlInfoWindow(data);
            showInfo(marker, ul);
        }
    });
}

/**
 * Removes markers from map.
 */
function removeMarkers()
{
    // Ітерації через глобальні макети маркерів
    var len_markers = markers.length;
    for (var i = 0; i < len_markers; i++)
    {
        // Видалити маркер з карти
        markers[i].setMap(null);
    }
    markers.length = 0;
}

/**
 * Searches database for typeahead's suggestions.
 */
function search(query, cb)
{
    // get places matching query (asynchronously)
    var parameters = {
        geo: query
    };
    $.getJSON("search.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // call typeahead's callback with search results (i.e., places)
        cb(data);
    })
    .fail(function(jqXHR, textStatus, errorThrown) {

        // log error to browser's console
        console.log(errorThrown.toString());
    });
}

/**
 * Shows info window at marker with content.
 */
function showInfo(marker, content)
{
    // start div
    var div = "<div id='info'>";
    if (typeof(content) === "undefined")
    {
        // http://www.ajaxload.info/
        div += "<img alt='loading' src='img/ajax-loader.gif'/>";
    }
    else
    {
        div += content;
    }

    // end div
    div += "</div>";

    // set info window's content
    info.setContent(div);

    // open info window (if not already open)
    info.open(map, marker);
}

/**
 * Updates UI's markers.
 */
function update() 
{
    // get map's bounds
    var bounds = map.getBounds();
    var ne = bounds.getNorthEast();
    var sw = bounds.getSouthWest();

    // get places within bounds (asynchronously)
    var parameters = {
        ne: ne.lat() + "," + ne.lng(),
        q: $("#q").val(),
        sw: sw.lat() + "," + sw.lng()
    };
    $.getJSON("update.php", parameters)
    .done(function(data, textStatus, jqXHR) {

        // remove old markers from map
        removeMarkers();

        // add new markers to map
        for (var i = 0; i < data.length; i++)
        {
            addMarker(data[i]);
        }
     })
     .fail(function(jqXHR, textStatus, errorThrown) {

         // log error to browser's console
         console.log(errorThrown.toString());
     });
}