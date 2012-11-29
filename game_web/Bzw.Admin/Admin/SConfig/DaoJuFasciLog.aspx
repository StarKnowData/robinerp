<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_DaoJuFasciLog" Codebehind="DaoJuFasciLog.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>道具购买列表</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />

	<script src="/Public/Js/jquery.js"></script>

	<script src="/Public/Js/public.js"></script>

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
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td class="title_03" colspan="4">
					<strong><font color="red">魅力值清零道具购买、使用记录列表</font></strong></td>
				<td colspan="5" class="title_03" align="right">
					用户名：
					<input type="text" value="请输入用户名" class="put" size="30" id="txtKey" name="txtKey" />&nbsp;<input type="button" value=" 搜 索 " onclick="OnSearch()" class="put" />&nbsp;<input type="button" value=" 清 空 " onclick="RefreshMe();" class="put" />

					<script>
						var info = "请输入用户名";
						var o = $("#txtKey");
						o.css("color","gray");
						o.blur(
							function(){
								var oo = $(this);
								if(oo.val().Trim() == "")
								{
									oo.val(info);
									oo.css("color","gray");
								}
							}
						);
						o.focus(
							function(){
								var oo = $(this);
								oo.css("color","black");
								if(oo.val().Trim() == info)
								{
									oo.val("");
								}
							}
						);
						var k = decodeURIComponent( GetRequest("un",""));
						if(k != "")
						{
							o.css("color","black");
							o.val(k);
						}
						DropSetByValue("selType",GetRequest("type","none"));
						function OnSearch()
						{
							var sk = o.val().Trim();
							if(sk == "" || sk == info)
							{
								alert("请先输入搜索用户名。");
								o.focus();
								return;
							}
							LocationToMeParam("un=" + encodeURIComponent(sk));
						}
						function OnSelectChange(obj){
							var type = obj.options[obj.selectedIndex].value;
							if(isNaN(type))
							{
								RefreshMeDelParam("[&]?type=(\\d+)&?");
							}
							else
							{
								LocationToMeParam("type=" + type);
							}
						}
					</script>

				</td>
			</tr>
			<tr>
			<td colspan="9">
			 <strong>[道具销售共计]</strong>&nbsp;&nbsp;初级魅力值清零：&nbsp;<%=DiJiPropFasci %>&nbsp;&nbsp;&nbsp;中级魅力值清零：&nbsp;<%=ZhongJiPropFasci%>&nbsp;&nbsp;&nbsp;高级魅力值清零：&nbsp;<%=GaoJiPropFasci%>
			    
			</td>
			</tr>
			<tr>
				<td width="6%">
					ID号</td>
				<td width="10%">
					用户名</td>
				<td width="10%">
					用户昵称</td>
				<td width="16%">
					道具名称</td>
				<td width="8%">
					花费金币</td>
				<td width="10%">
					清零魅力值</td>
				<td width="10%">
					清零前魅力值</td>
				<td width="10%">
					清零后魅力值</td>
				<td width="17%">
					时间</td>
			</tr>
			<asp:Repeater ID="rptDataList" runat="server">
				<ItemTemplate>
					<tr>
						<td>
							<%#anpPageIndex.PageSize * ( anpPageIndex.CurrentPageIndex - 1 ) + ( Container.ItemIndex + 1 )%>
						</td>
						<td>
							<%# Eval("UserName")%>
						</td>
						<td>
							<%# Eval("NickName")%>
						</td>
						<td>
							<%# Eval("Title")%>
							&nbsp;</td>
						<td>
							<%# Eval("ChangeMoney")%>
						</td>
						<td>
							<%# Eval("ChangeFasci")%>
						</td>
						<td>
							<%# Eval("BeforeFasci")%>
						</td>
						<td>
							<%# Eval("AfterFasci")%>
						</td>
						<td>
							<%# Eval("InputDate") %>
						</td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
			<asp:Label runat="server" Text="<tr><td colspan='30'>暂无任何记录！</td></tr>" ID="lbNonData" Visible="false"></asp:Label><tr>
				<td colspan='13' align='right'>
					<div id="page_link" class="page_link">
						<webdiyer:AspNetPager PageSize="30" ID="anpPageIndex" runat="server" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True" AlwaysShow="True">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
