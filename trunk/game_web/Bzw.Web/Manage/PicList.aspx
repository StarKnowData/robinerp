<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_PicList" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>
      
    </title>
    <link href="/Style/mainstyle.css" rel="stylesheet" type="text/css" />
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script src="/public/js/public.js"></script>

    <script src="/Public/Js/lightbox.js"></script>

    <link href="/css/lightbox.css" type="text/css" rel="stylesheet" />
    <style type="text/css">
        .photo_list li
        {
            width: 200px;
            float: left;
            text-align: center; /*margin-top:20px;*/
            height: 240px;
            overflow: hidden;
        }
        .photo_list li dl
        {
            border: 0px;
            width: 190px;
        }
        .photo_list li dl dt
        {
            font-weight: bold;
            float: none;
        }
        .photo_list li dl dt a
        {
            color: #072a90;
        }
        .photo_list li dl dd
        {
            color: #666666;
            float: none;
        }
    </style>
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
                    相片管理</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 相片管理</p>
            </div>
            <div id="sub_nr" style="margin-top: 15px;">
                <div class="frie_pro">
                    <a href="Album.aspx" id="current">
                        <img src="/images/fhphoto.gif" width="12" height="12" />
                        返回相册列表</a> &nbsp;&nbsp;| &nbsp;&nbsp;<a href="PicListWrite.aspx" title="上传照片"><img
                            src="/images/scphoto.gif" width="12" height="12" />
                            上传照片</a><br />
                </div>
                <div class="modipoto">
                    <asp:Repeater ID="rptAlbumColumnList" runat="server">
                        <ItemTemplate>
                            <dl class="phoLib">
                                <dt>
                                    <%# "<a href='/Public/Thumbs.aspx?path=" + Server.UrlEncode( Eval( Bzw.Entities.VUsersAlbum._.PicPath.Name ).ToString() ) + "&width=547&height=404' title='" + Eval( Bzw.Entities.VUsersAlbum._.PicName.Name ) + "' rel='lightbox'>" +
								"<img src='/Public/Thumbs.aspx?path=" + Server.UrlEncode( Eval( Bzw.Entities.VUsersAlbum._.PicPath.Name ).ToString() ) + "&width=100&height=98' alt='" + Eval( Bzw.Entities.VUsersAlbum._.PicName.Name ) + "' title='" + Eval( Bzw.Entities.VUsersAlbum._.PicName.Name ) + "' onerror='this.src=\"/images/none.jpg\"' /></a>"%>
                                </dt>
                                <dd>
                                    <strong>
                                        <%#Eval( Bzw.Entities.VUsersAlbum._.PicName.Name )%>
                                    </strong>
                                </dd>
                                <dd class="pic_ms">
                                    <%# BCST.Common.CommonManager.String.CutString( Eval( Bzw.Entities.VUsersAlbum._.PicDescription.Name ).ToString().Replace( "\r\n", "<br />" ), 14, "..." )%>
                                </dd>
                                <dd>
                                    上传于<%# Eval(Bzw.Entities.VUsersAlbum._.InputTime.Name,"{0:yyyy-MM-dd}") %></dd>
                                <dd>
                                    <a href="javascript:void(0);" onclick="SetToCover(<%#Eval( Bzw.Entities.VUsersAlbum._.ID.Name )%>);">
                                        设为封面</a> <a href="PicListWrite.aspx?params=<%#Eval( Bzw.Entities.VUsersAlbum._.ID.Name )%>"
                                            title="修改">修改</a> <a href="javascript:void(0);" onclick="DeletePic(<%#Eval( Bzw.Entities.VUsersAlbum._.ID.Name )%>)">
                                                删除</a></dd>
                            </dl>
                        </ItemTemplate>
                    </asp:Repeater>
                   
                    <div class="clear">
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
            </div>    <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
        <div class="clear">
        </div>
    </div>
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />

    <script>
        function DeletePic(id) {
            //删除
            if (id == null || id == "" || isNaN(id))
                return;
            if (!confirm("您确定要删除这张照片吗？\r\n注意：此操作不可恢复。"))
                return;
            OpenStateBar("正在删除，请稍候...");
            $.get(
				"/Manage/UsersForm.aspx?params=delpic&type=1&id=" + id + "&x=" + Math.random(),
				function(data) {
				    if (data == "success") {
				        RefreshMe();
				    }
				    else {
				        Msg(data, 200);
				    }
				}
			);
        }

        //设为封面
        function SetToCover(id) {
            if (id == null || id == "" || isNaN(id))
                return;
            OpenStateBar("正在设置，请稍候...");
            $.get(
				"/Manage/UsersForm.aspx?params=settocover&id=" + id + "&x=" + Math.random(),
				function(data) {
				    if (data == "success") {
				        LocationToMe();
				    }
				    else {
				        Msg(data, 200);
				    }
				}
			);
        }
    </script>

</body>
</html>
