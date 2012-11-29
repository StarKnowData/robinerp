<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Games_RoomRuleSet" Codebehind="RoomRuleSet.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title>房间规则明细</title>
</head>
<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />

<style type="text/css">
<!--
body {
	background-color: #E4F7F8;
}
-->
</style>	<script src="/Public/Js/jquery.js" type="text/javascript"></script>
	<script src="/Public/Js/public.js" type="text/javascript"></script>

	<script src="/Public/Js/admin.js" type="text/javascript"></script>
<body>
	<div align="center">
		<div align="left">
			<form name="form1">
				<span>
					<input type="checkbox" name="checkbox" value="1" <%=getRoomRule(1) %>/>会员房间</span>
				 <span>
					<input type="checkbox" name="checkbox" value="2" <%=getRoomRule(2) %>/>地址限制</span>
				<span><input type="checkbox" name="checkbox" value="4" <%=getRoomRule(4) %>/>允许旁观</span><br/><br/> 
				<span>
					<input type="checkbox" name="checkbox" value="8" <%=getRoomRule(8) %> />不许旁观</span>
				 <span>
					<input type="checkbox" name="checkbox" value="16" <%=getRoomRule(16) %> />自动坐下</span>
				<span>
					<input type="checkbox" name="checkbox" value="32" <%=getRoomRule(32) %> />限制坐位</span> <br/><br/>
				
				<span>
					<input type="checkbox" name="checkbox" value="64" <%=getRoomRule(64) %> />限制IP</span>
				<span>
					<input type="checkbox" name="checkbox" value="128" <%=getRoomRule(128) %> />记录游戏</span>
				<%-- <span>
					<input type="checkbox" name="checkbox" value="4096" <%=getRoomRule(4096) %> />比赛报名</span>--%><br/><br/> 
				
				
				
				<span>
					<input type="checkbox" name="checkbox" value="1024" <%=getRoomRule(1024) %> />禁止房间聊天</span>
				<span>
					<input type="checkbox" name="checkbox" value="2048" <%=getRoomRule(2048) %> />禁止游戏聊天</span><br/>
				<br/> 
				<%--<span>
					<input type="checkbox" name="checkbox" value="256" <%=getRoomRule(256) %> />停止时间控制</span> --%>
				<span>
					<input type="checkbox" name="checkbox" value="512" <%=getRoomRule(512) %> />是否所有人坐下才开始启动</span><br/>
				<br/>
				<span>
					<input type="checkbox" name="checkbox" value="524288" <%=getRoomRule(524288) %> />不扣除积分</span> 
				<span><input type="checkbox" name="checkbox" value="8192"<%=getRoomRule(8192) %>/>练习房</span> 
				<span><input type="checkbox" name="checkbox" value="1573504"<%=getRoomRule(1310720) %>/>比赛房</span><br/><br/> 
				<span><input type="checkbox" name="checkbox" value="262144" <%=getRoomRule(262144) %>/>排队机</span>
				<span><input type="checkbox" name="checkbox" value="65536"<%=getRoomRule(65536) %>/>防作弊</span>
				<span><input type="checkbox" name="checkbox" value="2097152" />U3D游戏</span>
				<input name="btn" id="btn" type="button" value="确定选择"  />
			</form>
			<font style="color:Red">勾选比赛房后，不能勾选排队机房</font>
		</div>
	</div>
</body>
</html>
<script type="text/javascript">
    $(document).ready(function() {
        $("#btn").click(function() {

        
        setValue();
       
        });
    });

 </script>
