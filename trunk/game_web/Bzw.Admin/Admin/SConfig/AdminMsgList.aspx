<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AdminMsgList.aspx.cs" Inherits="Admin_SConfig_AdminMsgList" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
       <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>无标题页</title>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
 
    body {
	    background-color: #FFFFFF;
	    margin-top: 0px;
    }
  
    </style>
</head>
<body>
    <form id="form1" runat="server">
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
            bgcolor="F2F8FF" class="admin_table2">
            <tr>
                <td class="title_03">
                    <strong>管理员信息群发管理</strong>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a
                        href="SendMsg.aspx">添加信息 </a> &nbsp;&nbsp; <a href="SendMsg2.aspx">添加弹窗内容</a> </td>
            </tr>
            
        </table>
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr>
                <td height="5">
                </td>
            </tr>
        </table>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <th style="width:8%;">
                    序号</th>
                <th>
                    信息</th>  
                    <th>用户ID</th>
                    <th>发送时间</th>
                    <th>是否发送</th>
                    <th>是否是群发</th>
                    <th>是否是游戏跑马灯</th>
                    <th>大厅跑马灯</th>
                    <th>是否是弹窗</th>
                <th style="width:15%;">
                    操作</th>
            </tr>
            <asp:Repeater ID="Messagelist" runat="server">
                <ItemTemplate>
                    <tr>
                        <td align='center'>
                            <%=TableID=TableID+1 %>
                        </td>
                        <td  align='center'><%#Eval("MsgContent") %></td>
                        <td  align='center'><%#Eval("UserID") %></td>
                        <td  align='center'><%#Eval("SendTime") %></td>
                        <td  align='center'><%#Eval("IsSend").ToString() == "1" ? "是" : "否"%></td>
                         <td  align='center'><%#Eval("IsToAll").ToString() == "1" ? "是" : "否"%></td>
                         <td align="center"><%#Eval("IsMarquee").ToString() == "1" ? "是" : "否"%></td>
                         <td align="center"><%#Eval("IsHallMarquee").ToString()=="1"?"是":"否" %></td>
                         <td align="center"><%#Eval("Type").ToString()=="2"?"是":"否" %></td>
                        <td align='center'>
                        <%#Eval("Type").ToString()=="2"?"<a href='SendMsg2.aspx?mid="+Eval("MsgID")+"'>修改</a>":"<a href='SendMsg.aspx?mid="+Eval("MsgID")+"'>修改</a>" %>
                       
                        <a  href='AdminMsgList.aspx?act=Del&id=<%# Eval("MsgID") %>' onclick="javacript:return confirm('是否确定要删除吗?删除后不能恢复!');">
                                删除</a></td>
                    </tr>
                </ItemTemplate>
            </asp:Repeater>
        </table>
            <asp:Literal runat="server" ID="NoDataList" Text="<tr><td colspan='9' align='center' bgcolor='#ffffff'>暂无数据...</td></tr>"></asp:Literal>
  
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
                        <webdiyer:AspNetPager PageSize="20" UrlPaging="True" runat="server" ID="WebPager1"
                            CustomInfoHTML="%CurrentPageIndex%/%PageCount%，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页"
                            LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList"
                            PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go"
                            TextAfterPageIndexBox="" TextBeforePageIndexBox="" AlwaysShow="True">
                        </webdiyer:AspNetPager>
                    </div>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>
