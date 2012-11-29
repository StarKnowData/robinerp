<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_GetPassAnswer" %>

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
                    密码找回</h3>
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
                                第二步：输入注册用户名
                            </th>
                        </tr>
                      
                        <tr style="display: none;">
                            <th width="40%" height="30" align="right" scope="row">
                                证件类型：
                            </th>
                            <td width="60%" valign="middle">
                                <asp:DropDownList ID="ddlCardType" runat="server" Enabled="False">
                                </asp:DropDownList>
                            </td>
                        </tr>
                        <tr>
                            <th align="right" height="30" scope="row" width="40%">
                                身份证号：
                            </th>
                            <td valign="middle" width="60%">
                                <asp:TextBox ID="txtCardNo" runat="server" CssClass="pro_input" MaxLength="18"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <th align="right" height="30" scope="row" width="40%">
                                提示问题：
                            </th>
                            <td valign="middle" width="60%">
                                <asp:DropDownList ID="ddlQuestion" runat="server" Enabled="False">
                                </asp:DropDownList>
                            </td>
                        </tr>
                        <tr>
                            <th align="right" height="30" scope="row" width="40%">
                                问题答案：
                            </th>
                            <td valign="middle" width="60%">
                                <asp:TextBox ID="txtAnwer" runat="server" CssClass="pro_input"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <th align="right" height="30" scope="row" width="40%">
                                银行密码：
                            </th>
                            <td valign="middle" width="60%">
                                <asp:TextBox ID="txtTwoPass" runat="server" TextMode="Password" CssClass="pro_input"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <td colspan="2" valign="middle" align="center"><br />
                                注意：输入以上三个问题，只要其中有二个问题回答正确即可找回密码！
                            <br />
                                <input class="but_011" type="submit" name="button5" id="button5" value="下一步" onserverclick="button5_ServerClick"
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

								//证件号码-----------
								var ZJ_Number = document.getElementById('txtCardNo');
								if (!alertNull(ZJ_Number, '请输入身份证号！')) {
									return false;
								}


								//问题答案-----------
								var Answer = document.getElementById('txtAnwer');
								if (!alertNull(Answer, '请输入问题答案！')) {
									return false;
								}

								//银行密码-----------
								var pass = document.getElementById('txtTwoPass');
								if (!alertNull(pass, '请输入银行密码！')) {
									return false;
								}


								return true;
							}
     //-->
                    </script>

                </div>   
                <div class="clear">
                </div>
            
            </div> <p>
                    <img src="/Images/cont_img01.jpg" alt="" /></p>
            <!--right End-->
        </div>
        <!--content End-->
    </div>
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
