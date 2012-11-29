<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_SConfig_FilterGameName" Codebehind="FilterGameName.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<style type="text/css">
<!--
body {
	background-color: #FFFFFF;
	margin-top: 0px;
}
-->
</style>
</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td class="title_03">
					<strong>设置是否累积游戏时长的游戏</strong></td>
			</tr>
		</table>
		<table border="0" width="100%" cellpadding="2" cellspacing="1" bordercolor="#A4B6D7" bgcolor="#A4B6D7" class="admin_table">
			<tr style="text-align:center; background-color:#ffffff; font-weight:bold;">
				<td>
					名称</td>
				<td>
					需要统计的游戏</td>
				<td>
					不需统计的游戏</td>
				<td>
					编辑</td>
			</tr>
			<tr style="text-align:center; background-color:#ffffff; ">
				<td>
					奖品兑换</td>
				<td><asp:Label ID="lbaward" runat="server"></asp:Label> 
				</td>
				<td>
				<asp:Label ID="lbfiteraward" runat="server"></asp:Label> 
				</td>
				<td>
				<a href="FilterGameName.aspx?type=0">修改</a>
				</td>
			</tr>
			<tr style="text-align:center; background-color:#ffffff; ">
				<td>
					游戏推广</td>
				<td><asp:Label ID="lbextent" runat="server"></asp:Label> 
				</td>
				<td>
				<asp:Label ID="lbfiterextent" runat="server"></asp:Label> 
				</td>
				<td><a href="FilterGameName.aspx?type=1">修改</a>
				</td>
			</tr>
		</table>
		<table align="center">
			<tr>
				<td>
				</td>
			</tr>
			<tr style="display:none;" id="map" runat="server">
				<td>
					<table border="0">
						<tr>
							<td align="right" width="25%">
							</td>
							<td align="left" width="100">
								需要统计的游戏
							</td>
							<td width="20">
							</td>
							<td>
								不需统计的游戏
							</td>
						</tr>
						<tr>
							<td align="right" width="25%">
							</td>
							<td align="left" width="100">
								<asp:ListBox ID="listLeft" ondblclick="listLeft_DoubleClick()" runat="server" Width="100" Height="150" SelectionMode="Multiple"></asp:ListBox>
								<input type="hidden" name="listLeftHidden" />
							</td>
							<td width="20">
								<asp:Button ID="btnToRight" runat="server" Text=">>" OnClick="btnToRight_Click" /><br />
								<br />
								<asp:Button ID="btnToLeft" runat="server" Text="<<" OnClick="btnToLeft_Click" />
							</td>
							<td>
								<asp:ListBox ID="listRight" ondblclick="listRight_DoubleClick()" runat="server" Width="100" Height="150" SelectionMode="Multiple"></asp:ListBox>
								<input type="hidden" name="listRightHidden" />
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td>
					<div style="padding-left: 100px;">
						<asp:Button ID="Button1" runat="server" Text="提交修改" class="put" OnClick="EditFilt" /></div>
				</td>
			</tr>
		</table>

		<script language="javascript">
     function listLeft_DoubleClick() {      
        document.forms[0].listLeftHidden.value = "leftdoubleclicked";
        document.forms[0].listRightHidden.value = "";
        document.forms[0].submit();
     }
     function listRight_DoubleClick(){
		document.forms[0].listRightHidden.value = "rightdoubleclicked";
		document.forms[0].listLeftHidden.value = "";
        document.forms[0].submit();
     }
   
		</script>

	</form>
</body>
</html>
