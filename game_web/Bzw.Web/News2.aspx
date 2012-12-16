<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.News2"%>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>

<%@ Register TagPrefix="Bzw" TagName="NewsTypeList" Src="~/Public/NewsTypeList.ascx" %>
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
	 
	<style type="text/css">
    #r_content img {max-width: 500px;} /* for Firefox & IE7 */
    * html #r_content img { /* for IE6 */
    width:expression(this.width > 700 ? 500 : true);
    }
    </style>
</head>
<body>
<div id="container">
<!--header-->
 <WebTop:Control ID="webTopOne" runat="server" pageType="4"/> 

<!--content-->
 
      <div id="left">
		<BZW:WebShortCutKey ID="webshortcutkey1" runat="server" isDisplay="0" />
		<WebService:Control ID="webservice1" runat="server" />
      </div>
      <div id="content01">
			<div id="title01">
				<h3 class="fl">新闻中心</h3>
				<p class="dqwz">当前位置：首页 > 新闻中心</p>
			</div>
			<div id="sub_nr" style=" overflow:hidden;">
				 <Bzw:NewsTypeList ID="newsTypeListone" runat="server" />
				<div class="cz">
					<table  summary="" border="0" style=" overflow:hidden;">
						<caption></caption>
						<colgroup>
							<col width="20%" />
							<col width="80%" />
						</colgroup>
						<tbody>
							<tr>
								<th scope="row"><label for="id01">标&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;题</label></th>
								<td>	<span style="color:<%=TitleColor %>;"><%=NewTitle %></span></td>
							</tr>
							<tr>
								<th scope="row"><label for="id02">时&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;间</label></th>
								<td><%=AddTime%> </td>
							</tr>
							<tr>
								<th scope="row"><label for="id03">浏览次数</label></th>
								<td><%=Hits %></td>
							</tr>
							<tr>
								<th scope="row"><label for="id04">内&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;容</label></th>
								<td style=" overflow:hidden;">  <%=NewContent %></td>
							</tr>
						</tbody>
					</table>
					<p class="cz_btn"><a href="/NewsList.aspx"><img src="Images/cont_btn08.jpg" alt="" /></a></p>
				</div>
			</div>
			<p><img src="/Images/cont_img01.jpg" alt="" /></p>
		</div>
  
     <div class="clear"></div>
      </div>
<!--footer-->
<WebFooter:Control ID="webFooterone" runat="server" /> 
</body>
</html>