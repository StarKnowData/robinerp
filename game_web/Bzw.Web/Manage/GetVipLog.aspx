<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_GetVipLog" %>

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

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/DatePicker/WdatePicker.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/jquery.js"></script>

    <script type="text/javascript" src="/Public/Js/public.js"></script>

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
                <div class="rank_title">
                    获赠VIP记录</div>
                <table width="100%" border="0" cellspacing="0" cellpadding="0" class="tab01">
                    <tr>
                        <td style="text-align: left; text-indent: 20px; padding: 0 0 3px 0;">
                            <span style="vertical-align: middle;">按时间段搜索：从&nbsp;<input type="text" id="txtBeginDate"
                                size="8" class="in" style="vertical-align: middle;" onfocus="WdatePicker({maxDate:'#F{$dp.$D(\'txtEndDate\')}',dateFmt:'yyyy-MM-dd'})" />&nbsp;
                                到：<input type="text" id="txtEndDate" class="in" size="8" style="vertical-align: middle;"
                                    onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'})" />&nbsp;
                                <input type="button" value=" 搜索 " onclick="OnSearch();" class="but_011" />
                                &nbsp;
                                <input type="button" class="but_022" value=" 刷 新 " onclick="RefreshMeDelParam('[?&]{1}bd=(\\d){4}-(\\d){2}-(\\d){2}&ed=(\\d){4}-(\\d){2}-(\\d){2}');" />
                            </span>

                            <script>
                                SetLogNav(8);
                                var bd = $("#txtBeginDate");
                                var ed = $("#txtEndDate");

                                var ubd = decodeURIComponent(GetRequest("bd", ""));
                                var ued = decodeURIComponent(GetRequest("ed", ""));

                                if (ubd != "")
                                    bd.val(ubd);
                                if (ued != "")
                                    ed.val(ued);


                                function OnSearch() {
                                    if (bd.val().Trim() == "" && ed.val().Trim() == "") {
                                        alert("请先输入起止时间再搜索。");
                                        return;
                                    }
                                    var url = location.href;
                                    if (bd.val().Trim() != "")
                                        url = SetUrlParam(url, "bd=" + encodeURIComponent(bd.val().Trim()));
                                    if (ed.val().Trim() != "")
                                        url = SetUrlParam(url, "ed=" + encodeURIComponent(ed.val().Trim()));
                                    LocationTo(url);
                                }
											
                            </script>

                        </td>
                    </tr>
                </table>
                <div id="zx">
                    <table width="100%" border="0" cellspacing="0" cellpadding="0" class="tab01">
                        <thead>
                            <tr>
                                <th>
                                    序号
                                </th>
                                <th>
                                    赠送玩家
                                </th>
                                <th>
                                    VIP类型
                                </th>
                                <th>
                                    花费<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>
                                </th>
                                <th>
                                    时间
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
                                        <%#Eval("UserName") %>
                                    </td>
                                    <td>
                                        <%#UiCommon.StringConfig.ConvertVipType(Eval("AddVipTime"))%>
                                    </td>
                                    <td>
                                        <%#Eval("Money")%>
                                    </td>
                                    <td>
                                        <%#Eval("AddTime")%>
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
