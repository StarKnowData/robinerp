<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_PropClearFasci" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>
      
    </title>
  
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" />
        <!--content-->
        <div id="left">
            <Left:Control ID="leftOne" runat="server" />
            <WebService:Control ID="webServiceOne" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    魅力值清零</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 魅力值清零</p>
            </div>
            <div id="sub_nr">
                <form id="form1" runat="server" onsubmit="return onFormSubmit(this)">
                <div  class="cz">
                    <table border="0" cellpadding="2" cellspacing="0" width="100%" >
                        <tr>
                            <td align="right">
                                您当前的魅力值：
                            </td>
                            <td align="left">
                                <%=UserFasci %>
                            </td>
                        </tr>
                        <tr>
                            <td align="right">
                                选择类型：
                            </td>
                            <td align="left">
                                <asp:DropDownList ID="ddlType" runat="server" AutoPostBack="False">
                                </asp:DropDownList>
                                <br />
                            </td>
                        </tr>
                        <tr><td colspan="2" style=" text-align:center; height:40px; line-height:40px;"> <input class="but_011" type="submit" name="button5" id="button5" value="购买并使用" onserverclick="button5_ServerClick"
                        runat="server" /></td></tr>
                    </table>
                </div>
                <div style="margin: 10px;">
                    <asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                </div>
               
                <div style="text-align: left; margin-left: 8px; margin-top: 10px;">
                    <b>魅力清零道具说明：</b><br />
                    <table width="100%" border="0" align="center" cellpadding="3" cellspacing="0" class="memberTable">
                        <asp:Repeater ID="rptList" runat="server">
                            <ItemTemplate>
                                <tr align="center">
                                    <td align="left">
                                        <%# Eval("Description") %>
                                    </td>
                                    <td align="left">
                                        价格：<%# UiCommon.StringConfig.AddZeros(Eval( "Price" ))%><%=ConfigurationManager.AppSettings["moneyName"].ToString()%>
                                    </td>
                                </tr>
                            </ItemTemplate>
                        </asp:Repeater>
                    </table>
                </div>
                </form>

                <script type="text/javascript">
							<!--
							function onFormSubmit(f){

								if(confirm('确认购买并使用吗？')){
									return true;
								}
								else{
									return false;
								}
							}
							//-->
                </script>

            </div>
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
        <div class="clear">
        </div>
    </div>
    <!--right End-->
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
