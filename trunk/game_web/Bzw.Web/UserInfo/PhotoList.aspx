<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.UserInfo.UserInfo_PhotoList" %>

<%--相片列表--%>
<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>
      
    </title>
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script src="/public/js/public.js" type="text/javascript"></script>

    <script src="/Public/Js/lightbox.js" type="text/javascript"></script>
<link href="/css/lightbox.css" type="text/css" rel="stylesheet" />
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
                    玩家靓照</h3>
                <p class="dqwz">
                    当前位置：<a href="/Default.aspx" title="首页">首页</a> > <a href="/UserInfo/Default.aspx?params=<%=Server.UrlEncode(uid)%>"
                        title="查看玩家信息">查看玩家信息</a> > <a href="/UserInfo/Album.aspx?params=<%=Server.UrlEncode(uid)%>">
                            相册列表</a> >
                    <%=AlbumName %></p>
            </div>
            <div id="sub_nr" style="margin-top: 10px;">
          
                <ul class="php_ul" style=" width:500px;">
                    <li style=" float:left; width:200px;"><a href="/UserInfo/Default.aspx?params=<%=Server.UrlEncode(uid)%>" class="link04">查看TA的资料</a></li>
                    <li><a href="/UserInfo/Album.aspx?params=<%=Server.UrlEncode(uid)%>"  class="link04">查看TA的相册</a></li>
                </ul>
                <div id="memText02">
                    <div class="modipoto">
                        <asp:Repeater ID="rptAlbumColumnList" runat="server">
                            <ItemTemplate>
                                <dl>
                                    <dt>
                                        <%# "<a href='/Public/Thumbs.aspx?path=" + Server.UrlEncode( Eval( Bzw.Entities.VUsersAlbum._.PicPath.Name ).ToString() ) + "&width=547&height=404' title='" + Eval( Bzw.Entities.VUsersAlbum._.PicName.Name ) + "' rel='lightbox'>" +
									"<img src='/Public/Thumbs.aspx?path=" + Server.UrlEncode( Eval( Bzw.Entities.VUsersAlbum._.PicPath.Name ).ToString() ) + "&width=140&height=140' alt='" + Eval( Bzw.Entities.VUsersAlbum._.PicName.Name ) + "' title='" + Eval( Bzw.Entities.VUsersAlbum._.PicName.Name ) + "' onerror='this.src=\"/images/none.jpg\"' /></a>"%>
                                    </dt>
                                    <dd>
                                        <%#Eval( Bzw.Entities.Web_UserAlbum._.PicName.Name )%>
                                    </dd>
                                    <dd>
                                        <%# BCST.Common.CommonManager.String.CutString( Eval( Bzw.Entities.VUsersAlbum._.PicDescription.Name ).ToString().Replace( "\r\n", "<br />" ), 14, "..." )%>
                                    </dd>
                                    <dd>
                                        上传于<%# Eval(Bzw.Entities.VUsersAlbum._.InputTime.Name,"{0:yyyy-MM-dd}") %></dd>
                                </dl>
                            </ItemTemplate>
                        </asp:Repeater>
                        <asp:Literal runat="server" ID="ltNonData" Text="<li>TA还没有上传相片...</li>"></asp:Literal>
                    </div>
                    <!--pageNumber-->
                    <div class="sabrosus">
                        <webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
                            FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
                            ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
                            TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5"
                            CurrentPageButtonClass="current" ShowPrevNext="False" PageSize="8">
                        </webdiyer:AspNetPager>
                    </div>
                </div>
            </div>
             <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
        <div class="clear">
        </div>
        </div><!--right End-->
    
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
