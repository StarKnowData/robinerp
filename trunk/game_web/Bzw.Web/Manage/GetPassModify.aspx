<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_GetPassModify" %>

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
        <WebTop:Control ID="webTopOne" runat="server" pageType="3" />
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
            <WebService:Control ID="webservice1" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    重置密码</h3>
                <p class="dqwz">
                    当前位置：首页 > 找回密码
                </p>
            </div>
            <div id="sub_nr">
                <div class="cz">
                    <form id="form1" runat="server" onsubmit="return onFormSubmit(this)">
                    <table width="100%" border="0" cellpadding="0" cellspacing="0" class="tab03">
                        <tr>
                            <th colspan="2" style="height: 40px; font-size: 14px;">
                                第三步：设置新的密码
                            </th>
                        </tr>
                       
                        <tr>
                            <th width="40%" height="30" align="right" scope="row">
                                输入新密码：
                            </th>
                            <td width="60%" valign="middle">
                                <asp:TextBox ID="txtPass" CssClass="pro_input" runat="server" TextMode="password"
                                    MaxLength="20"></asp:TextBox>
                                由6-20个英文字母或数字组成
                            </td>
                        </tr>
                        <tr>
                            <th align="right" height="30" scope="row" width="40%">
                                确认新密码：
                            </th>
                            <td valign="middle" width="60%">
                                <asp:TextBox ID="txtPass2" CssClass="pro_input" runat="server" TextMode="password"
                                    MaxLength="20"></asp:TextBox>
                                请再输入您上面输入的密码
                            </td>
                        </tr>
                        <tr>
                            <td height="65" scope="row">
                                &nbsp;
                            </td>
                            <td>
                                <input class="but_011" type="submit" name="button5" id="button5" value="更新密码" onserverclick="button5_ServerClick"
                                    runat="server" />
                                <input class="but_022" type="reset" name="button5" id="Submit1" value="重置" />
                            </td>
                        </tr>
                         <tr>
                            <td colspan="2" align="center" valign="middle">
                                <asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                            </td>
                        </tr>
                    </table>
                    </form>

                    <script type="text/javascript">
    <!--

							function onFormSubmit(f) {

								var txtPass = document.getElementById('txtPass');
								if (!alertNull(txtPass, '请输入密码')) {
									return false;
								}

								if (!/^[0-9a-zA-Z]{6,20}$/.test(txtPass.value)) {
									alert('密码由6-20个英文字母或数字组成');
									txtPass.focus();
									return false;
								}

								var txtPass2 = document.getElementById('txtPass2');
								if (txtPass.value.trim() != txtPass2.value.trim()) {
									alert('两次输入密码不一致，请重新输入。');
									txtPass2.focus();
									return false;
								}

								return true;
							}
     //-->
                    </script>

                </div>
                <div class="clear">
                </div>
            </div>
            <!--right End-->
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
        <!--content End-->
    </div>
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
