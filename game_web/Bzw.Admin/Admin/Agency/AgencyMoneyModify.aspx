<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_UserManager_AgencyMoneyModify" Codebehind="AgencyMoneyModify.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>代理商帐上金币</title>
	<link href="/Admin/css/inc_style.css" rel="stylesheet" type="text/css" />
</head>
<body style="text-align: center">
	<form id="form1" runat="server">
		<div style="text-align: center; background-color: aliceblue; border: 1px outset; width: 98%; border-color: powderblue; vertical-align: middle;">
			<strong>代理商帐上金币</strong>
		</div>
		<div style="text-align: center; background-color: ivory; border: 1px outset; width: 98%; border-color: powderblue; vertical-align: middle;">
			<table cellpadding="5" cellspacing="0" border="0" style="text-align: center; width: 100%; font-size: 12px; border-collapse: collapse">
				<tr>
					<th colspan="2">
						代理帐号：<%=AgencyInfo["AgencyName"].ToString()%>
						&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;真实姓名：<%=AgencyInfo["TrueName"].ToString() %>
						&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;帐号当前金币：<%= UiCommon.StringConfig.MoneyChu100(AgencyInfo["Account"])%>。
					</th>
				</tr>
				<tr>
					<td style="text-align: right; height: 24px;" width="50%">
						金币修改为：</td>
					<td style="text-align: left; height: 24px;">
						<asp:TextBox ID="tbxAccount" MaxLength="9" Width="65" runat="server" Style="ime-mode: disabled;" onkeyup="if(isNaN(value))execCommand('undo')" />
						<asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="tbxAccount" Display="Dynamic" ErrorMessage="请输入大于或等于零的整数"></asp:RequiredFieldValidator>
						<asp:CustomValidator ID="CustomValidator1" runat="server" ControlToValidate="tbxAccount" Display="Dynamic" SetFocusOnError="True" ClientValidationFunction="ValidTextInput" ErrorMessage="请输入大于或等于零的整数"></asp:CustomValidator>
                        <script language="javascript">
                            function ValidTextInput(oSrc, args){
                                var p = new RegExp(/^(0+|([1-9]{1}[\d]*))$/gi);
                                var blVal = true;
                                if(!p.test(args.Value)){
                                    blVal = false;
                                }
                                args.IsValid = blVal;
                            }
                        </script>
					</td>
				</tr>
				<tr>
					<td colspan="2" align="center">
						<asp:Button ID="btnModfyMoney" runat="server" Text=" 修 改 " CssClass="put" OnClick="btnModfyMoney_Click" />&nbsp;&nbsp;
						<input type="button" id="btnReturn" class="put" onclick="location.href='<%=Utility.Common.UrlValue %>'" value=" 返 回 " />
					</td>
				</tr>
			</table>
		</div>
		<div style="text-align: center; background-color: aliceblue; border: 1px outset; margin-top: 20px; height: 35px; width: 98%; border-color: powderblue; vertical-align: middle; padding-top: 20px; font-size: 13px; font-weight: bold">
			该代理商帐号历史金币操作记录
		</div>
		<div style="font-size: 12px; width: 98%">
			<table border="1" bordercolor="#587073" cellpadding="3" cellspacing="0" width="100%" style="border-collapse: collapse;">
				<tr>
					<th>
						序号</th>
					<th>
						操作人</th>
					<th>
						代理商</th>
					<th>
						操作前金币</th>
					<th>
						操作金币</th>
					<th>
						操作后金币</th>
					<th>
						操作时间</th>
				</tr>
				<asp:Repeater runat="server" ID="rptDataList">
					<ItemTemplate>
						<tr>
							<td align="center">
								<%# anpPageIndex.PageSize * (anpPageIndex.CurrentPageIndex - 1) + ( Container.ItemIndex + 1 ) %>
							</td>
							<td align="center">
								<%# Eval("AdminName") %>
							</td>
							<td align="center">
								<%# Eval( "AgencyName" )%>
							</td>
							<td align="center">
								<%# UiCommon.StringConfig.MoneyChu100(Eval( "MoneyB" ))%>
							</td>
							<td align="center">
								<%# UiCommon.StringConfig.MoneyChu100(Eval( "Range" ))%>
							</td>
							<td align="center">
								<%# UiCommon.StringConfig.MoneyChu100(Eval( "MoneyA" ))%>
							</td>
							<td align="center">
								<%# Eval("InputDate","{0:yyyy-MM-dd HH:mm:ss}") %>
							</td>
						</tr>
					</ItemTemplate>
				</asp:Repeater>
				<asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='10'>暂无记录...</td></tr>"></asp:Literal></table>
			<table border="0" bordercolor="#587073" cellpadding="3" cellspacing="0" width="100%" style="margin-top: 10px; border-collapse: collapse;">
				<tr>
					<td>
						<webdiyer:AspNetPager ID="anpPageIndex" PageSize="20" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True" NumericButtonCount="5">
						</webdiyer:AspNetPager>
					</td>
				</tr>
			</table>
		</div>
	</form>
</body>
</html>
