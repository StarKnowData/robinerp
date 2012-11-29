<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Games_GameBattleRooms" Codebehind="GameBattleRooms.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table2">
			<tr>
				<td class="title_03">
					<strong>混战房间管理</strong></td>
				<td class="title_03" align="right">
					<a href="GameBattleRoomsWrite.aspx">添加</a>
				</td>
			</tr>
		</table>
		<table border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td style="height:2px;">
					
				</td>
			</tr>
		</table>
		<asp:Repeater ID="rptDataList" runat="server">
			<HeaderTemplate>
				<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
					<tr>
						<td class="title_03" colspan="11">
							<strong>房间信息显示</strong></td>
					</tr>
					<tr>
						<td>
							序号</td>
						<td>
							房间ID</td>
						<td>
							房间名称</td>
						<td>
							开始时间</td>
						<td>
							结束时间</td>
						<td>
							操作</td>
					</tr>
			</HeaderTemplate>
			<ItemTemplate>
				<tr>
					<td>
						<%# Container.ItemIndex + 1 + anpPageIndex.PageSize * ( anpPageIndex.CurrentPageIndex - 1 ) %>
					</td>
					<td>
						<%# Eval( "BattleRoomID" )%>
					</td>
					<td>
						<%# Eval( "RoomName" )%>
					</td>
					<td>
						<%# Eval( "BeginTime", "{0:yyyy-MM-dd HH:mm:ss}" )%>
					</td>
					<td>
						<%# Eval( "EndTime", "{0:yyyy-MM-dd HH:mm:ss}" )%>
					</td>
					<td>
						<a href='GameBattleRoomsWrite.aspx?params=<%# Eval("BattleRoomID") %>'>修改</a>&nbsp;&nbsp;<a href='GameBattleRooms.aspx?action=del&params=<%# Eval("BattleRoomID") %>' onclick="javascript:return confirm('你确定要删除该房间吗？');">删除</a></td>
				</tr>
			</ItemTemplate>
		</asp:Repeater>
		<asp:Label ID="lbNonData" runat="server" Text="暂无任何记录！" Visible="false"></asp:Label>
		</table>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td style="height: 5px" style="background-color: White">
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td align="left">
					<div id="page_link" class="page_link">
						<webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="%CurrentPageIndex%/%PageCount%，每页%PageSize%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" UrlPaging="True" AlwaysShow="True" PageSize="30">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
