<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_FasciExchange" %>

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
  
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/public.js"></script>

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
                    魅力值兑换</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 魅力值兑换</p>
            </div>
            <div id="sub_nr">
                <table width="685" summary="" border="0">
                    <tr>
                        <td align="right">
                            您的魅力值：
                        </td>
                        <td align="left">
                            <%=Fascination%>
                        </td>
                    </tr>
                </table>
                <div id="zx">
                    <table width="100%" border="0" cellspacing="0" cellpadding="0" class="tab01">
                        <tr>
                            <th>
                                序号
                            </th>
                            <th>
                                可兑换类型
                            </th>
                            <th>
                                需要魅力值数
                            </th>
                            <th>
                                兑换数量
                            </th>
                            <th>
                                操作
                            </th>
                        </tr>
                        <asp:Repeater ID="rpList" runat="server">
                            <ItemTemplate>
                                <tr align="center">
                                    <td>
                                        <%=Rowid+= 1%>
                                    </td>
                                    <td>
                                        <%#Eval( "PropName" )%>
                                    </td>
                                    <td>
                                        <%#Eval( "CharmValue" )%>
                                    </td>
                                    <td>
                                        <%#Eval( "PropCount" )%>
                                    </td>
                                    <td>
                                        <a href='FasciExchange.aspx?pid=<%#Eval("id") %>' onclick=" return confirm('确定要兑换吗？');">
                                            兑换</a>
                                    </td>
                                </tr>
                            </ItemTemplate>
                        </asp:Repeater>
                    </table>
                    <div class="clear">
                    </div>
                    <div class="sabrosus">
                        <webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
                            FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
                            ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
                            TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5"
                            CurrentPageButtonClass="current" ShowPrevNext="False" PageSize="20">
                        </webdiyer:AspNetPager>
                    </div>
                    </form>
                </div>
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
