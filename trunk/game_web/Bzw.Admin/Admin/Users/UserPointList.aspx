<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="UserPointList.aspx.cs"
    Inherits="Admin_Users_UserPointList" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />

    <script src="/Public/Js/jquery.js" type="text/javascript"></script>

    <script src="/Public/Js/public.js" type="text/javascript"></script>

    <style type="text/css">
        <!
        -- body
        {
            background-color: #FFFFFF;
            margin-top: 0px;
        }
        -- ></style>
</head>
<body>
    <form id="form1" runat="server">
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
        bgcolor="F2F8FF" class="admin_table2">
        <tr>
            <td class="title_03">
                <strong>会员积分管理</strong>
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
        bgcolor="#A4B6D7" class="admin_table">
        <tr bgcolor="#ffffff">
            <td class="title_03" colspan="13" style="height: 35px">
            关键字：
                <input type="text" id="txtKey" name="txtKey" style="width: 150px;" class="put" />&nbsp;
                <select id="stType">
                    <option value="byid">根据用户ID</option>
                    <option value="byname">根据用户名</option>
                </select>
                &nbsp;&nbsp;&nbsp;类型
              
                <select name="userType" id="userType" style="width: 90px;"  >
                    <option value="all">所有</option>
                    <option value="realplayer">真实玩家</option>
                    <option value="robotplayer">机器人</option>
                </select>
                 &nbsp;&nbsp;&nbsp;
                 <select id="nameId">
                 <%=GameList %>
                 </select>
                &nbsp;&nbsp;&nbsp;积分排列方式：
                <select name="sortType" id="sortType" style="width: 70px;" >
                    <option value=" desc">降序</option>
                    <option value=" asc">升序</option>
                </select>
                	<input type="button" value=" 搜 索 " class="put" onclick="Search();" />&nbsp;
					<input type="button" class="put" value=" 刷 新 " onclick="RefreshMe();" />&nbsp;
            </td>
        </tr>

        <script type="text/javascript">
            var startStType = GetRequest("sttype", "");
            var startSortType = GetRequest("sorttype", "");
            var startUserType = GetRequest("usertype", "");
          
            var startGameNameId = GetRequest("nameid", "");
            var startKey = GetRequest("key", "");
            var key = $("#txtKey");
            key.val(startKey);
            if (startStType != "") {
                DropSetByValue("stType", startStType);
            }
            if (startSortType != "") {
                DropSetByValue("sortType", startSortType);
            }
        
            if (startUserType != "") {
                 
                DropSetByValue("userType", startUserType);
            }
            else {
                DropSetByValue("userType", "realplayer");
            }
            if (startGameNameId != "") {
                DropSetByValue("nameId", startGameNameId);
            }
            function Search() {
                var st = $("#sortType option:selected");
                var sr = $("#stType option:selected");
                var su = $("#userType option:selected");
                var game = $("#nameId option:selected");
                var key1 = $("#txtKey");
                
                var url = location.href;
                url = SetUrlParam(url, "sorttype=" + st.val().Trim());
                url = SetUrlParam(url, "sttype=" + sr.val().Trim());
                url = SetUrlParam(url, "usertype=" + su.val().Trim());
                url = SetUrlParam(url, "nameid=" + game.val().Trim());
                url = SetUrlParam(url, "key=" + key1.val().Trim());
                location.href = url;
            }
        </script>

        <tr align="center" bgcolor="#ffffff">
            
            <td>
                序号
            </td>
            <td>
                用户ID号
            </td>
            <td>
                用户名
            </td>
            <td>
                游戏名称
            </td>
            <td>
                积分数
            </td>
            <td>
                操作
            </td>
        </tr>
        <asp:Repeater ID="UserList" runat="server">
            <ItemTemplate>
                <tr align='center' bgcolor='#F7F8F8' onmouseout="this.style.backgroundColor='#F7F8F8'"
                    onmouseover="this.style.backgroundColor='#E1E1E1'"  height='25px' >
                     
                    <td>
                        <%# anpPageIndex.PageSize * anpPageIndex.CurrentPageIndex - anpPageIndex.PageSize + ( Container.ItemIndex + 1 )%>
                    </td>
                    <td>
                        <%# Eval("UserID")%>
                    </td>
                    <td>
                        <%# Eval("UserName")%>
                    </td>
                    <td>
                        <%# Eval("ComName")%>
                    </td>
                    <td>
                        <%# Eval("Point")%>
                    </td>
                    <td>
                        <a href='EditUserPoint.aspx?uid=<%# Eval("Userid") %>&nameid=<%#Eval("NameID") %>'>修改积分</a>&nbsp;| &nbsp; 
                        <a href='UserPointList.aspx?uid=<%# Eval("Userid") %>&act=del&nameid=<%#Eval("NameID") %>&url=<%=Server.UrlEncode( Request.Url.ToString())  %>'
                            onclick="javascript:return confirm('严重警告！您确定要删除当前记录吗？删除后该用户下记录将不能恢复!!');"><font color="red">
                                删除</font></a>&nbsp; 
                       
                    </td>
                </tr>
            </ItemTemplate>
        </asp:Repeater>
    </table>
    <asp:Label ID="NoUserList" runat="server" Text="暂无任何记录！" Visible="false"></asp:Label>
    <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
            <td style="height: 5px; background-color: White">
            </td>
        </tr>
    </table>
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
         
            <td align="left">
                <webdiyer:AspNetPager PageSize="20" ID="anpPageIndex" runat="server" AlwaysShow="True"
                    CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页；每页%PageSize%条，共%RecordCount%条"
                    FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left"
                    ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到"
                    UrlPaging="True">
                </webdiyer:AspNetPager>
            </td>
        </tr>
    </table>
    </form>

 
</body>
</html>
