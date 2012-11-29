<%@ Page Language="C#" AutoEventWireup="true"  Inherits="Bzw.Inhersits.RankLotteries" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>

<%@ Register TagName="Control" TagPrefix="RankLeft" Src="~/Public/RankLeft.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>
	</title>
	
	<link href="/Style/mainstyle.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" src="/Public/Js/Global.js"></script>
</head>
<body>
<div id="wrap">
<!--header-->
	  <WebTop:Control ID="webTopOne" runat="server" pageType="7"/> 
<!--content-->
    <div id="content">
      <div id="left1">
		<RankLeft:Control ID="rankLeft" runat="server" />
      </div>
 <div id="right">
      <div class="right_con_title"><span>当前位置：<a href="/Default.aspx" title="首页">首页</a> > <a href="/RankMoney.aspx" title="奖券排行榜" ><%=UiCommon.StringConfig.GoldName %>排行榜</a></span>
      <h1><%=UiCommon.StringConfig.GoldName%>排行榜</h1></div>
      <div class="rightbox" >
		<div id="rank">
         <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab01">
		  <thead>
			<tr>
			  <th width="30%">排名</th>
			  <th width="40%">昵称</th>
			  <th width="40%">总<%=UiCommon.StringConfig.GoldName%></th>
			</tr>
		 </thead>
			<asp:Repeater ID="rpList" runat="server">
				<ItemTemplate>
					<tr>
						<td>
							<%# Container.ItemIndex + 1 %>
						</td>
						<td>
							<%#Eval("NickName") %>&nbsp;
						</td>
						<td>
							<%#UiCommon.StringConfig.AddZeros(Eval("Lotteries"))%>
						</td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
		  </table>
		</div>     
				<div class="clear"></div>
			  </div>  
			</div>
			 <div class="clear"></div>
			  </div><!--right End-->
			   
    </div><!--content End-->
</div>
<!--footer-->
<WebFooter:Control ID="webFooterone" runat="server" /> 
</body>
</html>
