<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="UserLoginSearch.aspx.cs" Inherits="Admin_Users_UserLoginSearch" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
    	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<script src="/Public/Js/jquery.js" type="text/javascript"></script>
	<script src="/Public/Js/public.js" type="text/javascript"></script>
	<script type="text/javascript" src="/Public/Js/DatePicker/WdatePicker.js"></script>
	<script src="/Public/Js/admin.js" type="text/javascript"></script>
	<style type="text/css">
<!--
body {
	background-color: #FFFFFF;
	margin-top: 0px;
}
-->
</style>
</head>
<body>
    <form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table2">
			<tr>
				<td class="title_03">
					<strong>会员管理</strong></td>
			</tr>
		</table>
		<table width="100%" border="0" cellspacing="0" cellpadding="0" style="background-color: White">
			<tr>
				<td style="height: 5px; background-color: White">
				</td>
			</tr>
		</table>
		<table width="100%" border="0" align="center" cellpadding="0" cellspacing="1" bordercolor="#A4B6D7" bgcolor="#A4B6D7" class="admin_table">
			<tr bgcolor="#ffffff">
				<td class="title_03" colspan="13">
					<strong><font color="red">
						会员登录记录
					</font></strong>
				</td>
			</tr>
			<tr bgcolor="#ffffff">
				<td class="title_03" colspan="13" style="height:35px">
			 登录时间 从：<input name="bt" id="bt" type="text" size="10" class="put" onfocus="WdatePicker({maxDate:'#F{$dp.$D(\'et\')}',dateFmt:'yyyy-MM-dd'})"/>
到：<input name="et" id="et" type="text" size="10"class="put" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'bt\')}',dateFmt:'yyyy-MM-dd'})"/>
            关键字：<input type="text" name="kw" id="kw" class="put" />&nbsp;&nbsp;
            <select name="sel" id="sel">
            <option value="1">根据用户名</option>
            <option value="2">根据用户ID</option>
            <option value="3">根据IP地址</option>
            <option value="4">根据机器码</option> 
            <option value="5">根据硬盘码</option>
            </select>
				 <input type="checkbox" name="IsLike" id="IsLike"  />模糊查询<br />
				 同一<select id="sel2" name="sel2"><option value="ip">IP地址</option><option value="mcode">机器码</option>
				 </select>&nbsp;&nbsp;&nbsp;登录次数>
				 <input type="text" name="LoginCount" id="LoginCount" value="0" size="5" class="put" /> &nbsp;&nbsp;&nbsp;  状态<select id="sel3" name="sel3"><option value="0">所有</option><option value="1">限制</option><option value="2">正常</option></select>
				
				 排列条件：<select id="sel4" name="sel4"><option value="time">登录时间</option><option value="mcode">机器码</option><option value="ip">IP地址</option></select>&nbsp;&nbsp;&nbsp;排列方式：<select id="sel5" name="sel5"><option value="desc">降序</option><option value="asc">升序</option></select>
				 <input name="submit" type="button" value=" 查询 " class="put" onclick="Search()"/> <input type="button" value="刷新" class="put" onclick="location.href='UserLoginSearch.aspx';" />     <font color="red">注：红色表示该值被禁止</font>   
				</td>
			</tr>
			<script type="text/javascript">
			   
			    var startSortField = GetRequest("sel", "");
			    var startSel2 = GetRequest("sel2", "");
			    var startSel3 = GetRequest("sel3", "");
			    var startSel4 = GetRequest("sel4", "");
			    var startSel5 = GetRequest("sel5", "");
			    
			    
			    var bt = $("#bt");
			    var et = $("#et");
			    var kw1 = $("#kw");
			    var sel = $("#sel");
			    var sel2 = $("#sel2");
			    var sel3 = $("#sel3");
			    var sel4 = $("#sel4");
			    var sel5 = $("#sel5");
			    var isLike = $("#IsLike");
			    var loginNum = $("#LoginCount");
			    if (startSortField != "") {
			        DropSetByValue("sel", startSortField);
			    }
			    if (startSel2 != "")
			        DropSetByValue("sel2", startSel2);
			    if (startSel3 != "")
			        DropSetByValue("sel3", startSel3);
			    if (startSel4 != "")
			        DropSetByValue("sel4", startSel4);
			    if (startSel5 != "")
			        DropSetByValue("sel5", startSel5);
			    if (decodeURIComponent(GetRequest("IsLike", "")) == "1") {
			        document.getElementById("IsLike").checked = true;
			    }  
			     bt.val(decodeURIComponent(GetRequest("bt","")));
			     et.val(decodeURIComponent(GetRequest("et", "")));

			     kw1.val(decodeURIComponent(GetRequest("kw", "")));
		 
			     loginNum.val(decodeURIComponent(GetRequest("loginCount","0")));
			   function Search() {
			       // if (bt.val().Trim() != "" || et.val().Trim() != "" || kw1.val().Trim() != "") {
			       var url = location.href;
			       url = SetUrlParam(url, "bt=" + encodeURIComponent(bt.val().Trim()));
			          url = SetUrlParam(url, "kw=" + ((kw1.val().Trim() != "") ? encodeURIComponent(kw1.val().Trim().replace('\\','$')) : ""));  
			           url = SetUrlParam(url, "et=" + encodeURIComponent(et.val().Trim()));
			           
			           url = SetUrlParam(url, "IsLike=" +encodeURIComponent( ((document.getElementById("IsLike").checked == true) ? "1" : "0")));

			           url = SetUrlParam(url, "sel=" + encodeURIComponent(sel.val().Trim()));

			           url = SetUrlParam(url, "sel2=" + encodeURIComponent(sel2.val().Trim()));

			           url = SetUrlParam(url, "sel3=" + encodeURIComponent(sel3.val().Trim()));

			           url = SetUrlParam(url, "sel4=" + encodeURIComponent(sel4.val().Trim()));

			           url = SetUrlParam(url, "sel5=" + encodeURIComponent(sel5.val().Trim()));

			           url = SetUrlParam(url, "loginCount="+encodeURIComponent(loginNum.val().Trim()));
			           location.href = url;
			     
			         return;
			      // }
			         //alert("请先输入您要搜索的关键字，或选择要查看的时段。");
			     } function abc() {
			     location.href = 'UserLoginSearch.aspx';
			    }
			</script>
			<tr align="center" bgcolor="#ffffff">
				<td width="3%">
					序号</td>
				<td width="5%">
					用户ID号</td>
				<td width="12%">
					用户名</td>
				<td>用户昵称</td>
				<td>注册日期</td>
				<td>登录时间</td>
			    <td width="12%">机器码</td>
			     <td>硬盘编码</td>
			    <td width="10%">登录IP</td>
				<td width="10%">地区</td> 
				<td>状态</td>
				<td width="10%">
					操作</td>
			</tr>
			<asp:Repeater ID="UserList" runat="server">
				<ItemTemplate>
				<%
						if( ( Userids ) % 2 == 0 )
						{
							Response.Write( "  <tr align='center' bgcolor='#F7F8F8' height='25px' onmouseout=\"this.style.backgroundColor='#F7F8F8'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >" );
						}
						else
						{
							Response.Write( "  <tr align='center' bgcolor='#ffffff' height='25px' onmouseout=\"this.style.backgroundColor='#ffffff'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >" );
						}       
					%>
				<td>
				<%# anpPageIndex.PageSize * anpPageIndex.CurrentPageIndex - anpPageIndex.PageSize + ( Container.ItemIndex + 1 )%>
					 </td>
					<td>
						 
						<%# (Convert.ToBoolean( Eval("Disabled"))) ? "<font color='red'>" + Eval("UserID") + "</font>" : Eval("UserID")%>
					</td>
					<td>
						<%# Eval("UserName")%>
					</td>
					 <td><%# Eval("NickName") %></td>
					 <td><%#Eval("RegisterTM") %></td>
					 <td><%#Eval("LastLoginTM")%></td>
					<td>  
						<%#  (Convert.ToBoolean( Eval("IsLockCode"))) ? "<font color='red'>" + Eval("MachineCode") + "</font>" : Eval("MachineCode")%>
					</td> 
					<td><%#  (Convert.ToBoolean(Eval("IsLockHard"))) ? "<font color='red'>" + Eval("HardID") + "</font>" : Eval("HardID")%> </td>
					<td> 
						<%# (Convert.ToBoolean(Eval("IsLimitIP"))) ? "<font color='red'>" + Eval("LastLoginIP") + "</font>" : Eval("LastLoginIP")%>
					</td>
					 <td>
						<%# GetAddressByIP(Eval("LastLoginIP").ToString())%> 
					</td>
				     <td><%# ( Convert.ToBoolean(Eval("Disabled")) || Convert.ToBoolean(Eval("IsLockCode")) || Convert.ToBoolean(Eval("IsLimitIP"))) ? "限制" : "正常"%></td>
					<td> 
					<a href='Edit_User.aspx?id=<%# Eval("Userid") %>'>详细</a>&nbsp;| &nbsp; <a href="#" onclick="openRoomRuleDiv('User_Lock.aspx?limitID=<%#Eval("Disabled") %>&limitIP=<%#Eval("IsLimitIP") %>&limitMcode=<%# Eval("IsLockCode")%>&limitHard=<%#Eval("IsLockHard") %>&uid=<%#Eval("UserID") %>&m=<%# Eval("MachineCode")%>&h=<%#Eval("HardID").ToString().Replace('\\','*') %>&ip=<%# Eval("LastLoginIP") %>',350,120);setTimeout('abc()',5000); " >修改</a><br />
					<a href='UserGameSeach.aspx?id=<%# Eval("Userid") %>'>记录查询</a>  
	                 </td>
					</tr>
				</ItemTemplate>
				
			</asp:Repeater>
		</table>
		<asp:Label ID="NoUserList" runat="server" Text="暂无任何记录！" Visible="false"></asp:Label>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td style="height: 5px; background-color: White">
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td align="left">
					<webdiyer:AspNetPager PageSize="20" ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页；每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True">
					</webdiyer:AspNetPager>
				</td>
			</tr>
		</table>
	</form>
	 
</body>
</html>

