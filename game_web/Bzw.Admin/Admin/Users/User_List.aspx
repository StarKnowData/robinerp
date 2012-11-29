<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Users_User_List" Codebehind="User_List.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title>无标题页</title>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<script src="/Public/Js/jquery.js" type="text/javascript"></script>
	<script src="/Public/Js/public.js" type="text/javascript"></script>
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
				<td class="title_03" colspan="14">
					<strong><font color="red">
						<%=UserListTitle%>
					</font></strong>
				</td>
			</tr>
			<tr bgcolor="#ffffff">
				<td class="title_03" colspan="14" style="height:35px">
			 
					&nbsp;&nbsp;&nbsp;类型
					<select name="userType" id="userType" style="width:90px;" onchange="Search()">
						<option value="all">所有</option>
						<option value="realplayer" selected="selected">真实玩家</option>
						<option value="robotplayer">机器人</option>
					</select> 
					&nbsp;&nbsp;&nbsp;排列条件：
					<select name="sortField" id="sortField" style="width:110px;" onchange="Search()">
						<option value="time">注册时间</option>
						<option value="money">总金币数</option>
						<option value="id">用户ID</option>
						<option value="vip">VIP日期</option>
						<option value="loginc">登录次数</option>
					</select>
					&nbsp;&nbsp;&nbsp;排列方式：
					<select name="sortType" id="sortType" style="width:70px;" onchange="Search()">
						<option value="desc">降序</option>
						<option value="asc">升序</option>
					</select>
				</td>
			</tr>
			<script type="text/javascript">
				var startSortField = GetRequest("sortfield", "");
				var startSortType = GetRequest("sorttype", "");
				var startUserType = GetRequest("usertype", "");
				if (startSortField != "") {
					DropSetByValue("sortField",startSortField);
				}
				if (startSortType != "") {
					DropSetByValue("sortType",startSortType);
				}
				if (startUserType != "") {
					DropSetByValue("userType", startUserType);
				}
				function Search() {
					var st = $("#sortType option:selected");
					var sr = $("#sortField option:selected");
					var su = $("#userType option:selected");
					var url = location.href;
					url = SetUrlParam(url, "sorttype=" + st.val().Trim());
					url = SetUrlParam(url, "sortfield=" + sr.val().Trim());
					url = SetUrlParam(url, "usertype=" + su.val().Trim());
					location.href = url;
				}
			</script>
			<tr align="center" bgcolor="#ffffff">
			 <td>全选<input name="cbxAllCheck" type="checkbox" onclick="SelectAll(this)" /></td>
				<td width="3%">
					序号</td>
				<td width="5%">
					用户ID号</td>
				<td width="12%">
					用户名</td>
				<%--<td width="3%">
					性别</td>--%>
				<td width="11%">
					呢称</td>
				<!--<td>注册IP</td>-->
				<td width="10%">
					注册日期</td>
				<td width="3%">
					禁止登录</td>
				<td width="9%">
					总金币数</td>
					<td><%=UiCommon.StringConfig.GoldName %>数</td>
				<td width="10%">
					VIP日期</td>
				<td width="4%">
					登录次数</td>
				<%--<td width="13%">
					游戏时间</td>--%>
				<td width="13%">地区</td>
				<td>注册IP</td>
			 
				<td width="10%">
					操作</td>
			</tr>
			<asp:Repeater ID="UserList" runat="server"  >
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
                        Userids = Userids + 1;		      
					%>
					 <td><input name="cbxCheck" type="checkbox" value="<%#Eval("UserID")%>" /></td>
					<td>
						<%# anpPageIndex.PageSize * anpPageIndex.CurrentPageIndex - anpPageIndex.PageSize + ( Container.ItemIndex + 1 )%>
					</td>
					<td>
						<%# Eval("UserID")%>
					</td>
					<td>
						<%# Eval("UserName")%>
					</td>
					<%--<td>
						<%# Man(Eval("userid").ToString())%>
					</td> --%>
					<td>
						<%# BCST.Common.CommonManager.String.CutString( Eval( "NickName" ).ToString() ,12,"...")%>
					</td>
					<td>
						<%# Convert.ToDateTime(Eval("RegisterTM")).ToString("yyyy-MM-dd")%>
					</td>
					<td>
						<%# Eval("Disabled").ToString().ToLower() == "1" ? "<font color=red>是</font>" : "否"%>
					</td>
					<td>
						<%# Eval("SumMoney")%>
					</td>
					<td>
					<%# Eval("Lotteries")%>
				    </td>
					<td>
						<%# IsVIP(Eval("userid").ToString())%>
					</td>
					<td>
						<%# Eval("AllLoginTime")%>
					</td>
					<%--<td>
						<%# converTimer(getSumPlayTimeCount(Eval("userid").ToString())) %>--%>
					<td>
						<%# GetAddressByIP(Eval("RegisterIP").ToString())%> 
					</td>
					<td><%#Eval("RegisterIP") %></td>  
					<td> 
						<a href='Edit_User.aspx?id=<%# Eval("Userid") %>'>修改</a>&nbsp;| &nbsp;<a href='GameList.aspx?userid=<%#Eval("Userid") %>'>游戏记录</a><br />
						<a href='Del_UserList.aspx?id=<%# Eval("Userid") %>&url=<%=Server.UrlEncode( Request.Url.ToString())  %>' onclick="javascript:return confirm('严重警告！您确定要删除当前记录吗？删除后该用户下记录将不能恢复!!');"><font color="red">删除</font></a>&nbsp;| &nbsp;<a href='UserGameSeach.aspx?id=<%# Eval("Userid") %>'>记录查询</a> <%--|<a href="UnLockUser.aspx?id=<%#Eval("Userid") %>">解锁</a>--%>
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
			<td width="30%" >
			        <input type="button" value="批量删除" onclick="return AllDel()" class="put" /> <input type="button"  value="批量禁用" onclick="return AllDisabled()" class="put" /> <input type="button"  value="批量启用" onclick=" return AllEnabled()" class="put" />
			    </td>
				<td align="left">
					<webdiyer:AspNetPager PageSize="10" ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页；每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True">
					</webdiyer:AspNetPager>
				</td>
			</tr>
		</table>
	</form>
	<script type="text/javascript">
	    function SelectAll(obj) {
	        var theTable = obj.parentElement.parentElement.parentElement;
	        var i;
	        var j = obj.parentElement.cellIndex;
	        for (i = 0; i < theTable.rows.length; i++) {
	            var objCheckBox = theTable.rows[i].cells[j].firstChild;
	            if (objCheckBox.checked != null) {
	                objCheckBox.checked = obj.checked;
	            }
	        }
	    }
	    var selectedlist = new Array();
	    function GetSelectedValue() {
	      
	        var selectedCheck = document.getElementsByName("cbxCheck");
	        //var hdfSelected =document.getElementById("hdfSelected");
	        for (var i = 0; i < selectedCheck.length; i++) {
	            if (selectedCheck[i].checked) {
	                selectedlist.push(selectedCheck[i].value);
	            }
	        }
	        if (selectedlist.length <= 0) {
	            alert("至少选择一条记录");
	            return false;
	        } 
	        //hdfSelected.value = selectedlist.toString();
	      
	    }
	    function AllDel() {
	        GetSelectedValue();
	        if (confirm("您确定要删除所选的记录吗？删除后将不能恢复!!")) {

	            document.location.href =location.href+ '&batchaction=batchdel&uid=' + selectedlist.toString();
	            
	        }
	        return true;
	    }
	    //批量禁用
	    function AllDisabled() {
	        GetSelectedValue();
	        if (confirm("您确定要禁用所选的记录吗？")) {
	            document.location.href = location.href + '&batchaction=batchdisabled&uid=' + selectedlist.toString();
	        }
	        return true;
	    }
	    //批量启用
	    function AllEnabled() {
	        GetSelectedValue();
	        if (confirm("您确定要启用所选的记录吗？!!")) {
	            document.location.href = location.href + '&batchaction=batcheabled&uid=' + selectedlist.toString();
	        }
	        return true;
	    }
	</script>
</body>
</html>
