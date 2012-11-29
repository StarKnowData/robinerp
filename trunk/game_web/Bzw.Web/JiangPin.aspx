<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.JiangPin" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ OutputCache Duration="60" VaryByParam="page" %>
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
                    当前位置：首页 > 兑奖中心</p>
            </div>
            <div id="sub_nr">
                <div id="dhzx">
                    <ul class="dhzx_list">
                        <asp:Repeater ID="rpJiangPin" runat="server">
                            <ItemTemplate>
                                <li>
                                    <p class="dhzx_img">
                                        <a href='/DuiJiang.aspx?id=<%#Eval("Award_ID") %>' title='<%#Eval("Award_Name") %>'>
                                                <img src='<%#Eval("Award_Pic") %>' alt="" width="136" height="107"  onerror="this.src='/Images/NoPicture/no_pic.gif';this.onerror='';" /></a></p>
                                    <div class="dhzx_tm">
                                        <ul>
                                            <li><strong class="text05">
                                                <%#Eval("Award_Name") %></strong></li>
                                            <li>
                                                <%=UiCommon.StringConfig.GoldName%>：<%#UiCommon.StringConfig.AddZeros(Eval("Award_MoneyCost"))%></li>
                                            <li><a href='/DuiJiang.aspx?id=<%#Eval("Award_ID") %>' title='<%#Eval("Award_Name") %>'><img src="/Images/cont_btn09.jpg" alt=""></a></li>
                                            <ul>
                                    </div>
                                </li>
                            </ItemTemplate>
                        </asp:Repeater>
                    </ul>
                    <div class="sabrosus">
					<webdiyer:AspNetPager PageSize="12" ID="anpPageIndex" runat="server" AlwaysShow="True"
								CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
								FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left"
								ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
								TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5">
							</webdiyer:AspNetPager>
						
					</div>
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
