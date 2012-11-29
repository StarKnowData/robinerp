
/*****************************************
字符串去除头尾空格
*****************************************/
String.prototype.Trim = function() {
    return this.replace(/(^\s*)|(\s*$)/g, "");
}

String.prototype.LTrim = function() {
    return this.replace(/(^\s*)/g, "");
}

String.prototype.RTrim = function() {
    return this.replace(/(\s*$)/g, "");
}
/*****************************************
取得event
*****************************************/
function Evt(e) {
    if (!e) {
        e = window.event;
    }
    return e;
}
function BEvent() {
    return window.event ? window.event : arguments.callee.caller.arguments[0];
}
/*****************************************
限制输入的执行函数
*****************************************/
//只能输入数字
function KeyPressNum(obj, evt) {
    var key = window.event ? evt.keyCode : evt.which;
    if (key < 27 || key > 128) return true; //如果输入的是功能按键，则不限制
    else if (key >= 48 && key <= 57) return true;
    else
        return false;
}
//只能输入数字和小数点，并且小数点要按规则输入
function KeyPressNumPoint(obj, evt) {
    var key = window.event ? evt.keyCode : evt.which;
    if (key < 27 || key > 128) //如果输入的是功能按键，则不限制
    {
        return true;
    }
    else if ((key >= 48 && key <= 57) || key == 46) {
        if (key == 46) {
            if (obj.value.Trim() == "") {
                return false;
            }
            if (obj.value.indexOf(".") >= 1) {
                return false;
            }
        }
        return true;
    }
    else
        return false;
}
//只允许输入带负号的小数数字格式
function KeyPressSignFloatNum(obj, evt) {
    var key = window.event ? evt.keyCode : evt.which;
    if (key < 27 || key > 128) //如果输入的是功能按键，则不限制
    {
        return true;
    }
    else if ((key >= 48 && key <= 57) || key == 46 || key == 45) {
        if (key == 46) {
            if (obj.value.Trim() == "") {
                return false;
            }
            if (obj.value.indexOf(".") >= 1) {
                return false;
            }
        }
        if (key == 45) {
            if (obj.value.Trim() != "")
                return false;
        }
        return true;
    }
    else
        return false;
}
//只能输入数字和横线
function KeyPressNumLine(obj, evt) {
    var key = window.event ? evt.keyCode : evt.which;
    if (key < 27 || key > 128) {
        return true;
    }
    else if ((key >= 48 && key <= 57) || key == 45) {
        return true;
    }
    else
        return false;
}
//只能输入数字、横线和括号（电话号码形式）
function KeyPressPhone(obj, evt) {
    var key = window.event ? evt.keyCode : evt.which;
    if (key < 27 || key > 128) {
        return true;
    }
    else if ((key >= 48 && key <= 57) || key == 45 || key == 40 || key == 41) {
        return true;
    }
    else
        return false;
}
/**********************************************
页面跳转
**********************************************/
//跳到本页并且去除url参数
function RefreshMe() {
    location.href = location.pathname;
}
//跳转到本页，不去除参数
function LocationToMe() {
    location.href = location.href;
}
//跳转到本页，并删除指定的参数
//参数：param:应为匹配指定参数的js正则表达式字符串
function RefreshMeDelParam(param) {
    var url = location.href;
    var reg = new RegExp(param, "ig");
    var x = url.replace(reg, "");
    LocationTo(x);
}
//跳到指定页
function LocationTo(url) {
    location.href = url;
}
//顶部窗口跳转
function TopLocationTo(url) {
    top.location.href = url;
}
//跳转到本页，并添加参数
function LocationToMeParam(param) {
    location.href = SetUrlParam(location.href, param);
}
//提交页面
function SubmitToMeParam(url) {
    document.forms[0].action = url;
    document.forms[0].submit();
}

//打开窗口的js类，默认打开空页面
function NewWindow() {
    this.Url = "about:blank";
    this.Name = "_blank";
    this.Height = Math.round(window.screen.height / 2);
    this.Width = Math.round(window.screen.width / 2);
    this.ToolBar = "yes";
    this.MenuBar = "yes";
    this.ScrollBars = "yes";
    this.Location = "yes";
    this.Status = "yes";
    this.Resizable = "yes";
    this.Left = Math.round(((window.screen.availWidth - this.Width) / 2) / 2);
    this.Top = Math.round(((window.screen.availHeight - this.Height) / 2) / 2);
}
NewWindow.prototype.Open = function() {
    window.open(this.Url, this.Name, 'height=' + this.Height + ',width=' + this.Width + ',toolbar=' + this.ToolBar + ',menubar=' + this.MenuBar + ',scrollbars=' + this.ScrollBars + ',resizable=' + this.Resizable + ',location=' + this.Location + ',status=' + this.Status + ',left=' + this.Left + ',top=' + this.Top + '');
}
//打开一个没有任何限制的窗口
function OpenUrl(url) {
    var win = new NewWindow();
    win.Url = url;
    win.Open();
}
//打开一个所有操作工具条都没有的窗口
function OpenUrlNotAll(url, width, height) {
    if (url == null || url == "")
        url = "/";
    if (width == null || width == 0)
        width = Math.round(window.screen.width / 2);
    if (height == null || height == 0)
        height = Math.round(window.screen.height / 2);

    var win = new NewWindow();
    win.Url = url;
    win.Height = height;
    win.Width = width;
    win.ToolBar = "no";
    win.MenuBar = "no";
    win.ScrollBars = "yes";
    win.Location = "no";
    win.Status = "no";
    win.Resizable = "yes";
    win.Left = Math.round((window.screen.availWidth - win.Width) / 2);
    win.Top = Math.round((window.screen.availHeight - win.Height) / 2);
    win.Open();
}
/**************************************************
屏幕尺寸
**************************************************/
function Screen() {
    this.ScrollTop = document.documentElement.scrollTop; //网页被卷去的高
    this.ScrollLeft = document.documentElement.scrollLeft; //网页被卷去的左
    this.ScrollWidth = document.documentElement.scrollWidth; //网页正文全文宽
    this.ScrollHeight = document.documentElement.scrollHeight; //网页正文全文高
    this.ClientHeight = document.documentElement.clientHeight; //网页可见区域高
    this.ClientWidth = document.documentElement.clientWidth; //网页可见区域宽
    this.OffsetWidth = document.documentElement.offsetWidth; //网页可见区域宽(包括边线)
    this.OffsetHeight = document.documentElement.offsetHeight; //网页可见区域高(包括边线)
    this.ScreenTop = window.screenTop; //网页正文部分上
    this.ScreenLeft = window.screenLeft; //网页正文部分左
    this.ScreenHeight = window.screen.height; //屏幕分辨率的高
    this.ScreenWidth = window.screen.width; //屏幕分辨率的宽
    this.AvailHeight = window.screen.availHeight; //屏幕有效工作区高
    this.AvailWidth = window.screen.availWidth; //屏幕有效工作区宽
};
/**************************************************
可用于显示页面进度条的隐藏层操作
**************************************************/
//创建一个浮动的div，未指定宽高度及位置，指定部分样式
//var timer = null;
function CreateStateDiv(divID) {
    var div = document.createElement("div");
    div.id = divID;
    with (div.style) {
        fontSize = "12px";
        color = "#000";
        background = "url(/Images/System/D_bg.gif) repeat-x left top";
        border = "1px solid #99bfd8";
        position = "absolute";
        zIndex = "100000";
        display = "none";
    }
    return div;
}
//浮动层操作：关闭
function HiddenState(divID, time) {
    if ($("#" + divID).length > 0) {
        if (time == null || time == "undefined" || time == 0) time = 1000
        var tmp = "#" + divID;

        $("#" + divID).hide(time, function() {
            $(tmp).remove();
        });
    }
}
//扩展：显示网页提示信息
function Msg(text, width) {

    var s = new Screen();
    //创建遮罩层
    var mask = $("#Mask");
    if (mask.length == 0) {

        mask = CreateStateDiv("Mask");
        with (mask.style) {
            border = "0px";
            filter = "alpha(opacity=80)";
            opacity = "0.8";
            zIndex = "99999";
            backgroundImage = "none";
            backgroundColor = "#fefefe";
            position = "absolute";
            top = 0;
            left = 0;
            width = Math.max(s.ClientWidth, s.ScrollWidth) + "px";
            height = Math.max(s.ClientHeight, s.ScrollHeight) + "px";
            display = "inline";
        }
        $(mask).css("-moz-opacity", "0.8");
        $(mask).click(function() { HiddenState("Mask", 1); HiddenState("Tranning", 1) });
        AppendElement(mask);
    }
    else {

        mask.css("display", "inline");
    }

    var state = $("#Tranning")[0];
    if (state == null) {
        state = CreateStateDiv("Tranning");
        AppendElement(state);
    }
    var swidth = (width == null || width == "" || width == 0) ? 600 : width;

    var content = '<div style="color: #153c64; font-weight: bold; font-size: 14px; padding: 7px 0 0 12px;cursor:move;" onmouseover="DivMove(\'Tranning\');">';
    content += '<span style="position: absolute; top: 4px; right: 5px;">';
    content += '<img src="/Images/System/d_close.gif" width="21" height="19" style="border: 0;cursor:pointer;" title="关闭" alt="关闭" onclick="HiddenState(\'Mask\', 1);HiddenState(\'Tranning\',200);" /></span>';
    content += '网页对话框</div>';
    content += '<div style="padding: 25px; line-height: 24px;">';
    content += text;
    content += '</div>';
    content += '<div style="height: 27px; background: url(/Images/System/d_bottom.gif) repeat-x left top; border-top: 1px solid #e1e1e1; text-align: center; padding-top: 4px;">';
    content += '<img src="/Images/System/d_btn.gif" style="border:0;cursor:pointer;" title="关闭" alt="关闭" onclick="HiddenState(\'Mask\', 1);HiddenState(\'Tranning\',200);" />';
    content += '</div>';

    $(state).css("display", "inline");
    $(state).css("width", swidth + "px");
    $(state).html(content);
    $(state).css("top", s.ScrollTop + (s.ClientHeight - $(state).attr("clientHeight")) / 2);
    $(state).css("left", s.ScrollLeft + ((s.ClientWidth - width) / 2));

}
//function CreateStateDiv(divID) {
//	var div = document.createElement("div");
//	div.id = divID;
//	div.style.display = "none";
//	div.style.position = "absolute";
//	div.style.zIndex = "100000";
//	div.style.border = "1px solid #cccccc";
//	div.style.backgroundColor = "#ffffff";
//	return div;
//}
////浮动层操作：关闭
//function HiddenState(divID, time) {
//	if ($("#" + divID).length > 0) {
//		if (time == null || time == "undefined" || time == 0) time = 1000
//		var tmp = "#" + divID;
//		$("#" + divID).hide(time, function() {
//			$(tmp).remove();
//		});
//	}
//}
////扩展：显示网页提示信息
//function Msg(text, width) {
//	var state = $("#Tranning")[0];
//	if (state == null) {
//		state = CreateStateDiv("Tranning");
//		AppendElement(state);
//	}
//	var swidth = (width == null || width == "" || width == 0) ? 234 : width;

//	var content = '<div style="cursor:move;background-color:#23abee; height:22px;padding-top:3px; color:#ffffff;width:' + swidth + 'px;" onmouseover="DivMove(\'Tranning\');">';
//	content += '<div style="display:inline; font-size: 14px; vertical-align:middle; padding-left:2px;float:left;">网页对话框</div>';
//	content += '<div title="关闭" style="position: absolute; width: 12px; height: 9px; z-index: 100003;float:right; left: ' + (swidth - 23) + 'px; top: 1px; font-size: 14px; font-weight: bold; cursor: pointer;" onclick="HiddenState(\'Tranning\',500);">×</div>';
//	content += '</div>';
//	content += '<div style="MARGIN-TOP: 8px! important; MARGIN-BOTTOM: 5px; MARGIN-LEFT: 11px; WIDTH: ' + (swidth - 23) + 'px; color:red;">';
//	content += text;
//	content += '</div>';

//	$(state).show("fast");
//	$(state).html(content);
//	var s = new Screen();
//	$(state).css("top", s.ScrollTop + (s.ClientHeight - $(state).attr("clientHeight")) / 2);
//	$(state).css("left", s.ScrollLeft + ((s.ClientWidth - width) / 2));
//}
//扩展：显示进度条
function OpenStateBar(text) {
    var state = $("#Tranning")[0];
    if (state == null) {
        state = CreateStateDiv("Tranning");
        AppendElement(state);
    }

    var content = LOADING_ICON + text;

    $(state).show("fast");
    $(state).html(content);
    var s = new Screen();
    $(state).css("border", "0");
    $(state).css("top", s.ScrollTop + (s.ClientHeight - $(state).attr("clientHeight")) / 2);
    $(state).css("left", s.ScrollLeft + ((s.ClientWidth - $(state).attr("clientWidth")) / 2));
}
//扩展：关闭进度条
function CloseStateBar() {
    $("#Tranning").hide(500, function() { $("#Tranning").remove(); });
}
//扩展：层的移动
var drag_ = false;
function DivMove(objID) {
    var x, y;
    var tmp = "#" + objID;
    $(tmp).mousedown(
		function(e) {
		    drag_ = true;
		    with ($(tmp)) {
		        css("position", "absolute");
		        var off = offset();
		        var temp1 = off.left;
		        var temp2 = off.top;
		        x = Evt(e).clientX;
		        y = Evt(e).clientY;

		        document.onmousemove = function(e) {
		            if (!drag_) return false;
		            with (this) {
		                css("left", temp1 + Evt(e).clientX - x);
		                css("top", temp2 + Evt(e).clientY - y);
		            }
		        }
		    }
		}
	);
    document.onmouseup = new Function("drag_=false;");
}
//扩展：为文档添加一个元素
function AppendElement(element) {
    if (document.readyState) {
        if (document.readyState == "complete") {
            $(document.body).append(element);
        }
        else {
            $(document).ready(
			function() { $(document.body).append(element); }
			);
        }
    }
    else {
        $(document.body).append(element);
    }
}
/***************************************************************
url操作
***************************************************************/
//获取url中一个指定的参数值
function GetRequest(paramName, defaultValue) {
    var search = paramName + "=";
    var FieldValue = "";
    var URL = location.href;
    var offset = URL.indexOf(search);
    if (offset != -1) {
        offset += search.length;
        var end = URL.indexOf("&", offset);
        if (end == -1) {
            FieldValue = URL.substring(offset);
        }
        else {
            FieldValue = URL.substring(offset, end);
        }
    }
    if (FieldValue == "") {
        FieldValue = defaultValue;
    }
    return FieldValue.toLowerCase();
}
//为url添加参数，自动判断是更新还是添加
//参数格式：如：page=1的形式，不能是“page=1&params=1”的形式，即一次只能添加一个参数
function SetUrlParam(url, param) {
    var interrogation = url.indexOf("?");

    if (interrogation == -1) {
        url += "?" + param;
    }
    else {
        //如果?后面有查询字符串,则检测有没有该字段，如果有，则重新付值
        var fp = param.split("=");
        var search = fp[0] + "=";
        var offset = url.indexOf(search);
        if (offset != -1) {
            offset += search.length;
            end = url.indexOf("&", offset);
            if (end == -1) {
                url = url.substring(0, offset) + fp[1];
            }
            else {
                url = url.substring(0, offset) + fp[1] + url.substring(end);
            }
        }
        else {
            url = url + "&" + param;
        }
    }
    return url;
}
/*************************************************************
* 对象操作
*************************************************************/
//获取select的当前选定项的文本
function DropGetText(dropID) {
    var selector = "#" + dropID + " option:selected"
    return $(selector).text();
}
//获取select的当前选定项的值
function DropGetValue(dropID) {
    var selector = "#" + dropID + " option:selected"
    return $(selector).val();
}
//根据文本设置select的选定项
function DropSetByText(dropID, text) {
    var selector = "#" + dropID + " option";
    $(selector).each(
		function() {
		    this.selected = (this.text == text) ? true : false;
		}
	);
}
//根据值设置select的选定项
function DropSetByValue(dropID, value) {
    var selector = "#" + dropID + " option";
    $(selector).each(
		function() {
		    this.selected = (this.value == value) ? true : false;
		}
	);
}

/**************************************************************************
设为主页、加入收藏和复制到剪贴板
**************************************************************************/
//设为主页
function SetHomePage() {
    if (document.all) {
        document.body.style.behavior = 'url(#default#homepage)';
        document.body.setHomePage(location.href);
    }
    else if (window.sidebar) {
        if (window.netscape) {
            try {
                netscape.security.PrivilegeManager.enablePrivilege("UniversalXPConnect");
            }
            catch (e) {
                alert("该操作被浏览器拒绝，如果想启用该功能，请在地址栏内输入 about:config,然后将项 signed.applets.codebase_principal_support 值改为true");
            }
        }
        var prefs = Components.classes['@mozilla.org/preferences-service;1'].getService(Components.interfaces.nsIPrefBranch);
        prefs.setCharPref('browser.startup.homepage', location.href);
    }
}
//加入浏览器收藏
function AddFavorite(title, url) {
    if (document.all) {
        window.external.addFavorite(url, title);
    }
    else if (window.sidebar) {
        window.sidebar.addPanel(title, url, "");
    }
}
//加入会员收藏夹
function AddMemberFavorite(title, url) {
    //加入会员收藏夹的代码
    //进度条
    OpenStateBar("请稍候...");
    var url = "/Members/UsersForm.aspx?params=addfavorite&title=" + encodeURIComponent(title) + "&url=" + encodeURIComponent(url) + "&x=" + Math.random();
    $.get(
		url,
		function(data) {
		    if (data == "nologin") {
		        Msg(ERROR_MSG_ICON + '<p style="text-indent:2em;">您尚未登录，不能使用会员收藏夹，要收藏到浏览器中吗？<div style="text-align:center;">【<a href="javascript:HiddenState(\'Tranning\',500);AddFavorite(\'' + title + '\',\'' + url + '\');" title="收藏到浏览器">收藏</a>】&nbsp;&nbsp;【<a href="/Login.aspx" title="现在登录">现在登录</a>】</div></p>', 450);
		    }
		    else if (data == "success") {
		        Msg(SUCCESS_MSG_ICON + '<p style="text-indent:2em;">已添加到您的商品收藏夹，您可以在会员中心再次查看这个商品，现在查看收藏夹吗？<div style="text-align:center;">【<a href="/Members/ProductsFavorite.aspx" title="进入会员收藏夹">是</a>】&nbsp;&nbsp;【<a href="javascript:HiddenState(\'Tranning\',500);">否</a>】</div></p>', 450);
		    }
		    else {
		        Msg(ERROR_MSG_ICON + "错误：" + data, 300);
		    }
		}
	);
}
//复制信息到剪贴板
function CopyToClipboard(str) {
    var msg = "本页信息复制成功，您可以粘贴到QQ、MSN或邮箱中，发送给您的好友。";
    if (window.clipboardData) {
        window.clipboardData.clearData();
        window.clipboardData.setData("Text", str);
        alert(msg);
    }
    else if (window.netscape) {
        try {
            netscape.security.PrivilegeManager.enablePrivilege("UniversalXPConnect");
        } catch (e) {
            alert("被浏览器拒绝！\n请在浏览器地址栏输入'about:config'并回车\n然后将'signed.applets.codebase_principal_support'设置为'true'");
        }
        var clip = Components.classes['@mozilla.org/widget/clipboard;1'].createInstance(Components.interfaces.nsIClipboard);
        if (!clip)
            return;
        var trans = Components.classes['@mozilla.org/widget/transferable;1'].createInstance(Components.interfaces.nsITransferable);
        if (!trans)
            return;
        trans.addDataFlavor('text/unicode');
        var len = new Object();
        var str2 = Components.classes["@mozilla.org/supports-string;1"].createInstance(Components.interfaces.nsISupportsString);
        var copytext = str;
        str2.data = copytext;
        trans.setTransferData("text/unicode", str2, copytext.length * 2);
        var clipid = Components.interfaces.nsIClipboard;
        if (!clip)
            return false;
        clip.setData(trans, null, clipid.kGlobalClipboard);
        alert(msg);
    }
}
//复制信息到剪贴板，无提示
function CopyToClipboardNonAlert(str) {
    if (window.clipboardData) {
        window.clipboardData.clearData();
        window.clipboardData.setData("Text", str);
    }
    else if (window.netscape) {
        try {
            netscape.security.PrivilegeManager.enablePrivilege("UniversalXPConnect");
        } catch (e) {
        }
        var clip = Components.classes['@mozilla.org/widget/clipboard;1'].createInstance(Components.interfaces.nsIClipboard);
        if (!clip)
            return;
        var trans = Components.classes['@mozilla.org/widget/transferable;1'].createInstance(Components.interfaces.nsITransferable);
        if (!trans)
            return;
        trans.addDataFlavor('text/unicode');
        var len = new Object();
        var str2 = Components.classes["@mozilla.org/supports-string;1"].createInstance(Components.interfaces.nsISupportsString);
        var copytext = str;
        str2.data = copytext;
        trans.setTransferData("text/unicode", str2, copytext.length * 2);
        var clipid = Components.interfaces.nsIClipboard;
        if (!clip)
            return false;
        clip.setData(trans, null, clipid.kGlobalClipboard);
    }
}

/*****************************************************
表单验证
*****************************************************/
//var ERROR_MSG_ICON="<img src='/Images/System/smallerror.gif' align='absmiddle' width='32' height='32' />&nbsp;";
var ERROR_MSG_ICON = "<img src='/Images/System/053753112.gif' align='absmiddle' width='16' height='16' />&nbsp;";
var LOADING_ICON = "<img src='/Images/System/smallloading.gif' align='absmiddle' width='32' height='32' />&nbsp;";
var INFO_MSG_ICON = "<img src='/Images/System/no.jpg' align='absmiddle' width='32' height='32' />&nbsp;";
//var SUCCESS_MSG_ICON = "<img src='/Images/System/ORB_Icons_by_014.png' align='absmiddle' width='32' height='32' />&nbsp;";
var SUCCESS_MSG_ICON = "<img src='/Images/System/053753200.gif' align='absmiddle' width='16' height='16' />&nbsp;";
function CK_HtmlControl() {
    this.Message = ""; //错误信息容器
    this.Postfix = "<br />"; //错误信息后缀
    //验证不能为空，可加长度限制
    //参数：obj:要验证的对象; objTitle:要显示的错误信息前缀; maxlength:要限制的字符串长度最大值，为-1表示不限制；minLength:要限制的字符串长度最小值，为-1表示不限制
    //返回：true:表示验证成功，false:表示发生错误
    this.Required_TextBox = function(obj, objTitle, maxLength, minLength) {
        if (obj) {
            var tmp = obj.value.Trim();
            if (tmp == "") {
                this.Message += objTitle + "不能留空" + this.Postfix;
                return false;
            }
            else {
                if (maxLength > -1 && minLength > -1) {//两种长度同时限制
                    if (!((tmp.length <= maxLength) && (tmp.length >= minLength))) {
                        this.Message += objTitle + "长度应在" + minLength + "～" + maxLength + "个字之间" + this.Postfix;
                        return false;
                    }
                    return true;
                }
                else if (maxLength > -1 && minLength <= -1) {//限制最大长度
                    if (!(tmp.length <= maxLength)) {
                        this.Message += objTitle + "长度应小于" + maxLength + "个字" + this.Postfix;
                        return false;
                    }
                    return true;
                }
                else if (maxLength <= -1 && minLength > -1) {//限制最小长度
                    if (!(tmp.length >= minLength)) {
                        this.Message += objTitle + "长度应大于" + minLength + "个字" + this.Postfix;
                        return false;
                    }
                    return true;
                }
                return true;
            }
        }
        this.Message = "内部错误：对象不存在。";
        return false;
    }
    //验证数字字符串不能为空，只能输入数字，并带有数字范围验证
    this.Required_Number_TextBox = function(obj, objTitle, maxValue, minValue) {
        if (obj) {
            var tmp = obj.value.Trim();
            if (tmp == "") {
                this.Message += objTitle + "不能留空" + this.Postfix;
                return false;
            }
            else if (isNaN(tmp)) {
                this.Message += objTitle + "只能输入数字" + this.Postfix;
                return false;
            }
            else {
                var value = parseInt(tmp);
                if (value > maxValue || value < minValue) {
                    this.Message += objTitle + "必须在" + minValue.toString() + "和" + maxValue.toString() + "之间" + this.Postfix;
                    return false;
                }
                return true;
            }
        }
        this.Message = "内部错误：对象不存在。";
        return false;
    }
    //验证字符串格式
    //参数：reg:要匹配的正则模式
    this.Regular_TextBox = function(obj, objTitle, reg) {
        if (obj) {
            var tmp = obj.value.Trim();
            if (tmp.match(reg) == null) {
                this.Message += objTitle + "格式不正确" + this.Postfix;
                return false;
            }
            return true;
        }
        this.Message = "内部错误：对象不存在";
        return false;
    }
    //验证两个字符串相等
    this.CompareEquals = function(str1, str2, mess) {
        if (str1 == str2) return true;
        this.Message += mess;
        return false;
    }
    //验证两个字符串不相等
    this.CompareNotEquals = function(str1, str2, mess) {
        if (str1 != str2) return true;
        this.Message += mess;
        return false;
    }
    //验证一组checkbox或radio至少选中了一个
    this.Checked = function(objseltor, errormsgtitle, isradio) {
        if ($(objseltor + ":checked").length > 0) { return true; }
        else {
            if (isradio)
            { this.Message += "请选择" + errormsgtitle + this.Postfix; }
            else
            { this.Message += "您至少应该选择" + errormsgtitle + "中的一个" + this.Postfix; }
            return false;
        }
    }
    //验证两个输入控件至少要填写一个
    this.Alternative_TextBox = function(obj1, obj2, title1, title2) {
        if (obj1 == null || obj2 == null) {
            this.Message += "错误：对象不存在！";
            return false;
        }
        if ($(obj1).val().Trim() == "" && $(obj2).val().Trim() == "") {
            this.Message += title1 + "和" + title2 + "您至少应该填写一项。" + this.Postfix;
            return false;
        }
        else {
            return true;
        }
    }
}

/*****************************************************************
会员登录验证
*****************************************************************/
//会员登录页表单验证
function CheckMemberFullLogin() {
    var ck = new CK_HtmlControl();
    ck.Postfix = "</li>";
    if (
		ck.Required_TextBox($("#txtLoginName")[0], "<li style='color:red;'>-用户名", 50, 2) &&
		ck.Required_TextBox($("#txtLoginPassword")[0], "<li style='color:red;'>-密码", 200, 6) &&
		ck.Required_TextBox($("#txtValidate")[0], "<li style='color:red;'>-验证码", 4, 4)
		) {
        return true;
    }
    else {
        var error = '<strong>您的输入有以下错误：</strong><br /><ol>';
        error += ck.Message + "</ol>";
        Msg(ERROR_MSG_ICON + error, 300);
        return false;
    }
}
//顶部会员登录表单验证
function CheckTopMemberLogin() {
    var ck = new CK_HtmlControl();
    ck.Postfix = "</li>";
    if (
		ck.Required_TextBox($("#txtTopLoginName")[0], "<li style='color:red;'>-用户名", 50, 2) &&
		ck.Required_TextBox($("#txtTopLoginPwd")[0], "<li style='color:red;'>-密码", 200, 6)
		) {
        return true;
    }
    else {
        var error = '<strong>您的输入有以下错误：</strong><br /><ol>';
        error += ck.Message + "</ol>";
        Msg(ERROR_MSG_ICON + error, 300);
        return false;
    }
}
//顶部会员登录动作
function TopLoginAction() {
    if (CheckTopMemberLogin()) {
        var btn = $("#spanTopLoginBtn").html();
        $("#spanTopLoginBtn").html("<font color='#3794e2'>请稍候...</font>");
        var url = "/Members/UsersForm.aspx?params=login&un=" + encodeURIComponent($("#txtTopLoginName").val()) + "&pwd=" + $("#txtTopLoginPwd").val();
        var msg = $.get(url, function(data) {
            if (data != "登录成功") {
                Msg(ERROR_MSG_ICON + "错误：" + data, 200);
                $("#spanTopLoginBtn").html(btn);
            }
            else {
                LocationTo("/Members/");
            }
        });
    }
}
/**************************************************************
分站函数
**************************************************************/
function IsSubSite() {
    var subdomain = location.host.substring(0, location.host.indexOf("."));
    return (subdomain != "www" && subdomain.indexOf("test") < 0)
}
function SubDomain() {
    return location.host.substring(0, location.host.indexOf("."));
}
/**************************************************************
在线客服
**************************************************************/
function InitFloatService(objseltor) {
    //移动的效果
    var obj = $(objseltor);
    var s = new Screen();
    obj.css("top", s.ScrollTop + 200);
    obj.css("right", 0);
    //跟随滚动条
    $(window).scroll(
		function() {
		    var s = new Screen();
		    $(objseltor).css("top", s.ScrollTop + 200);
		    $(objseltor).css("right", 0);
		}
	);
    //读取在线客服
    var file = "/XML/";
    var subdomain = location.host.substring(0, location.host.indexOf("."));
    if (subdomain != "www" && subdomain.indexOf("test") < 0) {
        file += subdomain + "/Service.xml";
    }
    else {
        file += "Service.xml";
    }
    $.get(
		file + "?x=" + Math.random(),
		function(xml) {
		    $("#big>ul").remove();
		    $("#big>h3").remove();

		    //先取得所有部门
		    var sector = new Array();
		    $(xml).find("Item").each(
				function() {
				    var g = $(this).attr("Group");
				    if (sector.length <= 0) {
				        sector.push(g);
				    }
				    else {
				        if (sector.toString().indexOf(g) < 0) {
				            sector.push(g);
				        }
				    }
				}
			);

		    for (var i = 0; i < sector.length; i++) {
		        var h3 = $(document.createElement("h3"));
		        h3.text(sector[i]);
		        $("#big").append(h3);
		        var ul = $(document.createElement("ul"));
		        $(xml).find("Item[Group=" + sector[i] + "]").each(
					function() {
					    var node = $(this);
					    var type = node.children("Type").text();
					    var sn = node.children("SN").text();
					    var title = node.children("Name").text();
					    var li = $(document.createElement("li"));
					    var href = $(document.createElement("A"));
					    var img = $(document.createElement("img"));
					    var txt = $(document.createTextNode(title));
					    if (type.toLowerCase() == "msn") {
					        href.attr("href", "msnim:chat?contact=" + sn);
					        href.attr("title", title);
					        img.attr("src", "/Images/msn_online.gif");
					    }
					    else {
					        href.attr("href", "http://wpa.qq.com/msgrd?V=1&Uin=" + sn + "&Site=" + location.host);
					        href.attr("target", "_blank");
					        href.attr("title", title);
					        img.attr("src", "http://wpa.qq.com/pa?p=1:" + sn + ":4");
					    }
					    href.append(img);
					    href.append(txt);
					    li.append(href);
					    ul.append(li);
					    $("#big").append(ul);
					}
				);
		    }
		    $("#big>ul:last").css("border-bottom", "2px solid #0977cd");
		}
	);
}

/***************************************************************************
*					tab效果
***************************************************************************/
//参数：navseltor：导航栏选择器；listseltor：列表内容选择器；activecss：活动导航css样式
function TabbedPanels(navseltor, listseltor, activecss) {
    $(navseltor).each(
		function() {
		    $(this).mousemove(
				function() {
				    this.className = activecss;
				    $(this).siblings().each(
						function() { this.className = ""; }
					);
				    var index = $.inArray(this, $.makeArray($(navseltor)));
				    $(listseltor).each(
						function(i) {
						    $(this).css("display", (i == index ? "" : "none"));
						}
					);
				}
			);
		}
	);
}
//参数：navseltor：导航栏选择器；listseltor：列表内容选择器；activecss：活动导航css样式；morecontainer：更多链接的容器
function TabbedPanelsMore(navseltor, listseltor, activecss, morecontainer) {
    $(navseltor).each(
		function() {
		    $(this).mousemove(
				function() {
				    this.className = activecss;
				    $(morecontainer).html("<a href='" + this.href + "' title='查看更多'>更多&gt;&gt;</a>");
				    $(this).siblings().each(
						function() { this.className = ""; }
					);
				    var index = $.inArray(this, $.makeArray($(navseltor)));
				    $(listseltor).each(
						function(i) {
						    $(this).css("display", (i == index ? "" : "none"));
						}
					);
				}
			);
		}
	);
}