<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_Default" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>
      
    </title>
  
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
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
                    基本信息</h3>
                <p class="dqwz">
                    当前位置：首页 > 基本信息</p>
            </div>
            <div id="sub_nr">
                <div class="fl">
                    <p>
                        <img src="/Images/cont_tbl_img27.jpg" alt="" /></p>
                    <div class="dlzl">
                        <p class="hyxp">
                            <img src="<%=UserHeadImg %>" width="94px" height="105px" alt="" /><br />
                            我的相片</p>
                        <p class="fl">
                            <img src="/Images/cont_tbl_img31.jpg" alt="" /></p>
                        <ul>
                            <li>你好！<strong class="text05"><%=NickName%></strong> 欢迎来到游戏会员中心！</li>
                            <li>银行存款：<%=UiCommon.StringConfig.AddZeros(BankMoney)%>
                                <%=ConfigurationManager.AppSettings["moneyName"].ToString()%></li>
                            <li>
                                <%= UiCommon.StringConfig.BankVersion=="2"?"游戏总":"钱包" %><%=ConfigurationManager.AppSettings["moneyName"].ToString()%>：
                                <%=UiCommon.StringConfig.AddZeros(WalletMoney)%>
                                <%=ConfigurationManager.AppSettings["moneyName"].ToString()%>
                            </li>
                        </ul>
                    </div>
                    <p class="cb">
                        <img src="/Images/cont_tbl_img28.jpg" alt="" /></p>
                </div>
                <p>
                    <img src="/Images/cont_tbl_img29.jpg" alt="" /></p>
                <div class="cz">
                    <table width="685" summary="" border="0">
                        <caption>
                        </caption>
                        <colgroup>
                            <col width="20%" />
                            <col width="80%" />
                        </colgroup>
                        <tbody>
                            <tr>
                                <th scope="row">
                                    <label for="id01">
                                        游戏帐号</label>
                                </th>
                                <td>
                                    <%=UiCommon.UserLoginInfo.UserName %>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    <label for="id02">
                                        昵称</label>
                                </th>
                                <td>
                                    <%=NickName %>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    <label for="id03">
                                        性别</label>
                                </th>
                                <td>
                                    <%=Sex==1?"男":"女" %>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    <label for="id03">
                                        <%=ConfigurationManager.AppSettings["moneyName"].ToString()%>数值</label>
                                </th>
                                <td>
                                    <%=UiCommon.StringConfig.AddZeros(AllMoney)%><%=ConfigurationManager.AppSettings["moneyName"].ToString()%>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    <label for="id03">
                                        电子邮件</label>
                                </th>
                                <td>
                                    <%=Email%>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    <label for="id03">
                                        <%=UiCommon.StringConfig.GoldName %>数值：</label>
                                </th>
                                <td>
                                    <%=Lotteries %>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    <label for="id03">
                                        魅力值</label>
                                </th>
                                <td>
                                    <%=UserFasci %>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    <label for="id03">
                                        财富排名</label>
                                </th>
                                <td>
                                    <%= new BLL.Member().CaifuPaiming(UiCommon.UserLoginInfo.UserID)%>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    <label for="id03">
                                        登陆次数</label>
                                </th>
                                <td>
                                    <%=AllLoginCount%>次
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    <label for="id03">
                                        在线时间</label>
                                </th>
                                <td>
                                    <%=OnLineTimeCount %>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    <label for="id03">
                                        游戏时间</label>
                                </th>
                                <td>
                                    <%=GameTimeCount%>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    <label for="id03">
                                        注册时间</label>
                                </th>
                                <td>
                                    <%=RegisterTM %>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    <label for="id03">
                                        最近一次登陆</label>
                                </th>
                                <td>
                                    <%=LastLoginTM %>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    <label for="id03">
                                        VIP到期时间</label>
                                </th>
                                <td>
                                    <%=VipTime %><a href="/Manage/VipApply.aspx" class="link02">不是VIP，立即申请</a>
                                </td>
                            </tr>
                        </tbody>
                    </table>
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
