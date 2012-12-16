<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.DuiJiang" %>

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
    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <style type="text/css">
        .red
        {
            color: red;
            font-family: Arial, "宋体";
        }
        #r_content img
        {
            max-width: 500px;
        }
        /* for Firefox & IE7 */* html #r_content img
        {
            /* for IE6 */
            width: expression(this.width > 700 ? 500 : true);
        }
    </style>
</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" pageType="8" />
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" />
            <WebService:Control ID="webservice1" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    兑奖中心</h3>
                <p class="dqwz">
                    当前位置：首页 >兑奖中心 > 兑换奖品</p>
            </div>
            <div id="sub_nr">
                <p class="dhzx_img" style="float: left;">
                    <img src="<%= AwardPic%>" alt="" width="136" height="107" onerror="this.src='/Images/NoPicture/no_pic.gif';this.onerror='';" /></p>
                <div class="yxjs" style="width: 452px;">
                    <table width="402" summary="" border="0">
                        <caption>
                        </caption>
                        <colgroup>
                            <col width="20%" />
                            <col width="1%" />
                            <col width="79%" />
                        </colgroup>
                        <tbody>
                            <tr>
                                <th scope="row">
                                    奖品名称
                                </th>
                                <td>
                                    <img src="/Images/cont_line02.jpg" alt="" />
                                </td>
                                <td class="font01 l10">
                                   <%=AwardName %>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    所需<%=UiCommon.StringConfig.GoldName%>
                                </th>
                                <td>
                                    <img src="/Images/cont_line02.jpg" alt="" />
                                </td>
                                <td class="font01 l10">
                                   <%=UiCommon.StringConfig.AddZeros(AwardMoney)%><%=UiCommon.StringConfig.GoldName%>
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    所需时长
                                </th>
                                <td>
                                    <img src="/Images/cont_line02.jpg" alt="" />
                                </td>
                                <td class="font01 l10">
                                   <%=AwardTime %>小时（游戏时间）
                                </td>
                            </tr>
                            <tr>
                                <th scope="row">
                                    剩余数量
                                </th>
                                <td>
                                    <img src="/Images/cont_line02.jpg" alt="" />
                                </td>
                                <td class="font01 l10">
                                    <%=AwardCount%>
                                </td>
                            </tr>
                        </tbody>
                    </table>
                </div>
                <div class="dtjs">
                    <h3>
                        奖品详细说明</h3>
                    <br />
                    <div id="r_content" style="width: 100%; word-wrap: break-word;">
                        <%= Server.HtmlDecode(AwardInfo) %>
                    </div>
                    <br />
                    <strong>请认真填写您的姓名和联系方式以及详细收货地址，以便确保您所兑换的奖品准确送到您的手中!</strong>
                    <br />
                    <form id="Form1" class="democss" runat="server" onsubmit="return onFormSubmit(this)">
                    <asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                    <div class="cz">
                    <table width="100%" border="0" cellspacing="0" cellpadding="0">
                        <tr>
                            <th width="20%" height="30" align="right" scope="row">
                                <label for="id01">
                                    真实姓名：</label>
                            </th>
                            <td width="80%">
                                <asp:TextBox ID="txtTrueName" runat="server" CssClass="in" MaxLength="20"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <th height="30" align="right" scope="row">
                                <label for="id01">
                                    联系电话：</label>
                            </th>
                            <td>
                                <asp:TextBox ID="txtPhone" runat="server" CssClass="in" MaxLength="20"></asp:TextBox>
                                <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="txtPhone"
                                    Display="Dynamic" ErrorMessage="电话号码不能空！"></asp:RequiredFieldValidator>
                                <asp:RegularExpressionValidator ID="RegularExpressionValidator1" runat="server" ControlToValidate="txtPhone"
                                    Display="Dynamic" ErrorMessage="请输入正确的电话号码！" ValidationExpression="^(\(\d{3,4}\)|\d{3,4}-|\d{3})\d{7,8}$"></asp:RegularExpressionValidator>
                            </td>
                        </tr>
                        <tr>
                            <th>
                                &nbsp;
                            </th>
                            <td>
                                注：固定电话的区号用()或- 隔开！
                            </td>
                        </tr>
                        <tr>
                            <th height="30" align="right" scope="row">
                                <label for="id01">
                                    收货地址：</label>
                            </th>
                            <td>
                                <asp:TextBox ID="txtAddress" runat="server" CssClass="in" MaxLength="100" Width="365px"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <th height="30" align="right" scope="row">
                                <label for="id01">
                                    备注信息：</label>
                            </th>
                            <td>
                                <asp:TextBox ID="txtUserRemark" runat="server" Rows="5" TextMode="MultiLine" Width="365px"
                                    MaxLength="500"></asp:TextBox>
                            </td>
                        </tr>
                        <tr>
                            <th height="60" scope="row">
                            </th>
                            <td>
                                <input type="submit" name="imageField2" id="imageField2" class="but_01" value="  "
                                    onserverclick="button5_ServerClick" runat="server" />
                            </td>
                        </tr>
                    </table>
                    </div>
                    </form>

                    <script type="text/javascript">
    <!--
                        function onFormSubmit(f) {

                            //            var pass  = document.getElementById("txtPassword");
                            //            if(!alertNull(pass,"请先输入您的密码！")){
                            //				return false;
                            //            }

                            //真实姓名-----------
                            var txtTrueName = document.getElementById('txtTrueName');
                            if (!alertNull(txtTrueName, '请输入真实姓名！')) {
                                return false;
                            }

                            //联系电话-----------
                            var txtPhone = document.getElementById('txtPhone');
                            if (!alertNull(txtPhone, '请输入联系电话！')) {
                                return false;
                            }

                            //联系地址-----------
                            var txtAddress = document.getElementById('txtAddress');
                            if (!alertNull(txtAddress, '请输入收货地址！')) {
                                return false;
                            }

                            var o = document.getElementById("txtUserRemark");
                            if (o.value.length > 500) {
                                alert('备注不能超过500个字符');
                                return false;
                            }

                            return true;
                        }
     //-->
                    </script>

                </div>
            </div>
            <p>
                <img src="Images/cont_img01.jpg" alt="" /></p>
            <!--pageNumber-->
        </div>
    </div>
    <div class="clear">
    </div>
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
