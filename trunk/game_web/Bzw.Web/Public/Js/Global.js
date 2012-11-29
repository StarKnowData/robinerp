

 String.prototype.trim = function(){
	return this.replace(/(^\s+)|(\s+$)/g, '');
}

function tokenKey(){
	var hex = new Array('0','1','2','3','4','5','6','7','8', '9','a','b','c','d','e','f');
	var t = '';
	for (var i = 0; i<32; i++){
		t += hex[Math.floor(Math.random() * 16)];
	}
	return t.toUpperCase();
}

function alertNull(e, m){
    if(e.value.trim().length == 0){
        alert(m);
        e.focus();
        return false;
    }
	return true;
}

/* 非负数 */
function alertNonNegativeNumber(e, m){
    var p = new RegExp(/^(0+|([1-9]{1}[\d]*))$/gi);
    if(!p.test(e.value)){
        alert(m);
        e.select();
        e.focus();
        return false;
    }
	return true;
}

/* 大于0的正整数 */
function alertNegativeNumber(e, m){
    var p = new RegExp(/^[1-9]{1}[\d]*$/gi);
    if(!p.test(e.value)){
        alert(m);
        e.select();
        e.focus();
        return false;
    }
	return true;
}

/* 非负浮点 */
function alertNonNegativeFloat(e, m){
    var p = new RegExp(/^\d+(\.\d+)?$/gi);
    if(!p.test(e.value)){
        alert(m);
        e.select();
        e.focus();
        return false;
    }
	return true;
}

/* check is match email */
function isEmail(vEMail)
{
	var regInvalid = new RegExp(/(@.*@)|(\.\.)|(@\.)|(\.@)|(^\.)/);
	var regValid = new RegExp(/^.+\@(\[?)[a-zA-Z0-9\-\.]+\.([a-zA-Z]{2,3}|[0-9]{1,3})(\]?)$/);
	return (!regInvalid.test(vEMail)&&regValid.test(vEMail));
}

/* check is match url */
function isUrl(vUrl)
{
    var regValid = new RegExp(/^http:\/\/[A-Za-z0-9]+\.[A-Za-z0-9]+[\/=\?%\-&_~`@[\]\':+!]*([^<>\"\"])*$/ig);
    return (regValid.test(vUrl));
}

/* check is date */
function isDate(date)
{
    //[\-\/] 2008-08-08 or 2008/08/08
    var regValid = new RegExp(/^((\d{2}(([02468][048])|([13579][26]))[\-\/]((((0?[13578])|(1[02]))[\-\/]((0?[1-9])|([1-2][0-9])|(3[01])))|(((0?[469])|(11))[\-\/]((0?[1-9])|([1-2][0-9])|(30)))|(0?2[\-\/]((0?[1-9])|([1-2][0-9])))))|(\d{2}(([02468][1235679])|([13579][01345789]))[\-\/]((((0?[13578])|(1[02]))[\-\/]((0?[1-9])|([1-2][0-9])|(3[01])))|(((0?[469])|(11))[\-\/]((0?[1-9])|([1-2][0-9])|(30)))|(0?2[\-\/]((0?[1-9])|(1[0-9])|(2[0-8]))))))$/);
    return (regValid.test(date));
    
    //[\-\/\s]? 2008-08-08 or 2008/08/08 or 2008.08.08 or 20080808
    //var regValid = new RegExp(/^((\d{2}(([02468][048])|([13579][26]))[\-\/\s]?((((0?[13578])|(1[02]))[\-\/\s]?((0?[1-9])|([1-2][0-9])|(3[01])))|(((0?[469])|(11))[\-\/\s]?((0?[1-9])|([1-2][0-9])|(30)))|(0?2[\-\/\s]?((0?[1-9])|([1-2][0-9])))))|(\d{2}(([02468][1235679])|([13579][01345789]))[\-\/\s]?((((0?[13578])|(1[02]))[\-\/\s]?((0?[1-9])|([1-2][0-9])|(3[01])))|(((0?[469])|(11))[\-\/\s]?((0?[1-9])|([1-2][0-9])|(30)))|(0?2[\-\/\s]?((0?[1-9])|(1[0-9])|(2[0-8]))))))$/);
    //return (regValid.test(date));
}

/* check is tel */
function isTel(tel)
{
    var regValidTel = new RegExp(/(^[0-9]{3,4}\-[0-9]{7,8}$)|(^[0-9]{7,8}$)|(^\([0-9]{3,4}\)[0-9]{3,8}$)|(^0{0,1}13[0-9]{9}$)/);
    var regValidMobile = new RegExp(/^(130|131|132|133|134|135|136|137|138|139|158|159)\d{8}$/);
    if (regValidTel.test(tel) | regValidMobile.test(tel)){
        return true;
    }else{
        return false;
    }
}

/* check is fax */
function isFax(tel)
{
    var regValidFax = new RegExp(/(^[0-9]{3,4}\-[0-9]{7,8}$)|(^[0-9]{7,8}$)|(^\([0-9]{3,4}\)[0-9]{3,8}$)|(^0{0,1}13[0-9]{9}$)/);
    if (regValidFax.test(tel)){
        return true;
    }else{
        return false;
    }
}

/* check is postalcode */
function isPostalcode(code)
{
    var regValidCode = new RegExp(/^[1-9]\d{5}$/);
    if (regValidCode.test(code)){
        return true;
    }else{
        return false;
    }
}

/* create a Ajax object */
function CreateAjax(){
	var oXmlHttp = null;
	if(window.XMLHttpRequest){
		oXmlHttp = new XMLHttpRequest();
	}else{
		try{
			oXmlHttp = new ActiveXObject('MSXML2.XMLHTTP.4.0');
		}catch(e){
			try{
				oXmlHttp = new ActiveXObject('MSXML2.XMLHTTP.3.0');
			}catch(e){
				try{
					oXmlHttp = new ActiveXObject('MSXML2.XMLHTTP.2.6');
				}catch(e){
					try{
						oXmlHttp = new ActiveXObject('MSXML2.XMLHTTP');
					}catch(e){
						try{
							oXmlHttp = new ActiveXObject('Microsoft.XMLHTTP');
						}catch(e){}
					}
				}
			}
		}
	}
	if(oXmlHttp == null){
		alert('The browser does not surport XMLHTTP.');
	}
	return oXmlHttp;
}

function CheckIsNull(o){
	return ("undefined" == typeof(o) || "unknown" == typeof(o) || null == o)
}

/* Ajax call a method or function of page(url) */
function AjaxCall(url, sync, request){
	var oXmlHttp = CreateAjax();
	var issync = !CheckIsNull(sync);
	var doc = CheckIsNull(request) ? '' : request;
	
	oXmlHttp.open('POST', url +'&token='+ token(), issync);
	oXmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
	oXmlHttp.send(doc);
	
	if(issync){
		//async call
		oXmlHttp.onreadystatechange = readyStateChanged;
	}else{
		//return result of sync call
		return oXmlHttp.responseText;
	}
	
	function token(){
		var hex = new Array('0','1','2','3','4','5','6','7','8', '9','a','b','c','d','e','f');
		var t = '';
		for (var i = 0; i<32; i++){
			t += hex[Math.floor(Math.random() * 16)];
		}
		return t.toUpperCase();
	}
	
	function readyStateChanged(){
		if (oXmlHttp.readyState == 4)
		{
			if (oXmlHttp.status != 0)
			{
				var result = oXmlHttp.responseText;
				//callback-function deal return result of async call
				sync(result);
				//cancel current's request
				oXmlHttp.abort();
			}
		}
	}
}
