<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Down2"%>

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
    <script type="text/javascript" src="/Public/Js/topbtn.js"></script>

    <script type="text/javascript" src="/Public/Js/submu.js"></script>
</head>
<body>
   <div id="container">
<!--header-->
     <WebTop:Control ID="webTopOne" runat="server" pageType="2"/> 
<!--content-->
    
    <div id="left">
       	<BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
		<WebService:Control ID="webservice1" runat="server" />
      </div>
      <div id="content01">

			<div id="title01">

				<h3 class="fl">游戏下载</h3>

				<p class="dqwz">当前位置：首页 > 游戏下载</p>

			</div>

			<div id="sub_nr">

				<p class="cp_img01"><img src="<%= mainImg%>" alt=""  width="240px" height="208px" /></p>

				<div class="yxjs">

					<p class="yx_tit"><%=UiCommon.StringConfig.SiteName %>游戏大厅下载</p>

					<table width="402" summary="" border="0">

						<caption></caption>

						<colgroup>

							<col width="20%" />

							<col width="1%" />

							<col width="79%" />

						</colgroup>

						<tbody>

							<tr>

								<th scope="row">更新时间</th>

								<td><img src="/Images/cont_line02.jpg" alt="" /></td>

								<td class="font01 l10"><asp:Literal ID="lteTime" runat="server"></asp:Literal></td>

							</tr>

							<tr>

								<th scope="row">版&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;本</th>

								<td><img src="/Images/cont_line02.jpg" alt="" /></td>

								<td class="font01 l10"><asp:Literal ID="lteCopy" runat="server"></asp:Literal> </td>

							</tr>

							<tr>

								<th scope="row">应用平台</th>

								<td><img src="/Images/cont_line02.jpg" alt="" /></td>

								<td class="font01 l10"><asp:Literal ID="LteUse" runat="server"></asp:Literal> </td>

							</tr>

							<tr>

								<th scope="row">软件大小</th>

								<td><img src="/Images/cont_line02.jpg" alt="" /></td>

								<td class="font01 l10"><asp:Literal ID="LteSize" runat="server"></asp:Literal>KB</td>

							</tr>

						</tbody>

					</table>

					<div class="yx_btn"><a href="<%= smallUrl%>"><img src="/Images/cont_btn01.jpg" alt="" /></a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href="<%= fullUrl%>"><img src="/Images/cont_btn02.jpg" alt="" /></a></div>

				</div>

				<div class="dtjs">

					<h4><img src="/Images/cont_tit04.jpg" alt="" /></h4>

					<p><asp:Literal ID="lteInfo" runat="server"></asp:Literal></p>

				</div>

				<div class="yxlb">

					<h4><img src="/Images/cont_tit05.jpg" alt="" /></h4>

					 <ul>
                    <asp:Repeater ID="rpGameList" runat="server">
									<ItemTemplate>
								 
										<li>
											<a href="/GameInfo.aspx?id=<%#Eval("Game_id") %>" title="<%# Eval("Game_Name") %>">
												<img src="<%#Eval("Image_URL") %>" width="68" height="51" alt="<%# Eval("Game_Name") %>"/>
											</a>
											<p  class="ac t03"><a href="/GameInfo.aspx?id=<%#Eval("Game_id") %>" title="<%# Eval("Game_Name") %>"><%# Eval("Game_Name") %></a></p>
										</li>
									</ItemTemplate>
					</asp:Repeater>
              </ul>

				</div>

			</div>

			<p><img src="Images/cont_img01.jpg" alt="" /></p>

		</div>

 
    <div class="clear"></div>
      </div><!--right End-->
     
     <!--content End-->
 
<!--footer-->
	<WebFooter:Control ID="webFooterone" runat="server" /> 
</body>
</html>
