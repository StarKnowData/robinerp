<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Users_LoginIp_seach" Codebehind="LoginIp_seach.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <title>无标题页</title>
            <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
<style type="text/css">
<!--
body {
	background-color: #ffffff;
	margin-top: 0px;
}
-->
</style>
<script type="text/javascript" src="/Public/Js/DatePicker/WdatePicker.js"></script>

</head>
<body>
    <form id="form1"  method="get" action="User_List.aspx?act2=post2"> 
    <input type="hidden" id="act2" name="act2" value ="post2" />
<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF"  class="admin_table2">
<tr>
<td class="title_03"><strong>会员管理</strong></td>
</tr>
<%--<tr>
<td class="title_05">
<a href="?action=search" >搜索用户</a>
<a href="?action=list" >所有用户列表</a>
<a href="?action=dayreg" >今日注册用户</a>
<a href="?action=24reg" >24小时内注册</a>
<a href="?action=24login" >24小时内登录</a>
<a href="?action=regip" style='color:red'>注册IP查询</a>
<a href="?action=regip100" >注册IP（TOP100）排行榜</a>
</td>
</tr>--%>
</table>

<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td height="5px"></td>
  </tr>
</table>
<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
<tr><td class="title_03"><strong>登录IP查询</strong></td></tr>
<tr><td align="left">
从：<input name="bt" type="text" value="<%= beginTime%>" szie="8" Class="put" onfocus="WdatePicker({maxDate:'#F{$dp.$D(\'et\')}',dateFmt:'yyyy-MM-dd'})"/>
到：<input name="et" type="text" value="<%=EndTime %>"  szie="8" Class="put" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'bt\')}',dateFmt:'yyyy-MM-dd'})"/>
IP：<input name="ip" type="text" value="127.0.0.1" size="15" Class="put" maxlength="15"/>
<input name="submit" type="submit" value=" 查询 " class="put"/>
<input type="hidden" name="action2" value="search" />
</td></tr>
</table>
    </form>
</body>
</html>
