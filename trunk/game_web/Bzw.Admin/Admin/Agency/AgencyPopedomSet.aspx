<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_AgencyPopedomSet" Codebehind="AgencyPopedomSet.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>代理商权限</title>
</head>
<body>
	<form id="form1" runat="server">
		<div>
			<table cellpadding="2" cellspacing="1" border="1" width="650" align="center" style="background-color: aliceblue; border-color: powderblue; border-collapse: collapse">
				<tr>
					<td height="25" align="center" style="border-color: powderblue; font-size: 14px;">
						<strong>设置代理商权限</strong></td>
				</tr>
				<tr>
					<td align="center" style="border-color: powderblue; font-size: 11px;">
						<table width="563" border="1" cellpadding="3" cellspacing="0" style="border-collapse: collapse; border-color: powderblue;">
							<tr>
								<td width="163" height="30" align="right">
									代理帐号：</td>
								<td width="87" align="left">
									<%=AgencyUserName %>
								</td>
								<td width="74" align="right">
									真实姓名：</td>
								<td width="159" align="left">
									<%=AgencyTrueName %>
								</td>
							</tr>
							<tr>
								<td colspan="4" align="left" style="height: 30px; font-size: 14px;">
									<asp:CheckBox runat="server" ID="cbxIsAddAgency" Text="允许添加直属代理" /><br />
									<asp:CheckBox runat="server" ID="cbxIsPickUpCashToAgency" style="margin-right:15px;" />
									<asp:CheckBox runat="server" ID="cbxIsGiveToAgency" /><br />
									<asp:CheckBox runat="server" ID="cbxIsPickUpCashToPlayer" style="margin-right:25px;" />
									<asp:CheckBox runat="server" ID="cbxIsGiveToPlayer" />
								</td>
							</tr>
							<tr>
								<td align="center" colspan="4">
									<asp:Button ID="btnMondify" runat="server" Text=" 修 改 " OnClick="btnMondify_Click" />&nbsp;
									<input id="btnBack" type="button" onclick="document.location.href='<%=Utility.Common.UrlValue %>'" value=" 返 回 " />
								</td>
							</tr>
						</table>
					</td>
				</tr>
			</table>
		</div>
	</form>
</body>
</html>
