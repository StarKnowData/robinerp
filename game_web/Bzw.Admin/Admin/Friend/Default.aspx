<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Friend_Default" Codebehind="Default.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />

	<script src="/Public/Js/jquery.js"></script>

	<script src="/Public/Js/public.js"></script>

	<style type="text/css">
	.imeclose{ime-mode:disabled;}
	</style>
</head>
<body>
	<form id="form1" runat="server" enctype="multipart/form-data">
		<table width="100%" border="0" align="center" cellpadding="5" cellspacing="0" bgcolor="F2F8FF" class="admin_table2" style="border-collapse: collapse; border: 1px solid;">
			<tr>
				<th align="left">
					友情链接管理</th>
			</tr>
		</table>
		<table width="100%" border="0" align="center" cellpadding="0" cellspacing="1" bgcolor="#A4B6D7" class="admin_table" style="margin-top: 5px;">
			<tr align="center" bgcolor="#ffffff">
				<th>
					序号</th>
				<th>
					标题</th>
				<th>
					链接</th>
				<%--<th>
					图片</th>
				<th>
					类型</th>--%>
				<th>
					有效</th>
				<th>
					录入时间</th>
				<th>
					操作</th>
			</tr>
			<asp:Repeater ID="rptDataList" runat="server">
				<ItemTemplate>
					<%# ( ( Container.ItemIndex + 1 ) % 2 ) == 0 ? "  <tr align='center' bgcolor='#F7F8F8' height='25px' onmouseout=\"this.style.backgroundColor='#F7F8F8'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >" : "  <tr align='center' bgcolor='#ffffff' height='25px' onmouseout=\"this.style.backgroundColor='#ffffff'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >"%>
					<td>
						<%# anpPageIndex.PageSize * ( anpPageIndex.CurrentPageIndex - 1 ) + ( Container.ItemIndex + 1 ) %>
					</td>
					<td>
						<%# Eval("Title")%>
					</td>
					<td style="width: 160px; text-overflow: ellipsis; overflow: hidden;" title="<%# Eval("Link")%>">
						<%# Eval("Link")%>
					</td>
					<%--<td>
						<%# (string.IsNullOrEmpty(Eval( "ImagePath" ).ToString())) ? "无图" : "<img src='/Public/Thumbs.aspx?path=" + Server.UrlEncode( Eval( "ImagePath" ).ToString() ) + "&width=100&height=30' title='图片预览' alt='图片预览' />"%>
					</td>
					<td>
						<%# ((int)Eval("Type")) == 0 ? "文字链接" : "图片链接" %>
					</td>--%>
					<td>
						<%# (bool)Eval("IsEnable") ? "有效" : "无效"%>
					</td>
					<td>
						<%# Eval("InputTime","{0:yyyy-MM-dd}")%>
					</td>
					<td>
						<a href="Default.aspx?action=edit&params=<%#Eval("ID") %>">修改</a>&nbsp;&nbsp;|&nbsp;&nbsp;
						<a href='Default.aspx?action=del&params=<%# Eval("ID") %>' onclick="javascript:return confirm('警告！\r\n您确定要删除当前记录吗？删除后该记录将不能恢复!!');"><font color="red">删除</font></a></td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
			<asp:Label ID="NoUserList" runat="server" Text="<tr><td>暂无任何记录！</td></tr>" Visible="false"></asp:Label></table>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td style="height: 5px; background-color: White">
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td align="left">
					<div id="page_link" class="page_link">
						<webdiyer:aspnetpager runat="server" id="anpPageIndex" custominfohtml="%CurrentPageIndex%/%PageCount%，每页%PageSize%条" firstpagetext="首页" lastpagetext="尾页" nextpagetext="下一页" numericbuttoncount="5" pageindexboxtype="DropDownList" prevpagetext="上一页" showcustominfosection="Left" showpageindexbox="Always" submitbuttontext="Go" textafterpageindexbox="" textbeforepageindexbox="" urlpaging="True" alwaysshow="True" pagesize="15">
						</webdiyer:aspnetpager>
					</div>
				</td>
			</tr>
		</table>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td style="height: 5px; background-color: White">
				</td>
			</tr>
		</table>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td align="center">
					<table border="0" width="70%" cellpadding="5" cellspacing="0">
						<tr>
							<th colspan="2">
								添加\修改
							</th>
						</tr>
						<tr>
							<td align="right" width="30%">
								标题：
							</td>
							<td align="left">
								<asp:TextBox ID="txtTitle" runat="server" Width="230px" MaxLength="20"></asp:TextBox>
								<asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txtTitle" Display="Dynamic" ErrorMessage="请输入标题"></asp:RequiredFieldValidator></td>
						</tr>
						<tr>
							<td align="right">
								链接：
							</td>
							<td align="left">
								<asp:TextBox ID="txtLink" runat="server" Width="230px" MaxLength="1000"></asp:TextBox>
								<asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="txtLink" Display="Dynamic" ErrorMessage="请输入链接"></asp:RequiredFieldValidator></td>
						</tr>
						<%--<tr>
							<td align="right">
								类型：
							</td>
							<td align="left">
								<asp:RadioButtonList ID="rdolType" runat="server" RepeatDirection="Horizontal" RepeatLayout="Flow">
									<asp:ListItem Selected="True" Value="0">文字链接</asp:ListItem>
									<asp:ListItem Value="1">图片链接</asp:ListItem>
								</asp:RadioButtonList></td>
						</tr>
						<tr>
							<td align="right">
								图片上传：
							</td>
							<td align="left">
								<asp:PlaceHolder runat="server" ID="phFileUpload">
									<input id="fileImagePath" type="file" name="fileImagePath" />
								</asp:PlaceHolder>
								<asp:PlaceHolder runat="server" ID="phFileShow" Visible="false">
									<input id="txtImagePath" type="text" runat="server" readonly="readonly" />
									<input id="Button1" type="button" value="查看" onclick="OpenUrl($('#txtImagePath').val().Trim())" />
									<input id="Button2" type="button" value="删除" onclick="DelImage()" />
								</asp:PlaceHolder>
							</td>
						</tr>--%>
						<tr>
							<td align="right">
								有效：
							</td>
							<td align="left">
								<asp:CheckBox ID="cbxIsEnable" runat="server" Text="有效" /></td>
						</tr>
						<tr>
							<td align="right">
								排序数字：
							</td>
							<td align="left">
								<asp:TextBox ID="txtOrderID" runat="server" Width="230px" CssClass="imeclose" onkeypress="return KeyPressNum(this,event);" MaxLength="5"></asp:TextBox>
								<span style="color: Red;">数字越大越靠前</span>
							</td>
						</tr>
						<tr>
							<td align="right">
								备注：
							</td>
							<td align="left">
								<asp:TextBox ID="txtShortDesc" TextMode="MultiLine" Rows="3" runat="server" Width="230px" MaxLength="200"></asp:TextBox></td>
						</tr>
						<tr>
							<td colspan="2" align="center">
								<asp:Button ID="btnSubmit" runat="server" Text="提交" OnClick="btnSubmit_Click" Width="60px" /></td>
						</tr>
					</table>
				</td>
			</tr>
		</table>
	</form>

	<script>
		function DelImage()
		{
			OpenStateBar("正在删除，请稍候...");
			$.get(
				"default.aspx?action=delimg&params=" + GetRequest("params","0") + "&x=" + Math.random(),
				function(){
					LocationTo(location.href);
				}
			);
		}
	</script>

</body>
</html>
