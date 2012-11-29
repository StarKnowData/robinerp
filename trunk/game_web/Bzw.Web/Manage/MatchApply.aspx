<%@ Page Language="C#" AutoEventWireup="true"  Inherits="Bzw.Inhersits.Manage.Manage_MatchApply" %>

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
	
	<link href="/Style/mainstyle.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" src="/Public/Js/Global.js"></script>
   <script type="text/javascript" src="/Public/Js/AviodHotKey.js"></script> 

 
</head>
<body>
<div id="wrap">
<!--header-->
   <WebTop:Control ID="webTopOne" runat="server" pageType="4"/> 
<!--content-->
    <div id="content">
      <div id="left1">
        <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
		<WebService:Control ID="webservice1" runat="server" />
      </div>
 <div id="right">
      <div class="right_con_title">  <span>当前位置：<a href="/Default.aspx" title="首页">首页</a> > <a href="/Manage/MatchApply.aspx" title="充值">比赛专区</a> </span>
      <h1>比赛报名</h1></div>
      <div class="rightbox" >
      <form runat="server" id="Form1">
               <div id="text" style="min-height:400px;">
            
               <asp:Panel ID="panShow" runat="server">
               <asp:HiddenField  ID="hids" runat="server" /> <asp:HiddenField ID="hide" runat="server" />
               	<h1 ><%=MatchName  %></h1>
               	<p></p>
               	<p><span  style="color:#2E66A1; font-size:14px; font-weight:bolder">报名费用：</span><%=NeedMoney %><%=ConfigurationManager.AppSettings["moneyName"].ToString()%></p>
               	<p><span  style="color:#2E66A1; font-size:14px; font-weight:bolder">开赛时间：</span><%=StartTime %>&nbsp;&nbsp;&nbsp;~&nbsp;&nbsp;&nbsp;<%=EndTime %></p>
        <%--       	<p ><%=MatchSend %></p>--%>
                <p>
               	<div style=" margin-top:0px; padding-left:25px;">
             <span style="color:#2E66A1; font-size:14px; font-weight:bolder">  	奖励方案</span>
               		<table style=" border:1px solid #2E66A1; width:50%;" cellpadding="0" cellspacing="0" > 
               	    <tr style=" border:1px solid #2E66A1;" ><th  style=" border-right:1px solid #2E66A1; ">名次</th><th>奖励</th></tr>
               	    <asp:Repeater ID="rptAward" runat="server">
               	    <ItemTemplate>
               	        <tr style=" border:1px solid #2E66A1; text-align:center;" ><td style=" border-right:1px solid #2E66A1; ">第<%# HZ(Convert.ToInt32( Eval("Rank").ToString()))%>名</td><td><%#Eval("GiveNum") %><%=UiCommon.StringConfig.GoldName %></td></tr>
               	    </ItemTemplate>
               	    </asp:Repeater>
               	</table>
               	</div></p>
               	<p><%=MatchContent %></p>
               	<p>	<input type="submit" name="imageField2" class="but_01" value="立即报名" onserverclick="button5_ServerClick"
						runat="server" id="imageField2" />&nbsp;&nbsp;&nbsp;&nbsp;
					<input type="button" name="btnExit" class="but_02" value="退赛"  
						id="btnExit" runat="server" visible="false"  onserverclick="btnExit_ServerClick"   onclick="confirm('确定要退出比赛报名吗？');" /></p>
						</asp:Panel>
               </div>
                   
      </form>
      </div>   
    </div> 

         </div><!--right End-->
 
    </div><!--content End-->  
  <div class="clear"></div>
       
<!--footer-->
	<WebFooter:Control ID="webFooterone" runat="server" /> 
</body>
</html>
