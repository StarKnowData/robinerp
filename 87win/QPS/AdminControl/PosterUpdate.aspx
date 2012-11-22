<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="PosterUpdate.aspx.cs" Inherits="QPS.Web.AdminControl.PosterUpdate" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>修改广告信息</title>
    <script src="../Manage/js/common_opwindow.js" type="text/javascript"></script>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <table  width="100%" align="center">
        <tr><td align="center">
            &nbsp;&nbsp;
        <table cellspacing="0" cellpadding="3" align="center" border="0" ><tr>
            <td align="left"  >
                链接地址: </td>
            <td align="left" >
             <asp:HiddenField ID="ID" runat="server" />
            <asp:TextBox ID="txName" runat="server" Width="190px" Height="22px"></asp:TextBox>
                                </td>
            <td align="left" class="style1">
                </td>
            <td align="left" class="style1">
                </td>
        

        <tr>
             <td align="left" class="style5">
                    广告图片:</td>
              <td align="left" class="style2">
               <asp:TextBox ID="Photo" runat="server" Width="189px"></asp:TextBox>
        <input name="UpLoad" type="button" id="UpLoad" value="上传" onclick="popupWindow('Upload.aspx?rid=Photo','UpLoad',420,130,1)" /></td>
                  <td style="height: 16px" align="left">
                         &nbsp;</td>
                   <td style="height: 16px" align="left">
                    &nbsp;</td>
           </tr>
                   <tr>
                <td align="left" class="style5">
                    </td>
                <td align="left" class="style2">
                    <asp:Button ID="btnupdate" runat="server" Text="修改"  OnClick="btnupdate_Click"  />
                    <asp:Button ID="btnsure" runat="server" Text="确定" OnClick="btnsure_Click"   Visible="false"/>
                       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                       
                    <asp:Button ID="btnback" runat="server" Text="返回" OnClientClick="return Button2_onclick();" />
                    
                  <script type="text/javascript">
                      function Button2_onclick() {
                          window.location.href = "Poster.aspx";
                          return false;
                      }
                  </script>  

                       </td>
                <td style="height: 24px" align="center">
                    &nbsp;</td>
                <td style="height: 24px" align="left">
                    </td>
            </tr> 
        </table>
          
                    </td></tr>
                    </table>
    
    </div>
    </form>
</body>
</html>
