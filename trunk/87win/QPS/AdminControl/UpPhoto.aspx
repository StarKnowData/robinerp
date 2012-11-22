<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="UpPhoto.aspx.cs" Inherits="SdCms.Web.Admin.UpPhoto" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>无标题页</title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    <div align="center">
        当前头像<br />
        <asp:Image ID="img" runat="server" style="height: 116px; width: 140px" />
        <br />
        <br />
        <asp:FileUpload ID="FileUpload1" runat="server" />
        <br />
        <br />
        <asp:Button ID="Button1" runat="server" onclick="Button1_Click" Text="上传头像" />
        <br />
        <asp:Label ID="Label1" runat="server" Text=""></asp:Label>
        <br />
      </div>
    </div>
    </form>
</body>
</html>
