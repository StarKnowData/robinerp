<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="JfIndert.aspx.cs" Inherits="QPS.Web.AdminControl.JfIndert" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    <p>添加积分</p>
    <table>
        <tr>
            <td>用户id</td>
            <td>
                <asp:TextBox ID="txtId" runat="server"></asp:TextBox>
            </td>
            <td></td>
        </tr>
        <tr>
            <td>用户名</td>
            <td>
                <asp:TextBox ID="txtName" runat="server"></asp:TextBox>
            </td>
            <td></td>
        </tr>
        <tr>
            <td>手机号</td>
            <td>
                <asp:TextBox ID="txtPhone" runat="server"></asp:TextBox>
            </td>
            <td></td>
        </tr>
        
        <tr>
            <td>积分</td>
            <td>
                <asp:TextBox ID="txtJf" runat="server"></asp:TextBox>
            </td>
            <td>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txtJf" ErrorMessage="积分不能为空"></asp:RequiredFieldValidator>
            </td>
        </tr>
        <tr>
            <td></td>
            <td>
                <asp:Button ID="Button1" runat="server" Text="添加" onclick="Button1_Click" />
            </td>
            <td></td>
        </tr>
        
    </table>
    
    </div>
    </form>
</body>
</html>
