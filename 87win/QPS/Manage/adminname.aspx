<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="adminname.aspx.cs" Inherits="QPS.Web.Manage.adminname" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <title>无标题页</title>
    <style type="text/css">
<!--
body {
	margin-left: 0px;
	margin-top: 0px;
}
-->
</style>
    
</head>
<body  bgcolor="#dce3f6">
    <table  cellpadding="0" cellspacing="0" border="0" bgcolor="#dce3f6"><tr><td style="margin-left:0; margin-top:0;"><%= Session["admin"]%></td></tr></table>

    
    
</body>
</html>
