<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="GameContestRank.aspx.cs" Inherits="Admin_Games_GameContestRank" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
</head>
<body>
  <form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" class="admin_table2">
			<tr>
				<td align="center" bgcolor="F2F8FF" class="title_03">
					<strong>玩家比赛排行榜                 </strong>&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<asp:Button  
                        ID="btnAddRank" runat="server"  class="put" Text="生成排行榜" 
                        onclick="btnAddRank_Click" /></td>
			</tr>
		 
		</table>	<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<th>
					用户ID</th>
				<th>
					用户名</th>
					<th>虚拟金币数</th>
					<th>局数</th>
				<th>
					游戏名</th>
				<th>
					比赛开始时间</th>
				<th>
					比赛结束时间</th>
				<th>
					玩家退出游戏时间</th>
				 
			</tr>
			<asp:Repeater ID="rptDataList" runat="server">
				<ItemTemplate>
					<tr>
						<td align="center" style="width:5%;">
							<%# Eval("UserID") %>
						</td>
						<td align="center" style="width:10%;">
							<%# Eval("UserName") %>
						</td>
						<td align="center" style="width:10%;">
							<%# Eval("ContestScore")%>
						</td>
						<td align="center" style="width:10%;">
							<%# Eval("ContestCount")%>
						</td>
						<td align="center" style="width:10%;">
							<%# Eval("ComName")%>
						</td>
						<td align="center" style="width:15%;">
							<%# Eval("StartTime")%>
						</td>
						<td align="center" style="width:10%;">
							<%# Eval("EndTime")%>
						</td>
						<td >
							<%# Eval("LeftTime")%>
						</td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
			<tr>
				<td colspan="8">
					<div id="page_link" class="page_link">
						<webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="%CurrentPageIndex%/%PageCount%，每页%PageSize%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" UrlPaging="True" AlwaysShow="True" PageSize="20">
						</webdiyer:AspNetPager>
					</div>
					<asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='10'>暂无记录...</td></tr>"></asp:Literal>
				</td>
			</tr>
			</table>		
	</form>
</body>
</html>
