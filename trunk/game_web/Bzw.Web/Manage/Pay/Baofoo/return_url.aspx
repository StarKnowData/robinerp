<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage_Pay_Baofoo_return_url" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<%@ Register TagName="WebLeft" TagPrefix="BZW" Src="~/Public/WebLeft.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>
      
    </title>
  
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script src="/Public/Js/jquery.js" type="text/javascript"></script>

    <script src="/Public/Js/public.js" type="text/javascript"></script>

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" pageType="4" />
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webCutKey" runat="server" />
            <BZW:WebLeft ID="webLeft" runat="server"></BZW:WebLeft>
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    宝付在线充值返回结果</h3>
                <p class="dqwz">
                    当前位置：首页 > 账号充值 > 宝付在线充值返回结果</p>
            </div>
            <div id="sub_nr" style="margin-top: 10px;">
                <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab03">
                    <tr>
                        <th align="right" scope="row">
                            &nbsp;
                        </th>
                        <td valign="middle">
                            &nbsp;
                        </td>
                    </tr>
                    <tr>
                        <th width="16%" height="30" align="left" scope="row">
                            支付方式：
                        </th>
                        <td width="84%" valign="middle">
                        
                            宝付在线充值
                        </td>
                    </tr>
                    <tr>
                        <th height="30" align="left" scope="row">
                            订单编号：
                        </th>
                        <td valign="middle">
                            <asp:Literal ID="lblBillon" runat="Server" />
                        </td>
                    </tr>
                    <tr>
                        <th height="30" align="left" scope="row">
                            订单金额：
                        </th>
                        <td valign="middle">
                            <asp:Literal ID="lblAmount" runat="Server" />元
                        </td>
                    </tr>
                    <tr>
                        <th height="30" align="left" scope="row">
                            支付结果：
                        </th>
                        <td valign="middle">
                            <asp:Literal ID="lblMsg" runat="Server" />
                        </td>
                    </tr>
                </table>
            </div>
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
    </div>
    <!--right End-->
    </form>
    <div class="clear">
    </div>
   
    <!--wrap-->
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
