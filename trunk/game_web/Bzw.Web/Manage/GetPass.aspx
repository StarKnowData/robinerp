<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_GetPass" %>

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

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" />
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
            <WebService:Control ID="webservice1" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    密码找回</h3>
                <p class="dqwz">
                    当前位置：首页 > 找回密码
                </p>
            </div>
            <div id="sub_nr">
                <div class="cz">
                    <form runat="server" name="form1" onsubmit="return onFormSubmit(this)">
                    <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab03">
                        <tr>
                            <td colspan="2" style="height: 40px; font-size: 14px;">
                                第一步：输入注册用户名
                            </td>
                        </tr>
                        
                        <tr>
                            <th width="20%" height="30" align="right" scope="row">
                                用户名：
                            </th>
                            <td width="60%" valign="middle">
                                <asp:TextBox ID="txtUserName" CssClass="pro_input" runat="server" MaxLength="20"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <th height="30" align="right" scope="row">
                                验证码：
                            </th>
                            <td valign="middle">
                                <%--<input name="textfield3" type="text" class="pro_input" id="textfield4" size="8" />
									<img src="temp/CF_CheckCode.gif" width="40" height="10" />--%>
                                <asp:TextBox ID="txtValidCode" CssClass="pro_input" runat="server" MaxLength="4"
                                    Width="61px"></asp:TextBox>
                                <img src="/Public/Getcode.aspx" onclick="this.src='/Public/Getcode.aspx?token='+tokenKey();"
                                    alt="点击换一张图片" style="vertical-align: top; cursor: pointer; width: 40px; height: 16px" />
                            </td>
                        </tr>
                        <tr>
                          <td></td>
                            <td  >
                                <input type="submit" value="下一步" class="but_011" onserverclick="button5_ServerClick"
                                    runat="server" id="button5" />
                            </td>
                        </tr>
                        <tr>
                            <td colspan="2" align="center" valign="middle">
                                <asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                            </td>
                        </tr>
                    </table>
                    </form>
                </div>
                <div class="clear">
                </div>
            </div> <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
            <!--right End-->
        </div>
        <!--content End-->
        <div class="clear">
        </div>
    </div>
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>

<script type="text/javascript">
    <!--

	function onFormSubmit(f) {

		var txtUserName = document.getElementById('txtUserName');
		if (!alertNull(txtUserName, '请输入注册时填写的用户名')) {
			return false;
		}

		var txtValidCode = document.getElementById('txtValidCode');
		if (!alertNull(txtValidCode, '请输入验证码！')) {
			return false;
		}

		return true;
	}
     //-->
</script>

</html>
