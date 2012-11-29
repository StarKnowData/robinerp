<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AlmsConfig.aspx.cs" Inherits="Admin_SConfig_AlmsConfig" %>

<%@ Register Assembly="FredCK.FCKeditorV2" Namespace="FredCK.FCKeditorV2" TagPrefix="FCKeditorV2" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <title></title>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
	<script type="text/javascript" src="/Public/Js/jquery.js"></script>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	
	<style type="text/css">
		<!
		-- body { background-color: #FFFFFF; margin-top: 0px; }
		-- ></style>
</head>
<body>
 
    <form id="form1" runat="server">
    <div>
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table2">
		<tr>
			<td class="title_03">
				<strong>设置领取金币参数</strong>
			</td>
		</tr>
	</table>
	<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td height="5">
			</td>
		</tr>
	</table>
	<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
		
		<tr>
			<td align="right">
				领取金币数：&nbsp;&nbsp;</td>
				<td align="left">
				<asp:TextBox ID="txtAlmsMoney" MaxLength="9" CssClass="put" runat="server"></asp:TextBox>
		 
				</td>
				 <td>
					设置每次玩家领取金币时的金币数
				</td>
		</tr>
		<tr>
			<td align="right">
				每个玩家每天最多领取的次数&nbsp;&nbsp;</td>
				<td align="left">
				<asp:TextBox ID="txtAlmsDayCounts" MaxLength="9" runat="server" CssClass="put></asp:TextBox> 
				</td>
				<td>
					 
				</td>
		</tr>
		<tr>
			<td align="right">领取金币时的底线金币&nbsp;&nbsp;</td><td align="left">
				<asp:TextBox ID="txtLimitMoney" MaxLength="9" runat="server" CssClass="put></asp:TextBox> 
				</td>
				<td>
					 玩家只有在金币数低于这个时才能领取金币
				</td>
		</tr>
		<tr>
			<td align="right">大厅领取金币页面第一步：&nbsp;&nbsp; 
			</td>
			<td align="left">
			 <FCKeditorV2:FCKeditor ID="fckFirstNews" runat="server" Width="600" Height="400" BasePath="/Public/Js/fckeditor/"></FCKeditorV2:FCKeditor>
			 
			</td>
			<td>
				领取金币时进入的第一广告页面 *请选择救济金模版<br/>
操作如下：<br/>1，点击工具第一排的第三个按钮即"模版"，选择救济金广告模版；<br/>
			   2，在内容框中右键图片，选择图片属性，点击"浏览服务器"，图片存在则单击图片即可，否则点击底部"浏览","upload"即可<br />
			   3，在内容框中点击"请在此处点击输入文字内容"，输入文字。注：为了页面样式，建议使用"12px"字体；
			</td>
		</tr>
		<tr>
			<td align="right">
				大厅领取金币页面第二步&nbsp;&nbsp;</td><td align="left">
					 <FCKeditorV2:FCKeditor ID="fckSecondNews" runat="server" Width="600" Height="400" BasePath="/Public/Js/fckeditor/"></FCKeditorV2:FCKeditor>
				 
				</td>
				<td>
					 领取金币时进入的第二广告页面  *请选择救济金模版
				</td>
		</tr>
		<tr >
			<td align="right">
				大厅领取金币页面第三步&nbsp;&nbsp; </td>
			 
			<td align="left">
			<FCKeditorV2:FCKeditor ID="fckThirdNews" runat="server" Width="600" Height="400" BasePath="/Public/Js/fckeditor/"></FCKeditorV2:FCKeditor>
				 
			</td>
			<td>领取金币时进入的最后一个广告页面 *请选择救济金模版
			</td>
		</tr>
		 
		 
		<tr>
			<td align="center" colspan="3">
				<asp:Button ID="Button1" runat="server" Text=" 修 改 " OnClick="PrCsEdit" class="put" />
			</td>
		</tr>
	</table>
    </div>
    </form>
</body>
</html>
