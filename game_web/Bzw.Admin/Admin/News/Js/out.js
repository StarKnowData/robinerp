function createXMLHttps()
{
    var ret = null;
    try {
        ret = new ActiveXObject('Msxml2.XMLHTTP');
    }
    catch (e) {
        try {
            ret = new ActiveXObject('Microsoft.XMLHTTP');
        }
        catch (ee) {
            ret = null;
        }
    }
    if (!ret && typeof XMLHttpRequest != 'undefined')
        ret = new XMLHttpRequest();
    return ret;
}

//function doClose()
//{
//	if (event.clientX > document.body.clientWidth - 50 && event.clientY < 0 || event.altKey)
//	{
//		event.returnValue = "───────────────────────\r\n您确定要离家锁门吗?\n\n离家锁门后您的朋友将不能直接给您发送即时帖哦！\r\n───────────────────────";
//		window.attachEvent("onunload", doLogout);
//	}else{
//		window.detachEvent("onunload", doLogout);
//	}
//}

//function doLogout()//发送退出指令
//{
//	var d,t;
//	d = new Date();
//	t = d.getTime();
//	var xmlhttp = createXMLHttps();
//	xmlhttp.Open("GET", "http://manage.5lin.com/Public/Logout.asp?a=offonline&tmp="+t, false);
//	//alert("温馨提示：\n\n已经将您的登录状态设置为离线！");
//	xmlhttp.Send(null);
//}

//function confirmQuit(){
//	if(!confirm("确认要退出管理中心吗？"))
//		{event.returnValue=false;}
//}

//window.attachEvent("onbeforeunload", doClose);