<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="EditUserPoint.aspx.cs"
    Inherits="Admin_Users_EditUserPoint" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />

    <script src="/Public/Js/public.js" type="text/javascript"></script>

    <script src="/Public/Js/jquery.js" type="text/javascript"></script>

    <script src="/Public/Js/admin.js" type="text/javascript"></script>

    <style type="text/css">
        body
        {
            background-color: #FFFFFF;
            margin-top: 0px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server"><asp:HiddenField ID="hidNameID" runat="server" /> 
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
        bgcolor="F2F8FF" class="admin_table2">
        <tr>
            <td class="title_03">
                <strong>会员游戏积分管理</strong>
            </td>
        </tr>
    </table>
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
        bgcolor="F2F8FF" class="admin_table">
        <tr>
            <td colspan="2" class="title_03">
            用户ID：
            </td>
            <td>
                <asp:Label ID="lblUserID" runat="server"></asp:Label>
            </td>
        </tr>
        <tr>
            <td colspan="2" class="title_03">
            用户名：
            </td>
            <td>
                <asp:Label ID="lblUserName" runat="server"></asp:Label>
            </td>
        </tr>
        <tr>
            <td colspan="2" class="title_03">
            游戏名：
            </td>
            <td>
                <asp:Label ID="lblComName" runat="server"></asp:Label>
            </td>
        </tr>
        <tr>
            <td colspan="2" class="title_03">
            游戏积分：
            </td>
            <td>
             <asp:Label ID="lblPoint" runat="server"></asp:Label>
            </td>
            
        </tr>
         <tr>
            <td colspan="2" class="title_03">
         修改积分为：
            </td>
            <td>
             <asp:TextBox ID="txtNewPoint" runat="server" Text="0"></asp:TextBox>
            </td>
            
        </tr>
        <tr> 
        <td colspan="2" style=" text-align:right;">&nbsp;<asp:Button ID="Button1" runat="server" 
                Text="确认修改" Class="put" onclick="Button1_Click"  /></td><td><input type="button" value="返回积分列表" class="put"  onclick="location.href='UserPointList.aspx';"/></td>
        </tr>
    </table>
    </form>
</body>
</html>
