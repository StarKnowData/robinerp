var map;  


function $(id){  
    return document.getElementById(id);  
}

function initMap() {
    map = new BMap.Map("mapBox"); // 创建地图实例   
    var point = new BMap.Point(116.404,39.915); // 创建点坐标   
    map.centerAndZoom(point,15); // 初始化地图，设置中心点坐标和地图级别  
}  

function initMapW() {
	var map = new BMap.Map("mapBox");            // 创建Map实例
	var point = new BMap.Point(116.404, 39.915);    // 创建点坐标
	map.centerAndZoom(point,15);                     // 初始化地图,设置中心点坐标和地图级别。
	map.enableScrollWheelZoom();                            //启用滚轮放大缩小 
}

function search(address) {
    if(map==null){
        initMap();
    }
    var local = new BMap.LocalSearch(map, {
        renderOptions:
        {
            map: map
        }
    });

    local.search(address);
}  

function getBus(){  
    var areaName = $("startPoint").value;  
    if(areaName=="")return;  
    if(map==null){  
        initMap();  
    }  
    var busline = new BMap.BusLineSearch(map);
    alert(busline);
    busline.getBusList(areaName);     
}

function getTrans()
{
var areaName = $("area").value;  
    if(areaName=="")return;  
var startPoint = $("startPoint").value;  
    if(startPoint=="")return; 

var transit = new BMap.TransitRoute(map, {
  renderOptions: {map: map}
});

transit.search(startPoint, areaName);

}

