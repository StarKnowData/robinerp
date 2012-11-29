<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_Album" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>
      
    </title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/public/js/jquery.js"></script>

    <script type="text/javascript" src="/public/js/public.js"></script>

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
                    相册管理</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 相册管理</p>
            </div>
            <div id="sub_nr" style=" margin-top:15px;">
                <div class="frie_pro"  >
                    共有<%=anpPageIndex.RecordCount.ToString() %>个相册。 | <a href="AlbumWrite.aspx" title="新建相册">
                        <img src="/images/modiphoto.gif" width="14" height="14" />
                        新建相册</a> | <a href="PicListWrite.aspx" title="上传照片">
                            <img src="/images/scphoto.gif" width="12" height="12" />
                            上传照片</a>
                </div> <br />
                <div class="modipoto">
                    <asp:Repeater ID="rptAlbumColumnList" runat="server">
                        <ItemTemplate>
                            <dl class="phoLib">
                                <dt>
                                    <%# "<a href='/Manage/PicList.aspx?params=" + Eval( Bzw.Entities.Web_vUserAlbumColumn._.ID.Name ).ToString() + "' title='" + Eval( Bzw.Entities.Web_vUserAlbumColumn._.AlbumName.Name ) + "'>" +
								( string.IsNullOrEmpty( Eval( Bzw.Entities.Web_vUserAlbumColumn._.Cover.Name ).ToString() )
																			? "<img src='/Images/NoPicture/no_pic.gif' width='120' height='90' alt='暂无封面' title='暂无封面' />"
								: "<img src='/Public/Thumbs.aspx?path=" + Server.UrlEncode( Eval( Bzw.Entities.Web_vUserAlbumColumn._.Cover.Name ).ToString() ) + "&width=120&height=90' alt='" + Eval( Bzw.Entities.Web_vUserAlbumColumn._.AlbumName.Name ) + "' title='" + Eval( Bzw.Entities.Web_vUserAlbumColumn._.AlbumName.Name ) + "' />" ) + "</a>"%>
                                </dt>
                                <dd >
                                    <%#"<a href='/Manage/PicList.aspx?params=" + Eval( Bzw.Entities.Web_vUserAlbumColumn._.ID.Name ).ToString() + "' title='" + Eval( Bzw.Entities.Web_vUserAlbumColumn._.AlbumName.Name ) + "'>" + Eval(Bzw.Entities.Web_vUserAlbumColumn._.AlbumName.Name) + "</a>"+
								( Eval(Bzw.Entities.Web_vUserAlbumColumn._.IsPublic.Name).ToString() == Library.PublicState.公开.ToString()
								? "&nbsp;&nbsp;<img src='/images/system/unlock_blue.gif' alt='这是公开相册，点击设置为隐藏' title='这是公开相册，点击设置为隐藏' style='cursor:pointer' onclick='SetPublicState(1," + Eval( Bzw.Entities.Web_vUserAlbumColumn._.ID.Name ) + ")' />"
								: "&nbsp;&nbsp;<img src='/images/system/lock_blue.gif' alt='这是隐藏相册，点击设置为公开' title='这是隐藏相册，点击设置为公开' style='cursor:pointer' onclick='SetPublicState(0," + Eval( Bzw.Entities.Web_vUserAlbumColumn._.ID.Name ) + ")' />" )
                                    %>
                                </dd>
                                <dd>
                                    照片数量：<%# GetPicCount((int)Eval(Bzw.Entities.Web_vUserAlbumColumn._.ID.Name)) %></dd>
                                <dd>
                                    上传于<%# Eval(Bzw.Entities.Web_vUserAlbumColumn._.InputTime.Name,"{0:yyyy-MM-dd HH:mm}") %></dd>
                                <dd>
                                    <a href="/Manage/AlbumWrite.aspx?params=<%# Eval(Bzw.Entities.Web_vUserAlbumColumn._.ID.Name) %>"
                                        class="edit">修改</a> <a href="javascript:void(0);" onclick="SetTop(<%# Eval(Bzw.Entities.Web_vUserAlbumColumn._.ID.Name) %>);"
                                            class="top">置顶</a> <a href="javascript:void(0);" class="del" onclick="DelAlbumColumn(<%#Eval( Bzw.Entities.Web_vUserAlbumColumn._.ID.Name ) %>);">
                                                删除</a>
                                </dd>
                            </dl>
                        </ItemTemplate>
                    </asp:Repeater>
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
            </div>    <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
    </div>
    <div class="clear">
    </div>
    
    <!--content End-->
    </div>
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />

    <script>
        function SetPublicState(state, id) {
            if (isNaN(state) || isNaN(id))
                return;
            OpenStateBar("正在设置，请稍候...");
            $.get(
				"/Manage/UsersForm.aspx?params=setalbumpublic&public=" + state + "&id=" + id + "&x=" + Math.random(),
				function(data) {
				    if (data != "success") {
				        alert("错误！\r\n" + data);
				        CloseStateBar();
				    }
				    else {
				        //Msg("设置成功！",200);
				        RefreshMe();
				    }
				}
			);
        }

        function DelAlbumColumn(id) {
            if (!confirm("您确定要删除这个相册吗？\r\n注意：此操作不可恢复！\r\n如果相册内有相片，删除相册后，将自动转移到您最新添加的相册中。"))
                return;

            OpenStateBar("正在删除，请稍候...");
            $.get(
				"/Manage/UsersForm.aspx?params=delalbumcolumn&id=" + id + "&x=" + Math.random(),
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
        //置顶
        function SetTop(id) {
            if (isNaN(id) || isNaN(id))
                return;
            OpenStateBar("正在设置，请稍候...");
            $.get(
				"/Manage/UsersForm.aspx?params=setalbumtop&id=" + id + "&x=" + Math.random(),
				function(data) {
				    if (data != "success") {
				        alert("错误！\r\n" + data);
				        CloseStateBar();
				    }
				    else {
				        RefreshMe();
				    }
				}
			);
        }
    </script>

</body>
</html>
