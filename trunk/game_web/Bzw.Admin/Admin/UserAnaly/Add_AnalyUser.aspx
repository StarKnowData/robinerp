<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_UserAnaly_Add_AnalyUser" Codebehind="Add_AnalyUser.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>添加管理员 </title>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <link href="../css/Inc_style.css" rel="stylesheet" type="text/css">
    <style type="text/css">
    <!--
    body {
	    background-color: #E7EEF5;
	    margin-left: 0px;
	    margin-top: 0px;
	    margin-right: 0px;
	    margin-bottom: 0px;
    }
    -->
    </style>

    <script type="text/ecmascript" language="javascript">
    <!--

    function CheckForm() {
          
        var AdminName = document.getElementById('<%=AdminName.ClientID %>');
        if(!/^[0-9a-zA-Z]{5,20}$/.test(AdminName.value)){   //  /^[0-9a-zA-Z\-_]{5,20}$/ 用户名由5-20位的字母、数字、中横杠(-)、下横杠(_)组成
            alert('用户名由5-20位的英文字母或数字组成');
            AdminName.focus();
            return false;
        }
        
        var AdminPwd = document.getElementById('<%=AdminPwd.ClientID %>');
        if(!/^[0-9a-zA-Z]{6,20}$/.test(AdminPwd.value)){
            alert('密码由6-20位的英文字母或数字组成');
            AdminPwd.focus();
            return false;
        }
        
        return true;
    }

    //-->
    </script>

</head>
<body>
    <div align="center">
        <form method="POST" name='Login' id="Login" action="" runat="server" onsubmit='return CheckForm();'>
            <center>
                <table width="68%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolorlight="#335078"
                    bordercolordark="#FFFFFF" bgcolor="#C5D5E4" style="font-size: 12px; letter-spacing: 1px;">
                    <tr bgcolor="#B6EBC4">
                        <td bgcolor="#C5D5E4" height="25" style="width: 615px">
                            <p align="center"/>
                                <b>增加管理员</b>
                        </td>
                    </tr>
                    <tr>
                        <td height="21" align="middle" bgcolor="#DFE8F0" style="border-bottom: medium none;
                            width: 615px;">
                            <div align="center">
                                <br/>
                                用户名：
                                <asp:TextBox ID="AdminName" runat="server" class="put" MaxLength="20"></asp:TextBox>由5-20位的英文字母或数字组成
                            </div>
                        </td>
                    </tr>
                    <tr>
                        <td height="25" align="middle" bgcolor="#DFE8F0" style="border-top: medium none;
                            border-bottom: medium none; width: 615px;">
                            <div align="center">
                                密&nbsp;&nbsp;&nbsp;码：
                                <asp:TextBox ID="AdminPwd"  runat="server" class="put" MaxLength="20"></asp:TextBox>由6-20位的英文字母或数字组成
                            </div>
                        </td>
                    </tr>
                    <tr>
                        <td height="25" bgcolor="#DFE8F0" style="border-top: medium none; width: 615px;">
                            <p align="center"/>
                                <asp:Button ID="Button1" runat="server" Text="确定添加" name="B1" class="put" OnClick="Add_AdminUsers" />
                        </td>
                    </tr>
                </table>
            </center>
        </form>
    </div>
    <div align="center">
    </div>
    <div align="center">
        <center>
            <table width="68%" border="1" align="center" cellpadding="1" cellspacing="0" bordercolorlight="#335078"
                bordercolordark="#FFFFFF" bgcolor="#C5D5E4" style="font-size: 12px; letter-spacing: 1px;">
                <tr align="center" bgcolor="#B6EBC4">
                    <td width="10%" bgcolor="#C5D5E4" style="height: 24px">
                        <font color="#990000">序号</font></td>
                    <td width="23%" bgcolor="#C5D5E4" style="height: 24px">
                        <font color="#990000">帐号</font></td>
                    <td width="15%" bgcolor="#C5D5E4" style="height: 24px">
                        <font color="#990000">创建时间</font></td>
                    <td width="20%" bgcolor="#C5D5E4" style="height: 24px">
                        <font color="#990000">操作</font></td>
                </tr>
                <asp:Repeater ID="List_AdminUsers" runat="server">
                    <ItemTemplate>
                        <tr valign="middle">
                            <td height="24" bgcolor="#E0E9F1">
                                <%=AdminId=AdminId+1%>
                            </td>
                            <td height="24" bgcolor="#E0E9F1">
                                <%# Eval("UserName") %>
                            </td>
                            <td height="24" bgcolor="#E0E9F1">
                                <%# Eval("AddTime") %>
                            </td>
                            <td height="24" bgcolor="#E0E9F1">
                                <a href="Edit_Users.aspx?id=<%# Eval("UserID")%>&url=<%=Utility.Common.CurrentPageUrl %>">修改密码</a>
                                |<a href="Add_AnalyUser.aspx?action=del&params=<%#Eval("UserID") %>" onclick="javascript:return confirm('确定要删除吗？');">删除</a>
                            </td>
                        </tr>
                    </ItemTemplate>
                </asp:Repeater>
                <tr>
                <td colspan="4"><a href="/Analy" target="_blank">跳转到运营系统 </a></td>
                </tr>
            </table>
        </center>
    </div>
</body>
</html>
