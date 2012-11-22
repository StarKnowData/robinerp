var etwserverurl='http://217.16.1.99/';
var etwgotopageIp='193.34.131.153';
var etw_server_url='http://www.etwinternational.fr';
var topjs='chat/top/fr.js';
var dragjs='chat/top/dragDiv.js';
var favorite_msg="Fail,Add to favorite fails, please use Ctrl D";
var support_javascript="Votre navigateur ne supporte pas Javascript";
var skype_msg="Veuillez cliquer ok si vous disposez de Skype et d'un compte Skype, sinon veuillez cliquer sur Annuler";
var msn_msg="Veuillez cliquer ok si vous disposez de MSN et d'un compte MSN, sinon veuillez cliquer sur Annuler";
var pdf_msg="Adobe Reader est nécessaire pour lire ce document\n\rSi vous désirez ouvrir ce document avec Adobe Reader, veuillez cliquer sur 'confirmer'\n\rSi vous ne voulez pas ouvrir ce document maintenant ou que vous ne disposez pas d'Adobe Reader, veuillez cliquer sur 'annuler'";
var mail_msg="Microsoft Outlook est nécessaire pour envoyer un email\n\rSi vous avez un compte Outlook, veuillez cliquer sur 'confirmer'\n\rSinon, veuillez cliquer sur 'annuler' et contacter nous via le  formulaire de feedback";

var jsq_url='http://jsq.etwun.com:8080';
var tmp_url_base=window.location.host;
var etwObj=new Object();
etwObj.state=true;
function showflowdiv(divid,width,height,tempurl)
{ 
	var parentob=document.getElementById(divid);
	if(width==undefined){width=460;}
	if(height==undefined){height=410;} 
	etwObj.width=width; etwObj.height=height; 
	if(etwObj.state){
		var i=0; var j=0; var div=document.createElement("div");  	var xmlhttp; 
		function createxmlhttp(){
			if(window.ActiveXObject){
				xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
				}else{
					xmlhttp=new XMLHttpRequest()}
					} 
					createxmlhttp(); 
					xmlhttp.open("GET",tempurl,true); 
					xmlhttp.onreadystatechange=function() { 
					if(xmlhttp.readyState==4){
						if(xmlhttp.status==200)	{ 
						etwObj.string=xmlhttp.responseText; div.innerHTML=etwObj.string;
						}}};
						xmlhttp.send(null);
						var rollstartHeight=document.documentElement.scrollTop; etwObj.rollendHeight=parentob.getBoundingClientRect().top+document.documentElement.scrollTop;div.style.cssText="display:none;height:0px; width:"+etwObj.width+"px;overflow:hidden;";div.setAttribute("id","etwshowlayer");parentob.appendChild(div);etwObj.show_time_action=setInterval(show_div_slowly,1);etwObj.show_time_action;etwObj.state=false;}else{i=etwObj.height;j=0;var div=document.getElementById("etwshowlayer");etwObj.hiddendiv=setInterval(hidden_div_slowly,1);hidden_div_slowly;etwObj.state=true;} 
function show_div_slowly(){j=j+1;i=i+j;if(document.documentElement.scrollTop<=etwObj.rollendHeight){document.documentElement.scrollTop=rollstartHeight+i;}if(i<=etwObj.height){div.style.cssText="height:"+i+"px;width:"+etwObj.width+"px;overflow:hidden; display:block;"}else{window.clearInterval(etwObj.show_time_action);}} 
function hidden_div_slowly(){j=j+1;i=i-j;if(i>=0){div.style.cssText="height:"+i+"px;width:"+etwObj.width+"px;overflow:hidden; "}else{clearInterval(etwObj.hiddendiv);i=0;j=0;div.parentNode.removeChild(div);}}} 
function showopenwindow(url) {var iTop=(window.screen.height-500)/2; var iLeft=(window.screen.width-500)/2; window.open(url,"Detail","Scrollbars=no,Toolbar=no,Location=no,Direction=no,Resizeable=no,Width="+500+" ,Height="+500+",top="+iTop+",left="+iLeft);} 
function writejs(src,id){ 	var script=document.createElement('script'); script.setAttribute('src',src);  script.setAttribute('id',src);  document.body.appendChild(script); }
function write_top_js(){ writejs(etwserverurl+topjs,'settopjs');}
write_top_js();
writejs(etwserverurl+dragjs,'setdrag');
function showopenwindow(url) {
var iTop=(window.screen.height-500)/2;
var iLeft=(window.screen.width-500)/2;
window.open(url,"Detail","Scrollbars=no,Toolbar=no,Location=no,Direction=no,Resizeable=no,Width="+500+" ,Height="+500+",top="+iTop+",left="+iLeft);
}
function skype(user){if(confirm(skype_msg)){var userac="skype:"+user+"?call";window.open(userac)}}
function msn(user){if(confirm(msn_msg)){var userac="msnim:chat?contact="+user;window.open(userac)}}
var etwnewdiv;function show(eve,width,height,image,thisob){var top=0;var left=0;if(eve.pageY||eve.pageX){top = eve.pageY +10;left = eve.pageX +10;}else{left = event.clientX + document.body.scrollLeft+ document.documentElement.scrollLeft +10;top = event.clientY + document.body.scrollTop + document.documentElement.scrollTop + 10;}etwnewdiv=document.createElement("div");etwnewdiv.style.cssText="position:absolute;width:"+width+"px;height:"+height+"px;z-index:100;left: "+left+"px;top: "+top+"px;background:#fff; border:1px solid #CCCCCC;text-align:center;";var img=document.createElement("img");img.setAttribute("src",image);var imgwidth=width-2;var imgheight=height-2;img.style.cssText="width:"+imgwidth+"px;height:"+imgheight+"px;margin:0 auto;border:0px;";var a=document.createElement("a");a.setAttribute("href",thisob.parentNode.getAttribute("href"));a.appendChild(img);etwnewdiv.appendChild(a);document.body.appendChild(etwnewdiv);}function hide(){etwnewdiv.innerHTML="";document.body.removeChild(etwnewdiv)}
function gotopage(myurl){window.location.href=myurl.value}

function checkaddtofaver(url){var tempurl=jsq_url+"/query/doc.php?url="+url;var reiframe=document.createElement("iframe");reiframe.setAttribute("width",0);reiframe.setAttribute("height",0);reiframe.setAttribute("frameBorder",0);reiframe.setAttribute("scrolling","no");reiframe.setAttribute("src",tempurl);document.body.appendChild(reiframe);}

function AddFavorite(sURL, sTitle){checkaddtofaver(sURL);    try    {        window.external.addFavorite(sURL, sTitle);    }    catch (e)    {        try        {            window.sidebar.addPanel(sTitle, sURL, "");        }        catch (e)        {            alert(favorite_msg);        }    }}function SetHome(obj,vrl){ try{checkaddtofaver(vrl)}catch(err){}        try{                obj.style.behavior='url(#default#homepage)';obj.setHomePage(vrl);       }        catch(e){                if(window.netscape) {                        try {                                netscape.security.PrivilegeManager.enablePrivilege("UniversalXPConnect");                        }                        catch (e) {                                alert(support_javascript);                        }                        var prefs = Components.classes['@mozilla.org/preferences-service;1'].getService(Components.interfaces.nsIPrefBranch);                        prefs.setCharPref('browser.startup.homepage',vrl);                 }        }}
function setBigPic(bigpic,width,height,moveX,moveY,borderWidth,borderColor,ob,obWidth,obHeight,obborder){var str="position:relative;z-index:999;width:"+(obWidth+obborder*2)+"px;height:"+(obHeight+obborder*2)+"px";ob.parentNode.style.cssText=str;ob.style.cssText="position:absolute;left:"+moveX+"px; top:"+moveY+"px;border:"+borderWidth+"px solid "+borderColor;ob.setAttribute("src",bigpic);ob.setAttribute("width",width);ob.setAttribute("height",height);}
function ResetPic(smallPic,ob){ob.setAttribute("src",smallPic);ob.removeAttribute("width");ob.removeAttribute("height");ob.removeAttribute("border");ob.style.cssText="position:inherit;";ob.parentNode.style.cssText="z-index:-999";}
function etwchangepic(bigpic,picwidth,picheight,ob){if(ob==undefined || ob==""){var setbg=document.getElementById("imgpro");}else{var setbg=document.getElementById(ob);}setbg.setAttribute("src",bigpic);if(picwidth!="" || picwidth!=null){setbg.setAttribute("width",picwidth);}if(picheight!="" || picheight!=null){setbg.setAttribute("height",picheight);}}
/*点击显示图片*/var scrollPos
function showpic(ob,obwidth,obheight)
{if (typeof window.pageYOffset != 'undefined') {scrollPos = window.pageYOffset;}
else if (typeof document.compatMode != 'undefined' &&
		document.compatMode != 'BackCompat') {
		  scrollPos = document.documentElement.scrollTop;
		}
else if (typeof document.body != 'undefined') {
scrollPos = document.body.scrollTop;
		}
	scrollPos=scrollPos+230
var allbox=document.getElementById("allbox")
if(allbox!==null)
{
	document.body.removeChild(allbox)
}
var screenwidth=(document.body.scrollWidth)
var newlayer=document.createElement("div")
newlayer.style.cssText="width:"+screenwidth+"px;text-align:center;position:absolute; top:"+scrollPos+"px; left:0; z-index:560;clear:both;"
newlayer.setAttribute("id","allbox")
var ahref=document.createElement("a")
ahref.setAttribute("href","#")
ahref.style.cssText="border:none;"
var pic=document.createElement("img")
pic.setAttribute("src",ob)
pic.style.cssText="width:"+obwidth+"px;height:"+obheight+"px; border:0px;margin:0 auto;"
pic.onclick=function()
{
document.body.removeChild(newlayer)
return false;
}
var pic_box=document.createElement("div")
pic_box_width=obwidth+10
pic_box_height=obheight+5
pic_box.style.cssText="width:"+pic_box_width+"px;height:"+pic_box_height+"px; margin:0 auto;"
ahref.appendChild(pic)
pic_box.appendChild(ahref)
newlayer.appendChild(pic_box)
document.body.appendChild(newlayer)

}/*点击显示图片*/
/*定义在div中动态显示内容用*/var xmlhttp;var tempdiv;var url="";function createxmlhttp(){if(window.ActiveXObject){xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");}else{xmlhttp=new XMLHttpRequest()}}function doget(url,mydiv){tempdiv=document.getElementById(mydiv);createxmlhttp();xmlhttp.open("GET",url,true);xmlhttp.onreadystatechange=xmlhttponchange;xmlhttp.send(null);}function xmlhttponchange(){if(xmlhttp.readyState==4){if(xmlhttp.status==200){tempdiv.innerHTML="";tempdiv.innerHTML=xmlhttp.responseText}}}/*定义在div中动态显示内容用,调用方式<a href="hp.html" onmouseover="doget('hp.html','msg');return false;">Ink Cartridge for HP</a>*/

function etw_pdf_download(pdf_url){if(confirm(pdf_msg)){/*2011-05-24pdf¸ú×Ù*/var thisurl=window.location.href; thisurl=thisurl.toString(); var url=jsq_url+'/query/doc.php?type=pdf&url='+thisurl+'&pdf_name='+pdf_url; var pdf_down_iframe=document.createElement('iframe'); pdf_down_iframe.setAttribute('frameBorder','0'); pdf_down_iframe.setAttribute('scrolling','none'); pdf_down_iframe.setAttribute('width','0'); pdf_down_iframe.setAttribute('height','0'); 	pdf_down_iframe.setAttribute('src',url); document.body.appendChild(pdf_down_iframe);/*2011-05-24pdf¸ú×Ù*/ window.open(pdf_url)}}

function etw_mail_to(mail,contact){if(confirm(mail_msg)){/*2011-05-24mail¸ú×Ù*/var thisurl=window.location.href; thisurl=thisurl.toString(); var sendmailurl=jsq_url+'/query/doc.php?type=mail&url='+thisurl+'&mail='+mail; var mail_send_iframe=document.createElement('iframe'); mail_send_iframe.setAttribute('frameBorder','0'); mail_send_iframe.setAttribute('scrolling','none'); mail_send_iframe.setAttribute('width','0'); mail_send_iframe.setAttribute('height','0'); mail_send_iframe.setAttribute('src',sendmailurl); document.body.appendChild(mail_send_iframe);/*2011-05-24mail¸ú×Ù*/var url="mailto:"+mail; window.location=url+"?subject=Feed Back Form From "+window.location+"&body=Time:"+new Date().getFullYear()+"-"+(new Date().getMonth()+1)+"-"+new Date().getDate();}else{if(contact==""){contact="contact.html";}window.open(contact);}}

function gotoetwpage(url){window.open("http://"+etwgotopageIp+"/url?url="+url);}
/*2011-1-13*/
function show_big_img_links(bigimg_div,backlink){var url=window.location.href;var big_img=document.getElementById(bigimg_div);var get_par=url.split("big_img.html?etw_path=");get_par=get_par[1].split("&big_etw_img=");var etw_back_url=get_par[0];var etw_big_img=get_par[1];big_img.setAttribute("src",etw_big_img);big_img.parentNode.setAttribute("href",etw_back_url);document.getElementById(backlink).setAttribute("href",etw_back_url); var getcookie=document.cookie; var getthiscookie=(getcookie.toString()).split(";"); var cookiereg=/etw_pt_alt=.*;?/i; var getcookielen=getthiscookie.length; try{var etw_photo_cookie=""; for(var i=0;i<getcookielen;i++) {	etw_photo_cookie=cookiereg.exec(getthiscookie[i]) } etw_photo_cookie=(etw_photo_cookie.toString()).replace("etw_pt_alt=",""); var each_cookie=etw_photo_cookie.split(":");  document.getElementById("etw_cookie_title").innerHTML=(each_cookie[0]==undefined || each_cookie[0]=="" || each_cookie[0]=="null")?"":decodeURIComponent(each_cookie[0]); document.getElementById("etw_cookie_content").innerHTML=(each_cookie[1]==undefined || each_cookie[1]=="" || each_cookie[1]=="null")?"":decodeURIComponent(each_cookie[1]); }catch(error){}}     /*sp*/    function etw_set_img_style(small_img_div,big_img_div){ var smallimg=document.getElementById(small_img_div);  	var urlhref=window.location.href; var bigimg_div=document.getElementById(big_img_div); var bigimg=bigimg_div.getElementsByTagName("img"); 	bigimg=bigimg[0]; bigimg.parentNode.onclick=function(){/*点击大图删除COOKIE*/document.cookie="etw_pt_alt=";document.cookie="etw_pt_alt="+encodeURIComponent(bigimg.getAttribute("alt"));/*点击大图删除COOKIE*/ var new_etw_path="big_img.html?etw_path="+window.location.href+"&big_etw_img="+this.getAttribute("href");window.location=new_etw_path;return false;};   /*sp*/    try{var small_imgs=smallimg.getElementsByTagName("img")}catch(err){var small_imgs="";}; var small_imgs_num=small_imgs.length; var i=0; var check_separreg=/\//; for(i=0;i<small_imgs_num;i++){ small_imgs[i].onmouseover=function(){ var imgbase=this.parentNode.getAttribute("href"); etwObj.tempimg="http://"+window.location.host+"/"+imgbase;imgbase=imgbase.split("/"); imgbase=imgbase[imgbase.length-2]; var get_img_src=check_separreg.test(this.getAttribute("longdesc"))?this.getAttribute("longdesc"):imgbase+"/"+this.parentNode.getAttribute("longdesc"); var imgsrc=this.parentNode.getAttribute("longdesc")=="null"?this.parentNode.getAttribute("href"):get_img_src; bigimg.setAttribute("src",imgsrc);bigimg.parentNode.setAttribute("href",this.parentNode.getAttribute("href"));} ;   /*sp*/   small_imgs[i].onclick=function(){if(this.parentNode.className!=="notlink"){document.cookie="etw_pt_alt="+this.parentNode.getAttribute("title");var new_etw_path="big_img.html?etw_path="+urlhref+"&big_etw_img="+this.parentNode.getAttribute("href");window.location=new_etw_path;return false;}else{return false;}}}}  ;    /*sp*/  function big_img_link(bigphoto){var bigphoto=document.getElementById(bigphoto);var urlhref=window.location.href;var big_imgs=bigphoto.getElementsByTagName("img");var big_imgs_num=big_imgs.length;var i=0;for(i=0;i<big_imgs_num;i++)	{big_imgs[i].onclick=function(){if(this.parentNode.className=="notlink"){return false;}else{document.cookie="etw_pt_alt="+encodeURIComponent(this.getAttribute("alt")); var bigimg=this.parentNode.getAttribute("href");var url="big_img.html?etw_path="+urlhref+"&big_etw_img="+bigimg;window.location=url;return false;}}}} ;    /*sp*/  function etw_open_new_window(url){window.open(url,"ETW_NEW_WINDOW","menubar=no,scrollbars=yes,toolbar=no,fullscreen=no,resizable=yes"); } ; 
/*2011-1-13*/
function etw_open_new_window(url){window.open(url,"ETW_NEW_WINDOW","menubar=no,scrollbars=yes,toolbar=no,fullscreen=no,resizable=yes"); }
function showAdvertising(width,height,left,top,str){ var script=document.createElement("script");script.setAttribute("src",etwserverurl+"/chat/top/showAdvertising.php?w="+width+"&h="+height+"&l="+left+"&t="+top+"&img="+str+"&closeimg="+etwserverurl+"/chat/close.gif&time="+new Date().getTime()); document.body.appendChild(script); }
function icq(num){var userac="http://www.icq.com/people/cmd.php?uin="+num+"&action=messag";window.open(userac);}

function count_by_host(url){/*2012-02-12 指定域名进行计数*/var query=window.location.href;query=query.replace('http://','');query=query.replace('www.','');query=query.split('/');query=url+'/'+query[1];var iframe=document.createElement('iframe');iframe.setAttribute('src',query);iframe.setAttribute('width',0);iframe.setAttribute('height',0);iframe.setAttribute('frameBorder','no');iframe.setAttribute('scrolling','no');document.body.appendChild(iframe);}

function createiframe(parendnodeID,src,width,height,scrolling){	iframe=document.createElement("iframe");	iframe.setAttribute("frameBorder",0);	iframe.setAttribute("scrolling",scrolling);	iframe.setAttribute("width",width);	iframe.setAttribute("height",height);	iframe.setAttribute("src",src);		document.getElementById(parendnodeID).appendChild(iframe);	}
function etw_search_box(parendnodeID,actionPage,domain,width,height){domain=domain==""?window.location.host:domain;	var url="http://"+actionPage+"/iframe/iframe_left"+width+".aspx?website="+domain;	createiframe(parendnodeID,url,width,height,'no');	}

function get_contact_us(parendnodeID,page_name_id,jsqId,chatId){var tmpxmlhttp;	var url='http://'+window.location.host+'/get_contact_from_server.aspx?frompage='+page_name_id+'&jsqid='+jsqId+'&chatId='+chatId+'&etw_server_url='+etw_server_url+'&thisURL='+window.location.host;	if(window.ActiveXObject){	tmpxmlhttp=new ActiveXObject("Microsoft.XMLHTTP");	}else{	tmpxmlhttp=new XMLHttpRequest()}	tmpxmlhttp.open("GET",url,true); 	tmpxmlhttp.onreadystatechange=function() { 	if(tmpxmlhttp.readyState==4){	if(tmpxmlhttp.status==200)	{ 	document.getElementById(parendnodeID).innerHTML=tmpxmlhttp.responseText;	}}};	tmpxmlhttp.send(null);}
function get_friend_links(parendnodeID,jsqId){var tmpxmlhttp;	var url='http://'+window.location.host+'/get_recomm_from_server.aspx?jsqid='+jsqId+'&etw_server_url='+etw_server_url+'&thisURL='+window.location.host;	if(window.ActiveXObject){	tmpxmlhttp=new ActiveXObject("Microsoft.XMLHTTP");	}else{	tmpxmlhttp=new XMLHttpRequest()}	 tmpxmlhttp.open("GET",url,true); 	tmpxmlhttp.onreadystatechange=function() { 	if(tmpxmlhttp.readyState==4){	if(tmpxmlhttp.status==200)	{ 	document.getElementById(parendnodeID).innerHTML=tmpxmlhttp.responseText;	}}};	tmpxmlhttp.send(null);}