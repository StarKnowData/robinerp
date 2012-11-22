<%@ Page Language="C#" AutoEventWireup="True" CodeBehind="Upload.aspx.cs" Inherits="SdCms.Web.Admin.Upload" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>上传文件</title>
    <link href="style/Global.css" rel="stylesheet" type="text/css" />
</head>
<body>
  
    <form id="form1" runat="server">
    <fieldset>
      <legend>上传文件</legend>    
      <div align="center">
        <br />
        <asp:FileUpload ID="FileUpload1" runat="server" />
        <asp:Button ID="Button1" runat="server" onclick="Button1_Click" Text="上传" />
        <br />
        <asp:Label ID="Label1" runat="server" Text=""></asp:Label>
        <br />
      </div>
    </fieldset>
    </form>
</body>
</html>
