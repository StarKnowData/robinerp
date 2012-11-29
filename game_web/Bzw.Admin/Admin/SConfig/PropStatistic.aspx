<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_PropStatistic" Codebehind="PropStatistic.aspx.cs" %>
<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
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
        <table width="100%" border="0" align="center" cellpadding="5" cellspacing="0" bgcolor="F2F8FF" class="admin_table2" style="border-collapse: collapse; border: 1px solid;">
			<tr>
				<th align="left">
					每日道具消耗量统计</th>
			</tr>
		</table>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr align="center">
				<td>
					序号</td>
				<td>
					日期</td>
				<td>
					负分清零</td>
				<td>
					送鲜花</td>
				<td>
					拍砖头</td>
				<td>
					小喇叭</td>
				<td>
					大喇叭</td>
				<td>
					1小时双倍积分卡</td>
				<td>
					3小时双倍积分卡</td>
				<%--<td>
					飞吻</td>
				<td>
					扇耳光</td>--%>
			</tr>
            <asp:Repeater ID="rpList" runat="server">
                <ItemTemplate>
                    <%# ( ( Container.ItemIndex + 1 ) % 2 ) == 0 ? "  <tr align='center' bgcolor='#F7F8F8' height='25px' onmouseout=\"this.style.backgroundColor='#F7F8F8'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >" : "  <tr align='center' bgcolor='#ffffff' height='25px' onmouseout=\"this.style.backgroundColor='#ffffff'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >"%>
						<td>
							<%=Rowid = Rowid + 1%>
						</td>
						<td>
							<%#Eval("ActionTime")%>
						</td>
						<td>
							<%#Eval("负分清零")%>
						</td>
						<td>
							<%#Eval("送鲜花")%>
						</td>
						<td>
							<%#Eval("拍砖头")%>
						</td>
						<td>
							<%#Eval("小喇叭")%>
						</td>
						<td>
							<%#Eval("大喇叭")%>
						</td>
						<td>
							<%#Eval( "一小时双倍积分卡" )%>
						</td>
						<td>
							<%#Eval( "三小时双倍积分卡" )%>
						</td>
						<%--<td>
							<%#Eval( "飞吻" )%>
						</td>
						<td>
							<%#Eval( "扇耳光" )%>
						</td>--%>
					</tr>
                </ItemTemplate>
            </asp:Repeater>
            <asp:Label ID="NoDataList" runat="server" Text="暂无任何记录！" Visible="false"></asp:Label>
        </table>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td align="left">
					<div id="page_link" class="page_link">
						<webdiyer:AspNetPager runat="server" ID="WebPager1" CustomInfoHTML="%CurrentPageIndex%/%PageCount%，每页%PageSize%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" AlwaysShow="True" PageSize="20" OnPageChanging="WebPager1_PageChanging">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
		</table>
		
	</form>

</body>
</html>
