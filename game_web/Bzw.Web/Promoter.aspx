<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Promoter"%>

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
 <WebTop:Control ID="webTopOne" runat="server" pageType="6"/> 

<!--content-->
   
      <div id="left">
		<BZW:WebShortCutKey ID="webshortcutkey1" runat="server" isDisplay="0" />
		<WebService:Control ID="webservice1" runat="server" />
		</div>
		<div id="content01">
			<div id="title01">
				<h3 class="fl">推广员</h3>
				<p class="dqwz">当前位置：首页 > 推广员</p>
			</div>
			<div id="sub_nr">
				<div id="tgxt">
					<ul>	<asp:Repeater ID="rpNewZhiNan" DataSourceID="objDataZhiNan" runat="server">
					<ItemTemplate>
						<li>
							<a href="/Promoter.aspx?id=<%#Eval("News_ID") %>" class="link03">
					<%# Eval("News_ID") == Request.QueryString["id"] ? "<strong class='text05'>" + Eval("Title").ToString()+"</strong>": Eval("Title").ToString()%>		 
							</a>
						</li>
						
					</ItemTemplate>
				</asp:Repeater>
						<asp:ObjectDataSource ID="objDataZhiNan" SelectMethod="ListByTypeNameOfTG" TypeName="BLL.News"
					runat="server">
					<SelectParameters>
						<asp:Parameter Name="newTypeName" DefaultValue="推广系统" />
					</SelectParameters>
				</asp:ObjectDataSource> 
					</ul>
				</div>
				<p class="yxxz_xxnr ac"><strong class="text04"><%=NewTitle %></strong></p>
				<p class="yxxz_xxnr01"><%=NewContent %>
				</p>
			</div>
			<p><img src="/Images/cont_img01.jpg" alt="" /></p>
		</div>
		<%-- <div class="clear"></div>
	 	<div class="left_cont_title"><h5>推广系统</h5></div> 
	
		<div class="left_cont">
		 <ul class="memcemter">
				<asp:Repeater ID="rpNewZhiNan" DataSourceID="objDataZhiNan" runat="server">
					<ItemTemplate>
						<li>
							<a href="/Promoter.aspx?id=<%#Eval("News_ID") %>">
								<%#Eval("Title") %>
							</a>
						</li>
					</ItemTemplate>
				</asp:Repeater>
				
		 </ul>
		</div>
      </div>
 <div id="right">
     <div class="right_con_title"><span>当前位置：<a href="/Default.aspx" title="首页">首页</a> > 
													<a href="/NewsList.aspx" title="新闻中心">推广系统</a></span>
      <h1>推广系统</h1></div>
      <div class="rightbox" >
              <div id="text">
                          	<h1><%=NewTitle %></h1>
        <h6 style="display:none;">&nbsp;&nbsp; 时间： &nbsp; 浏览次数：</h6>
			 <%=NewContent %>
        </div>   
        <div class="clear"></div>
      </div>  
    </div>--%>
     <div class="clear"></div>
      </div><!--right End-->
      
    
 
<!--footer-->
<WebFooter:Control ID="webFooterone" runat="server" /> 
</body>
</html>
