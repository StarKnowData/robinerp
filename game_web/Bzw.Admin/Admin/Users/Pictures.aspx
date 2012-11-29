<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Users_Pictures" Codebehind="Pictures.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>无标题页</title>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<style type="text/css">
<!--
body {
	background-color: #FFFFFF;
	margin-top: 0px;
}
-->
</style>
	<script src="/Public/Js/jquery.js"></script>
	<script src="/Public/Js/public.js"></script>
</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table2">
			<tr>
				<td class="title_03">
					<strong>用户相片审核</strong></td>
				<td class="title_03" align="right">
					按会员查看：<input  type="text" id="txtUserName" name="txtUserName" value="请输入会员名" maxlength="30" />&nbsp;<input type="button" value=" 搜 索 " onclick="SelectMember();" />&nbsp; 按审核状态：<asp:DropDownList runat="server" ID="dropEnable" onchange="SelectEnableState();">
					</asp:DropDownList>&nbsp;<input type="button" value="重新搜索" onclick="RefreshMe();" />
				</td>
			</tr>
		</table>
		<asp:Repeater ID="UserList" runat="server">
			<HeaderTemplate>
				<table width="100%" border="0" cellspacing="0" cellpadding="0" style="background-color: White">
					<tr>
						<td style="height: 5px" style="background-color: White">
						</td>
					</tr>
				</table>
				<table width="100%" border="0" align="center" cellpadding="0" cellspacing="1" bordercolor="A4B6D7" bgcolor="#A4B6D7" class="admin_table">
					<tr bgcolor="#ffffff">
						<td class="title_03" colspan="12">
							<strong><font color="red">
								用户相片审核
							</font></strong>
						</td>
					</tr>
					<tr align="center" bgcolor="#ffffff">
						<th style="display: none" width="1%">
						</th>
						<th>
							序号</th>
						<th>
							图片预览</th>
						<th>
							图片名称</th>
						<th>
							图片描述</th>
						<th>
							所属用户</th>
						<th>
							上传时间</th>
						<th>
							审核状态</th>
						<th>
							操作</th>
					</tr>
			</HeaderTemplate>
			<ItemTemplate>
				<%#( (Container.ItemIndex + 1)  % 2 == 0) ? "  <tr align='center' bgcolor='#F7F8F8' height='25px' onmouseout=\"this.style.backgroundColor='#F7F8F8'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >" :"  <tr align='center' bgcolor='#ffffff' height='25px' onmouseout=\"this.style.backgroundColor='#ffffff'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >" %>
				<td style="display: none">
					<%#Container.ItemIndex + 1 %>
				</td>
				<td>
					<%# anpPageIndex.PageSize * anpPageIndex.CurrentPageIndex - anpPageIndex.PageSize + ( Container.ItemIndex + 1 )%>
				</td>
				<td title="点击预览">
						<%# "<img src='" + Eval("PicPath").ToString() + "' width='95' />"%>
					</td>
					<td>
						<%# Eval("PicName")%>
					</td>
					<td>
						<%# Eval("PicDescription")%>
					</td>
					<td>
						<%# Eval("UserName")%>
					</td>
					<td>
						<%# Eval("InputTime","{0:yyyy-MM-dd HH:mm:ss}")%>
					</td>
					<td>
						<%# Eval("Enable")%>
					</td>
					<td>
						<a href="<%# Eval("PicPath").ToString() %>" target="_blank">查看原图</a>&nbsp;| &nbsp;
						<a href='Pictures.aspx?action=enable&id=<%# Eval("ID") %>'>通过</a>&nbsp;| &nbsp;
						<a href='Pictures.aspx?action=disable&id=<%# Eval("ID") %>'>不通过</a>&nbsp;| &nbsp;
						<a href='Pictures.aspx?action=del&id=<%# Eval("ID") %>' onclick="javascript:return confirm('警告！\r\n您确定要删除当前记录吗？删除后该记录将不能恢复!!');">
							<font color="red">删除</font></a></td>
				</tr>
			</ItemTemplate>
			<FooterTemplate>
				</table>
			</FooterTemplate>
		</asp:Repeater>
		<asp:Label ID="NoUserList" runat="server" Text="暂无任何记录！" Visible="false"></asp:Label>
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
						<webdiyer:AspNetPager PageSize="30" runat="server" ID="anpPageIndex" CustomInfoHTML="%CurrentPageIndex%/%PageCount%，每页%PageSize%条"
							FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5"
							PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left"
							ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox=""
							UrlPaging="True" AlwaysShow="True">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
		</table>
	</form>
	<script>
		DropSetByValue("dropEnable",decodeURIComponent(GetRequest("es","none")));
		//DropSetByValue("dropMemberList",GetRequest("userid","none"));
		var memname = "请输入会员名";
		
		
		$(document).ready(
			function(){
				var x = decodeURIComponent(GetRequest("userid",memname));
				var o = $("#txtUserName");
				if(x == memname)
					o.css("color","gray");
				else
					o.val(x);
				o.focus(
					function(){
						if(o.val().Trim() == memname)
						{
							o.val("");
							o.css("color","black");
						}
					}
				);
				o.blur(
					function(){
						if(o.val().Trim() == "")
						{
							o.val(memname);
							o.css("color","gray");
						}
					}
				);
			}
		);
	
		function SelectMember()
		{
			var uid = $("#txtUserName").val().Trim();//DropGetValue("dropMemberList");
			if( uid==memname || uid=="")
			{
				//RefreshMeDelParam("(&)?userid=(\\d)+(&)?");
				return;
			}
			LocationTo(SetUrlParam(location.href,"userid=" + encodeURIComponent(uid)));
		}
		
		function SelectEnableState()
		{
			var u = DropGetValue("dropEnable").Trim();
			if(u == "none")
			{
				RefreshMeDelParam("(&)?es=[%a-zA-Z0-9]+(&)?");
				return;
			}
			LocationTo(SetUrlParam(location.href,"es=" + encodeURIComponent(u)));
		}
		
		$("table.admin_table").find("img").each(
			function(){
				var msg = "<img src='"+this.src+"' ";
				var img = new Image;
				img.src = this.src;
				if(img.width > 500)
					msg += "width='480' />";
				else 
					msg += "/>";
					
				this.style.cursor = "pointer";
				this.onclick = function()
				{
					Msg(msg,500);
				}
			}
		);
	</script>
</body>
</html>
