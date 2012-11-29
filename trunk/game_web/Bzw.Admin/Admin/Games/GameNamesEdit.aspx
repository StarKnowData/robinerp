<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Games_GameNamesEdit" Codebehind="GameNamesEdit.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>无标题页</title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="../../Public/Js/Global.js"></script>
    <style type="text/css">
<!--
body {
	background-color: #FFFFFF;
	margin-top: 0px;
}
-->
</style>
    <script language="javascript" type="text/javascript">

    function CheckForm() {

        if(!alertNull(document.getElementById("NameID"),'温馨提示：\n\n请输入游戏ID号！')) {
        return false;
      }
      else if(!alertNonNegativeNumber(document.getElementById("NameID"),'温馨提示：\n\n游戏ID号请输入一个正的数字！')) {
        return false;
      }
      
      if(document.getElementById("ComName").value == '') {
        alert('温馨提示：\n\n请输入游戏名称！');
        document.getElementById("ComName").focus();
        return false;
      }
      
        if(document.getElementById("ComProcess").value == '') {
        alert('温馨提示：\n\n请输入客户端EXE文件名！');
        document.getElementById("ComProcess").focus();
        return false;
      }
      
      if(!alertNull(document.getElementById("IDSort"),'温馨提示：\n\n请输入排列号！')) {
        return false;
      }
      else if(!alertNonNegativeNumber(document.getElementById("IDSort"),'温馨提示：\n\n排列号请输入一个正的数字！')) {
        return false;
      }
      
        if(document.getElementById("DLLFileName").value == '') {
        alert('温馨提示：\n\n请输入游戏服务端文件名！');
        document.getElementById("DLLFileName").focus();
        return false;
      }
      
        if(!alertNull(document.getElementById("DeskPeople"),'温馨提示：\n\n请输入桌子上的人数！')) {
        return false;
      }
      else if(!alertNonNegativeNumber(document.getElementById("DeskPeople"),'温馨提示：\n\n桌子上的人数请输入一个正的数字！')) {
        return false;
      }
    }
    </script>
</head>
<body>
    <form id="form1" runat="server" >
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td class="title_03" colspan="2">
                    <strong>修改游戏信息</strong></td>
            </tr>
            <tr>
                <td align="right">
                    游戏类别：</td>
                <td align="left">
                    <asp:DropDownList ID="KindID" runat="server"  
                        onselectedindexchanged="KindID_SelectedIndexChanged" AutoPostBack="true">
                    </asp:DropDownList>
                    <a href="GameTypesAdd.aspx">添加游戏类别</a>
                </td>
            </tr>
             <tr>
            <td align="right">二级游戏目录：</td>
            <td align="left">
            <asp:DropDownList ID="ChildKindID" runat="server">
            
            </asp:DropDownList>
            </td>
            </tr>
            <tr>
                <td align="right">
                    游戏ID号：</td>
                <td align="left">
                    <input type="text" id="NameID" name="NameID" value='<%=NameID %>' readonly class="put" maxlength="20" /><font color="red">（需与游戏提供商咨询）</font>
                </td>
            </tr>
            <tr>
                <td align="right">
                    游戏名称：</td>
                <td align="left">
                    <input type="text" id="ComName" name="ComName" value="<%=ComName %>" class="put" maxlength="14"/></td>
            </tr>
              <tr>
                <td align="right">
                    房间租赁价格设置：</td>
                <td align="left">
                    <input type="text" id="EveryDayRent" name="EveryDayRent" class="put" maxlength="14"  value="<%=EveryDayRent %>" />金币/每日（填写整数，0表示不开通租凭房间）</td>
            </tr>
            <tr><td style="padding-left:250px;" colspan="2"><b>客户端资料</b></td></tr>
            
            <tr>
                <td align="right">
                    客户端EXE文件名：</td>
                <td align="left">
                    <input type="text" id="ComProcess" name="ComProcess" value="<%=ComProcess %>" class="put" maxlength="20"/>（如：10000305.exe，需与游戏提供商咨询）</td>
            </tr>
            <tr>
                <td align="right">
                    排列号：</td>
                <td align="left">
                    <input type="text" id="IDSort" name="IDSort" value="<%=IDSort %>" class="put" maxlength="4" /></td>
            </tr>
            <tr>
                <td align="right">
                    是否激活：</td>
                <td align="left">
                    <input name="Enable" type="radio" value="1" <%=(Enable.ToString().ToLower() =="1" ? "checked" : "" ) %> Class="put"/>激活
                    <input name="Enable" type="radio" value="0" <%=(Enable.ToString().ToLower() =="0" ? "checked" : "") %> Class="put"/>未激活
                </td>
            </tr>
            
            <tr><td style="padding-left:250px;" colspan="2"><b>服务端资料</b></td></tr>
            
            <tr>
                <td align="right">
                    服务端文件名：</td>
                <td align="left">
                    <input type="text" id="DLLFileName" name="DLLFileName" value="<%=DLLFileName %>" class="put" maxlength="20"/>（比如：XQSrv.DLL）</td>
            </tr>
            <tr>
                <td align="right">
                    桌子上的人数：</td>
                <td align="left">
                    <input type="text" id="DeskPeople" name="DeskPeople" value="<%=DeskPeople %>" value="4" class="put" maxlength="4" />
                </td>
            </tr>
            
            
            <tr>
            <td align="right">
                <input type="hidden" name="action" value="edit" />
                <input type="hidden" name="action2" value="edit" />
                <input type="hidden" name="id" value="20004" />
            </td>
            <td align="left">
                <asp:Button ID="Button1" runat="server" Text="修改"  OnClick="GameNamesEdit" Class="put"/>
                <input name="reback" type="button" value="返回" onclick="javascript:history.back();" Class="put"/>
            </td>
            </tr>
        </table>
        <p></p>
         
        <table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td align="left">
                    <strong>游戏大类</strong>
                    <asp:DataList ID="GameBigList" runat="server" RepeatColumns="8">
                        <ItemTemplate>
                            &nbsp;&nbsp;&nbsp; <a href='GameRooms.aspx?bid=<%# Eval("Kindid") %>'>
                                <%# Eval("KindName") %>
                            </a>&nbsp;&nbsp;&nbsp;|
                        </ItemTemplate>
                    </asp:DataList>
                    <asp:Label ID="NoGameBigList" runat="server" Text="暂无任何记录！" Visible="false"></asp:Label>
                </td>
            </tr>
            <tr>
                <td align="left">
                    <strong>游戏小类 </strong>
                    <asp:DataList ID="GameSmallList" runat="server" RepeatColumns="8">
                        <ItemTemplate>
                            &nbsp;&nbsp;&nbsp; <a href='GameRooms.aspx?bid=<%=RoomBigID %>&sid=<%# Eval("Nameid") %>'>
                                <%# Eval("ComName") %>
                            </a>&nbsp;&nbsp;&nbsp;
                        </ItemTemplate>
                    </asp:DataList>
                    <asp:Label ID="NoGameSmallList" runat="server" Text="暂无任何记录！" Visible="false"></asp:Label>
                </td>
            </tr>
        </table>
        <table>
            <tr>
                <td height="5">
                </td>
            </tr>
        </table>
        <asp:Repeater ID="RoomListInfos" runat="server">
            <HeaderTemplate>
                <table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
                    bgcolor="F2F8FF" class="admin_table">
                    <tr>
                        <td class="title_03" colspan="11">
                            <strong>房间信息显示</strong></td>
                    </tr>
                    <tr>
                        <td>
                            序号</td>
                        <td>
                            房间ID</td>
                        <td>
                            游戏性质</td>
                        <td>
                            游戏名称</td>
                        <td>
                            排列ID</td>
                        <td>
                            名称ID</td>
                        <td>
                            在线人数</td>
                        <td>
                            是否激活</td>
                        <td>
                            版本号</td>
                        <td>
                            房间规则</td>
                        <td>
                            操作</td>
                    </tr>
            </HeaderTemplate>
            <ItemTemplate>
                <tr>
                    <td>
                        <%=tableids = tableids+1%>
                    </td>
                    <td>
                        <%# Eval("id") %>
                    </td>
                    <td>
                        <%# GetGameRooms(Convert.ToInt32(Eval("GameTypeID")))%>
                    </td>
                    <td>
                        <%# Eval("RoomName")%>
                    </td>
                    <td>
                        <%# Eval("idsort") %>
                    </td>
                    <td>
                        <%# Eval("RoomID") %>
                    </td>
                    <td>
                        <%# Eval("OnLineCount") %>
                    </td>
                    <td>
                        <%# Eval("EnableRoom").ToString().ToLower() == "true" ? "未激活" : "已激活"%>
                    </td>
                    <td>
                        <%# Eval("version")%>
                    </td>
                    <td>
                       <a href="#" onclick="openRoomRuleDiv('RoomRule.aspx?RoomRule=<%# Eval("RoomRule")%>',350,320)" title="点击查看规则明细"><%# Eval("RoomRule")%></a>
                    </td>
                    <td>
                        <a href='GameRoomsEdit.aspx?sid=<%# Eval("id") %>'>修改</a>&nbsp;&nbsp;<a href='GameRoomsDel.aspx?sid=<%# Eval("id") %>'
                            onclick="javascript:return confirm('您确定要删除该房间吗？');">删除</a></td>
                </tr>
            </ItemTemplate>
        </asp:Repeater>
        <asp:Label ID="NoRoomListInfos" runat="server" Text="暂无任何记录！" Visible="false"></asp:Label>
        
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr>
                <td style="height: 5px" style="background-color: White">
                </td>
            </tr>
        </table>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td align="left">
                    <div id="page_link" class="page_link">
						<webdiyer:AspNetPager PageSize="20" ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页；每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True">
						</webdiyer:AspNetPager>
					</div>
                </td>
            </tr>
        </table>
    </form>
    
</body>
</html>
