<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Games_RoomRule" Codebehind="RoomRule.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>房间规则明细</title>
</head>
<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
<style type="text/css">
<!--
body {
	background-color: #E4F7F8;
}
-->
</style>
<script language="javascript">
function getTheValue()
{
	var temp=0;
	for ( i = 0 ; i< document.form1.elements.length;i++)
	{
		var e = document.form1.elements[i];
		if (e.checked)
			{
				temp = temp+parseInt(e.value);
			}
	}
	return temp;
}
</SCRIPT>
<body>
<div align="center">
<div align="left">
<form name="form1">
<span><input type="checkbox" name="checkbox" disabled ="disabled" value="1" <%=getRoomRule(1) %>/>会员房间</span>
<span><input type="checkbox" name="checkbox" disabled ="disabled" value="2" <%=getRoomRule(2) %>/>地址限制</span>
<%--<span><input type="checkbox" name="checkbox" value="4" <%=getRoomRule(4) %>>允许旁观</span>--%>
<span><input type="checkbox" name="checkbox" disabled ="disabled"  value="8" <%=getRoomRule(8) %>/>不许旁观</span><br><br>
	
<span><input type="checkbox" name="checkbox" disabled ="disabled" value="16" <%=getRoomRule(16) %>/>自动坐下</span>
<span><input type="checkbox" name="checkbox" disabled ="disabled" value="32" <%=getRoomRule(32) %>/>限制坐位</span>
<span><input type="checkbox" name="checkbox" disabled ="disabled" value="64" <%=getRoomRule(64) %>/>限制IP</span><br><br>
<span><input type="checkbox" name="checkbox" disabled ="disabled" value="128" <%=getRoomRule(128) %>/>记录游戏</span>
<span><input type="checkbox" name="checkbox" disabled ="disabled" value="4096" <%=getRoomRule(4096) %>/>比赛报名</span><br><br>
<span><input type="checkbox" name="checkbox" disabled ="disabled" value="1024" <%=getRoomRule(1024) %>/>禁止房间聊天</span>
<span><input type="checkbox" name="checkbox" disabled ="disabled" value="2048" <%=getRoomRule(2048) %>/>禁止游戏聊天</span><br><br>
<span><input type="checkbox" name="checkbox" disabled ="disabled" value="256" <%=getRoomRule(256) %>/>停止时间控制</span><br><br>
<span><input type="checkbox" name="checkbox" disabled ="disabled" value="512" <%=getRoomRule(512) %>/>是否所有人坐下才开始启动</span><br><br>
<span><input type="checkbox" name="checkbox" disabled ="disabled" value="524288" <%=getRoomRule(524288) %>/>不扣除积分</span><br><br>
</form>
</div>
</div>
</body>
</html>
