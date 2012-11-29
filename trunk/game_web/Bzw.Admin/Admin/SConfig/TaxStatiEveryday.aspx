<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_TaxStatiEveryday" Codebehind="TaxStatiEveryday.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />

	<script type="text/javascript" src="/Public/Js/DatePicker/WdatePicker.js"></script>

	<script type="text/javascript" src="/Public/Js/jquery.js"></script>

	<script type="text/javascript" src="/Public/Js/public.js"></script>

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
	<form id="form1" runat="server">
		<table>
			<tr>
				<td style="height: 5px; width: 3px;">
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td class="title_03" colspan="4">
					<font color="red"><strong>每天游戏<%=UiCommon.StringConfig.RoomTaxName %>总额统计</strong></font>&nbsp;&nbsp;（共：<%=TotalTax %>）&nbsp;&nbsp; 选择日期：<input id="txtdate" type="text" name="txtdate" class="put" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd'})" />
					<asp:DropDownList ID="ddlGameName" runat="server">
					</asp:DropDownList>
					<input id="search" name="search" class="put" type="button" value=" 搜 索 " onclick="OnSearch();" />&nbsp;
					<input type="button" class="put" value=" 刷 新 " onclick="RefreshMe();" />

					<script>						
						var dd = $("#txtdate");	
						var type = $("#<%=ddlGameName.ClientID %>");
						var udd = decodeURIComponent(GetRequest("dd",""));
						var utype = decodeURIComponent(GetRequest("type",""));
											
						
						if(udd != "")
							dd.val(udd);
						if (utype != "0")	
							DropSetByValue("<%=ddlGameName.ClientID %>",utype);						
						//搜索事件
						function OnSearch()
						{	
							var key = type.find("option:selected").val().Trim();					 
							if( dd.val().Trim() == "" && key == "0" )
							{
								alert("请先输入日期或游戏名称再搜索！");
								return;
							}
							var url = location.href;							
							if(dd.val().Trim() != "")
								url = SetUrlParam(url,"dd=" + encodeURIComponent(dd.val().Trim()));	
							if ( key != "0")
								url = SetUrlParam(url,"type="  + encodeURIComponent(key));
										
							LocationTo(url);
						}
					</script>

				</td>
			</tr>
			<tr style="font-weight: bold; text-align: center;">
				<td>
					序号</td>
				<td>
					日期</td>
				<td>
					游戏名称</td>
				<td>
					游戏<%=UiCommon.StringConfig.RoomTaxName %>总额</td>
			</tr>
			<asp:Repeater ID="rptList" runat="server">
				<ItemTemplate>
					<tr style="text-align: center;">
						<td>
							<%=listids=listids+1 %>
						</td>
						<td>
							<%# Utility.Common.GetDateTime( Eval("StatTime").ToString())%>
						</td>
						<td>
							<%# Eval("NameID") %>
						</td>
						<td>
							<%# Eval("Tax") %>
						</td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
			<asp:Label ID="NoRecord" runat="server" Text="<tr><td colspan='4' align='center'>暂无记录！</td></tr>" Visible="false"></asp:Label>
		</table>
		<table>
			<tr>
				<td style="height: 5px; text-align: center;">
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td align="left">
					<div id="page_link" class="page_link">
						<webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
