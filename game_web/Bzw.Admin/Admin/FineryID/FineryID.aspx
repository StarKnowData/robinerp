<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="FineryID.aspx.cs" Inherits="Bzw.Web.Admin.FineryID.FineryID1" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
<style>

p{padding:0;margin:0; line-height:25px;}

	</style>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
		<!--FinelyID, UserID,  Price, IsUse, DateTime-->
			<tr>
				<td colspan="2">
					<strong><font color="red">靓号管理  >  生成靓号</font></strong>
					<hr />
					<a href="FineryID.aspx">生成靓号</a> | <a href="NoBuyFineryID.aspx">待售靓号</a> | <a href="IsBuyFineryID.aspx">已售出靓号</a>
					</td>
				
			</tr>
			<tr>
				<td colspan="2">
					<p>靓号说明，生成靓号有两种方式：</p>
					<p>1.注册时根据靓号规则，判断该用户注册的ID号是否是符合靓号规则，如符合产生靓号，用户重新生成ID号，靓号规则如下</p>
					 <p> &nbsp;&nbsp;&nbsp;&nbsp;a.&nbsp;&nbsp;&nbsp;&nbsp;ID内含3位或以上重复数字，模式为AAA，AAAA，AAAAA，AAAAAA，例如222，3333，55555，666666等</p>
					  <p>&nbsp;&nbsp;&nbsp;&nbsp;b.&nbsp;&nbsp;&nbsp;&nbsp;ID内含连续2次或以上2位重复数字，模式为AABB，AABBCC，例如1122，335577，776699等</p>
					  <p>&nbsp;&nbsp;&nbsp;&nbsp;c.&nbsp;&nbsp;&nbsp;&nbsp;ID内含4位或4位以上按顺序排列数字，模式为ABCD，ABCDE，ABCDEF，FEDCBA，EDCBA，DCBA，例如12345，23456，65432，98765等</p>
					  <p>&nbsp;&nbsp;&nbsp;&nbsp;e.&nbsp;&nbsp;&nbsp;&nbsp;ID内2位或2位以上某段连续重复，模式为ABAB，ABCABC，例如3535，124124，436436等</p>
					  <p>&nbsp;&nbsp;&nbsp;&nbsp;g.&nbsp;&nbsp;&nbsp;&nbsp;ID内2位或以上相隔1位重复，模式为ABGAB，例如36836，97397等</p>
					  <p>&nbsp;&nbsp;&nbsp;&nbsp;f.&nbsp;&nbsp;&nbsp;&nbsp;ID内的含有生日类型，比如19710708，19691012等</p>
					<p>2.管理员手动添加靓号，此方法是为了添加一些特殊无规律的号码</p>
				</td>
			</tr>
		</table>
		<br />
		  <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
		  	<tr>
			<th colspan="2" align="left">
			<strong>手动添加靓号</strong></th>
			</tr>
			<tr>
			<td>号码：</td>
			<td><asp:TextBox ID="FineryID" runat="server" MaxLength="9" Width="176px"></asp:TextBox> </td>
			</tr>
			<tr>
			<td width="12%">靓号价格：</td>
			<td><asp:TextBox ID="pr" runat="server" MaxLength="9" Width="176px"></asp:TextBox>&nbsp;金币</td>
			</tr>
			<tr>
			<td>靓号描述：</td>
			<td><asp:TextBox ID="bewriteTB" runat="server" MaxLength="9" Width="176px"></asp:TextBox>最多20个字符，多余会被截取，一个中文算2个字符</td>
			</tr>
			<tr>
				<td>是否上架：</td>
				<td align="left">
					<asp:RadioButtonList ID="sjRDO" runat="server" RepeatDirection="Horizontal">
						<asp:ListItem Value="1" Selected=True>是</asp:ListItem>
						<asp:ListItem Value="0">否</asp:ListItem>
					</asp:RadioButtonList>
				</td>
			</tr>
			<tr>
				<td>是否推荐：</td>
				<td align="left">
					<asp:RadioButtonList ID="tjRDO" runat="server" RepeatDirection="Horizontal">
						<asp:ListItem Value="1"  Selected=True>是</asp:ListItem>
						<asp:ListItem Value="0">否</asp:ListItem>
					</asp:RadioButtonList>
				</td>
			</tr>
			<tr>
			<td colspan="2"><asp:Label ID="msg" runat="server" Text="" ForeColor="Red"></asp:Label><asp:Button ID="Button1" runat="server" Text="确定添加" onclick="Button1_Click" CssClass="put" Width="100"/></td>
			</tr>
		  </table>
		  <br/>
		  
		  <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
			<th colspan="2" align="left">
				<strong>修改靓号默认设置</strong></th>
			</tr>
			<tr>
			<td width="12%">
				默认价格：</td>
			<td>
				<asp:TextBox ID="PriceTX" runat="server" Width="176px" MaxLength="9"></asp:TextBox>&nbsp;金币&nbsp;&nbsp;<asp:Label ID="msgup" runat="server" Text="" ForeColor="Red"></asp:Label></asp:Label></td>
			</tr>
			<tr>
			<td>
				靓号规则：</td>
			<td>
				<asp:TextBox ID="rulesTX" runat="server" Height="93px" TextMode="MultiLine" Width="700px"></asp:TextBox>
				<br />靓号规则请不要轻易修改，如修改后有误需还原默认值，请在下文本框中拷贝初始化值再更新<br />
				<textarea readonly="readonly" rows="5" style="width: 698px;background-color:gray;">(\d)\1{2,}-(\d)\1{1,}(\d)\2{1,}-(?:0(?=1)|1(?=2)|2(?=3)|3(?=4)|4(?=5)|5(?=6)|6(?=7)|7(?=8)|8(?=9)){4}\d-(?:9(?=8)|8(?=7)|7(?=6)|6(?=5)|5(?=4)|4(?=3)|3(?=2)|2(?=1)|1(?=0)){4}\d-(([\d]){1,}([\d]){1,})\1{1,}-((\d){2,})\d\1{1}-(19|20)[\d]{2}((1[0,1,2])|(0[1,2,3,4,5,6,7,8,9]))((3[0,11])|(2[0,1,2,3,4,5,6,7,8,9])|(1[0,1,2,3,4,5,6,7,8,9])|(0[0,1,2,3,4,5,6,7,8,9]))</textarea>
				</td>
			</tr>
			<tr><td colspan="2"><asp:Button ID="button" runat="server" Text="确定修改" onclick="Button2_Click" CssClass="put" Width="100"/></td></tr>
		  </table>
    </div>
    </form>
</body>
</html>
