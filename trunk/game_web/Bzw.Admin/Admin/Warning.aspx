<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Warning" Codebehind="Warning.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=gb2312" />
    <title><%= SiteConfig.GetParaValue("Title")%></title>
</head>
<body>
    <form id="form1" runat="server">
    <div style="text-align:center; margin-top:50px;">
    <h1>警告：您没有该页面的操作权限！</h1><h2><a href="javascript:history.back();">返回</a></h2>
    </div>
    </form>
</body>
</html>
