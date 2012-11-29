<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.FineryIDManage" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title></title>
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" />
        <!--content-->
        <div id="left">
            <Left:Control ID="leftOne" runat="server" />
            <WebService:Control ID="webServiceOne" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    靓号管理</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 靓号管理</p>
            </div>
            <div id="sub_nr" style="margin-top: 10px;">
                <div id="memText01">
                    <div id="rank">
                        <a href="/Manage/FineryID.aspx">
                            <asp:Label ID="msgLB" runat="server" Text="您还没有靓号？那赶紧去拍吧！！" Visible="false" Font-Underline="True"></asp:Label></a>
                        <br />
                        <strong>靓号使用说明：</strong> 欢迎您进入靓号管理，在游戏之前希望您花几分钟的时间看看靓号说明，首先购买靓号后需要激活，没有激活的靓号无法正常游戏，激活后登录及银行初始化密码都与您申请靓号时设置的靓号密码一至，账号的基本信息与大号一至，每一个靓号激活后都有一次“数据转移”的机会，关于数据转移下面详细介绍。
                        <br />
                        <br />
                        <strong>关于“数据转移”功能：</strong>“数据转移”功能是将您能老号的所有数据转移到新的靓号里，使用前靓号必须是激活状态，转移后您老号的数据包括财富，游戏记录，信息等都将转移至新的靓号里，并且每个靓号只拥有一次转移的机会，而且必须是从老号中转至靓号，请您慎重使用。
                        <br />
                        <br />
                        <div id="zx">
                            <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab01">
                                <thead>
                                    <tr>
                                        <th width="30%">
                                            靓号ID
                                        </th>
                                        <th width="40%">
                                            是否激活
                                        </th>
                                        <th width="40%">
                                            是否数据转移
                                        </th>
                                    </tr>
                                </thead>
                                <asp:Repeater ID="FineryIDList" runat="server">
                                    <ItemTemplate>
                                        <tr>
                                            <td style="text-align: center;">
                                                <%#Eval("FineryID")%>
                                            </td>
                                            <td style="text-align: center;">
                                                <%#Convert.ToInt32(Eval("IsUse"))==1?"已激活":"<a href='/Manage/FineryIDSpring.aspx?id="+Eval("FineryID")+"'>点击激活靓号</a>"%>
                                            </td>
                                            <td style="text-align: center;">
                                                <%#Convert.ToInt32( Eval( "IsCopy" ) ) == 1 ? "已使用过数据转移" : "<a href='/Manage/FineryIDDataCopy.aspx?id=" + Eval( "FineryID" ) + "'>点击数据转移</a>"%>
                                            </td>
                                        </tr>
                                    </ItemTemplate>
                                </asp:Repeater>
                            </table>
                        </div>
                    </div>
                </div>
                <div class="clear">
                </div>
            </div>
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
    </div>
    <!--right End-->
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
