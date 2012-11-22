<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="JfXiuGai.aspx.cs" Inherits="QPS.Web.AdminControl.JFxg" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <table>
            <tr>
                 <td>用 户 ID</td>
                 <td>
                     <asp:TextBox ID="txtName" runat="server" ReadOnly="True"></asp:TextBox>                
                     </td>
                 <td></td>
            </tr>
            <tr>
            <td>
                棋牌室ID
            </td>
                 <td>
                 <asp:TextBox ID="txtRoom" runat="server" ReadOnly="True"></asp:TextBox>               
                 </td>
                 <td></td>
            </tr>
            <tr>
                 <td>时&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 间</td>
                 <td>
                 <asp:TextBox ID="txtTime" runat="server" ReadOnly="True"></asp:TextBox>               
                 </td>
                 <td></td>
            </tr>
            <tr>
                 <td>积&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 分</td>
                 <td>
                 <asp:TextBox ID="txtJiFen" runat="server"></asp:TextBox>               
                 </td>
                 <td></td>
            </tr>
            <tr>
                <td></td>
                 <td>
                 
                 <script type="text/javascript">
                      function Button2_onclick() {
                          window.location.href = "Jfgl.aspx";
                          return false;
                      }
                  </script>
                  
                 <asp:Button ID="bntUpdate" runat="server" Text="修 改" onclick="bntUpdate_Click" />
                     &nbsp;&nbsp;
                     
                     <asp:Button ID="bntReturn" runat="server" Text="返 回"  OnClientClick="return  Button2_onclick();" />
            
                  </td>
                  <td></td>
            </tr>
        </table>
    
    </div>
    </form>
</body>
</html>
