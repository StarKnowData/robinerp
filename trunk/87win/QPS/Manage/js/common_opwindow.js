/**
* Pops up a new window in the middle of the screen
*/
function popupWindow(mypage, myname, w, h, scroll) {
	var winl = (screen.width - w) / 2;
	var wint = (screen.height - h) / 2;
	winprops = 'height='+h+',width='+w+',top='+wint+',left='+winl+',scrollbars='+scroll+',resizable'
	win = window.open(mypage, myname, winprops)
	if (parseInt(navigator.appVersion) >= 4) { win.window.focus(); }
}
function isIE(){
	var agentStr=navigator.userAgent;
	if(agentStr.indexOf("MSIE")!=-1)
	{
		return true;
	}
	else{
		return false;
	}
}
function $(id) {
	return document.getElementById(id);
}
function Back(){
  history.back();
}