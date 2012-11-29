<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="FasciExchange.aspx.cs" Inherits="Admin_FasciExchange_FasciExchange" %>


<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <title></title>
    <script src="/Public/Js/jquery.js" type="text/javascript"></script>

	<script src="/Public/Js/public.js" type="text/javascript"></script> 
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<style type="text/css">
	 
		body {
	background-color: #FFFFFF;
	margin-top: 0px;
}
	</style>
</head>
<body>
    <form id="form1" runat="server">
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table" >
			 
		 <tr>
				<td class="title_03" colspan="11">
					<strong><font color="red">	魅力值兑换设置列表</font></strong></td>
			</tr>
		 
						<tr>
						 
 
							
							<th>
								道具ID</th>
								<th>道具名称</th>
							 
                            <th>
								魅力值数
								</th>
								<th>道具数</th>
							 <th>操作</th>
				 
						</tr>
						<asp:Repeater ID="rptDataList" runat="server">
							<ItemTemplate>
								<tr>
									<td><%# Eval("PropID")%></td>
									<td><%#Eval("PropName") %></td>
								 	<td>
									 <%#Eval("CharmValue") %>
									</td>
									<td>
										<%#Eval("PropCount")%>
									</td>
								<td><a href='FasciExchangeEdit.aspx?id=<%#Eval("ID") %>&pname=<%#Eval("PropName") %>'>修改</a>&nbsp;&nbsp;&nbsp;<a href='FasciExchange.aspx?act=del&id=<%#Eval("ID") %>' onclick='if(confirm("确定要删除吗?")){return true;}return false;'>删除</a></td>
                                     				
								</tr>
							</ItemTemplate>
						</asp:Repeater>
						<asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='15'>没有记录...</td></tr>"></asp:Literal>
					<tr>
				<td colspan='11' align='right'>
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

