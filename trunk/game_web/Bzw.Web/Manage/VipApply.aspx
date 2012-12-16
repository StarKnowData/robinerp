<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_VipApply"  %>

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
	
	 <link href="/css/layout.css" rel="stylesheet" type="text/css" />
	<script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>
	<script type="text/javascript" src="/Public/Js/Global.js"></script>

</head>
<body>
    <div id="container">
<!--header-->
	 <WebTop:Control ID="webTopOne" runat="server"/> 
<!--content-->
 
      <div id="left">
        <Left:Control ID="leftOne" runat="server" />
        <WebService:Control ID="webServiceOne" runat="server" />
      </div>
       <div id="content01">
            <div id="title01">
                <h3 class="fl">
                   申请VIP</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 申请VIP录</p>
            </div>
            <div id="sub_nr" style="margin-top: 10px;">
       
           <div id="memText01">
           						<h4>
							 VIP状态：
							<asp:Literal ID="lblVipState" runat="server"></asp:Literal></h4>
						<form id="Form1" runat="server" onsubmit="return onFormSubmit(this)">
						  <div class="cz">
							<table width="100%" border="0" cellpadding="0" cellspacing="0" class="memberTable">
								<tr>
									<th height="30" align="right" scope="row">
										&nbsp;</th>
									<td valign="middle">
										<asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label></td>
								</tr>
								<tr>
									<th width="23%" height="30" align="right" scope="row">
										申请VIP类型：</th>
									<td width="77%" valign="middle">
										<asp:DropDownList ID="ddlVipType" runat="server">
											<asp:ListItem Value="7" Text="一周VIP"></asp:ListItem>
											<asp:ListItem Value="30" Text="一月VIP"></asp:ListItem>
											<asp:ListItem Value="180" Text="半年VIP"></asp:ListItem>
											<asp:ListItem Value="360" Text="一年VIP"></asp:ListItem>
										</asp:DropDownList></td>
								</tr>
								<tr>
									<th height="40" scope="row">
										&nbsp;</th>
									<td>
										<input class="but_011" type="submit" name="button5" id="button5" value="申请VIP" onserverclick="button5_ServerClick"
											runat="server" /></td>
								</tr>
							</table>
							</div>
						</form>
						<script type="text/javascript">
<!--
function onFormSubmit(f){

    if(confirm('确认购买VIP吗？')){
        return true;
    }
    else{
        return false;
    }
}
//-->
						</script>
						<br />
						(一周VIP<%=UiCommon.StringConfig.AddZeros(MoneyToViptimeWeek)%><%=ConfigurationManager.AppSettings["moneyName"].ToString()%>,一月VIP<%=UiCommon.StringConfig.AddZeros(MoneyToViptimeMonth)%><%=ConfigurationManager.AppSettings["moneyName"].ToString()%>,半年VIP<%=UiCommon.StringConfig.AddZeros(MoneyToViptimeHYear)%><%=ConfigurationManager.AppSettings["moneyName"].ToString()%>,一年VIP<%=UiCommon.StringConfig.AddZeros(MoneyToViptimeYear)%><%=ConfigurationManager.AppSettings["moneyName"].ToString()%>)
						<br /><br />
						<strong>VIP会员说明：</strong> 申请成为VIP会员后，享有在游戏中红色高亮显示昵称、购买所有游戏道具享受最优惠价格、可踢非VIP会员离开游戏房间的尊贵待遇。（注：申请VIP会员需扣除您银行帐户中对应的游戏<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>，在申请前请确保您的银行帐户中有足够的游戏<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>）
				             </div>
      </div>  
       <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
    </div>
     <div class="clear"></div>
      </div><!--right End-->
 
     
<!--footer-->
	<WebFooter:Control ID="webFooterone" runat="server" /> 
</body>
</html>