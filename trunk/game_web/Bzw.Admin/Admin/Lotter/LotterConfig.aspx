<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="LotterConfig.aspx.cs" Inherits="Admin_Lotter_LotterConfig" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <title></title>
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
	<script type="text/javascript" src="/Public/Js/jquery.js"></script>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<script src="/Public/Js/DatePicker/WdatePicker.js" type="text/javascript"></script>
 
</head>
<body>
 
    <form id="form1" runat="server" >
    <div>
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table2">
		<tr>
			<td class="title_03">
				<strong>设置抽奖消耗金币参数设置</strong><asp:HiddenField ID="hidType" Value="0" runat="server" />
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
				金奖所需的金币数：&nbsp;&nbsp;</td>
				<td align="left">
				<asp:TextBox ID="txtGoldMoney" MaxLength="19" CssClass="put" runat="server"></asp:TextBox>
	  
					 
				</td>
		</tr> 
		
    	<tr>
			<td align="right">
				玉奖所需的金币数：&nbsp;&nbsp;</td>
				<td align="left">
				<asp:TextBox ID="txtJadeMoney" MaxLength="19" runat="server" CssClass="put"  ></asp:TextBox>  
				</td>
			 
		</tr>
		<tr>
			<td align="right">银奖所需的金币数：&nbsp;&nbsp;</td>
			<td align="left">
				<asp:TextBox ID="txtSilverMoney" MaxLength="19" runat="server" CssClass="put"></asp:TextBox>  
					 
			</td>
		</tr>
		<tr style="display:none">
			<td align="right">
				活动开始时间：&nbsp;&nbsp;</td>
				<td align="left">
				<asp:TextBox ID="txtBeginTime" MaxLength="19" runat="server" CssClass="put" onfocus="WdatePicker({maxDate:'#F{$dp.$D(\'txtEndTime\')}',dateFmt:'yyyy-MM-dd HH:mm:ss'})" Text="2012-1-1"></asp:TextBox>  
				</td>
			 
		</tr>
		<tr  style="display:none">
			<td align="right">
				活动结束时间：&nbsp;&nbsp;</td>
				<td align="left">
				<asp:TextBox ID="txtEndTime" MaxLength="19" runat="server" CssClass="put"  onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginTime\')}',dateFmt:'yyyy-MM-dd HH:mm:ss'})"  Text="2012-1-1"></asp:TextBox>  
				</td>
			 
		</tr>
		<tr>
			<td align="center" colspan="2">
				<asp:Button ID="Button1" runat="server" Text=" 添 加 " OnClick="Edit" class="put" />
			</td>
		</tr>
	</table>
    </div>
    </form>
</body>
</html>

