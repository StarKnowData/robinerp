<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_GameInfo_GameMain" Codebehind="GameMain.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
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

	<script language="javascript" type="text/javascript">

function CheckForm() {
  if(document.getElementById("title").value == '') {
    alert('温馨提示：\n\n请输入关键字！');
    document.getElementById("title").focus();
    return false;
  }  
}
	</script>

</head>
<body>
	<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table2">
		<tr>
			<td class="title_03">
				<strong>游戏管理</strong></td>
		</tr>
		<tr>
			<td class="title_05">
				<a href="GameMain.aspx?type=1">审核游戏列表</a>
				<a href="GameMain.aspx?type=0">待审核游戏</a></td>
		</tr>
		<form name='search' method="get" action="" runat="server" onsubmit='return CheckForm();'>
			<!--<tr>
				<td class="title_05">
					游戏搜索：
					<input type="text" name="title" class="put" value="<%=sqltitle %>" />
					<asp:DropDownList ID="sotype" runat="server" class="put">
					</asp:DropDownList>
					<input type="hidden" name="actiontop" value="so">
					<asp:Button ID="Button1" runat="server" Text=" 搜 索 " class="put" OnClick="GameMainSo" />
				</td>
			</tr>-->
		</form>
	</table>
	<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td height="5">
			</td>
		</tr>
	</table>
	<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
		<tr>
			<td width="16%" align="center" valign="top">
				<table width="100%" border="0" align="center" cellpadding="5" cellspacing="0">
					<tr>
						<td align="center">
							<strong><b>
								<%=typeids.ToString().ToLower() == "1" ? "<font color=\"red\">审核游戏类别</font>" : "未审核游戏类别"%>
							</b></strong>
						</td>
					</tr>
					<asp:Repeater ID="GameTypeList" runat="server">
						<ItemTemplate>
							<tr>
								<td align='center'>
									<a href='GameMain.aspx?type=<%=typeids %>&sid=<%# Eval("kindid") %>'>
										<%# Eval("KindName")%>
									</a>
								</td>
							</tr>
						</ItemTemplate>
					</asp:Repeater>
					<asp:Label ID="NoGameTypeList" runat="server" Text="暂无任何分类！" Visible="false"></asp:Label>
				</table>
			</td>
			<td width="86%" align="center" valign="top">
				<asp:Repeater ID="GameMainList" runat="server">
					<HeaderTemplate>
						<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" style="border-collapse: collapse">
							<tr>
								<td width="35" align="center">
									序号</td>
								<td width="384" align="center">
									游戏名称</td>
								<td width="177" align="center">
									发布时间</td>
								<td width="63" align="center">
									属性</td>
								<td width="40" align="center">
									修改</td>
								<td width="39" align="center">
									删除</td>
							</tr>
					</HeaderTemplate>
					<ItemTemplate>
						<tr>
							<td align='center'>
								<%=tableids = tableids+1%>
							</td>
							<td align='left'>
								<%# Eval("Game_Name") %>
							</td>
							<td align='center'>
								<%# Eval("Update_Time") %>
							</td>
							<td align="center">
								<%# Eval("through").ToString().ToLower() =="true" ? "<font color=\"red\">审核</font>" :"未审核" %>
							</td>
							<td align="center">
								<a href="GameMainEdit.aspx?id=<%# Eval("Game_id") %>">修改</a></td>
							<td align="center">
								<a href='GameMainDel.aspx?id=<%# Eval("Game_id") %>' onclick="javascript:return confirm('您确定要删除该游戏吗？');">删除</a></td>
						</tr>
					</ItemTemplate>
				</asp:Repeater>
				<asp:Label ID="NoGameMainList" runat="server" Text="暂无任何记录！" Visible="false"></asp:Label>
				<tr>
					<td colspan="6" align="right">
						<div id="page_link" class="page_link">
							<webdiyer:AspNetPager PageSize="20" ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页；每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Never" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True">
							</webdiyer:AspNetPager>
						</div>
					</td>
				</tr>
	</table>
	</td> </tr> </table>
</body>
</html>
