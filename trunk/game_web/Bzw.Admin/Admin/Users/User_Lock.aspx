<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="User_Lock.aspx.cs" Inherits="Admin_Users_User_Lock" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>玩家锁定详情</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />

<style type="text/css">
<!--
body {
	background-color: #E4F7F8;
}
-->
</style>
	<script src="/Public/Js/public.js" type="text/javascript"></script>
	<script src="/Public/Js/jquery.js" type="text/javascript"></script>
	<script src="/Public/Js/admin.js" type="text/javascript"></script>
</head>
<body>
 <div align="center">
		<div align="left">
			<form name="form1" runat="server">
			<span>
			<asp:CheckBox ID="chkID" Text="帐号锁定"  runat="server"/>
				 </span>
					<span>
					  <asp:CheckBox ID="chkIP" Text="IP锁定" runat="server"  /></span>
					<br /><span>
					<asp:CheckBox ID="chkMcode" Text="机器码锁定" runat="server" />
					 </span>
					 <span>
					<asp:CheckBox ID="chkHard" Text="硬盘编码锁定" runat="server" />
					 </span>
				 <p></p>
				 <asp:Button runat="server" ID="btnSure"  Text="修改" 
                onclick="btnSure_Click" />
			 
			</form>
			</div>
			</div>
		 
</body>

</html>
