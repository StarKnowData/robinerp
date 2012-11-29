<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Promotion_PrList" Codebehind="PrList.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" src="/Public/Js/jquery.js"></script>
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
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
			bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td colspan="2" >
					<strong>推广员列表</strong>
					</td>
					<td colspan="9" align="right">
					搜索用户名：<input type="text" value="请输入用户名" size="30" id="txtKey" name="txtKey" />&nbsp;<input type="button" value=" 搜 索 " onclick="OnSearch()" class="put" />
					&nbsp;<input type="button" value=" 清 空 " class="put"  onclick="RefreshMe();" />
					<script type="text/javascript" >
						var info = "请输入用户名";
						var o = $("#txtKey");
						o.css("color","gray");
						o.blur(
							function (){
								var oo = $(this);
								if (oo.val().Trim()==""){
									oo.val(info);
									oo.css("color","gray");
								}
							}
						);
						o.focus(							
							function(){
								var oo = $(this);
								oo.css("color","black");
								if (oo.val().Trim()== info){
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
						function OnSearch(){
							var sk=o.val().Trim();
							if(sk=="" || sk== info){
								alert("请先输入搜索用户名！");
								o.focus();
								return;
							}
							LocationToMeParam("un=" + encodeURIComponent(sk));
						}
					</script>
					</td>
			</tr>
			<tr align="center">
				<td>
					序号</td>
				<td>
					用户名</td>
				<td>
					昵称</td>
				<td>
					真实姓名</td>
				<td>
					电话</td>
				<td>
					地址</td>
				<td>
					总收入</td>
				<td>
					申请时间</td>
				<td>
					结算时间</td>
				<td>
					状态</td>
				<td>
					操作</td>
			</tr>
			<asp:Repeater ID="OkPrList" runat="server">
				<ItemTemplate>
					<tr align="center">
						<td>
							<%=TableID = TableID+1%>
						</td>
						<td>
							<%#  Eval("UserName") %>
						</td>
						<td>
							<%#  Eval("NickName") %>
						</td>
						<td>
							<%# Eval("TrueName") %>
						</td>
						<td>
							<%# Eval("Phone") %>
						</td>
						<td title="<%# Eval("Address") %>" style="text-decoration:underline;">
						
								<%# Utility.Common.CutStringUnicode(Eval("Address").ToString(),10,"...") %>
							
						</td>
						<td>
							<a href="AllMoney.aspx?params=<%# Eval("userid") %>" style="color: Red;">
								<%# GetTGIncome(Eval("userid").ToString ())%>
							</a>
						</td>
						<td width="10%">
							<%# Eval("ApplyTime")%>
							&nbsp;</td>
						<td width="10%">
							<%# Eval("CountTime")%>
							&nbsp;</td>
						<td>
							<%# Eval("Pass").ToString().ToLower() == "true" ? "<font color=\"red\">审核</font>" :"未审核" %>
						</td>
						<td>
							<a href='PrEdit.aspx?id=<%# Eval("id") %>'>修改</a>&nbsp;|&nbsp;<a href='PrDel.aspx?id=<%# Eval("id") %>'
								onclick="javascript:return confirm('您确定要删除当前记录吗？删除后将不能恢复!!');"><font color="red">删除</font></a>
							<br />
							<a href='PrListInfo.aspx?id=<%# Eval("userid") %>'>推广记录</a>&nbsp;|&nbsp;<a href="PrDetail.aspx?params=<%# Eval("userid") %>">充值提成</a>
							<br />
							<a href="PrBalanceLog.aspx?params=<%# Eval("userid") %>">结账日志</a>&nbsp;|&nbsp;<a
								href="AllMoney.aspx?params=<%# Eval("userid") %>">明细</a>
						</td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
			<asp:Label ID="NoPrList" runat="server" Text="<tr><td colspan='11' align='center'>暂无任何记录！</td></tr>" Visible="false"></asp:Label><tr>
				<td colspan='11' align='right'>
					<div id="page_link" class="page_link">
						<webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条"
							FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5"
							PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left"
							ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到"
							UrlPaging="True" AlwaysShow="True" PageSize="20">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
