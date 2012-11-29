<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.DaoJuGM" %>

<%@ OutputCache Duration="60" VaryByParam="id" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>
      
    </title>
  
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
 <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
 <script type="text/javascript" src="/Public/Js/public.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/DaoJu.js"></script>

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server"   />
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
            <WebService:Control ID="webservice1" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    游戏商城</h3>
                <p class="dqwz">
                    当前位置：首页 > 游戏商城</p>
            </div>
            <div id="sub_nr">
                <div id="props">
                    <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab02">
                        <tr>
                            <td width="42%" align="right" valign="middle">
                                <img src="/Image/DaoJu/<%=PropID %>.gif" width="136" height="82" />
                            </td>
                            <td width="58%" class="prize_info">
                                <strong>道具名称：<%=PropName %></strong> <br />Vip价格：<%=UiCommon.StringConfig.AddZeros(VipPrice)%><%=UiCommon.StringConfig.MoneyName%><br />
                                普通价格：<%=UiCommon.StringConfig.AddZeros(Price)%><%=UiCommon.StringConfig.MoneyName%><br />
                                道具介绍：<span class="textgray"><%=PropDesc %></span>
                            </td>
                        </tr>
                    </table>
                    <div class="prizeText">
                        <table width="100%" border="0" cellspacing="0" cellpadding="0">
                            <tr>
                                <td height="30" align="right">
                                    购买数量：
                                </td>
                                <td>
                                    <input type="text" name="txtdj<%=PropID %>" id="txtdj<%=PropID %>" value="1" maxlength="3"
                                        size="5" class="fr_input" />
                                </td>
                            </tr>
                            <tr>
                                <th height="38" scope="row">
                                </th>
                                <td>
                                    <input type="submit" value="购  买" onclick="btnBuyDj('<%=PropID%>','<%=PropName%>','<%=VipPrice%>','<%=Price%>','<%=UiCommon.StringConfig.MoneyName %>')"
                                        class="but_011" />
                                </td>
                            </tr>
                        </table>
                    </div>
                </div>
                <div class="clear">
                </div>
              
            </div>
              <p>
                    <img src="/Images/cont_img01.jpg" alt="" /></p>
            <!--right End-->
        </div>
        </div>
        <!--footer-->
        <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
