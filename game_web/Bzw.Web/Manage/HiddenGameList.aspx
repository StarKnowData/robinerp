<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Web.Manage.OpenShow" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>
		
	</title>
	
	<link href="/Style/mainstyle.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" src="/Public/Js/Global.js"></script>
</head>
<body>
   <div id="wrap">
<!--header-->
	 <WebTop:Control ID="webTopOne" runat="server"/> 
<!--content-->
    <div id="content">
      <div id="left1">
        <Left:Control ID="leftOne" runat="server" />
        <WebService:Control ID="webServiceOne" runat="server" />
      </div>
 <div id="right">
     
      <div class="rightbox" >
            <p style=" font-size:18px ; font-weight:bold; text-align:center;">隐藏未开放游戏说明</p>
            <p></p>
            <p style=" font-size:14px">登录后台，游戏管理中心模块下的销售列表显示配置中，选择“只显示已启用的游戏”，点击保存设置。重新启动服务器即可。</p>
      </div>  
    </div>
     <div class="clear"></div>
      </div><!--right End-->
 
    </div><!--content End-->
 
<!--footer-->
	<WebFooter:Control ID="webFooterone" runat="server" /> 
</body>
</html>

 
