<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_ClothDetail" %>
 
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

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/marquee.js"></script>

    <script type="text/javascript" src="/Public/Js/jquery.js"></script>

    <script type="text/javascript" src="/Public/Js/DaoJu.js"></script>

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" pageType="3" />
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
            <WebService:Control ID="webservice1" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    服装商城</h3>
                <p class="dqwz">
                    当前位置：首页 > <a href="/Manage/ClothList.aspx?type=<%=Utility.Common.GetStringOfUrl("token") %>"
                        title="服装商城">服装商城</a></p>
            </div>
            <div id="sub_nr">
                <div id="props">
                    <form id="Form1" class="democss" runat="server">
                    <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab02">
                        <tr>
                            <td width="42%" align="right" valign="middle">
                                <img src="<%=ImgSrc %>" width="82" height="82" />
                            </td>
                            <td width="58%" class="prize_info">
                                <strong>名称：<%=LogName %></strong> 价格：<%=UiCommon.StringConfig.AddZeros(Price)%><%=UiCommon.StringConfig.MoneyName%><br />
                                赠送：<%=SendLotteries %>
                                <%=UiCommon.StringConfig.GoldName %><br />
                                道具说明：<span class="textgray"><%=Descript %></span>
                            </td>
                            <asp:HiddenField ID="hidId" runat="server" />
                        </tr>
                        <tr>
                            <td colspan="2" style="text-align: center;">
                                <asp:Button ID="btnBuy" class="but_011" runat="server" Text="购 买" OnClick="btnBuy_Click" />
                                &nbsp;&nbsp;&nbsp;
                            </td>
                        </tr>
                    </table>
                    </form>
                </div>
            </div>
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
                
        </div>
        <!--content End-->
        <div class="clear">
        </div>
    </div>
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
