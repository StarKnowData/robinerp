<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="EditFineryID.aspx.cs" Inherits="Bzw.Web.Admin.FineryID.EditFineryID" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<style type="text/css">
<!--
body {
	background-color: #FFFFFF;
	margin-top: 0px;
}
-->
</style>
<script type="text/javascript">
	function GotoBack() {
		window.location.href = history.go(-1);
	}
</script>
</head>
<body>
    <form id="form1" runat="server">
    <div>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
		<!--FinelyID, UserID,  Price, IsUse, DateTime-->
			<tr>
				<td  colspan="2">
					<strong><font color="red">靓号编辑</font></strong></td>
			</tr>
			<tr>
				<td align="right">靓号</td>
				<td align="left">
					<asp:Label ID="Label1" runat="server" Text="Label"></asp:Label>
				</td>
			</tr>
			<tr>
				<td align="right">价格</td>
				<td align="left">
					<asp:TextBox ID="TextBox1" runat="server" MaxLength="8"></asp:TextBox>金币
				</td>
			</tr>
			<tr> 
				<td align="right">靓号描述</td>
				<td align="left">
					<asp:TextBox ID="ExplainTB" runat="server" Width="200"></asp:TextBox>(最多只允许20个字符，一个中文算2字符，多余会被截取)
				</td>
			</tr>
			<tr>
				<td align="right">是否上架</td>
				<td align="left">
					<asp:RadioButtonList ID="sjRDO" runat="server" RepeatDirection="Horizontal">
						<asp:ListItem Value="1">是</asp:ListItem>
						<asp:ListItem Value="0">否</asp:ListItem>
					</asp:RadioButtonList>
				</td>
			</tr>
			<tr>
				<td align="right">是否推荐</td>
				<td align="left">
					<asp:RadioButtonList ID="tjRDO" runat="server" RepeatDirection="Horizontal">
						<asp:ListItem Value="1">是</asp:ListItem>
						<asp:ListItem Value="0">否</asp:ListItem>
					</asp:RadioButtonList>
				</td>
			</tr>
			<tr>
				<td colspan="2" align="center">
					<asp:Button ID="Button1" runat="server" Text="确定修改" CssClass="put" onclick="Button1_Click" />
					<asp:Button ID="Button2" runat="server" Text="返回靓号列表" CssClass="put" onclick="Button2_Click" />
				</td>
			</tr>
		</table>
    </div>
    </form>
</body>
</html>
