<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_BankMoneyOperaLog" %>

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

                <script type="text/javascript">
                    SetLogNav(3);
                </script>

                <div class="rank_title">
                    <%=ConfigurationManager.AppSettings["moneyName"].ToString()%>存取记录</div>
                <table width="100%" border="0" cellspacing="0" cellpadding="0">
                    <tr>
                        <td style="text-align: left; padding-left: 5px;">
                            <select id="stype">
                                <option value="0">==类型==</option>
                                <option value="1">存款</option>
                                <option value="2">取款</option>
                            </select>
                            按时间段搜索：从&nbsp;<input type="text" id="txtBeginDate" size="8" style="vertical-align: middle;"
                                onfocus="WdatePicker({maxDate:'#F{$dp.$D(\'txtEndDate\')}',dateFmt:'yyyy-MM-dd'})" />&nbsp;
                            到：<input type="text" id="txtEndDate" size="8" style="vertical-align: middle;" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'})" />&nbsp;
                            <input type="button" class="but_011" value=" 搜索 " onclick="OnSearch();" />
                            &nbsp;
                            <input type="button" class="but_022" value=" 刷 新 " onclick="RefreshMe();" />

                            <script>
                                var bd = $("#txtBeginDate");
                                var ed = $("#txtEndDate");
                                var type = $("#stype");
                                var ubd = decodeURIComponent(GetRequest("bd", ""));
                                var ued = decodeURIComponent(GetRequest("ed", ""));
                                var utype = decodeURIComponent(GetRequest("type", ""));
                                if (ubd != "")
                                    bd.val(ubd);
                                if (ued != "")
                                    ed.val(ued);
                                if (utype != "")
                                    DropSetByValue("stype", utype);

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
                                    if (type.find("option:selected").val().Trim() != "")
                                        url = SetUrlParam(url, "type=" + encodeURIComponent(type.find("option:selected").val().Trim()));

                                    LocationTo(url);
                                }
											
                            </script>

                        </td>
                    </tr>
                </table>
                <div id="zx">
                    <table width="100%" border="0" cellspacing="0" cellpadding="0">
                     <thead>
                        <tr>
                            <th>
                                序号
                            </th>
                            <th>
                                操作前银行<%=ConfigurationManager.AppSettings["moneyName"].ToString()%>
                            </th>
                            <th>
                                操作前<%=UiCommon.StringConfig.BankVersion=="2"?"游戏":"钱包" %><%=ConfigurationManager.AppSettings["moneyName"].ToString()%>
                            </th>
                            <th>
                                存款额
                            </th>
                            <th>
                                取款额
                            </th>
                            <th>
                                操作时间
                            </th>
                        </tr>
                        </thead>
                        <asp:Repeater ID="rpList" runat="server">
                            <ItemTemplate>
                                <tr align="center">
                                    <td>
                                        <%=Rowid+=1%>
                                    </td>
                                    <td>
                                        <%#UiCommon.StringConfig.AddZeros(Eval( "MoneyInBank" ))%>
                                    </td>
                                    <td>
                                        <%#UiCommon.StringConfig.AddZeros(Eval( "MoneyInRoom" ))%>
                                    </td>
                                    <td>
                                        <%#UiCommon.StringConfig.AddZeros(Eval( "OutMoney" ))%>
                                    </td>
                                    <td>
                                        <%#UiCommon.StringConfig.AddZeros(Eval( "InMoney" ))%>
                                    </td>
                                    <td>
                                        <%# Eval("TimeEx")%>
                                    </td>
                                </tr>
                            </ItemTemplate>
                        </asp:Repeater>
                    </table>
                </div>
                <div class="clear">
                </div>
                <div class="sabrosus">
                    <webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
                        FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
                        ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
                        TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5"
                        CurrentPageButtonClass="current" ShowPrevNext="False" PageSize="15">
                    </webdiyer:AspNetPager>
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
