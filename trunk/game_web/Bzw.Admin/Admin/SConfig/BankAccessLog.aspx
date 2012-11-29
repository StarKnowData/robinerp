<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="BankAccessLog.aspx.cs" Inherits="Bzw.Web.Admin.SConfig.BankAccessLog" %>

<%@ Register  Namespace="Wuqi.Webdiyer" Assembly="Pager" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <title></title>
<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
<script type="text/javascript" src="/public/js/jquery.js"></script>
<script type="text/javascript" src="/public/js/public.js"></script>

</head>
<body>
    <form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
			bgcolor="F2F8FF" class="admin_table">
			<tr>
		<td colspan="10">
		<strong>用户存取记录管理</strong>
		</td>
		</tr>
			<tr>
				<td class="title_03" colspan="10">
				<input type="text" class="put" id="username" name="username" value=""/>
				&nbsp;用户名：<input id="typerd" name="typerd" type="radio" value="0" checked/>
				&nbsp;昵称：<input id="typerd" name="typerd" type="radio" value="1"/>
				<input type="button" class="put" onclick="Seach()" name="bt" id="bt" value="点击搜索"/>
				<input type="button" class="put" onclick="Clear()" name="bt" id="Button1" value="显示全部"/>			
				<script type="text/javascript">
					var fusername = GetRequest("username", "");
					var ftype = GetRequest("type","");
					$("#username").val(fusername);
					$("input[@name='typerd'][value='"+ftype+"']").attr("checked", true);
					//$("input[@name='typerd']:checked").val("0");
					//$("#username").attr("value", "测试是否能赋值");
					function Seach() {
						var types = $("input[@name='typerd']:checked").val();
						var o = $("#username");
						var username = o.val().Trim();
						if (username == "" || username.length <= 0) {
							alert("请输入搜索条件");
							return false;
						}
						var url = location.href;
						url = SetUrlParam(url, "type=" + types);
						url = SetUrlParam(url, "username=" + username);
						LocationTo(url);
					}
					function Clear() {
						location.href = "BankAccessLog.aspx";
					}
				</script>
				</td>
			</tr>
			<tr>
				<th>
					序号</th>
				<th>
					用户ID</th>
				<th>
					用户名</th>
				<th>
					用户昵称</th>
				<th>
					操作前银行金币数</th>
				<th>
					操作前钱包金币数</th>
				<th>
				   取出</th>
				<th>
					存入</th>
				<th>
					存取时间</th>
				<th>
					操作</th>
					
			</tr>
			<asp:Repeater ID="rptDataList" runat="server">
				<ItemTemplate>
				<tr align="center">
				<td>
				<%=number=number+1 %>
				</td>
				<td>
				<%#Eval("UserID") %>
				<td>
				<%#Eval("UserName") %>
				</td>
				<td>
				<%#Eval("NickName") %>
				</td>
				<td>
				<%#Eval("MoneyInBank") %>
				</td>
				<td>
				<%#Eval("MoneyInRoom") %>
				</td>
				<td>
				<%#Eval("InMoney") %>
				</td>
				<td>
				<%#Eval("OutMoney") %>
				</td>
				<td>
				<%#Eval("TimeEx") %>
				</td>
				<td>
				<a href="BankAccessLog.aspx?action=del&id=<%# Eval("ID")%>">删除</a>
				</td>
			</tr>
				</ItemTemplate>
			</asp:Repeater>
			<asp:Literal ID="ltNonData" runat="server" Text="暂无任何记录！" Visible="false"></asp:Literal><tr>
				<td colspan="10" align="right">
				<asp:Literal ID="Literal1" runat="server" Text="暂无任何记录！" Visible="false"></asp:Literal><tr>
				<td colspan="10" align="right">
					<webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条"
						firstpagetext="首页" lastpagetext="尾页" nextpagetext="下一页" numericbuttoncount="5"
						pageindexboxtype="DropDownList" prevpagetext="上一页" showcustominfosection="Left"
						showpageindexbox="Never" submitbuttontext="Go" textafterpageindexbox="" textbeforeageindexbox=""
						urlpaging="True" alwaysshow="True" pagesize="20">
					</webdiyer:AspNetPager>
				</td>
			</tr>
		</table>
    </form>
</body>
</html>
