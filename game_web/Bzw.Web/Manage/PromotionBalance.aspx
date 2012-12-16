<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_PromotionBalance" %>

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

    <script type="text/javascript" src="/Public/Js/password_check.js"></script>

    <script type="text/javascript" src="/Public/Js/District.js"></script>

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
                    游戏推广记录</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 游戏推广记录</p>
            </div>
            <div id="sub_nr" style="margin-top: 10px;">
                <div id="memText02">
                    <form action="" method="get" class="democss">
                    <div id="zx">
                        <table width="100%" border="0" cellspacing="0" cellpadding="0" class="tab01">
                            <thead>
                                <tr>
                                    <th>
                                        序号
                                    </th>
                                    <th>
                                        被推荐用户名
                                    </th>
                                    <th>
                                        有效推广完成度
                                    </th>
                                    <th>
                                        推荐时间
                                    </th>
                                    <th>
                                        结算
                                    </th>
                                    <th>
                                        结算时间
                                    </th>
                                </tr>
                            </thead>

                            <script type="text/javascript">
          <!--
                                function OnClearing(tgUserid, userid) {
                                    var tdState = document.getElementById('tdState' + userid);
                                    var tdName = document.getElementById('tdName' + userid);
                                    //alert(tdState.innerHTML);
                                    var urlData = '/Public/XmlHttpUser.aspx?type=tgbalance&tguserid=' + tgUserid + '&userid=' + escape(userid);
                                    //alert(urlData);
                                    var strReturn = AjaxCall(urlData);
                                    //alert(strReturn);
                                    if (strReturn == "-1") {
                                        alert('对不起，被推广玩家[' + tdName.innerText + ']的有效推广完成度未达到100%，还不能进行结算！');
                                        return false;
                                    }
                                    else if (strReturn == "2") {
                                        alert('对不起，被推广玩家[' + tdName.innerText + ']的有效推广期已过！');
                                        tdState.innerHTML = '<font color="red">已过期</font>';
                                    }
                                    else if (strReturn == "0") {
                                        alert('结算成功！');
                                        tdState.innerHTML = '<font color="red">已结算</font>';
                                    } else {
                                        alert('抱歉，结算失败，可能是服务器繁忙，请稍候再试！');
                                    }
                                }

                                function GetLink(tgUserid, userid, flg) {
                                    if (flg == '1') {
                                        document.write('<font color="red">已结算</font>');
                                    }
                                    else if (flg == '2') {
                                        document.write('<font color="red">已过期</font>');
                                    }
                                    else {
                                        document.write('<a href="javascript:void(0);" style="text-decoration:underline;" onclick="javascript:OnClearing(' + tgUserid + ',' + userid + ');" title="点击进行结算">未结算</a>');
                                    }
                                }
          //-->
                            </script>

                            <asp:Repeater ID="rpLog" runat="server">
                                <ItemTemplate>
                                    <tr>
                                        <td>
                                            <%=RowNo=RowNo+1 %>
                                        </td>
                                        <td id="tdName<%#Eval("UserID")%>">
                                            <%#Eval("UserName") %>
                                        </td>
                                        <td>
                                            <%#GetUserPercent(Eval("UserID").ToString())%>
                                        </td>
                                        <td>
                                            <%#Eval("RegTime") %>
                                        </td>
                                        <td id="tdState<%#Eval("UserID")%>">

                                            <script type="text/javascript">                                                GetLink('<%#Eval("TG_UserID")%>', '<%#Eval("UserID")%>', '<%#Eval("IsRegAward")%>');</script>

                                        </td>
                                        <td>
                                            <%#Eval("CalTime")%>
                                            &nbsp;
                                        </td>
                                    </tr>
                                    <tr>
                                </ItemTemplate>
                            </asp:Repeater>
                        </table>
                        </div>
                    </form>
                </div>
                <!--pageNumber-->
                <div class="sabrosus">
                    <webdiyer:AspNetPager PageSize="20" ID="anpPageIndex" runat="server" AlwaysShow="True"
                        CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
                        FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left"
                        ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
                        TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5">
                    </webdiyer:AspNetPager>
                </div>
                <div class="clear">
                </div>
           
           
            <div class="clear">
            </div>
        </div>
         <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        <!--right End-->
    </div>
    <!--content End-->
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>
