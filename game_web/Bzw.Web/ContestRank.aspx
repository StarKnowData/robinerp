<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.ContestRank" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="RankLeft" Src="~/Public/RankLeft.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>
      
    </title>
  
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/jquery.js"></script>

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" pageType="7" />
        <!--content-->
        <div id="left">
            <RankLeft:Control ID="rankLeft" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    比赛排行榜</h3>
                <p class="dqwz">
                    当前位置：首页 > 比赛排行榜</p>
            </div>
            <div id="sub_nr">
                <div id="zx">
                    <table width="685" border="0" cellpadding="0" cellspacing="0">
                        <thead>
                            <tr>
                                <th width="15%">
                                    比赛开始时间
                                </th>
                                <th width="15%">
                                    比赛结束时间
                                </th>
                                <th width="30%">
                                    比赛游戏名
                                </th>
                                <th width="20%">
                                    报名费用
                                </th>
                                <th width="20%">
                                    操作
                                </th>
                            </tr>
                        </thead>
                        <asp:Repeater ID="rpList" runat="server">
                            <ItemTemplate>
                                <tr>
                                    <td>
                                        <%#Eval("StartTime") %>&nbsp;
                                    </td>
                                    <td>
                                        <%#Eval( "EndTime" )%>
                                    </td>
                                    <td>
                                        <%#Eval("ComName") %>
                                    </td>
                                    <td>
                                        <%#Eval("EntryFee") %><%=UiCommon.StringConfig.MoneyName %>
                                    </td>
                                    <td>
                                        <a href='ContestRankDetail.aspx?params=<%#Eval("ContestID") %>'>查看详细输赢排行</a>
                                    </td>
                                </tr>
                            </ItemTemplate>
                        </asp:Repeater>
                    </table>
                </div>
                <div class="clear">
                </div>
            </div>
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
        <div class="clear">
        </div>
    </div>
    <!--right End-->
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
