<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="SendMsg.aspx.cs" Inherits="Admin_SConfig_SendMsg" %>

 
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
            bgcolor="F2F8FF" class="admin_table"><asp:HiddenField  ID="hida"  runat="server"/>
            <tr>
                <td colspan="2" class="title_03">
                    <strong>发送站内信息</strong></td>
            </tr>
           <tr>
            <td align="right"> <span style="color:Red; font-weight:bold">*</span>发送时间：</td> 
            <td align="left"><input type="text" id="txtSendTime"  name="txtSendTime"  onfocus="WdatePicker({dateFmt:'yyyy-MM-dd HH:mm:ss'})" runat="server" /></td>
           </tr>
            
            <tr>
                <td align="right">
                    <span style="color:Red; font-weight:bold">*</span>内容：</td>
                <td align="left">
                     <textarea id="txtContent" name="txtContent" runat="server" style="width:300px; height:80px;" ></textarea>
                    注：内容不应超过200字
                </td>
            </tr>
            <tr>
            <td align="right">是否是游戏跑马灯：</td>
            <td align="left"><asp:RadioButtonList ID="rdoIsMarquee" runat="server" RepeatDirection="Horizontal" RepeatLayout="Flow">
                        <asp:ListItem Text="是" Value="1"></asp:ListItem>
                        <asp:ListItem Text="否" Value="0" Selected="True"></asp:ListItem>
                    </asp:RadioButtonList> </td>
            </tr>
            <tr>
                <td align="right">是否是大厅跑马灯：</td>
                <td align="left"><asp:RadioButtonList ID="rdoIsHallMarquee" runat="server" RepeatDirection="Horizontal">
                <asp:ListItem Text="是" Value="1" Selected="True"></asp:ListItem>
                <asp:ListItem Text="否" Value="0"></asp:ListItem>
                </asp:RadioButtonList></td>
            </tr>
                 <tr>
                <td align="right">
                    是否所有玩家群发：</td>
                <td align="left"> <asp:RadioButtonList ID="rdoIsToAll" runat="server" RepeatDirection="Horizontal" RepeatLayout="Flow">
                        <asp:ListItem Text="是" Value="1"></asp:ListItem>
                        <asp:ListItem Text="否" Value="0" Selected="True"></asp:ListItem>
                    </asp:RadioButtonList>
                     </td>
            </tr>
            
            <tr>
                <td align="right">
                    单个用户发送：</td>
                <td align="left">
                   <input type="text" name="txtUserID" id="txtUserID"  runat="server" maxlength="100" size="80" />(如果同时发几个用户，用户ID请用“,”隔开,)
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
    <font color="red">    注：修改仅限于内容和时间的修改</font>
    </form>
  
</body>
</html>
