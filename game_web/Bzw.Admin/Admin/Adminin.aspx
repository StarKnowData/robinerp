<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Adminin" Codebehind="Adminin.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<link href="css/left_style.css" rel="stylesheet" type="text/css" />
<title><%= SiteConfig.GetParaValue("Title")%>网站后台管理系统</title>
</head>
<frameset rows="*" cols="181,*" framespacing="0" frameborder="1" border="false" id="frame" scrolling="yes">
  <frame name="left" scrolling="auto" marginwidth="0" marginheight="0" src="menu.aspx">
    <frameset framespacing="0" border="false" rows="35,*" frameborder="0" scrolling="yes">
    <frame name="top" scrolling="no" src="top.aspx">
    <frame name="main" scrolling="yes" src="SConfig/SystemStatEveryDay.aspx">
  </frameset>
</frameset>
<noframes>
  <body leftmargin="2" topmargin="0" marginwidth="0" marginheight="0">
  <p>本页使用了框架结构，但是您的浏览器不支持它。请将您的浏览器升级为IE5.0或更高的版本！</p>
  </body>
</noframes>
</html> 
