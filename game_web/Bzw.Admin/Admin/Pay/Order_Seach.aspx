<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Order_Seach.aspx.cs" Inherits="Bzw.Web.Admin.Pay.Order_Seach" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
<title></title>
<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
<style type="text/css">
body {
	background-color: #ffffff;
	margin-top: 0px;
}
</style>
<script type="text/javascript" src="/Public/Js/jquery.js"></script>
<script type="text/javascript" src="/Public/Js/public.js"></script>
<script>
	function Seach() 
	{
		var o = $("#order");
		//o.val().value=GetRequest("order","");
		var url = "order=" + o.val().Trim();
		LocationToMeParam(url);
	}
</script>
</head>
<body>
<form id="form2" runat="server">
<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF"  class="admin_table2">
<tr>
<td class="title_03"><strong>订单查询</strong></td>
</tr>
</table>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td height="5px"></td>
  </tr>
</table>
<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
<tr><td align="left">
订单号：<input name="order" id="order" type="text" value="" class="put"/>
<input name="submit" type="button" value=" 查询 " class="put" onclick="Seach()" style="width:50px;"/>
</td></tr>
</table>
    	<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">     
            <tr>
                <td>
                    序号</td>
                <td>
                    用户名</td>
                <td>
                    金额</td>
                <td>
                    兑换率</td>
                <td>
                    充值金币</td>
               <td>
                    充值后金币</td>
                <td>
                    定单号</td>
                <td>
                    提交时间</td>
                <td>
                    返回时间</td>
                <td>
                    支付状态</td>
                <td>
                    充值状态</td>
                <td>
                    充值类型</td>
            </tr>
            <asp:Repeater ID="rptDataList" runat="server">
                <ItemTemplate>
                    <tr>
                        <td>
							 <%=number=number+1 %>                  
                        </td>
                        <td>
                            <%# Eval("UserName") %></td>
                        <td>
                            <%# Eval("PayMoney")%></td>
                        <td>
                            <%# Eval("ExchangeRate")%></td>
                         <td>
                            <%# Eval("InMoney")%></td>
                         <td>
                            <%# Eval("MoneyAfter")%></td>
                        <td>
                            <%# Eval("OrderID") %></td>
                        <td>
                           <%# Eval("AddTime")%></td>
                        <td>
                            <%# Eval("BackTime") %>&nbsp;</td>
                        <td>
                            <%# Eval("PaySuccess").ToString().ToLower() =="true" ? "<font color=\"red\">已支付</font>" :"未支付" %></td>
                        <td>
                            <%# Eval("InSuccess").ToString().ToLower() =="true" ? "<font color=\"red\">已充值</font>" :"未充值" %></td>
                        <td>
                           <%# Eval("TypeInfo") %></td>
                    </tr>
                </ItemTemplate>
            </asp:Repeater>
            <asp:Label ID="ltNonData" runat="server" Text="<tr><td colspan='15' align='center'><font color='red'>没有搜索到结果，请放宽搜索条件</font></td></tr>" Visible="False"></asp:Label>
            <tr>
                <td colspan='15' align='right'>
                    <div id="page_link" class="page_link">
						<webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="%CurrentPageIndex%/%PageCount%，每页%PageSize%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" UrlPaging="True" AlwaysShow="True" PageSize="20">
						</webdiyer:AspNetPager>
                    </div>
                </td>
            </tr>
        </table>
	</form>
</body>
</html>