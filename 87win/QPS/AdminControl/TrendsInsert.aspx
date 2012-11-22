<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="TrendsInsert.aspx.cs" Inherits="QPS.Web.AdminControl.TrendsInsert" validateRequest="false" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title>添加动态</title>

    <script src="../ckeditor/ckeditor.js" type="text/javascript"></script>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <table>
            <tr>
                <td>标题</td>
                <td>
                    <asp:TextBox ID="txtTitle" runat="server" Width="333px"></asp:TextBox>
                </td>
                <td>
                    <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server"  ControlToValidate="txtTitle" ErrorMessage="标题不为空"></asp:RequiredFieldValidator>
                </td>
            </tr>
            <tr>
                <td>内容</td>
                <td width="500">
                    <asp:TextBox ID="Content" runat="server" style="display:none;"
          TextMode="MultiLine"></asp:TextBox>
                <script type="text/javascript">
                    //<![CDATA[
                    // Replace the <textarea id="Content"> with an CKEditor instance.
                    var editor = CKEDITOR.replace('Content',
			      {
			          filebrowserBrowseUrl: 'ckfinder/ckfinder.html', //启用浏览功能
			          filebrowserImageBrowseUrl: 'ckfinder/ckfinder.html?Type=Images',
			          filebrowserFlashBrowseUrl: 'ckfinder/ckfinder.html?Type=Flash',
			          filebrowserUploadUrl: 'ckfinder/core/connector/aspx/connector.aspx?command=QuickUpload&type=Files',
			          filebrowserImageUploadUrl: 'ckfinder/core/connector/aspx/connector.aspx?command=QuickUpload&type=Images',
			          filebrowserFlashUploadUrl: 'ckfinder/core/connector/aspx/connector.aspx?command=QuickUpload&type=Flash'
			      }
            );
                    //]]>
                    function Button2_onclick() {
                        window.location.href = "TrendsList.aspx";
                        return false;
                    }

          </script> 
                </td>
                <td></td>
            </tr>
            
            <tr>
                <td></td>
                <td>
                    <asp:Button ID="bntInsert" runat="server" Text="添加" onclick="bntInsert_Click" />
                    
             &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                    
                    <asp:Button ID="Button2" runat="server" Text="返回"  OnClientClick="return Button2_onclick();" />
                </td>
                <td>
                </td>
            </tr>
        </table>
    </div>
    </form>
</body>
</html>
