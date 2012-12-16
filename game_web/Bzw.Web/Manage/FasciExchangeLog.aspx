<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_FasciExchangeLog" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<%@ Register TagName="WebLogBannister" TagPrefix="BZW" Src="~/Public/WebLogBannister.ascx" %>
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
            <Left:Control ID="LeftOne" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    交易记录</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 交易记录</p>
            </div>
            <div id="sub_nr" style="margin-top: 10px;">
                <!--Log Bannister-->
                <BZW:WebLogBannister ID="weblogbannister1" runat="server" />

                <script type="text/javascript">
                    SetLogNav(9);
                </script>

                <div class="rank_title">
                    魅力值兑换记录</div>
                <div id="zx">
                    <table width="100%" border="0" cellspacing="0" cellpadding="0">
                        <thead>
                            <tr>
                                <th>
                                    序号
                                </th>
                                <th>
                                    兑换时间
                                </th>
                                <th>
                                    兑换类型
                                </th>
                                <th>
                                    魅力值数
                                </th>
                                <th>
                                    奖品数
                                </th>
                                <th>
                                    状态
                                </th>
                            </tr>
                        </thead>
                        <asp:Repeater ID="rpList" runat="server">
                            <ItemTemplate>
                                <tr>
                                    <td>
                                        <%=Rowid+=1%>
                                    </td>
                                    <td>
                                        <%#Eval("InputDate")%>
                                    </td>
                                    <td>
                                        <%#Eval("PropName")%>
                                    </td>
                                    <td>
                                        <%#Eval("CharmValue")%>
                                    </td>
                                    <td>
                                        <%#Eval("PropCount") %>
                                    </td>
                                    <td>
                                        <%# Convert.ToBoolean(Eval("Status"))==true?"已兑换":"未兑换"%>
                                    </td>
                                </tr>
                            </ItemTemplate>
                        </asp:Repeater>
                    </table>
                </div>
                <!--pageNumber-->
                <div class="sabrosus">
                    <webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
                        FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
                        ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
                        TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5"
                        CurrentPageButtonClass="current" ShowPrevNext="False" PageSize="20">
                    </webdiyer:AspNetPager>
                </div>
            </div>
            <div class="clear">
            </div>
        </div>
        <!--right End-->
        <p>
            <img src="/Images/cont_img01.jpg" alt="" /></p>
    </div>
    <!--content End-->
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
