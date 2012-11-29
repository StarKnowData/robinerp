<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="ApplyRoomList.aspx.cs"
    Inherits="Admin_Games_ApplyRoomList" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
        <!
        -- body
        {
            background-color: #FFFFFF;
            margin-top: 0px;
        }
        -- ></style>

    <script src="/Public/Js/public.js" type="text/javascript"></script>

    <script src="/Public/Js/jquery.js" type="text/javascript"></script>

    <script src="/Public/Js/admin.js" type="text/javascript"></script>

</head>

<body>
    <form id="form1" runat="server">
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
        bgcolor="F2F8FF" class="admin_table2">
        <tr>
            <td class="title_03">
                <strong>租赁房间申请列表</strong>
            </td>
        </tr>
    </table>
    <table width="100%" border="0" cellspacing="0" cellpadding="0" style="background-color: White">
        <tr>
            <td style="height: 5px; background-color: White">
            </td>
        </tr>
    </table>
    <table width="100%" border="0" align="center" cellpadding="0" cellspacing="1" bordercolor="#A4B6D7"
      class="admin_table">
        <tr  >
            <td class="title_03" colspan="13" style="height: 35px">
                &nbsp;&nbsp;玩家帐号：<input type="text" id="txtKey" name="txtKey" maxlength="50" style="width: 99px"
                    class="put" />&nbsp;&nbsp;状态：<select id="selStatus" name="selStatus"><option value="3">
                        请选择</option>
                        <option value="0">未审核</option>
                        <option value="1">已审核</option>
                        <option value="2">不通过</option>
                    </select>
                &nbsp;<input type="button" value="搜 索" onclick="OnSearch();" class="put" />

                <script type="text/javascript">
                    var o = $("#txtKey");
                    var s = $("#selStatus");
                    o.val(decodeURIComponent(GetRequest("key", "")));
                    s.val(decodeURIComponent(GetRequest("status", "")));
                    function OnSearch() {
                        if (o.val().Trim() != "" && s.val().Trim() != "3") {
                            var url = SetUrlParam(location.href, "key=" + ((o.val().Trim() != pkey && o.val().Trim() != "") ? encodeURIComponent(o.val().Trim()) : ""));
                            LocationTo(SetUrlParam(url, "status=" + encodeURIComponent(s.val().Trim())));
                            return;

                        }
                    }
                </script>

            </td>
        </tr>
        <tr>
            <td>
                <table cellpadding="3" style="width: 100%; text-align: center; border-collapse: collapse;
                    margin: 0px; padding: 0px;" border="1px;">
                    <tr>
                        <th>
                            ID
                        </th>
                        <th>
                            玩家ID
                        </th>
                        <th>
                            用户名
                        </th>
                        <th>
                            游戏名
                        </th>
                        <th>
                            房间名
                        </th>
                        <th>
                            手机号
                        </th>
                         
                        <th>
                            租凭房间日期
                        </th>
                        <th>
                            租赁天数
                        </th>
                        <th>
                            租金
                        </th>
                        <th>
                            状态
                        </th>
                        <th>申请时间</th>
                        <th>操作</th>
                    </tr>
                    <asp:Repeater ID="rptRoomList" runat="server">
                        <ItemTemplate>
                            <tr>
                                <td>
                                    <%#Eval("ID") %>
                                </td>
                                <td>
                                    <%#Eval("UserID") %>
                                </td>
                                <td>
                                    <%#Eval("UserName") %>
                                </td>
                                <td>
                                    <%#Eval("ComName") %>
                                </td>
                                <td>
                                    <%#Eval("RoomName") %>
                                </td>
                                <td>
                                    <%#Eval("Mobile") %>
                                </td>
                               
                                <td>
                                    <%#Convert.ToDateTime( Eval("OpenRoomDate")).ToString("yyyy-MM-dd") %>
                                </td>
                                <td>
                                    <%#Eval("AppleyDays") %>
                                </td>
                                <td>
                                    <%#Convert.ToInt64( Eval("EveryDayRent"))*Convert.ToInt64(Eval("AppleyDays")) %><%=UiCommon.StringConfig.MoneyName %>
                                </td>
                               	<td>
							   <%# Eval("AuditStatus").ToString() == "0" ? "未审核" : Eval("AuditStatus").ToString() == "1" ? "已审核" : "不通过"%> 
									</td>									
									 <td><%#Eval("AddDate") %></td>
									 <td><a href='ApplyRoomEdit.aspx?id=<%#Eval("ID") %>' >查看详情</a>&nbsp;  </td>
                            </tr>
                        </ItemTemplate>
                    </asp:Repeater>
                    <asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='15'>没有记录...</td></tr>"></asp:Literal></table>
                <table width="100%">
                    <tr>
                        <td style="font-size: 12px; color: #0099ff; background-color: #e6feda;">
                            <webdiyer:AspNetPager PageSize="20" runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条"
                                FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5"
                                PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left"
                                ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox=""
                                AlwaysShow="True" PagingButtonSpacing="10px" UrlPaging="True">
                            </webdiyer:AspNetPager>
                        </td>
                    </tr>
                </table>
            </td>
        </tr>
    </table>
    </form>
</body>
</html>
