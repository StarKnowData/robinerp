<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AddUser.aspx.cs" Inherits="QPS.Web.AdminControl.AddUser" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>添加用户</title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <table>
        <tr>
            <td>会员用户名</td>
            <td>
                <asp:HiddenField ID="UserID" runat="server" />
                <asp:TextBox ID="TextUsername" runat="server"></asp:TextBox>
            </td>
            <td>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="TextUsername" ErrorMessage="用户名不能为空"></asp:RequiredFieldValidator>
            </td>
        </tr>
         <tr style="display:none;">
            <td>会员密码</td>
            <td>
            <asp:TextBox ID="TextPassword" runat="server"></asp:TextBox>
            </td>
            <td>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="TextPassword" ErrorMessage="密码不能为空"></asp:RequiredFieldValidator>
            </td>
        </tr>
        <tr>
            <td>会员移动电话</td>
            <td>
            <asp:TextBox ID="TextPhone" runat="server"></asp:TextBox>
            </td>
            <td></td>
        </tr>
        <tr>
            <td>用户名</td>
            <td>
            <asp:TextBox ID="TextAddress" runat="server"></asp:TextBox>
            </td>
            <td>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator3" ControlToValidate="TextAddress" runat="server" ErrorMessage="姓名不能为空"></asp:RequiredFieldValidator>
            </td>
        </tr>
        <tr>
            <td>邮箱地址</td>
            <td>
            <asp:TextBox ID="TextMail" runat="server"></asp:TextBox>
            </td>
            <td>
                &nbsp;</td>
        </tr>
        <tr style="display:none;">
            <td>会员类型</td>
            <td>
            <asp:TextBox ID="TextUsertype" runat="server"></asp:TextBox>
            </td>
            <td></td>
        </tr>
        <tr>
            <td>
                
           </td>
            <td>
            <asp:Button ID="Button1" runat="server" Text="添加" onclick="Button1_Click" 
                    style="height: 26px" />
            </td>
        </tr>
        
    </table>
        
    
    </div>
    </form>
</body>
</html>
