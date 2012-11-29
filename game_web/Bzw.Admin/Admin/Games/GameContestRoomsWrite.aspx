<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="GameContestRoomsWrite.aspx.cs" Inherits="Admin_Games_GameContestRoomsWrite" %>

<%@ Register Assembly="FredCK.FCKeditorV2" Namespace="FredCK.FCKeditorV2" TagPrefix="FCKeditorV2" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />

	<script src="/Public/Js/jquery.js"></script>

	<script src="/Public/Js/public.js"></script>

	<script src="/Public/Js/DatePicker/WdatePicker.js"></script>

</head>
<body>
	<form id="form1" runat="server" enctype="multipart/form-data"    >
		<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td colspan="2" class="title_03">
					<strong>添加/修改比赛房间</strong></td>
			</tr>
		 
			<tr>
				<td align="right">
					比赛开始时间：</td>
				<td align="left">
					<asp:TextBox ID="txtBeginTime" runat="server" CssClass="put" onfocus="WdatePicker({maxDate:'#F{$dp.$D(\'txtEndTime\')}',dateFmt:'yyyy-MM-dd HH:mm:ss'})"></asp:TextBox>
					<asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" ControlToValidate="txtBeginTime" Display="Dynamic" ErrorMessage="请输入起始时间"></asp:RequiredFieldValidator></td>
			</tr>
			<tr>
				<td align="right">
					比赛结束时间：</td>
				<td align="left">
					<asp:TextBox ID="txtEndTime" runat="server" CssClass="put" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginTime\')}',dateFmt:'yyyy-MM-dd HH:mm:ss'})"></asp:TextBox>
					<asp:RequiredFieldValidator ID="RequiredFieldValidator3" runat="server" ControlToValidate="txtEndTime" Display="Dynamic" ErrorMessage="请输入结束时间"></asp:RequiredFieldValidator></td>
			</tr>
			
			<tr>
			<td align="right">比赛初始积分：</td>
			<td align="left"><asp:TextBox ID="txtChip" runat="server" CssClass="put" MaxLength="19"  >0</asp:TextBox> </td>
			</tr>
			<tr>
			<td align="right">最少积分：</td>
			<td align="left"> <asp:TextBox ID="txtLowChip" runat="server" CssClass="put" MaxLength="19">0</asp:TextBox> </td>
			</tr>
			<tr>
			<td align="right">最少局数：</td><td align="left"><asp:TextBox ID="txtLowCount" runat="server" CssClass="put" MaxLength="19"  >0</asp:TextBox> </td>
			</tr>
			<tr>
			<td align="right">报名费用：</td><td align="left"><asp:TextBox ID="txtEntryFee" runat="server" CssClass="put" MaxLength="19"  >0</asp:TextBox> </td>
			</tr>
			<tr >
			<td align="right">比赛人数上限：</td><td align="left"><asp:TextBox ID="txtUpPeople" runat="server" CssClass="put" MaxLength="19"  >0</asp:TextBox> </td>
			</tr>
			 <tr>
			 <td align="right">退出时间限制：</td><td align="left"><asp:TextBox ID="txtTimeLimit" runat="server" CssClass="put" MaxLength="9">10</asp:TextBox>分钟  注：玩家在这段时间内退出比赛可以再进入</td>
			 </tr>
			<tr>
			<td align="right">发送信息提醒：</td><td align="left"><asp:TextBox ID="txtMessage" runat="server" CssClass="put" Width="340px" ></asp:TextBox></td>
			</tr>
			<tr>
			<td align="right">发送信息提醒时间：</td><td align="left"><asp:TextBox ID="txtSendTime" runat="server" CssClass="put" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd HH:mm:ss'})"></asp:TextBox>
					 </td>
			</tr>
			<tr>
			<td align="right">奖励方案名：</td>
			<td align="left"><asp:DropDownList ID="ddlSendType" runat="server"></asp:DropDownList></td>
			</tr>
			<tr style=" display:none;">
			<td align="right">奖励说明：</td>
			<td align="left">
			<textarea id="txtAwardContent" name="txtAwardContent" runat="server" style="width:300px; height:100px;"></textarea>
			</td>
			</tr>
			<tr>
			    <td align="right">比赛说明：</td>
			    <td align="left">
			      <FCKeditorV2:FCKeditor ID="txtMatchContent" runat="server" Width="100%" Height="450" BasePath="/Public/Js/fckeditor/">
                    </FCKeditorV2:FCKeditor>
			    </td>
			</tr>
			<tr>
				<td>
					&nbsp;</td>
				<td align="left">
					<asp:Button ID="btnSubmit" runat="server" Text="填好提交" Class="put" OnClick="btnSubmit_Click" />
					<p>修改完成后，模版页面样式问题，请<a href="/Manage/MatchApply2.aspx?id=<%=RoomID %>" target="_blank">点击此处</a>查看比赛页面具体的显示</p>
				</td>
			</tr>
		</table>
	</form>
</body>
</html>
