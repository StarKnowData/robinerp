<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="NoBuyFineryID.aspx.cs" Inherits="Bzw.Web.Admin.FineryID.IsBuyFineryID" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
<script type="text/javascript" src="/public/js/jquery.js"></script>
<script type="text/javascript" src="/Public/Js/public.js"></script>

</head>
<body>
   <form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
		<!--FinelyID, UserID,  Price, IsUse, DateTime-->
			<tr>
				<td  colspan="7">
				<strong><font color="red">靓号管理  >  待售靓号</font></strong>
					<hr />
					<a href="FineryID.aspx">生成靓号</a> | <a href="NoBuyFineryID.aspx">待售靓号</a> | <a href="IsBuyFineryID.aspx">已售出靓号</a></td>
			</tr>
			<tr>
				<td colspan="7">
					靓号：<asp:TextBox ID="FineryID" runat="server" MaxLength="9"></asp:TextBox>价格：<asp:TextBox ID="pr" runat="server"></asp:TextBox> <asp:Label ID="msg" runat="server" ForeColor="red"></asp:Label>&nbsp;<input type="button" class="put" value="添加靓号" runat="server" onserverclick="Button1_Click"/>
					<hr />
					设定类型：<input name="sjCKB" type="checkbox" id="sjCKB"/>上架&nbsp;<input name="tjCKB" type="checkbox" id="tjCKB"/>推荐 
					<br/>设定规则：
					<input id="Radio10" name="typerd" type="radio" value="all" checked="checked"/>全部
					<input id="" name="typerd" type="radio" value="aabb"/>AABB
				    <input id="" name="typerd" type="radio" value="aabbcc"/>AABBCC
					<input id="Radio1" name="typerd" type="radio" value="abab"/> ABAB
				    <input id="Radio2" name="typerd" type="radio" value="ababab"/>ABABAB
					<input id="Radio3" name="typerd" type="radio" value="abcabc"/> ABCABC
					<input id="Radio4" name="typerd" type="radio" value="abgab"/> ABGAB
					<input id="Radio5" name="typerd" type="radio" value="3a"/> 3A
					<input id="Radio6" name="typerd" type="radio" value="4a"/> 4A
					<input id="Radio7" name="typerd" type="radio" value="5a"/> 5A及以上
				    <input id="Radio8" name="typerd" type="radio" value="4sun"/>4顺及以上
				    <input id="Radio9" name="typerd" type="radio" value="date"/>生日
					<br/>
					设定搜索靓号(模糊查询)：<input type="text" class="put" id="seachid" name="seachid" value="" maxlength="8"/>
					<br/><input type="button" class="put" value="搜索靓号" onclick="Seach()"/>	
					<!--AABB | AABBCC | ABAB | ABABAB | 3A | 4A | 5A及以上  | ABCABC | ABGAB | 4顺及以上 | 生日-->
				</td>
			</tr>
			<tr>
			<!--FineryID, UserID, PassWord, Price, IsBuy, IsUse, DateTime, IsTop-->
				<td style="display: none" width="1%">
				</td>
				<td align="center">
					靓号</td>
				<td align="center">
					价格（金币）</td>
				<td align="center">
					是否上架</td>
				<td align="center">
					是否推荐</td>
				<td align="center">
					靓号描述</td>
				<td align="center">
					靓号产生时间</td>
				<td align="center">
					编辑</td>
			</tr>
			<asp:Repeater ID="FrineryIDList" runat="server">
				<ItemTemplate>
						<%
							if( ( TableID ) % 2 == 0 )
							{
								Response.Write( "  <tr align='center' bgcolor='#E1E1E1' height='25px' >" );
							}
							else
							{
								Response.Write( "  <tr align='center' bgcolor='#ffffff' height='25px'>" );
							}       
						%>
						<td style="display: none">
							<%=TableID = TableID + 1%>
						</td>
						<td>
							<%#Eval("FineryID")%>
						</td>
						<td>
							<%#Eval("Price")%></td>
						<td>
							<%#Convert.ToBoolean(Eval("IsSale"))==true?"上架":"未上架" %></a></td>
						<td>
							<%#Convert.ToBoolean(Eval("IsTop"))==true?"推荐":"未推荐" %></td>
						<td align="center">
							<%#Eval( "Explain" )%></td>
						<td>
							<%#Eval("DateTime")%></td>
						<td>
							<a href="EditFineryID.aspx?id=<%#Eval("FineryID")%>">编辑</td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
			<asp:Label runat="server" Text="暂无任何记录！" ID="NoProList" Visible="false"></asp:Label>
			<tr>
			</tr>
			<tr>
				<td colspan='7' align='right'>
					<div id="page_link">
						<webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Never" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" UrlPaging="True" AlwaysShow="True" PageSize="20">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
		</table>
	</form>
<script type="text/javascript">
	var ftype = GetRequest("type", "all");
	var seachid = GetRequest("seachid", "");
	$("#seachid").val(seachid);
	$("input[@name='typerd'][value='" + ftype + "']").attr("checked", true);
	if (GetRequest("sjCKB", "") == "1")
		document.getElementById("sjCKB").checked = true
	if (GetRequest("tjCKB", "") == "1")
		document.getElementById("tjCKB").checked = true
	function Seach() {
		var url = location.href;
		var types = $("input[@name='typerd']:checked").val();
		var seachid = $("#seachid").val().Trim();
		url = SetUrlParam(url,"seachid=" + seachid);
		url = SetUrlParam(url, "type=" + types);
		//是否上架
		if (document.getElementById("sjCKB").checked) {
			url = SetUrlParam(url, "sjCKB=1");
		}
		else {
			url = SetUrlParam(url, "sjCKB=0");
		}
		//是否推荐
		if (document.getElementById("tjCKB").checked) {
			url = SetUrlParam(url, "tjCKB=1");
		}
		else {
			url = SetUrlParam(url, "tjCKB=0");
		}
		LocationTo(url);
	}
	
</script>
</body>
</html>
