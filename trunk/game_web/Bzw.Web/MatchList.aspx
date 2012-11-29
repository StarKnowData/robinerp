<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.MatchList" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>
<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title></title>
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script src="/Public/Js/jquery.js" type="text/javascript"></script>

    <script type="text/javascript" src="/Public/Js/Public.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/common.js"></script>

</head>
<body>
    <div id="container">
        <!--header-->
        <div id="header">
            <WebTop:Control ID="webTopOne" runat="server" pageType="3" />
        </div>
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" isDisplay="0" />
            <WebService:Control ID="webService" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    比赛专区</h3>
                <p class="dqwz">
                    当前位置：首页 > 比赛专区</p>
            </div>
            <div id="sub_nr">
                <div id="zx">
                    <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab01">
                        <thead>
                            <tr>
                                <th width="20%">
                                    游戏名称
                                </th>
                                <th width="20%">
                                    开始时间
                                </th>
                                <th width="20%">
                                    结束时间
                                </th>
                                <th>
                                    报名费用
                                </th>
                                <th>
                                    比赛详情
                                </th>
                            </tr>
                        </thead>
                        <asp:Repeater ID="rpList" runat="server">
                            <ItemTemplate>
                                <tr>
                                    <td>
                                        <%# Eval("ComName") %>
                                    </td>
                                    <td>
                                        <%#Eval("StartTime") %>
                                    </td>
                                    <td>
                                        <%#Eval("EndTime")%>
                                    </td>
                                    <td>
                                        <%#Eval("EntryFee")%>
                                    </td>
                                    <td>
                                        <%# DateTime.Compare(Convert.ToDateTime(Eval("StartTime")), DateTime.Now) > 0 ? "请到大厅报名比赛" : "<a href='/ContestRankDetail.aspx?params=" + Eval("ContestID") + "'>查看排行榜</a>"%>
                                    </td>
                                </tr>
                            </ItemTemplate>
                        </asp:Repeater>
                    </table>
                </div>
                <div class="clear">
                </div>
                <div class="sabrosus">
                    <webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
                        FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
                        ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
                        TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5"
                        CurrentPageButtonClass="current" ShowPrevNext="False">
                    </webdiyer:AspNetPager>
                </div>
            </div>
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
    </div>
    <!--right End-->
    <!--content End-->
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
