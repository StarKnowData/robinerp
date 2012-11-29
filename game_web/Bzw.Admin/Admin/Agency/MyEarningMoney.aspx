<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_MyEarningMoney" Codebehind="MyEarningMoney.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>代理商收益报</title>
    <script src="/Public/Js/Global.js"></script>
    <script src="/Public/Js/My97DatePicker/WdatePicker.js"></script>
    <style type="text/css">
	*{font-family:Arial,'宋体'; font-size:12px;}
	</style>
</head>
<body>
    <form id="form1" runat="server">
		<table border="1px;" cellpadding="3" style="width: 100%; border-collapse: collapse;">
		    <tr><th style="text-align: center; background-color:aliceblue;border-color: powderblue;">查看代理商<%=Utility.Common.GetStringOfUrl("n")%>的收益报表</th></tr>
			<tr>
				<td>
				    开始日期：<asp:TextBox ID="dtpFrom" Width="85px"  MaxLength="10" runat="server"></asp:TextBox><span style="color:Red">*</span>
				    &nbsp;&nbsp;结束日期：<asp:TextBox ID="dtpTo" Width="85px"  MaxLength="10" runat="server"></asp:TextBox><span style="color:Red">*</span>
                    &nbsp;&nbsp;<asp:Button ID="btnSearch" runat="server" Text=" 查 询 " OnClick="btnSearch_Click" OnClientClick="return OnSearch()" />
                    <input id="btnBack" type="button" onclick="document.location.href='<%=Utility.Common.UrlValue %>'" value=" 返 回 "/>
                    查询时请先选择开始日期和结束日期
                    <script type="text/javascript" >
                        function OnSearch(){
                            var dtpFrom =document.getElementById('dtpFrom');
                            if(dtpFrom.value.trim()==''){
                                dtpFrom.focus();
                                return false
                            }
                            
                            var dtpTo =document.getElementById('dtpTo');
                            if(dtpTo.value.trim()==''){
                                dtpTo.focus();
                                return false
                            }
                            
                            return true;
                        }
                    </script>
				</td>
			</tr>
			<tr>
				<td>
					<table cellpadding="3" style="width: 100%; text-align: center; border-collapse: collapse; margin: 0px; padding: 0px;" border="1px;">
						<tr>
							<th>
								游戏类型</th>
							<th>
								门票贡献</th>
							<th>
								应得佣金</th>
							<th>
								应付佣金</th>
							<th>
								收益</th>
						</tr>
						<asp:Repeater ID="rptDataList" runat="server">
							<ItemTemplate>
								<tr>
									<td>
										<%# Eval("ComName")%>
									</td>
									<td>
										<%# UiCommon.StringConfig.MoneyChu100(Eval("SumMoney"))%>
									</td>
									<td>
										<%# UiCommon.StringConfig.MoneyChu100(Eval("MySumMoney"))%>
									</td>
									<td>
										<%# UiCommon.StringConfig.MoneyChu100(Eval("PayMoney"))%>
									</td>
									<td>
										<%# UiCommon.StringConfig.MoneyChu100(Eval("MyMoney"))%>
									</td>
								</tr>
							</ItemTemplate>
							<FooterTemplate>
							    <tr>
									<td>
										<a href='DirectTotal.aspx?id=<%= Utility.Common.GetStringOfUrl("id")+"&n="+Utility.Common.GetStringOfUrl("n")+"&sd="+GetStartTM()+"&ed="+GetEndTM() %>' title='点击进入直属代理和玩家统计页面'>游戏合计</a>
									</td>
									<td>
										<%=SumMoneyTotal %>
									</td>
									<td>
										<%=MySumMoneyTotal %>
									</td>
									<td>
										<%=PayMoneyTotal %>
									</td>
									<td>
										<%=MyMoneyTotal %>
									</td>
								</tr>
							</FooterTemplate>
						</asp:Repeater>
						<asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='5'>暂无记录...</td></tr>"></asp:Literal>
					</table>
				</td>
			</tr>
		</table>
    </form>
</body>
</html>
