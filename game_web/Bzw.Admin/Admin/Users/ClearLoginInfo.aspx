<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Users_ClearLoginInfo" Codebehind="ClearLoginInfo.aspx.cs" %>
<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<script src="/Public/Js/jquery.js"></script>

	<script src="/Public/Js/public.js"></script>
	<style type="text/css">
<!--
body {
	background-color: #ffffff;
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
					<strong>解除用户登录限制</strong></td>
			</tr>
			<tr>
				<td class="title_03">
					当用户强退游戏或掉线时，有时会出现无法再登录大厅或游戏房间的情况，可使用本功能为用户解除此类登录限制。
				</td>
			</tr>
				<tr bgcolor="#ffffff">
				<td class="title_03" colspan="13" style="height:35px">
			 
					&nbsp;&nbsp;&nbsp;玩家类型
					<select name="userType" id="userType" style="width:90px;">
						<option value="all">所有</option>
						<option value="realplayer" selected="selected">真实玩家</option>
						<option value="robotplayer">机器人</option>
					</select> 
				 关键字：<input type="text" id="kw" name="kw" /> 搜索类型
				  <select name="kwType" id="kwType"><option value="UserID">用户ID</option><option value="UserName">用户名</option><option value="NickName">昵称</option></select>
				  &nbsp;<input type="button" value=" 搜 索 " onclick="OnSearch()" class="put" />
				</td>
			</tr>
			<script type="text/javascript">
			   
			    var startUserType = GetRequest("usertype", "");
			 
			    if (startUserType != "") {
			        DropSetByValue("userType", startUserType);
			    }
			    var key = GetRequest("kw", "");
			    if (key != "") {
			        $("#kw").val(key);
			    }
			    var kwType = GetRequest("ktype", "");
			    if (kwType != "") {
			        DropSetByValue("kwType", kwType);
			    }
			    function OnSearch() {
			 
			        var su = $("#userType option:selected");
			        var url = "ClearLoginInfo.aspx";
			        var kw = $("#kw").val();

			        var kwType = $("#kwType option:selected");
			   
			        url = SetUrlParam(url, "usertype=" + su.val().Trim());
			        if (kw != "") {
			            url = SetUrlParam(url, "kw=" + encodeURIComponent(kw.Trim()));
			            url = SetUrlParam(url, "ktype=" + encodeURIComponent(kwType.val().Trim()));
			        }
			        location.href = url;
			    }
			</script>
		</table> 
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td height="5px">
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			 
		<%--	<asp:PlaceHolder runat="server" ID="phInfo" Visible="false">--%>
				<tr>
					<th colspan="13">
						用户信息
					</th>
				</tr>
				<tr>
					<th>
						用户ID</th>
					<th>
						用户名</th>
					<th>
						昵称</th>
					<th>
						帐号状态</th>
					<th>
						已登录大厅</th>
					<th>
						已登录游戏</th>
						<th>解除用户登录</th>
				 
				</tr>
				<asp:Repeater ID="UserList" runat="server">
				<ItemTemplate>
					<tr>
						<td>
							<%# Eval("UserID") %>
						</td>
						<td>
							<%#Eval("UserName")%>&nbsp;
						</td>
						<td>
							<%#Eval("NickName")%>
						</td>
						<td>	<%#Eval("Disabled").ToString() == "1" ? "禁止" : "正常"%></td>
						<td align="center">
						<%# (Convert.ToBoolean( Eval("IsInZ"))) ?"已登录":"未登录" %>&nbsp;
					</td>
					<td align="center">
						 <%# (Convert.ToBoolean(Eval("IsInW"))) ? "已登录" : "未登录"%>&nbsp;
					</td>
					
					 <td>
					 <%#( (Convert.ToBoolean( Eval("IsInZ")))||(Convert.ToBoolean(Eval("IsInW"))))?"<a href='ClearLoginInfo.aspx?userid="+ Eval("UserID")+"'/>解除登录</a>":"  " %>
					 
					 
					 </td> 
					</tr>
				</ItemTemplate>
			</asp:Repeater>
            <tr>
            <td colspan="6"><a href="ClearLoginInfo.aspx?action=unLockAll" id="showLockAll" >解除所有用户登录</a></td>
            </tr>
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
<script type="text/javascript" language="javascript">
    if (document.getElementById("NoUserList") != null) {
        document.getElementById("showLockAll").style.display = "none";
    }
 </script>
</html>
