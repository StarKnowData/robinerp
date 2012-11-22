<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="UserUpdate.aspx.cs" Inherits="QPS.Web.AdminControl.UserUpdate" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
<%--    
Username	Nvarchar	会员用户名
Password	Nvarchar	会员密码
Phone	Nvarchar	会员移动电话
Address	Nvarchar	用户名
Mail	Nvarchar	邮箱地址
Usertype	Int	会员类型
action	nvarchar(20)	固定值register（仅小写）
sign	nvarchar(20)	加密校验串
--%>
    
    <table>
        <tr>
            <td>会员用户名</td>
            <td>
                <asp:HiddenField ID="UserID" runat="server" />
                <asp:TextBox ID="TextUsername" runat="server"></asp:TextBox>
            </td>
            <td>
                <asp:RequiredFieldValidator ID="RequiredFieldValidator1" ControlToValidate="TextUsername" runat="server" ErrorMessage="用户名不能为空"></asp:RequiredFieldValidator>
            </td>
        </tr>
         <tr style="display:none;">
            <td>会员密码</td>
            <td>
            <asp:TextBox ID="TextPassword" runat="server"></asp:TextBox>
            </td>
            <td></td>
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
                <asp:RequiredFieldValidator ID="RequiredFieldValidator2" ControlToValidate="TextAddress" runat="server" ErrorMessage="不能为空"></asp:RequiredFieldValidator>
            </td>
        </tr>
        <tr>
            <td>邮箱地址</td>
            <td>
            <asp:TextBox ID="TextMail" runat="server"></asp:TextBox>
            </td>
            <td></td>
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
            <asp:Button ID="Button1" runat="server" Text="修改" onclick="Button1_Click" 
                    style="height: 26px" />
            </td>
        </tr>
        
    </table>
    
    </div>
    </form>
</body>
</html>
