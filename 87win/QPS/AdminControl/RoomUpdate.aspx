<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="RoomUpdate.aspx.cs" Inherits="QPS.Web.AdminControl.RoomUpdate" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
<script src="../script/Modality.js" type="text/javascript"></script>
    
    <script src="../Manage/js/calendar.js" type="text/javascript"></script>
    
    <script src="ckeditor/ckeditor.js" type="text/javascript"></script>
    <script src="ckfinder/ckfinder.js" type="text/javascript"></script>
<script type="text/javascript" src="editor/fckeditor.js">
</script>
<script src="../Manage/js/common_opwindow.js" type="text/javascript"></script>
<style type="text/css">
        .style1 
        {
            width: 269px;
        }
        .style2
        {
            height: 24px;
            width: 269px;
        }
        .style4
    {
        width: 102px;
    }
    .style5
    {
        height: 24px;
        width: 102px;
    }
    .style6
    {
        width: 102px;
        height: 34px;
    }
    .style7
    {
        height: 34px;
    }
        #UpLoad
    {
        width: 44px;
        margin-left: 4px;
    }
        #FileContent
    {
        height: 146px;
        width: 343px;
    }
        </style>

    <title>修改棋牌室信息</title>
</head>
<body style="padding:0px; border:0px;">
    <form id="form1" runat="server" method="post">
    
    <div>
        <table  width="100%" align="center">
        <tr><td align="center">
            &nbsp;&nbsp;
        <table cellspacing="0" cellpadding="3" align="center" border="0" 
                style="height: 358px; width: 690px"><tr>
            <td align="left" class="style4"  >
             棋牌室名称: </td>
            <td align="left" class="style1">
             <asp:HiddenField ID="ID" runat="server" />
            <asp:TextBox ID="txName" runat="server" Width="190px" Height="22px"></asp:TextBox>
                                </td>
            <td align="left">
                &nbsp;</td>
            <td align="left">
                &nbsp;</td>
        </tr>
                            <tr>
            <td align="left" class="style4"  >
                棋牌室类型:</td>
            <td align="left" class="style1">
                <asp:DropDownList ID="ddlCat" runat="server" Width="186px" Height="29px">
                    <asp:ListItem Value="0">豪华</asp:ListItem>
                    <asp:ListItem Value="1">标准</asp:ListItem>
                </asp:DropDownList></td>
            <td align="left">
                &nbsp;</td>
            <td align="left">
                &nbsp;</td>
        </tr>
        
       <tr>
            <td align="left" class="style4"  >
                棋牌室价格:</td>
            <td align="left" class="style1">
                <asp:TextBox ID="Textprice" runat="server" Width="190px" ></asp:TextBox>
            <td align="left">
                &nbsp;</td>
            <td align="left">
                &nbsp;</td>
        </tr>
         <tr>
            <td align="left" class="style4"  >
                棋牌室地域:</td>
            <td align="left" class="style1">
                <asp:TextBox ID="TextAre" runat="server" Width="190px" ></asp:TextBox>
            <td align="left">
                &nbsp;</td>
            <td align="left">
                &nbsp;</td>
        </tr>
        
        <tr>
            <td align="left" class="style4"  >
                棋牌室详细地址:</td>
            <td align="left" class="style1">
                <asp:TextBox ID="TextAddress" runat="server" Width="190px" ></asp:TextBox>
            <td align="left">
                &nbsp;</td>
            <td align="left">
                &nbsp;</td>
        </tr>
        
        
        <tr>
             <td align="left" class="style5">
                    棋牌室图片:</td>
              <td align="left" class="style2">
               <asp:TextBox ID="Photo" runat="server" Width="189px"></asp:TextBox>
        <input name="UpLoad" type="button" id="UpLoad" value="上传" onclick="popupWindow('Upload.aspx?rid=Photo','UpLoad',420,130,1)" /></td>
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
             <%--<tr id="Tr2" runat="server" >
                <td style="height: 24px; width: 86px;" align="left">
                   添加时间:</td>
                <td align="left" colspan="3" style="height: 24px">
                    <asp:TextBox ID="addTime" runat="server" 
                        onfocus="displayCalendar(this,'yyyy-mm-dd',this);"></asp:TextBox>(不添时间则为当前时间)</td>
            </tr>--%>
            
            <%--<tr id="Tr1" runat="server" >
                <td align="left" class="style5">
                   主页链接:</td>
                <td align="left" colspan="3" style="height: 24px">
                    <asp:TextBox ID="txsource" runat="server" Width="300px"></asp:TextBox>(用于填写文章链接,如："http://www.google.com")</td>
            </tr>--%>
            
                   <%--<tr runat="server" id="autr">
                <td style="height: 16px; width: 86px;" align="left">
                   置顶新闻:</td>
                <td align="left" class="style3">
                    <asp:CheckBox ID="cktop" runat="server" Text="是否置顶新闻" /></td>
                <td style="height: 16px" align="left">
                    &nbsp;</td>
                <td style="height: 16px" align="left">
                    &nbsp;</td>
            </tr>--%>
            <%--<tr id="Tr2" runat="server" >
                <td align="left" class="style5">
                   文章排序:</td>
                <td align="left" colspan="3" style="height: 24px">
                    <asp:TextBox ID="sort" runat="server" Width="40px"></asp:TextBox>&nbsp;用于文章排序(数字越大越靠前)
                </td>
            </tr>--%>
           <%-- <tr>
                <td align="left" class="style5">推荐文章:</td>
                <td><asp:CheckBox 
                        ID="ChbRecommend" runat="server" /></td>
            </tr>--%>
            <tr>
                <td align="left" class="style6">
                    <span style="font-size:10.5pt;mso-bidi-font-size:11.0pt;
font-family:宋体;mso-ascii-font-family:Calibri;mso-hansi-font-family:Calibri;
mso-bidi-font-family:&quot;Times New Roman&quot;;mso-font-kerning:1.0pt;mso-ansi-language:
EN-US;mso-fareast-language:ZH-CN;mso-bidi-language:AR-SA">祥细介绍</span>:</td>
                <td colspan="3" align="left" runat="server" id="tdShow" class="style7">
                     <%--<iframe id="doc_html" frameborder="0" scrolling="no"  
                         src="Control/WebEditor/eWebEditor.asp?id=txcontent&style=s_coolblue" 
                         style="width: 567px; height: 326px;"></iframe>--%>
                   <%--<FCKeditorV2:FCKeditor ID="FCKeditor1" runat="server" Height="400px" Width="600px"></FCKeditorV2:FCKeditor>--%>
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
                <td align="left" class="style5">
                    </td>
                <td align="left" class="style2">
                    <asp:Button ID="btnupdate" runat="server" Text="修改"  OnClick="btnupdate_Click"  />
                    <asp:Button ID="btnsure" runat="server" Text="确定" OnClick="btnsure_Click"   Visible="false"/>
                       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                      <script type="text/javascript">
                      function Button2_onclick() {
                          window.location.href = "Qps.aspx";
                          return false;
                      }
                  </script> 
                    <asp:Button ID="btnback" runat="server" Text="返回"  OnClientClick="return  Button2_onclick();" />
                    
                    
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
