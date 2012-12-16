<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_FineryID" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="WebShortCutKey" TagPrefix="BZW" Src="~/Public/WebShortCutKey.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<script type="text/javascript" src="/Public/Js/Public.js"></script>

<script type="text/javascript" src="/Public/Js/Global.js"></script>

<script src="/Public/Js/jquery.js" type="text/javascript"></script>

<head runat="server" id="Head1">
    <title> 
    </title>
  
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />
    <link href="/css/lightbox.css" type="text/css" rel="stylesheet" />
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/topbtn.js"></script>

    <script type="text/javascript" src="/Public/Js/submu.js"></script>

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" pageType="3" />
        <!--content-->
        <div id="left">
            <BZW:WebShortCutKey ID="webshortcutkey1" runat="server" isDisplay="0" />
            <WebService:Control ID="webService" runat="server" />
        </div>
        <!-- content start -->
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    精品ID</h3>
                <p class="dqwz">
                    当前位置：首页 > 精品ID</p>
            </div>
            <div id="sub_nr">
                <div id="idss">
                    <label>
                        <img src="/Images/id01.jpg" alt="" /></label>
                    <input type="text" size="50" class="in" name="seachid" id="seachid" />
                    <img src="/Images/cont_btn04.jpg" alt="" onclick="Seach()" />
                </div>
                <div id="tjlh">
                    <ul>
                        <asp:Repeater ID="FineryIDTop" runat="server">
                            <ItemTemplate>
                                <ul>
                                    <li><strong class="text05">ID:<a href='/Manage/FineryIDSale.aspx?id=<%#Eval("FineryID") %>'
                                        class="link02"><%#Eval("FineryID") %></a></strong><br />
                                        价格：
                                        <%#UiCommon.StringConfig.AddZeros(Eval("Price")) %>金币 </li>
                                </ul>
                            </ItemTemplate>
                        </asp:Repeater>
                        <asp:Label runat="server" Text="暂无推荐" ID="NoProTop" Visible="false"></asp:Label>
                    </ul>
                </div>
                <div id="gz">
                    <strong class="text05">规则</strong>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a
                        href="/Manage/FineryID.aspx?type=all" id="all" class="link03">全部</a> &nbsp;|&nbsp;
                    <a href="/Manage/FineryID.aspx?type=aabb" id="aabb" class="link03">AABB</a> &nbsp;|&nbsp;
                    <a href="/Manage/FineryID.aspx?type=aabbcc" id="aabbcc" class="link03">AABBCC</a>&nbsp;
                    | &nbsp;<a href="/Manage/FineryID.aspx?type=abab" id="abab" class="link03">ABAB</a>&nbsp;
                    |&nbsp; <a href="/Manage/FineryID.aspx?type=ababab" id="ababab" class="link03">ABABAB</a>&nbsp;
                    | &nbsp;<a href="/Manage/FineryID.aspx?type=abcabc" id="abcabc" class="link03">ABCABC</a>&nbsp;
                    | &nbsp;<a href="/Manage/FineryID.aspx?type=abgab" id="abgab" class="link03">ABGAB</a>&nbsp;
                    | &nbsp;<a href="/Manage/FineryID.aspx?type=3a" id="3a" class="link03">3A</a>&nbsp;
                    | &nbsp;<a href="/Manage/FineryID.aspx?type=4a" id="4a" class="link03">4A</a>&nbsp;
                    | &nbsp;<a href="/Manage/FineryID.aspx?type=5a" id="5a" class="link03">5A及以上</a>&nbsp;
                    | &nbsp;<a href="/Manage/FineryID.aspx?type=4sun" id="4sun" class="link03">4顺及以上</a>&nbsp;
                    | &nbsp;<a href="/Manage/FineryID.aspx?type=date" id="date" class="link03">生日</a>
                </div>
                <div id="jplh">
                    <p>
                        <strong class="text05">精品靓号</strong> <strong>您可以在页面上方的搜索框输入您想要找的号码，也可以看看我们推荐的精品靓号。</strong></p>
                    <ul>
                        <asp:Repeater ID="FineryIDList" runat="server">
                            <ItemTemplate>
                                <li><strong class="text05">ID&nbsp;&nbsp;&nbsp;&nbsp;：<a href='/Manage/FineryIDSale.aspx?id=<%#Eval("FineryID") %>'
                                    class="link02"><%#Eval("FineryID") %></a></strong><br />
                                    价格：<%# UiCommon.StringConfig.AddZeros(Eval("Price")) %><%=UiCommon.StringConfig.MoneyName %>
                                </li>
                            </ItemTemplate>
                        </asp:Repeater>
                        <asp:Label runat="server" Text="很抱歉！靓号已拍卖完毕" ID="NoProList" Visible="False" ForeColor="Red"
                            Font-Bold="True"></asp:Label>
                    </ul>
                </div>
            </div>
            <div class="sabrosus">
                <webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
                    FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
                    ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
                    TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5"
                    CurrentPageButtonClass="current" ShowPrevNext="False" PageSize="15">
                </webdiyer:AspNetPager>
            </div>
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
    </div>
    <!-- content end -->
    <div class="clear">
    </div>
   
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>

<script type="text/javascript">
    var seachid = GetRequest("seachid", "");
    $("#seachid").val(seachid);
    var type = GetRequest("type", "");
    if (type == "" || type == null) {
        type = "all";
    }
    //document.getElementById(type).className = "men_numRulvis";
    $("#" + type).addClass("men_numRulvis")
    function Seach() {
        var url = "/Manage/FineryID.aspx";
        var seachid = $("#seachid").val().Trim();
        url = SetUrlParam(url, "seachid=" + seachid);
        LocationTo(url);
    }
</script>

