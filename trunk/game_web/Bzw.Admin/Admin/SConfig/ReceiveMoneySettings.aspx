<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="ReceiveMoneySettings.aspx.cs" Inherits="Admin_SConfig_ReceiveMoneySettings" %>


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
					<strong><font color="red">	领取金币设置列表</font></strong></td>
			</tr>
		 
						<tr>
						 <th>记录ID</th>
 
							
							<th>
								领取金币数</th>
								<th>最少金币限制</th>
							 
                            <th>
								时间间隔
								</th>
							 <th>操作</th>
				 
						</tr>
						<asp:Repeater ID="rptDataList" runat="server">
							<ItemTemplate>
								<tr><td>
								<%=rowid+=1 %></td>
									 

									<td><%# Eval("ReceiveMoney")%></td>
								 	<td>
									 <%#Eval("MinMoney") %>
									</td>
									<td>
										<%#Eval("SpaceTime")%>
									</td>
								<td><a href='ReceiveMoneyEdit.aspx?id=<%#Eval("ID") %>'>修改</a>&nbsp;&nbsp;&nbsp;<a href='ReceiveMoneySettings.aspx?act=del&id=<%#Eval("ID") %>' onclick='{if(confirm("确定要删除吗?")){return true;}return false;}'>删除</a></td>
                                     				
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
