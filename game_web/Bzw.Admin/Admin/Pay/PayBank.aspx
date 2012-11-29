<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Pay_PayBank" CodeBehind="PayBank.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script src="/Public/Js/jquery.js" type="text/javascript"></script>
	<script src="/Public/Js/public.js" type="text/javascript"></script>
<script src="/Public/Js/admin.js" type="text/javascript"></script>
	 
    <style type="text/css">
        <!
        -- body
        {
            background-color: #FFFFFF;
            margin-top: 0px;
        }
        -- ></style>
</head>
<body>
    <form id="form1" runat="server">
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td class="title_03" colspan="15">
                <strong><font color="red">充值<%=lbState %>记录列表</font></strong> 
            </td>
        </tr>
        <tr>
            <td class="title_03" colspan="3">
            </td>
            <td colspan="8" class="title_03" align="right">
                <input type="text" value="按用户ID搜索，请输入用户ID" size="30" id="txtKey" name="txtKey" />&nbsp;<select
                    id="PayState" name="PayState" class="put"><option value="success">充值成功</option>
                    <option value="failed">充值失败</option>
                </select>&nbsp;排序<select id="ord" name="ord"><option value="backtime">返回时间</option><option value="paymoney">充值金额</option></select>
                <select id="ordType" name="ordType"><option value="desc">降序</option><option value="asc">升序</option></select>
                <input type="button" value=" 搜 索 " onclick="OnSearch()" class="put" />&nbsp;
                <input type="button" value=" 清 空 " onclick="RefreshMe();" class="put" />

                <script type="text/javascript">
                    var info = "按用户ID搜索，请输入用户ID";
                    var o = $("#txtKey");
                    o.css("color", "gray");
                    var o_ty = $("#PayState");
                    var ord = $("#ord");
                    o.blur(
							function() {
							    var oo = $(this);
							    if (oo.val().Trim() == "") {
							        oo.val(info);
							        oo.css("color", "gray");
							    }
							}
						);
                    o.focus(
							function() {
							    var oo = $(this);
							    oo.css("color", "black");
							    if (oo.val().Trim() == info) {
							        oo.val("");
							    }
							}
						);
							var r_ct = GetRequest("ps", "");
					
                    var k = decodeURIComponent(GetRequest("un", ""));
                    if (k != "") {
                        o.css("color", "black");
                        o.val(k);
                    }
                    if (r_ct != "") {
                        DropSetByValue("PayState", r_ct);
                    }

                    var r_ord = GetRequest("ord", "");

                    if (r_ord != "") {
                     
                        DropSetByValue("ord", r_ord);
                    }
                    var r_ordtype = GetRequest("ordtype", "");
                    if (r_ordtype != "") {
                        DropSetByValue("ordType", r_ordtype);
                    }
                    function OnSearch() {
                        var sk = o.val().Trim();
                        var url = "PayBank.aspx";
                       
                        if (o.val().Trim() != info && o.val().Trim() != "") {
                            url = SetUrlParam(url, "un=" + encodeURIComponent(o.val().Trim()));
                        }
                        if (o_ty.val().Trim() != "") {
                            url = SetUrlParam(url, "ps=" + o_ty.val().Trim());
                        }
                        url = SetUrlParam(url, "ord=" +ord.val().Trim());
                        url = SetUrlParam(url, "ordtype=" + $("#ordType").val().Trim());
                        //    LocationToMeParam("un=" + encodeURIComponent(sk));
                    
                        LocationTo(url);
                    }
                </script>

            </td>
        </tr>
        <tr>
            <td>
                序号
            </td>
            <td>
                充值人
            </td>
            <td>
                用户名
            </td>
            <td>
                金额
            </td>
            <td>
                兑换率
            </td>
            <td>
                充值金币
            </td>
            <td>
                充值后金币
            </td>
            <td>
                定单号
            </td>
            <td>
                提交时间
            </td>
            <td>
                返回时间
            </td>
            <td>
                支付状态
            </td>
            <td>
                充值状态
            </td>
            <td>
                充值类型
            </td>
            <td>
                操作
            </td>
        </tr>
        <asp:Repeater ID="rptDataList" runat="server">
            <ItemTemplate>
                <tr>
                    <td>
                        <%# anpPageIndex.PageSize * ( anpPageIndex.CurrentPageIndex - 1 ) + ( Container.ItemIndex + 1 ) %>
                    </td>
                    <td>
                        <%# Eval("TrueName")%>
                    </td>
                    <td>
                        <%# Eval("UserName") %>
                    </td>
                    <td>
                        <%# Eval("PayMoney")%>
                    </td>
                    <td>
                        <%# Eval("ExchangeRate")%>
                    </td>
                    <td>
                        <%# Eval("InMoney")%>
                    </td>
                    <td>
                        <%# Eval("MoneyAfter")%>
                    </td>
                    <td>
                        <%# Eval("OrderID") %>
                    </td>
                    <td>
                        <%# Eval("AddTime")%>
                    </td>
                    <td>
                        <%# Eval("BackTime") %>&nbsp;
                    </td>
                    <td>
                        <%# Eval("PaySuccess").ToString().ToLower() =="true" ? "<font color=\"red\">已支付</font>" :"未支付" %>
                    </td>
                    <td>
                        <%# Eval("InSuccess").ToString().ToLower() =="true" ? "<font color=\"red\">已充值</font>" :"未充值" %>
                    </td>
                    <td>
                        <%# Eval("TypeInfo") %>
                    </td>
                    <td>
                        <a href='PayBankDel.aspx?id=<%# Eval("payid") %>' onclick="javascript:return confirm('您确定要删除当前记录吗？删除后将不能恢复!!');">
                            <font color="red">删除</font></a>&nbsp;&nbsp;
                    </td>
                </tr>
            </ItemTemplate>
        </asp:Repeater>
        <asp:Label ID="ltNonData" runat="server" Text="<tr><td colspan='15' align='center'>暂无任何记录！</td></tr>"
            Visible="false"></asp:Label>
        <tr>
            <td colspan='15' align='right'>
                <div id="page_link" class="page_link">
                    <asp:Label ID="lblSumMoney" runat="server"></asp:Label>
                    <webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="%CurrentPageIndex%/%PageCount%，每页%PageSize%条"
                        FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5"
                        PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left"
                        ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox=""
                        UrlPaging="True" AlwaysShow="True" PageSize="15">
                    </webdiyer:AspNetPager>
                </div>
            </td>
        </tr>
    </table>
    </form>
</body>
</html>
