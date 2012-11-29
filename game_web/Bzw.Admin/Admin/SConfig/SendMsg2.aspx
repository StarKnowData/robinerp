<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="SendMsg2.aspx.cs" Inherits="Admin_SConfig_SendMsg2" %>

<%@ Register Assembly="FredCK.FCKeditorV2" Namespace="FredCK.FCKeditorV2" TagPrefix="FCKeditorV2" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
       <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>无标题页</title>
   
	<script src="/Public/Js/jquery.js"></script>

	<script src="/Public/Js/public.js"></script>

	<script src="/Public/Js/DatePicker/WdatePicker.js"></script>
	
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <style type="text/css">
 
    body {
	    background-color: #FFFFFF;
	    margin-top: 0px;
    }
  
    </style>
</head>
<body>
   <form id="form1" runat="server" enctype="multipart/form-data" >
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table"> 
            <tr>
                <td colspan="2" class="title_03">
                    <strong>发送站内信息</strong></td>
            </tr>
           <tr>
            <td align="right" width="180px"> <span style="color:Red; font-weight:bold">*</span>发送时间：</td> 
            <td align="left"><input type="text" id="txtSendTime"  name="txtSendTime"  onfocus="WdatePicker({dateFmt:'yyyy-MM-dd HH:mm:ss'})" runat="server" /></td>
           </tr>
            
            <tr>
                <td align="right">
                    <span style="color:Red; font-weight:bold">*</span>内容：</td>
                <td align="left">
                    <FCKeditorV2:FCKeditor ID="content" runat="server" Width="60%" Height="300" BasePath="/Public/Js/fckeditor/">
                    </FCKeditorV2:FCKeditor>
                </td>
            </tr>
           
            <tr>
                <td align="right">
                    &nbsp;</td>
                <td align="left">
                    <asp:Button ID="Button1" runat="server" Text="添加" class="put" OnClick="SendMessage" />
                    <input id="btnBack" type="button" onclick="document.location.href='AdminMsgList.aspx'" value=" 返 回 " class="put"/>
                </td>
            </tr>
        </table>
   
    </form>
  
</body>
</html>