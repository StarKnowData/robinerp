<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="RoomInsert.aspx.cs" Inherits="QPS.Web.AdminControl.RoomInsert" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
    <script src="../Manage/js/common_opwindow.js" type="text/javascript"></script>
    <style type="text/css">
        #FileContent
        {
            height: 86px;
            width: 208px;
        }
        .style1
        {
            width: 189px;
        }
        .style2
        {
            width: 96px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <table  width="100%" align="center">
        <tr><td align="center">
            &nbsp;&nbsp;
        <table cellspacing="0" cellpadding="3" align="center" border="0" 
                style="height: 358px; width: 690px"><tr>
            <td align="left" class="style2"  >
             棋牌室名称: </td>
            <td align="left" class="style1">
            <asp:TextBox ID="txName" runat="server" Width="150px"></asp:TextBox>
                                </td>
            <td align="left">
                <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" ControlToValidate="txName" ErrorMessage="棋牌室名称不能为空"></asp:RequiredFieldValidator> 
                
                </td>
            <td align="left">
                &nbsp;</td>
        </tr>
        <tr>
            <td align="left" class="style2"  >
                棋牌室类型:</td>
            <td align="left" class="style1">
                <asp:DropDownList ID="ddlCat" runat="server" Width="150px" Height="19px">
                    <asp:ListItem Value="0">豪华</asp:ListItem>
                    <asp:ListItem Value="1">标准</asp:ListItem>
                </asp:DropDownList></td>
            <td align="left">
                &nbsp;</td>
            <td align="left">
                &nbsp;</td>
        </tr>
        
       <tr>
            <td align="left" class="style2"  >
                棋牌室价格:</td>
            <td align="left" class="style1">
                <asp:TextBox ID="Textprice" runat="server" Height="23px" Width="150px" ></asp:TextBox>
            <td align="left">
                <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate ="Textprice" ErrorMessage="价格不能为空"></asp:RequiredFieldValidator>
                
                <asp:RegularExpressionValidator ID="RegularExpressionValidator1" runat="server" ErrorMessage="输入1-10000直接的货币格式" ControlToValidate="Textprice" ValidationExpression="^0|[1-9]+(.[0-9]{2})?$"></asp:RegularExpressionValidator>
                
                </td>
            <td align="left">
                &nbsp;</td>
        </tr>
        
         <tr>
            <td align="left" class="style2"  >
                棋牌室地域:</td>
            <td align="left" class="style1">
<%--         江岸区(476)武昌区(557)江汉区(628)硚口区(160)汉阳区(162)洪山区(972)青山区(82)东西湖区(26)蔡甸区(15)江夏区(15)黄陂区(8) 价格：20-5050-100100-200200-3008)
排序：默认热门折扣价格--%>
                <asp:TextBox ID="TextAre" runat="server" Height="22px" Width="150px" ></asp:TextBox>
                <br />
                <asp:Label ID="Label1" runat="server" Text="（如：武昌区，洪山区，东西湖区...）"></asp:Label>
            <td align="left">
            <asp:RequiredFieldValidator ID="RequiredFieldValidator3" runat="server" ControlToValidate ="TextAre" ErrorMessage="地域不能为空"></asp:RequiredFieldValidator>
            </td>
            <td align="left">
                &nbsp;</td>
        </tr>
        
        <tr>
            <td align="left" class="style2"  >
                棋牌室详细地址:</td>
            <td align="left" class="style1">
                <asp:TextBox ID="TextAddress" runat="server" Height="22px" Width="150px" ></asp:TextBox>
            <td align="left">
                <asp:RequiredFieldValidator ID="RequiredFieldValidator4" runat="server" ControlToValidate="TextAddress" ErrorMessage="详细地址不能为空"></asp:RequiredFieldValidator>  
                </td>
            <td align="left">
                &nbsp;</td>
        </tr>
        <tr>
             <td align="left" class="style2">
                    棋牌室图片:</td>
              <td align="left" class="style1">
               
               <asp:TextBox ID="Photo" runat="server" Width="149px"></asp:TextBox>
        <input name="UpLoad" type="button" id="UpLoad" value="上传" onclick="popupWindow('Upload.aspx?rid=Photo','UpLoad',420,130,1)" />
               
               </td>
                  <td style="height: 16px" align="left">
                         &nbsp;</td>
                   <td style="height: 16px" align="left">
                    &nbsp;</td>
           </tr> 
           <tr>
                <td align="left" class="style2">是否推荐:</td>
                <td align="left" class="style1">
                    <asp:CheckBox ID="Rec" runat="server" />
                </td>
                <td></td>
                <td></td>
           </tr>

            <tr>
                <td align="left" class="style2">
                    <span style="font-size:10.5pt;mso-bidi-font-size:11.0pt;
font-family:宋体;mso-ascii-font-family:Calibri;mso-hansi-font-family:Calibri;
mso-bidi-font-family:&quot;Times New Roman&quot;;mso-font-kerning:1.0pt;mso-ansi-language:
EN-US;mso-fareast-language:ZH-CN;mso-bidi-language:AR-SA">祥细介绍</span>:</td>
                <td colspan="3" align="left" runat="server" id="tdShow" class="style7">
         
              <textarea id="FileContent" runat="server"></textarea>
                   <script type="text/javascript">
                       //<![CDATA[
                       // Replace the <textarea id="Content"> with an CKEditor instance.
                       var editor = CKEDITOR.replace('FileContent',
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
		      </script>
                  <input id="txcontent" type="hidden" runat="server" />
            <!--编辑器开始-->
            <%--<script type="text/javascript" language="JavaScript">
                window.onload = function() {
                    var sBasePath = "editor/"
                    var oFCKeditor = new FCKeditor('FileContent');
                    oFCKeditor.BasePath = sBasePath;
                    oFCKeditor.Width = '100%';
                    oFCKeditor.Height = '100%';
                    oFCKeditor.ReplaceTextarea();
                }
			</script>
			<textarea name="FileContent" rows="1" cols="1" style="display:none" id="FileContent" runat="server" ></textarea>--%>
            </td></tr>
                   <tr>
                <td align="left" class="style2">
                    &nbsp;</td>
                <td align="center" class="style1">
                    <asp:Button ID="btnupdate" runat="server" Text="修改"   Visible="false" 
                        onclick="btnupdate_Click" />
                    <asp:Button ID="btnsure" runat="server" Text="确定" OnClick="btnsure_Click"   />
                       </td>
                <td style="height: 24px" align="center">
                    <asp:Button ID="btnback" runat="server" Text="返回" OnClick="btnback_Click" Visible="false" /></td>
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
