<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Users_UserGameSeachList_xg" Codebehind="UserGameSeachList_xg.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
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
		<div>
			<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
				<tr>
					<td class="title_03">
						<strong>游戏记录相关玩家</strong></td>
				</tr>
				<tr>
					<td class="title_03">
						<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
							<tr>
								<th>
									序号</th>
								<th>
									用户名</th>
								<th>
									房间名</th>
								<th>
									桌子</th>
								<th>
									结束时总分</th>
								<th>
									结束时金币</th>
								<th>
									改变分数</th>
								<th>
									改变金币</th>
								<th>
									税</th>
							</tr>
							<asp:Repeater runat="server" ID="rptDataList">
								<ItemTemplate>
							<tr>
								<td align="center">
									<%# Eval("id") %>
								</td>
								<td align="center">
									<%# Eval("UserName") %>
								</td>
								<td align="center">
									<%# Eval("RoomName") %>
								</td>
								<td align="center">
									<%# Eval("DeskIndex") %>桌
								</td>
								<td align="center">
									<%# Eval( "SrcPoint" )%>
								</td>
								<td align="center">
									<%# Eval( "SrcMoney" )%>
								</td>
								<td align="center">
									<%# Eval( "ChangePoint" )%>
								</td>
								<td align="center">
									<%# Eval( "ChangeMoney" )%>
								</td>
								<td align="center">
									<%# Eval( "ChangeTax" )%>
								</td>
							</tr>
								</ItemTemplate>
							</asp:Repeater>
							<asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='20' align='center'>暂无数据。。。</td></tr>"></asp:Literal>
						</table>
						<%--<asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="False" DataKeyNames="id,UserID1" DataSourceID="SqlDataSource1" Width="100%" OnRowDataBound="GridView1_RowDataBound">
							<Columns>
								<asp:BoundField DataField="id" HeaderText="序号" InsertVisible="False" ReadOnly="True" SortExpression="id" />
								<asp:BoundField DataField="RoomName" HeaderText="房间名" SortExpression="RoomName" />
								<asp:BoundField DataField="DeskIndex" DataFormatString="{0}桌" HeaderText="桌子" SortExpression="DeskIndex" />
								<asp:BoundField DataField="UserName" HeaderText="用户名" SortExpression="UserName" />
								<asp:BoundField DataField="SrcPoint" HeaderText="结束时总分" SortExpression="SrcPoint" />
								<asp:BoundField DataField="SrcMoney" HeaderText="结束时金币" SortExpression="SrcMoney" />
								<asp:BoundField DataField="ChangePoint" HeaderText="改变分数" SortExpression="ChangePoint" />
								<asp:BoundField DataField="ChangeMoney" HeaderText="改变金币" SortExpression="ChangeMoney" />
								<asp:BoundField DataField="ChangeTax" HeaderText="税" SortExpression="ChangeTax" />
							</Columns>
							<RowStyle Height="25px" HorizontalAlign="Center" />
						</asp:GridView>
						<asp:SqlDataSource ID="SqlDataSource1" runat="server" ConnectionString="<%$ ConnectionStrings:constr %>" SelectCommand="SELECT * FROM TChangeRecordUser,Tusers,TChangeRecord,TGameRoomInfo WHERE RecordIndex= @RecordIndex and TChangeRecordUser.UserID=Tusers.UserID and TChangeRecordUser.RecordIndex=TChangeRecord.ID and TChangeRecord.RoomID=TGameRoomInfo.RoomID">
							<SelectParameters>
								<asp:QueryStringParameter Name="RecordIndex" QueryStringField="id" Type="Int32" />
							</SelectParameters>
						</asp:SqlDataSource>--%>
					</td>
				</tr>
			</table>
		</div>
	</form>
</body>
</html>
