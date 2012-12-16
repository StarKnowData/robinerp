<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.GameInfo3" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>

<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
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
        <div id="header">
            <WebTop:Control ID="webTopOne" runat="server" pageType="1" />
        </div>
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" isDisplay="0" />
            <div class="clear">
            </div>
          <div id="xszn" style=" height:auto;">
               <h3><img src="/Images/left_btn001.gif" alt="游戏列表" /></h3>
            
                <ul >
                    <asp:Repeater ID="rpGameType" runat="server">
                        <ItemTemplate>
                            <li><a href="/GameInfo.aspx?id=<%#Eval("Game_id") %>" title="<%#Eval("Game_Name")%>">
                                <%#Eval("Game_Name")%>
                            </a></li>
                        </ItemTemplate>
                    </asp:Repeater>
                </ul>
            </div>
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    游戏下载</h3>
                <p class="dqwz">
                    当前位置：<a href="/Default.aspx" title="首页">首页</a> > <a href="/Down.aspx" title="游戏下载">游戏下载</a>
                    > <a href="/GameInfo.aspx?id=<%#Eval("Game_id") %>" title="游戏下载">
                        <%=GameName %></a></p>
            </div>
            <div id="sub_nr" style="overflow: hidden;">
                <p class="yxxz_xxnr ac">
                    <strong class="text04">
                        <%=GameName %>[<img src="/Images/cont_bullet02.jpg" alt="" /><a href="<%=GameDownAddress %>">点击下载</a>]</strong></p>
                <br />
                <br />
                <p>
                    <%=GameRule%></p>
                <p>
                    <%=GameInfo2%></p>
                <div class="clear">
                </div>
            </div>
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
    </div>
  
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
