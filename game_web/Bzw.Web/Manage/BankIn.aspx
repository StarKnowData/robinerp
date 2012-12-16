<%@ Page Language="C#" AutoEventWireup="true"   Inherits="Bzw.Inhersits.Manage.Manage_BankIn" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>
		
	</title>
	<script type="text/javascript" src="/Public/Js/jquery.js"></script>
	<link href="/Style/mainstyle.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" src="/Public/Js/Global.js"></script>

</head>
<body>
<div id="wrap">
<!--header-->
	 <WebTop:Control ID="webTopOne" runat="server"/> 
<!--content-->
    <div id="content">
      <div id="left1">
        <Left:Control ID="leftOne" runat="server" />
        <WebService:Control ID="webServiceOne" runat="server" />
      </div>
 <div id="right">
      <div class="right_con_title">  <span>当前位置：<a href="/Default.aspx" title="首页">首页</a> > 会员中心</span>
      <h1>存入<%=ConfigurationManager.AppSettings["moneyName"].ToString()%></h1></div>
      <div class="rightbox" >
           <div id="memText01">
            <div class="rank_manu" id="record">
            存入<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>&nbsp;&nbsp;
	|&nbsp;&nbsp;<a id="g2" href="/Manage/BankAccess.aspx">取出<%=ConfigurationManager.AppSettings["moneyName"].ToString()%></a>&nbsp;&nbsp;
            </div>
						<form id="Form1" runat="server" onsubmit="return onFormSubmit(this)">
							<table width="100%" border="0" cellpadding="0" cellspacing="0" class="memberTable">
								<tr>
									<th colspan="2" scope="row">
										<asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label></th>
								</tr>
								<tr>
									<th width="24%" height="35" align="right" scope="row">
										游戏帐号：</th>
									<td width="76%">
										<%=UiCommon.UserLoginInfo.UserName %>
									</td>
								</tr>
								<tr>
									<th align="right" height="35" scope="row">
										转出游戏：</th>
									<td>
										<asp:DropDownList ID="ddlGame" runat="server"></asp:DropDownList></td>
								</tr>
								
								<tr>
									<th height="35" align="right" scope="row">
										取出<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>数：</th>
									<td>
										<asp:TextBox ID="txtMoney" runat="server"></asp:TextBox> <%=ConfigurationManager.AppSettings["moneyName"].ToString()%></td>
								</tr>
							 <tr>
									<th height="35" align="right" scope="row">
										银行总数：</th>
									<td>
										<asp:Literal ID="lteBank" runat="server"></asp:Literal><%=ConfigurationManager.AppSettings["moneyName"].ToString()%></td>
								</tr>
								
								<tr>
									<th height="35" align="right" scope="row">
										银行密码：</th>
									<td>
										<asp:TextBox  TextMode="Password" ID="txtTwoPassword" runat="server" CssClass="pro_input" MaxLength="12" Width="104px"></asp:TextBox></td>
								</tr>
								<tr>
									<th height="50" scope="row">
										&nbsp;</th>
									<td>
										<input class="but_01" type="submit" name="button5" id="button5" value="提 交" runat="server" onserverclick="button5_ServerClick"    /><input class="but_02" type="button" name="button5" id="Submit1" value="重 置" onclick="ClearInfo()" /></td>
								</tr>
							</table>
						</form>

						<script type="text/javascript">
<!--  
    
    function ClearInfo(){
        document.getElementById('txtMoney').value = '';
        document.getElementById('txtTwoPassword').value = '';
    }
    
    function onFormSubmit(f){        
        var txtMoney = document.getElementById('txtMoney');
        var txtTwoPassword = document.getElementById('txtTwoPassword');
        if(!alertNonNegativeNumber(txtMoney, '取出金额必须是大于零的整数！') || !alertNull(txtTwoPassword,'请输入银行密码！')){
            return false;
        }
       
        return true;
    }
 

 //-->
                        </script>
                         <div class="rank_title" style=" padding-bottom:0px;" >游戏<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>列表</div>
                   <div id="rank">
                        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="tab01">
								<tr>
									<th>
										序号</th>
								<th>
										游戏名</th>
									<th>
										银行<%=ConfigurationManager.AppSettings["moneyName"].ToString()%></th>
									 
								</tr>
								<asp:Repeater ID="rpList" runat="server">
									<ItemTemplate>
										<tr align="center">
											<td>
												<%=Rowid+=1%>
											</td>											
											<td>
												<%#Eval("ComName")%>
											</td>
											<td>
												<%#Eval( "WalletMoney" )%>
											</td>
											 
										</tr>
									</ItemTemplate>
								</asp:Repeater>
							</table>
							<div class="clear">
							</div>
							  <div class="sabrosus" style="width:60%;">
								<webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True"
									CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
									FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
									ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
									TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5" CurrentPageButtonClass="current" ShowPrevNext="False" PageSize="20">
								</webdiyer:AspNetPager>
							</div></div>
  </div>
      </div>  
    </div>
     <div class="clear"></div>
      </div><!--right End-->
 <div class="counsel"><img src="/images/jkzg.gif" width="919" height="27" alt="健康游戏"/></div>
    </div><!--content End-->
 
<!--footer-->
	<WebFooter:Control ID="webFooterone" runat="server" /> 
</body>
</html>
