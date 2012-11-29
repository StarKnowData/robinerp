<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_LotteryLog" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title></title>
  
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" pageType="8" />
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
            <WebService:Control ID="webservice1" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    中奖名单</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 中奖名单</p>
            </div>
            <div id="sub_nr">
                <div class="cz">
                    <div id="rank">
                        <div class="rank_title">
                            所有玩家抽奖记录</div>
                        <table width="100%" border="0" cellspacing="0" cellpadding="0">
                            <thead>
                                <tr>
                                    <th>
                                        序号
                                    </th>
                                    <th>
                                        玩家名称
                                    </th>
                                    <th>
                                        奖品名称
                                    </th>
                                    <th>
                                        消耗<%=ConfigurationManager.AppSettings["moneyName"]%>
                                    </th>
                                    <th>
                                        兑奖时间
                                    </th>
                                </tr>
                            </thead>
                            <asp:Repeater ID="rpList" runat="server">
                                <ItemTemplate>
                                    <tr align="center">
                                        <td>
                                            <%=Rowid+=1%>
                                        </td>
                                        <td>
                                            <%#Eval("UserName") %>
                                        </td>
                                        <td>
                                            <%#Eval("LotteryAwardName")%>
                                        </td>
                                        <td>
                                            <%# Eval("ChangeMoney")%>
                                        </td>
                                        <td>
                                            <%#Eval("AddDate") %>
                                        </td>
                                    </tr>
                                </ItemTemplate>
                            </asp:Repeater>
                        </table>
                    </div>
                    <div class="clear">
                    </div>
                    <div style="text-align: right;">
                        <webdiyer:AspNetPager PageSize="20" ID="anpPageIndex" runat="server" FirstPageText="首页"
                            LastPageText="尾页" NextButtonStyle="margin:0 3px;" NextPageText="下一页" NumericButtonCount="5"
                            PagingButtonSpacing="5" PagingButtonLayoutType="None" PrevButtonStyle="margin:0 3px;"
                            PrevPageText="上一页" ShowFirstLast="False" ShowPageIndexBox="Never" UrlPaging="True"
                            AlwaysShow="true">
                        </webdiyer:AspNetPager>
                    </div>
                </div>
            </div>
            <p><img src="/Images/cont_img01.jpg" alt="" /></p>
            <div class="clear">
            </div>
        </div>
        <!--right End-->
       
    </div>
    <!--content End-->
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
