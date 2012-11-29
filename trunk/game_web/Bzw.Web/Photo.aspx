<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Photo"%>

<%@ OutputCache Duration="60" VaryByParam="page" %>
<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
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

    <script type="text/javascript" src="/Public/Js/common.js"></script>
      <script type="text/javascript" src="/Public/Js/jquery.js"></script>
	<script src="/Public/Js/lightbox.js" type="text/javascript"></script>
	<script type="text/javascript" src="/Public/Js/Global.js"></script>
	
</head>
<body>
    <div id="container">
<!--header-->
    <WebTop:Control ID="webTopOne" runat="server" pageType="5"/> 

<!--content-->
    <div id="content">
      <div id="left1">
        <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
		<WebService:Control ID="webservice1" runat="server" />
      </div>
 <div id="right">
      <div class="right_con_title"><span>当前位置：<a href="/Default.aspx">首页</a> > <a href="/Photo.aspx" title="玩家靓照">玩家靓照</a></span>
      <h1>玩家靓照</h1></div>
      <div class="rightbox" >
          <div id="allPho">
						<asp:Repeater runat="server" ID="rptDataList">
							<ItemTemplate>
								<dl>
									<dt>
										<%# "<a href='/Public/Thumbs.aspx?path=" + Server.UrlEncode( Eval( Bzw.Entities.VUsersAlbum._.PicPath.Name ).ToString() ) + "&width=547&height=404' title='" + Eval( Bzw.Entities.VUsersAlbum._.PicName.Name ) + "' rel='lightbox'>"
									+"<img src='/Public/Thumbs.aspx?path=" + Server.UrlEncode( Eval( Bzw.Entities.VUsersAlbum._.PicPath.Name ).ToString() ) + "&width=94&height=94' alt='" + Eval( Bzw.Entities.VUsersAlbum._.PicName.Name ) + "' title='" + Eval( Bzw.Entities.VUsersAlbum._.PicName.Name ) + "' onerror='this.src=\"/images/none.jpg\"' /></a>"%>
									</dt>
								<%--	<dd>
										<%#"<a href='"+Eval( Bzw.Entities.VUsersAlbum._.PicPath.Name).ToString()+"' title='查看原图' target='_blank'>" + Eval( Bzw.Entities.VUsersAlbum._.PicName.Name ).ToString() + "</a>"%>
									</dd>	--%>
									<dd>
										<%# "<a href='/UserInfo/Default.aspx?params=" + Server.UrlEncode(Eval(Bzw.Entities.VUsersAlbum._.UserID.Name).ToString()) + "' title=''>" + Eval(Bzw.Entities.VUsersAlbum._.NickName.Name).ToString() + "</a>"%>
									</dd>
								<%--	<dd>
										相册：<%# "<a href='/UserInfo/PhotoList.aspx?params="+Eval(Bzw.Entities.VUsersAlbum._.ColumnID.Name).ToString()+"' title='查看TA的相册' target='_blank'>"+Eval(Bzw.Entities.VUsersAlbum._.AlbumName.Name).ToString()+"</a>" %></dd>--%>
								</dl>
							</ItemTemplate>
						</asp:Repeater>
						<asp:Literal runat="server" ID="ltNonData" Text="还没有相片..."></asp:Literal>
						<%--<dl>
							<dt>
								<a href="#">
									<img src="temp/p01.jpg" width="94" height="94" /></a></dt>
							<dd>
								沉鱼MM</dd>
						</dl>--%>
					    <!--pageNumber-->
		<div class="sabrosus">
			<webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True"
				CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
				FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
				ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
				TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5" CurrentPageButtonClass="current" ShowPrevNext="False" PageSize="20">
			</webdiyer:AspNetPager>
		</div>                           
                                            
        </div>
        <div class="clear"></div>
      </div>  
    </div>
     <div class="clear"></div>
      </div><!--right End-->
       
    </div><!--content End-->
 
<!--footer-->
	<WebFooter:Control ID="webFooterone" runat="server" /> 
</body>
</html>
