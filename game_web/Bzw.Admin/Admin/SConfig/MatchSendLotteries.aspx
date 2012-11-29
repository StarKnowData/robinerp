<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_MatchSendLotteries" Codebehind="MatchSendLotteries.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title></title>
	<script src="/Public/Js/jquery.js"></script>

    <script src="/Public/Js/public.js"></script>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
</head>
<body>
	<form id="form1" runat="server">
	<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
		<caption>
			<font color='red'><strong>比赛赠送奖券参数配置列表</strong></font></caption>
			<tr>
                <td colspan="4">
				 <asp:DropDownList ID="ddlSmethod" runat="server" 
                      ></asp:DropDownList>
				 <input type="button" value="搜索" onclick="OnSearch();" />&nbsp;<input type="button" onclick="RefreshMe();" value="刷新" />
					 <script>
					     DropSetByValue("ddlSmethod", GetRequest("type", ""));
					     function OnSearch() {

					         LocationTo(SetUrlParam(location.href, "type=" + encodeURIComponent($("#ddlSmethod").val().Trim())));
					         return;
					     }
					 </script>
                </td>
            </tr>
		<tr>
		<th>所属方案案</th>
			<th>
				排名名次
			</th>
			<th>
				赠送数量
			</th>
			<th>
				操作
			</th>
		</tr>
		<asp:Repeater runat="server" ID="rptDataList">
			<ItemTemplate>
				<tr>
				<td align="center"><%#Eval("Name") %></td>
					<td align="center">
						<%# Eval( "Rank" )%>
					</td>
					<td align="center">
						<%# Eval( "GiveNum" ).ToString()%>张奖券
					</td>
					<td align="center">
						<a href="MatchSendLotteries.aspx?action=edit&params=<%# Eval("ID") %>&reurl=<%=Server.UrlEncode(Request.Url.AbsoluteUri) %>">修改</a>&nbsp;&nbsp; <a href="MatchSendLotteries.aspx?action=del&params=<%# Eval("ID") %>&reurl=<%=Server.UrlEncode(Request.Url.AbsoluteUri) %>" onclick="javascript:return confirm('确定要删除吗？\r\n注意：删除后将不会恢复!');">刪除</a>
					</td>
				</tr>
			</ItemTemplate>
		</asp:Repeater>
		<asp:Label ID="ltNonData" runat="server" Text="<tr><td colspan='3'>暂无任何数据！</td></tr>"></asp:Label>
		<tr>
			<td align="left" colspan="3">
				<webdiyer:aspnetpager runat="server" id="anpPageIndex" custominfohtml="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" firstpagetext="首页" lastpagetext="尾页" nextpagetext="下一页" numericbuttoncount="5" pageindexboxtype="DropDownList" prevpagetext="上一页" showcustominfosection="Left" showpageindexbox="Never" submitbuttontext="Go" textafterpageindexbox="" textbeforepageindexbox="" urlpaging="True" alwaysshow="True" pagesize="20">
					</webdiyer:aspnetpager>
			</td>
		</tr>
	</table>
	<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table" style="margin-top: 25px;">
		<tr>
			<th colspan="2">
				添加/修改比赛赠送奖券参数配置&nbsp;&nbsp;&nbsp;<h3><a href="MatchSendLotteries.aspx">添加</a></h3>
			</th>
		</tr>
		<tr>
		<th align="right">
				所属方案：
			</th>
			<td align="left">
			<asp:DropDownList  ID="ddlMethod" runat="server"></asp:DropDownList>
			</td>
		</tr>
		<tr>
			<th align="right">
				排名名次：
			</th>
			<td align="left">
				<asp:TextBox runat="server" ID="txtRank" CssClass="put" MaxLength="3" ></asp:TextBox>
				<asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txtRank" Display="Dynamic" ErrorMessage="请输入排名名次" ></asp:RequiredFieldValidator>
				<asp:CompareValidator ID="CompareValidator1" ControlToValidate="txtRank" Display="Dynamic" Operator="GreaterThan" ValueToCompare="0" Type="Integer" runat="server"  ErrorMessage="请输入大于0的整数"></asp:CompareValidator>
			</td>
		</tr>
		<tr>
			<th align="right">
				赠送数量：
			</th>
			<td align="left">
				<asp:TextBox runat="server" ID="txtGiveNum" CssClass="put" MaxLength="5" ></asp:TextBox>张奖券
				<asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="txtGiveNum" Display="Dynamic" ErrorMessage="请填写下载地址" ></asp:RequiredFieldValidator>
				<asp:CompareValidator ID="CompareValidator2" ControlToValidate="txtGiveNum" Operator="GreaterThanEqual" Display="Dynamic" ValueToCompare="0" Type="Integer" runat="server"  ErrorMessage="请输入大于0的整数"></asp:CompareValidator>
				&nbsp; </td>
		</tr>
		<tr>
			<th align="right">
				&nbsp;
			</th>
			<td align="left">
				<asp:Button runat="server" ID="btnSubmit" CssClass="put" Text=" 添 加 " OnClick="btnSubmit_Click"  />
			</td>
		</tr>
	</table>
	</form>
</body>
</html>
