// 163 AJAX Tab 
// update 2006.10.18
// 澧炲姞榧犳爣寤惰繜鎰熷簲鐗规€с€?
// update 2006.10.8
// A 鏍囩 href 灞炴€у皢淇濇寔鍘熸湁HTML鍔熻兘銆傚鍔爑rn灞炴€т负AJAX Load 璺緞銆?
// update 2006.10.11
// 淇IE5.0 undefined 鏈畾涔夐敊璇紝澧炲姞鑴氭湰閿欒灞忚斀
var Browser = new Object();
Browser.isMozilla = (typeof document.implementation != 'undefined') && (typeof document.implementation.createDocument != 'undefined') && (typeof HTMLDocument!='undefined');
Browser.isIE = window.ActiveXObject ? true : false;
Browser.isFirefox = (navigator.userAgent.toLowerCase().indexOf("firefox")!=-1);
Browser.isOpera = (navigator.userAgent.toLowerCase().indexOf("opera")!=-1);
if (Browser.isFirefox) { // entend Event Mod for FireFox
	extendEventObject();
}
function extendEventObject() {
	Event.prototype.__defineGetter__("srcElement", function () {
		var node = this.target;
		while (node.nodeType != 1) node = node.parentNode;
		return node;
	});

	Event.prototype.__defineGetter__("fromElement", function () {
		var node;
		if (this.type == "mouseover")
			node = this.relatedTarget;
		else if (this.type == "mouseout")
			node = this.target;
		if (!node) return;
		while (node.nodeType != 1) node = node.parentNode;
		return node;
	});

	Event.prototype.__defineGetter__("toElement", function () {
		var node;
		if (this.type == "mouseout")
			node = this.relatedTarget;
		else if (this.type == "mouseover")
			node = this.target;
		if (!node) return;
		while (node.nodeType != 1) node = node.parentNode;
		return node;
	});
}
function IsChild(cNode,pNode){
	while(cNode!=null){
		cNode=cNode.parentNode;
		if(cNode==pNode) return true; 
	}
	return false;
}

var ajccache=new Object();
var waitInterval;
var tempref;
var MouseDelayTime=150;//榧犳爣鎰熷簲寤惰繜300姣
function getTBprefixName(str,sta){
	if(str.indexOf("active")!=-1 || str.indexOf("normal")!=-1) str=str.substr(6);
		else if(str.indexOf("over")!=-1) str=str.substr(4);
			else str="";
	return sta+str;
}
function startajaxtabs(){
    
	for(var i=0;i<arguments.length;i++)
	{
		var ulobj=_gObj(arguments[i]);
			ulist=ulobj.getElementsByTagName("li");		
			for(var j=0;j<ulist.length;j++)
			{
				var thelist=ulist[j];
				if(typeof thelist.getElementsByTagName("a")[0]=='undefined') continue;
				if(thelist.parentNode.parentNode!=ulobj) continue;//鍙湁绗竴灞俵i鏈夋晥 fixed 2006.9.29
				var ulistlink=thelist.getElementsByTagName("a")[0];
				var ulistlinkurl=ulistlink.getAttribute("urn");
				var ulistlinktarget=ulistlink.getAttribute("rel");
				var ulistlinkleft=ulistlink.getAttribute("left");
					
				thelist.setActive=function(bactive){
					if(bactive){
						this.status="active";
						this.className=getTBprefixName(this.className,"active");
					}else{
						this.status="normal";
						this.className=getTBprefixName(this.className,"normal");
					}
				}
				thelist.LoadTab=function(){
					this.setActive(true);
					this.parentNode.parentNode.activetab.setActive(false);
					this.parentNode.parentNode.activetab=this;					
					var ulistlink=this.getElementsByTagName("a")[0];
					if(ulistlink.getAttribute("left")) _gObj(ulistlink.getAttribute("rel")).style.left=ulistlink.getAttribute("left");
					loadAJAXTab(ulistlink.getAttribute("urn"),ulistlink.getAttribute("rel"));
				}
				thelist.onclick=function(aEvent){
					var myEvent = window.event ? window.event : aEvent;
					var fm=myEvent.fromElement;
					if(IsChild(fm,this) || fm==this) return;//杩囨护瀛愬厓绱爀vent
					if(this.status=="active") return;
					tempref=this;
					clearTimeout(waitInterval);
					waitInterval=window.setTimeout("tempref.LoadTab();",MouseDelayTime);
				}

				thelist.onmouseout=function(aEvent){
					var myEvent = window.event ? window.event : aEvent;
					var em=myEvent.toElement;
					if(IsChild(em,this) || em==this) return; //杩囨护瀛愬厓绱爀vent
					if(this.status=="active") return;
					clearTimeout(waitInterval);
				}
                if(ulistlinkurl.indexOf("#default")!=-1){
					thelist.setActive(true);
					ulobj.activetab=thelist;
					ajccache[ulistlinkurl]=_gObj(ulistlinktarget).innerHTML;
				}else{
					thelist.setActive(false);
				}
		}
		if(ulobj.activetab==null) ulobj.activetab=ulist[0];
		
	}
}

function getXmlhttp()
{
	var http_request;
	if(window.XMLHttpRequest) { 
		http_request = new XMLHttpRequest();
		if (http_request.overrideMimeType) {
			http_request.overrideMimeType("text/xml");
		}
	}
	else if (window.ActiveXObject) { 
		try {
			http_request = new ActiveXObject("Msxml2.XMLHTTP");
		} catch (e) {
			try {
				http_request = new ActiveXObject("Microsoft.XMLHTTP");
			} catch (e) {}
		}
	}
	if (!http_request) { 
		window.alert("can't create XMLHttpRequest object.");
		return null;
	}	
	return http_request;
}

function loadAJAXTab(url,contentid){
    var ocontent=_gObj(contentid);
	AlertDIV(contentid);
	if(ajccache[url]==null) {
		var xhttp=getXmlhttp();		
			xhttp.onreadystatechange=function(){
				if(xhttp.readyState == 4 && (xhttp.status==200 || window.location.href.indexOf("http")==-1)) // && (xhttp.status==200 || window.location.href.indexOf("http")==-1)
				{	
					ocontent.innerHTML=xhttp.responseText;
					ajccache[url]=ocontent.innerHTML;
				}
			}
		xhttp.open("GET",url,true);
		xhttp.send(null);
	}else{
		ocontent.innerHTML=ajccache[url];
	}
}

function clearCache(url)
{
    ajccache[url]=null;
}
//window.onerror=function(){return true}
