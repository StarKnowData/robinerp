<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_DaoJuLog" Codebehind="DaoJuLog.aspx.cs" %>

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
				<td class="title_03" colspan="2">
					<strong><font color="red">道具购买记录</font></strong></td>
				<td colspan="5" class="title_03" align="right">
					<input type="text" value="按用户名搜索，请输入用户名" size="30" id="txtKey" name="txtKey"  />&nbsp;<input type="button" value=" 搜 索 " onclick="OnSearch()" class="put"/>&nbsp;<input type="button" value=" 清 空 " onclick="RefreshMe();" class="put" />
					<script>
						var info = "按用户名搜索，请输入用户名";
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
					</script>
				</td>
			</tr>
			<tr align="center">
				<td width="6%">
					ID号</td>
				<td width="20%">
					用户名</td>
				<td width="16%">
					购买道具名称</td>
				<td width="8%">
					数量</td>
				<td width="20%">
					花费金币</td>
				<td width="13%">
					类型</td>
				<td width="17%">
					时间</td>
			</tr>
			<asp:Repeater ID="PropList" runat="server" 
                onitemdatabound="PropList_ItemDataBound">
				<ItemTemplate>
					<tr align="center">
						<td>
							<%=TableID=TableID+1%>
						</td>
						<td>
							<%#Eval( "UserName" ).ToString()%>
						</td>
						<td>
							<%# Eval("PropName")%>
							&nbsp;</td>
						<td>
							<%# Eval("PropCount") %>
						</td>
						<td id="td1" runat="server">
							<%# Eval("Money") %>
						</td>
						<td>
							<%# Eval( "TargetID" ).ToString().ToLower() == "0" ? " <font color=\"red\">购买</font>" : "赠予：" +  Eval( "TargetUserName" ).ToString()  + ""%>
						</td>
						<td>
							<%# Eval("ActionTime") %>
						</td>
					</tr>
				 
				</ItemTemplate>
			</asp:Repeater>
			<asp:Label runat="server" Text="暂无任何记录！" ID="NoPropList" Visible="false"></asp:Label>
			<tr>
				<td colspan='7' align='right'>
				    花费金币合计：<%=sum %>
					<div id="page_link" class="page_link">
						<webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Never" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" UrlPaging="True" AlwaysShow="True" PageSize="20">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
		</table>
	</form>
	 
</body>
</html>
