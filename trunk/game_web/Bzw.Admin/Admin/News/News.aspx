<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_News_News" Codebehind="News.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
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
	<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table2">
		<tr>
			<td class="title_03">
				<strong>新闻资讯管理</strong></td>
		</tr>
		<tr>
			<td class="title_05">
				<a href="News.aspx">新闻列表</a>
				<a href="News.aspx?recommendation=1">推荐新闻</a>
				<a href="News.aspx?Istop=1">首页头条</a>
				<a href="News.aspx?through=1">待审核新闻</a>
				<a href="NewsType.aspx">新闻类别管理</a>
				<a href="News_Add.aspx">添加新闻</a>
		 
				<a href="NewsTypeAdd.aspx">添加新闻类别</a>
			</td>
		</tr>
		<tr>
			<td class="title_05">
				<song></song>
				<b>新闻分类</b> 
				<asp:Repeater ID="TypeList" runat="server">
					<ItemTemplate>
						&nbsp;&nbsp;<a href='News.aspx?cid=<%# Eval("typeid") %>'><%# Eval("TypeName") %>
						</a>
					</ItemTemplate>
				</asp:Repeater>
			</td>
		</tr>
	</table>
	<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td height="5">
			</td>
		</tr>
	</table>
	<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" style="border-collapse: collapse;">
		<tr>
			<td width="38">
				序号</td>
			<td width="458">
				新闻标题</td>
			<td width="140" align="center">
				发布时间</td>
			<td width="58" align="center" style="display: none">
				审核</td>
			<td width="59" align="center" style="display: none">
				推荐</td>
			<td width="45" align="center" style="display: none">
				头条</td>
			<td width="35" align="center">
				修改</td>
			<td width="44" align="center">
				删除</td>
		</tr>
		<asp:Repeater ID="NewsList" runat="server">
			<ItemTemplate>
				<tr>
					<td height="20" align='center'>
						<%=tableids = tableids+1%>
					</td>
					<td height="20" align='left'>
						<div style='color:<%#Eval("TitleColor") %>'><%# Eval("title")%></div>
					</td>
					<td height="20" align='center'>
						<%# Eval("issue_time") %>
					</td>
					<td height="20" align="center" style="display: none">
						<%# Eval("through").ToString().ToLower() == "true" ? " <font color=\"red\">审核</font>" : "未审核"%>
						&nbsp;</td>
					<td height="20" align="center" style="display: none">
						<%# Eval("recommendation").ToString().ToLower() == "true" ? "<font color=\"red\">推荐</font>" : "未推荐"%>
					</td>
					<td height="20" align="center" style="display: none">
						<%# Eval("Istop").ToString().ToLower() == "true" ? "<font color=\"red\">头条</font>" : "未头条"%>
					</td>
					<td height="20" align="center">
						<a href="NewsEdit.aspx?id=<%# Eval("News_id") %>">修改</a></td>
					<td height="20" align="center">
						<a href='NewsDel.aspx?id=<%# Eval("News_id") %>' onclick="javascript:return confirm('确定删除该新闻名称吗？删除后将不能恢复!');">删除</a></td>
				</tr>
			</ItemTemplate>
		</asp:Repeater>
		<asp:Label ID="NoNewsList" runat="server" Text="暂无任何数据！" Visible="false"></asp:Label>
		<tr>
			<td colspan="8" align="right">
				<div id="page_link" class="page_link">
					<webdiyer:AspNetPager PageSize="20" ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页；每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Never" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True">
					</webdiyer:AspNetPager>
				</div>
			</td>
		</tr>
	</table>
</body>
</html>
