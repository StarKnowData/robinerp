<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Pay.Manage_Pay_PointCard"  %>

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
	<script type="text/javascript" src="/Public/Js/Global.js"></script>
	<script type="text/javascript" src="/Public/Js/common.js"></script>
	 <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <style type="text/css">
        .style1
        {
            height: 30px;
        }
    </style>
</head>
<body>
<div id="container">

<!--header-->
    <WebTop:Control ID="webTopOne1" runat="server" pageType="4"/> 

<!--content-->
 
      <div id="left">
        <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
		<WebService:Control ID="webservice1" runat="server" />
      </div>
      <!-- content start -->

		<div id="content01">

			<div id="title01">

				<h3 class="fl">点卡充值</h3>

				<p class="dqwz">当前位置：首页 >  账户充值</p>

			</div>

			<div id="sub_nr">

				<div class="cz">

					<p><strong class="text04">您选择了点卡充值方式</strong></p>
 <form id="Form1" action="" class="democss" runat="server" onsubmit="return onFormSubmit(this)">
					<table width="685" summary="" border="0">

						<caption></caption>

						<colgroup>

							<col width="20%" />

							<col width="80%" />

						</colgroup>

						<tbody>
                            <tr>
						<td valign="middle" colspan="2" align="center">
							<asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>&nbsp;
						</td>
					</tr>
							<tr>

								<th scope="row"><label for="id01">游戏帐号</label></th>

								<td> <asp:TextBox ID="txtUserName" runat="server" CssClass="in" MaxLength="20"></asp:TextBox></td>

							</tr>

							<tr>

								<th scope="row"><label for="id02">确认帐号</label></th>

								<td><asp:TextBox ID="txtUserName2" runat="server" CssClass="in" MaxLength="20"></asp:TextBox></td>

							</tr>
                            	<%if (ConfigurationManager.AppSettings["IsPayToPoint"] == "1")
       { %>
                    <tr>
                          <th height="30" align="right" scope="row">充值类型：</th>
                           <td valign="middle">
                           <asp:RadioButtonList ID="rblPayType" runat="server" RepeatDirection="Horizontal"   onclick="ChangeType()">
                                <asp:ListItem Text="金币" Value="money" Selected="True"></asp:ListItem>
                                <asp:ListItem Text="积分" Value="point"></asp:ListItem>
                           </asp:RadioButtonList>
                           </td>
                    </tr>
					<tr>
					    <th height="30" align="right" scope="row">请选择游戏：</th>
					    <td valign="middle">
					    <asp:DropDownList ID="ddlGameList" runat="server"  Enabled="false">
					 
					    </asp:DropDownList>&nbsp;充值<%=UiCommon.StringConfig.MoneyName %>不用选择游戏
					    </td>
					</tr>
					<%} %>
							<tr>

								<th scope="row" class="style1"><label for="id03">充值卡卡号</label></th>

								<td class="style1"><asp:TextBox ID="txtCardNo" runat="server" CssClass="in" MaxLength="50"></asp:TextBox></td>

							</tr>

							<tr>

								<th scope="row"><label for="id04">充值卡密码</label></th>

								<td><asp:TextBox ID="txtCardPwd" runat="server" CssClass="in" TextMode="password" MaxLength="50"></asp:TextBox></td>

							</tr>

							<tr>

								<th scope="row"><label for="id05">验证码</label></th>

								<td><p class="yzm01"><asp:TextBox ID="txtValidCode" runat="server" CssClass="in" MaxLength="4" Width="54px"></asp:TextBox><span class="red">*</span><img style="vertical-align: top; cursor: pointer; width: 50px; height: 19px" onclick="this.src='/Public/Getcode.aspx?token='+tokenKey();"  alt="点击换一张图片" src="/Public/Getcode.aspx" /></td>

							</tr>

						</tbody>

					</table>

					<p class="text06">* 请正确的填写充值的游戏帐号（用户名），如填错，本棋牌游戏中心不负任何责任。</p>

					<p class="cz_btn"> 
<input type="submit" name="imageField2" id="imageField2" class="but_01" value="  " onserverclick="button5_ServerClick" runat="server" />&nbsp;&nbsp;&nbsp;&nbsp;
								  <a href="javascript:"  onclick="ClearInfo()"><img src="/Images/cont_btn07.jpg" alt="" /></a>

					</p>

					<p><img src="/Images/cont_tbl_img22.jpg" alt="" /></p>
</form>
				</div>

			</div>

			<p><img src="/Images/cont_img01.jpg" alt="" /></p>

		</div>

	<!-- content end -->


 
     <div class="clear"></div>
       
</div>
<!--footer-->
	<WebFooter:Control ID="webFooterone" runat="server" /> 
			<script type="text/javascript">
<!--

				function ClearInfo() {
					document.getElementById('txtUserName').value = '';
					document.getElementById('txtUserName2').value = '';
					document.getElementById('txtCardNo').value = '';
					document.getElementById('txtCardPwd').value = '';
					document.getElementById('txtValidCode').value = '';
				}

				function onFormSubmit(f) {
				  
					var txtUserName = document.getElementById('txtUserName');
					var txtUserName2 = document.getElementById('txtUserName2');
					if (!alertNull(txtUserName, '请输入游戏帐号！（用户名）')) {
						return false;
					}

					if (txtUserName.value.trim() != txtUserName2.value.trim()) {
						alert('两次输入游戏帐号不一致！');
						txtUserName2.focus();
						return false;
					}

					var txtCardNo = document.getElementById('txtCardNo');
					if (!alertNull(txtCardNo, '请输入充值卡卡号！')) {
						return false;
					}

					var txtCardPwd = document.getElementById('txtCardPwd');
					if (!alertNull(txtCardPwd, '请输入充值卡密码！')) {
						return false;
					}

					var txtValidCode = document.getElementById('txtValidCode');
					if (!alertNull(txtValidCode, '请输入验证码！')) {
						return false;
		}
	 
					return true;
	}
	function ChangeType() {

	    if ($("#rblPayType").find("input[@checked]").val() == "point") {

	        document.getElementById("ddlGameList").disabled = false;
	    }
	    else {

	        document.getElementById("ddlGameList").disabled = true;
	    }
	}
 //-->
		</script>
</body>
</html>
