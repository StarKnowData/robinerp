<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.UserInfo.UserInfo_Default" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>

<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%-- 用户信息展示 --%>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>
      
    </title>
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script src="/public/js/jquery.js" type="text/javascript"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" />
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webCutKey" runat="server" />
            <WebService:Control ID="webServiceOne" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    查看玩家</h3>
                <p class="dqwz">
                    当前位置：<a href="/Default.aspx" title="首页">首页</a> > 查看玩家信息</p>
            </div>
            <div id="sub_nr" style="margin-top: 10px;">
             <ul class="php_ul" style=" width:500px;">
                    <li style=" float:left; width:200px;"><a href="/UserInfo/Default.aspx?params=<%=Server.UrlEncode(InfoRow["UserID"].ToString())%>" class="link04">查看TA的资料</a></li>
			<li><a href="/UserInfo/Album.aspx?params=<%=Server.UrlEncode(InfoRow["UserID"].ToString())%>" class="link04">查看TA的相册</a></li>
                </ul>
                <div id="memText01">
                    <div class="cz">
                        <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab05">
                            <tr>
                                <th height="30" scope="row">
                                    &nbsp;
                                </th>
                                <td>
                                    &nbsp;
                                </td>
                                <td width="25%" rowspan="14" align="center" valign="top">
                                    <span class="myPhoto">
                                        <img src="<%=UserHeader %>" width="66" height="105" alt="头像" /><br />
                                        TA的形象</span>
                                </td>
                            </tr>
                            <tr>
                                <th height="30" scope="row">
                                    昵称：
                                </th>
                                <td>
                                    <%=InfoRow["NickName"].ToString()%>
                                </td>
                            </tr>
                            <tr>
                                <th height="30" scope="row">
                                    性别：
                                </th>
                                <td>
                                    <%=( (short)InfoRow["Sex"] == 0 ) ? "女" : "男"%>
                                </td>
                            </tr>
                            <tr>
                                <th height="30" scope="row">
                                    职业：
                                </th>
                                <td>
                                    <%=InfoRow["OccuPation"].ToString()%>
                                </td>
                            </tr>
                            <tr>
                                <th height="30" scope="row">
                                    地区：
                                </th>
                                <td>
                                    <%=InfoRow["AdrProvince"].ToString() + InfoRow["AdrCity"].ToString() + InfoRow["AdrZone"].ToString()%>
                                </td>
                            </tr>
                            <tr>
                                <th height="30" scope="row">
                                    电话：
                                </th>
                                <td>
                                    <%=InfoRow["PhoneNum"].ToString()%>
                                </td>
                            </tr>
                            <tr>
                                <th height="30" scope="row">
                                    登录次数：
                                </th>
                                <td>
                                    <%=InfoRow["AllLoginTime"].ToString()%>
                                    次
                                </td>
                            </tr>
                            <tr>
                                <th height="30" scope="row">
                                    注册时间：
                                </th>
                                <td>
                                    <%=( DateTime.Parse(InfoRow["RegisterTM"].ToString()) ).ToString( "yyyy-MM-dd HH:mm" )%>
                                </td>
                            </tr>
                            <tr>
                                <th height="30" scope="row">
                                    最近一次登录：
                                </th>
                                <td>
                                    <%=( (DateTime)InfoRow["LastLoginTM"] ).ToString( "yyyy-MM-dd HH:mm" )%>
                                </td>
                            </tr>
                            <tr>
                                <th height="30" scope="row">
                                    &nbsp;
                                </th>
                                <td>
                                    &nbsp;
                                </td>
                                <td align="center" valign="top">
                                    &nbsp;
                                </td>
                            </tr>
                        </table>
                    </div>
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
