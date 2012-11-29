<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Users_Seach" Codebehind="Users_Seach.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<style type="text/css">
<!--
body {
	background-color: #F2F8FF;
	margin-top: 0px;
}
-->
</style>
</head>
<body>
	<form id="form1" action="User_List.aspx?act=post" method="get">
		<input type="hidden" name="act" id="act" value="post" />
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table2">
			<tr>
				<td class="title_03">
					<strong>会员管理</strong></td>
			</tr>
		</table>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td style="height: 5px">
				</td>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td class="title_03" colspan="19">
					<strong>高级查询</strong></td>
			</tr>
			<tr>
				<td align="center" colspan="5">
					<strong>注意：在记录很多的情况下搜索条件越多查询越慢，请尽量减少查询条件。</strong></td>
			</tr>
			<%--<tr>
				<td align="right">
					最多显示记录数：</td>
				<td colspan="2" align="left">
					<input name="d" type="text" id="d" value="0" class="put" />（为0代表全部）</td>
			</tr>--%>
			<tr>
				<td align="right">
					用户昵称：</td>
				<td colspan="2" align="left">
					<input name="n" type="text" id="n" class="put" />
					<input name="nr" type="checkbox" id="nr" value="1"  class="put" />
					用户昵称完全匹配</td>
			</tr>
			<tr>
				<td align="right">
					用户名：</td>
				<td colspan="2" align="left">
					<input name="u" type="text" id="u" class="put" />
					<input name="ur" type="checkbox" id="ur" value="1"  class="put" />
					用户名完全匹配</td>
			</tr>
			<tr>
				<td align="right">
					用户ID：</td>
				<td colspan="2" align="left">
					<input name="id" type="text" id="id" class="put" /></td>
			</tr>
			<tr>
				<td align="right">
					电话包含：</td>
				<td colspan="2" align="left">
					<input name="e" type="text" id="e" class="put" /></td>
			</tr>
			<tr>
			<td align="right">
					注册IP：</td>
				<td colspan="2" align="left">
					<input name="ip" type="text" id="ip" class="put" /></td>
			</tr>
			<tr>
			<td align="right">
					机器码：</td>
				<td colspan="2" align="left">
					<input name="mac" type="text" id="mac" class="put" /></td>
			</tr>
			<tr>
				<td> </td>
				<td align="left" colspan="2">
					<input name="i" type="checkbox" id="i" value="1" class="put" />限制登录大厅
				</td>
			</tr>
			<tr>
				<td colspan="3" align="left" bgcolor="#99cccc">
					<strong>特殊查询（注意： &lt;多于&gt; 或 &lt;少于&gt; 已默认包含 &lt;等于&gt;；条件留空则不使用此条件） </strong>
				</td>
			</tr>
			<tr>
				<td align="left" bgcolor="#f4f4f4">
					登录次数：
					<input name="lr" type="radio" value="1" checked="checked" class="put"/>
					多于
					<input type="radio" name="lr" value="0" class="put" />
					少于
					<input name="l" type="text" id="l" size="10" class="put" maxlength="9" />
					次</td>
				<td align="left" bgcolor="#f4f4f4" colspan="2" >
					用户金币数：
					<input name="mr" type="radio" value="1" checked="checked" class="put" />
					多于
					<input type="radio" name="mr" value="0" class="put" />
					少于
					<input name="m" type="text" id="m" size="18" class="put" maxlength="10" />
					金币
					</td>
			</tr>
			<tr>
				<td align="left" bgcolor="#f4f4f4">
					注册天数：
					<input name="rr" type="radio" value="1" checked="checked" class="put" />
					多于
					<input type="radio" name="rr" value="0" class="put" />
					少于
					<input name="r" type="text" id="r" size="10" class="put" maxlength="9" />
					天</td>
				<td align="left" bgcolor="#f4f4f4"  colspan="2" >
					最后登录：
					<input name="zr" type="radio" value="1" checked="checked" class="put" />
					多于
					<input type="radio" name="zr" value="0" class="put" />
					少于
					<input name="z" type="text" id="z" size="10" class="put" maxlength="9" />
					天
				</td>
			</tr>
			<tr>
				<td  align="left" bgcolor="#f4f4f4">
					交税数：
					<input name="tr" type="radio" value="1" checked="checked" class="put" />
					多于
					<input type="radio" name="tr" value="0" class="put" />
					少于
					<input name="t" type="text" id="t" size="10" class="put" maxlength="9" />金币
				</td>
				<td align="left" bgcolor="#f4f4f4" colspan="2">
				</td>
			</tr>
			<tr>
				<td align="right">
					&nbsp;</td>
				<td colspan="2" align="left">
					<input type="submit" name="submit" value=" 搜 索 " class="put" />
					<input type="hidden" name="action" value="search" />
					<input type="hidden" name="action2" value="search" />
					<input name="submit2" type="reset" value="清空重写" class="put" /></td>
			</tr>
		</table>
	</form>
</body>
</html>
