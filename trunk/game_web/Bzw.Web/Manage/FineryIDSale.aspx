<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.FineryIDSale" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
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
        <WebTop:Control ID="webTop" runat="server" />
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webCutKey" runat="server" />
            <WebService:Control ID="webService" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    靓号购买</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 靓号购买</p>
            </div>
            <div id="sub_nr" style="margin-top: 10px;">
                <div class="cz">
                    <form id="frmLogin" runat="server" onsubmit="return onFormSubmit(this);">
                    <table width="100%" border="0">
                        <tr>
                            <th colspan="2" scope="row">
                                &nbsp;
                            </th>
                        </tr>
                        <tr>
                            <th width="24%" height="35" align="right" scope="row">
                                靓&nbsp;号&nbsp;ID：
                            </th>
                            <td width="76%">
                                <asp:Label ID="fineryLB" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                            </td>
                        </tr>
                        <tr>
                            <th height="35" align="right" scope="row">
                                靓号价格：
                            </th>
                            <td>
                                <asp:Label ID="priceLB" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>&nbsp;&nbsp;<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>
                            </td>
                        </tr>
                        <tr>
                            <th height="35" align="right" scope="row">
                                靓号描述：
                            </th>
                            <td>
                                <asp:Label ID="explainLB" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                            </td>
                        </tr>
                        <tr>
                            <th align="right" valign="middle">
                                <strong>靓号密码：</strong>
                            </th>
                            <td align="left" valign="middle">
                                <input name="pwd" type="password" id="pwd" maxlength="20" onblur="chkPwd()" style="width: 149px;" />
                                <span class="red">*设定您的靓号密码，并请您牢记</span><br />
                                <span class="note" id="pwdspan">密码由6-20个英文字母或数字组成，请牢记您的靓号密码</span>
                            </td>
                        </tr>
                        <tr>
                            <th align="right" valign="middle">
                                <strong>密码确认：</strong>
                            </th>
                            <td align="left" valign="middle">
                                <input name="pwd2" type="password" id="pwd2" maxlength="20" onblur="chkPwd2()" style="width: 149px;" />
                                <span class="red">*</span>
                                <br />
                                <span class="note" id="pwd2span">请再次输入您的密码，保证无误。 </span>
                            </td>
                        </tr>
                        <tr>
                            <th colspan="2" align="center">
                                <asp:Panel ID="Panel1" runat="server" Visible="false">
                                    <a href="/Manage/BankAccess.aspx">去存款 >></a>&nbsp;&nbsp;&nbsp;&nbsp;<a href="/Manage/Pay/Default.aspx">去充值
                                        >></a>
                                </asp:Panel>
                            </th>
                        </tr>
                        <tr>
                            <td colspan="2" align="center">
                                <input id="Submit1" type="submit" name="submit" value="购买 " runat="server" onserverclick="Button1_Click"
                                    class="but_011" onclick="javascript:if(!confirm('您确定购买吗')){return false};" />
                            </td>
                        </tr>
                    </table>
                    </form>
                </div>
                <div class="clear">
                </div>
            </div>
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
    </div>
    <!--footer-->
    <WebFooter:Control ID="webfooter1" runat="server" />
</body>
</html>

<script type="text/javascript">
    /*===Check Pwd========================*/
    function chkPwd() {
        var txt = document.getElementById('pwd');
        var tip = document.getElementById("pwdspan");

        //valid is null--------------
        if (txt.value.trim().length == 0) {
            tip.className = "note_no";
            return false;
        }
        //valid regx-----------------
        if (!/^[0-9a-zA-Z]{6,20}$/.test(txt.value)) {
            tip.className = "note_no";
            return false;
        }

        tip.className = "note_yes";
        tip.innerHTML = "恭喜您！密码通过验证，请牢记您的靓号密码";
        return true;
    }

    /*===Check Pwd2========================*/
    function chkPwd2() {
        var txt = document.getElementById('pwd');
        var txt2 = document.getElementById('pwd2');
        var tip = document.getElementById("pwd2span");

        if (txt.value.trim().length < 6 || txt.value.trim().length > 20) {
            txt.focus();
            return false;
        }

        if (txt.value.trim() != txt2.value.trim()) {
            tip.className = "note_no";
            tip.innerText = '两次输入密码不一致，请重新输入。';
            return false;
        }

        tip.className = "note_yes";
        tip.innerText = '恭喜您，密码检测通过。';
        return true;
    }
    function onFormSubmit(f) {
        if (!chkPwd()) {
            document.getElementById('pwd').focus();
            return false;
        }

        if (!chkPwd2()) {
            document.getElementById('pwd2').focus();
            return false;
        }
        return true;
    }
</script>

