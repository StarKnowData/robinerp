<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.NewsList"%>

<%@ OutputCache Duration="60" VaryByParam="tid;page" %>
<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>

<%@ Register TagPrefix="Bzw" TagName="NewsTypeList" Src="~/Public/NewsTypeList.ascx" %>
<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
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
<form runat="server">
<div id="container">
<!--header-->
     <WebTop:Control ID="webTopOne" runat="server" pageType="5"/> 
<!--content-->
 
      <div id="left">
		<BZW:WebShortCutKey ID="webshortcutkey1" runat="server" isDisplay="0"/>
		<WebService:Control ID="webservice1" runat="server" />
       </div>
       <div id="content01">
			<div id="title01">
				<h3 class="fl">新闻中心</h3>
				<p class="dqwz">当前位置：首页 > 新闻中心</p>
			</div>
			<div id="sub_nr"  >
				 <Bzw:NewsTypeList ID="newsTypeListone" runat="server" />
				<div id="zx">
					<table  summary="" border="0">
						<caption></caption>
						<colgroup>
							
							<col width="85%" />
							<col width="15%" />
						</colgroup>
						<thead>
							<tr>
							 
								<th scope="col" style=" text-align:left;">新闻标题</th>
								<th scope="col">日期</th>
							</tr>
						</thead>
						<tbody>                             <asp:Repeater ID="rpNewsList" runat="server">
				<ItemTemplate>
						<tr>
						 
								<td class="font02">[<%#Eval("TypeName")%>]&nbsp;<a href="/News.aspx?id=<%#Eval("News_ID") %>" style='color:<%#Eval("TitleColor").ToString() == "black" ? "#555454" : Eval("TitleColor")%>;' target="_blank" title="<%#Eval("Title").ToString() %>"><%# Eval("Title").ToString() %></a></td>
								<td><%#Eval("Issue_Time","{0:yyyy-MM-dd}")%></td>
							</tr>
					 
				</ItemTemplate>
			</asp:Repeater>
							 
						</tbody>
					</table>
					<div class="sabrosus">
			<webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True"
				CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
				FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
				ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
				TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5" CurrentPageButtonClass="current" ShowPrevNext="False">
			</webdiyer:AspNetPager>
		</div>
				</div>
			</div>
			<p><img src="/Images/cont_img01.jpg" alt="" /></p>
		</div>
   
    <div class="clear"></div>
      </div><!--right End-->
       


<!--footer-->
	<WebFooter:Control ID="webFooterone" runat="server" /> 
</form>
</body>
</html>
