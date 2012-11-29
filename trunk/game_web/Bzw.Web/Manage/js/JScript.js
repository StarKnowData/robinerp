// JScript 文件

//浏览器支持JavaScript显示
function ShowHtml()
{
    try
    {
        var ElementError = document.getElementById('GutHtml');
        ElementError.style.display = 'block';
        parent.document.all.main.height = document.body.scrollHeight;
    }
    catch(e)
	{
		//alert(e.description);
	}
}

/* 检测浏览器版本 */
function Navigator()
{
    var strIEversion = navigator.appVersion;
    var strTemp = "MSIE";
    var IEversion = (strIEversion.indexOf("MSIE"));
    var strVersion = null;
    for(var i = IEversion; i < IEversion + strTemp.length; i++)
    {
        if(strVersion != null)
        {
            strVersion = strVersion + strIEversion.charAt(i);
        }
        else
        {
            strVersion = strIEversion.charAt(i);
        }
    }
    if(strVersion != "MSIE")
    {
        document.write("");
        alert("系统检测 .....\n浏览器信息: " + strIEversion + " \r\n系统提示: 请使用 Internet Explorer 5.0 以上版本");
        history.back(-1);
    }
}
