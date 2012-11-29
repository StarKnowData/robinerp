
<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.DaoJu" %>

<%@ OutputCache Duration="1800" VaryByParam="page" %>
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
	<title>

	</title>
	
	<link href="/css/layout.css" rel="stylesheet" type="text/css" />
<script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
	<script type="text/javascript" src="/Public/Js/Global.js"></script>
	<script type="text/javascript" src="/Public/Js/DaoJu.js"></script>
</head>
<body>
    <div id="container">
<!--header-->
     <WebTop:Control ID="webTopOne" runat="server" pageType="3"/> 
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
              &nbsp;&nbsp;&nbsp;<a href="/Manage/ClothList.aspx">服装商城</a>&nbsp;|&nbsp;<font  style="color:Red;"> 游戏商城</font>
            <div id="sub_nr" style="margin-top: 10px;">
                <div id="dhzx">   
          	<asp:Repeater ID="rpDaoJu" runat="server">
				<ItemTemplate>
					<dl>
						<dd>
							<img src="Image/DaoJu/<%#Eval("PropID") %>.gif" width="136" height="82" alt="<%#Eval("PropName") %>"/></dd>
						<dt class="text05"><%#Eval("PropName") %></dt>
						<dt>
						<input name="" type="button" value="赠 送" class="shop_but_01" onclick="javascript:location.href='/DaoJuZS.aspx?id=<%#Eval("PropID") %>'" />
						<input name="" type="button" value="购 买" class="shop_but_02" onclick="javascript:location.href='/DaoJuGM.aspx?id=<%#Eval("PropID") %>'" /> 
						</dt>
					</dl>
				</ItemTemplate>
			</asp:Repeater>
                               <!--pageNumber-->
		<div class="sabrosus">
		<webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True"
				CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
				FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
				ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
				TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5" CurrentPageButtonClass="current" ShowPrevNext="False" PageSize="8">
			</webdiyer:AspNetPager>
		</div>
                            </div>
                            <div class="clear"></div>
      
      </div>  
  <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
     <div class="clear"></div>
      </div><!--right End-->
     
    </div><!--content End-->
 
<!--footer-->
	<WebFooter:Control ID="webFooterone" runat="server" /> 
</body>
</html>
