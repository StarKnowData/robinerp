<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="UserGameMoneyLog.aspx.cs" Inherits="Admin_Users_UserGameMoneyLog" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title></title>
	<link href="../css/Inc_style.css" rel="stylesheet" type="text/css">

	<script src="/Public/Js/jquery.js"></script>

	<script src="/Public/Js/public.js"></script>

	<script src="/Public/Js/DatePicker/WdatePicker.js"></script>

</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" class="admin_table2">
			<tr>
				<td align="center" bgcolor="F2F8FF" class="title_03">
					<strong>玩家游戏金币输赢统计</strong></td>
			</tr>
			<tr>
				<td align="left" bgcolor="F2F8FF" class="title_05">
					按时间段，从：<input type="text" id="txtBeginDate" name="txtBeginDate" class="put" style="width:125px;" onfocus="WdatePicker({maxDate:'#F{$dp.$D(\'txtEndDate\')}',dateFmt:'yyyy-MM-dd HH:mm:ss'})" />&nbsp;到&nbsp;<input type="text" id="txtEndDate" name="txtEndDate" style="width:125px;" class="put" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd HH:mm:ss'})" />
					<input type="text" id="txtUserName" name="txtUserName" style="width:150px;" class="put" />&nbsp;
					<!--<input type="text" id="txtAdminName" name="txtAdminName" style="width:100px;" class="put" />-->&nbsp;
					<select id="stType">				
						<option value="byid">根据用户ID</option>
						<option value="byname">根据用户名</option>
					</select>
					<select id="stUserType">
					<option value="0">请选择玩家类别</option>
					<option value="1"  selected="selected">玩家</option>
					<option value="2">机器人</option>
					</select>
					 
					<input type="button" value=" 搜 索 " class="put" onclick="OnSearch();" />&nbsp;
					<input type="button" class="put" value=" 刷 新 " onclick="RefreshMe();" />&nbsp;
					<script type="text/javascript">
					    var dkey = "请输入用户名或用户ID";
					    var o_un = $("#txtUserName");
					    var o_bd = $("#txtBeginDate");
					    var o_ed = $("#txtEndDate");
					    var o_ty = $("#stType");
					    var o_uty = $("#stUserType");


					    var r_unk = decodeURIComponent(GetRequest("un", ""));
					    var r_bdk = decodeURIComponent(GetRequest("bd", ""));
					    var r_edk = decodeURIComponent(GetRequest("ed", ""));
					    var r_tyk = decodeURIComponent(GetRequest("ty", ""));
					    var r_utyk = decodeURIComponent(GetRequest("uty", ""));


					    if (r_bdk != "") {
					        o_bd.val(r_bdk);
					    }

					    if (r_edk != "") {
					        o_ed.val(r_edk);
					    }
					    if (r_tyk != "") {
					        DropSetByValue("stType", r_tyk);
					    }
					    if (r_utyk != "") {

					        DropSetByValue("stUserType", r_utyk);
					    }
					    if (r_unk == "") {
					        o_un.css("color", "gray");
					        o_un.val(dkey);
					    }

					    else {
					        o_un.css("color", "black");
					        o_un.val(r_unk);
					    }
					    o_un.focus(function() { if (o_un.val().Trim() == dkey) { o_un.css("color", "black"); o_un.val(""); } });
					    o_un.blur(function() { if (o_un.val().Trim() == "") { o_un.css("color", "gray"); o_un.val(dkey); } });

					    function OnSearch() {
					        var url = location.href;
					        //							if((o_un.val().Trim() == dkey || o_un.val().Trim() == "") && o_bd.val().Trim() == "" && o_ed.val().Trim() == "")
					        //							{
					        //								alert("请先输入要搜索的用户或管理员名称，或选择操作起止时间。");
					        //								return;
					        //							}
					        url = SetUrlParam(url, "ty=" + encodeURIComponent(o_ty.val().Trim()));
					        if (o_un.val().Trim() != dkey && o_un.val().Trim() != "") {
					            url = SetUrlParam(url, "un=" + encodeURIComponent(o_un.val().Trim()));
					        }
					        if (o_bd.val().Trim() != "") {
					            url = SetUrlParam(url, "bd=" + encodeURIComponent(o_bd.val().Trim()));
					        }
					        if (o_ed.val().Trim() != "") {
					            url = SetUrlParam(url, "ed=" + encodeURIComponent(o_ed.val().Trim()));
					        }
					        if (o_uty.val().Trim() != "") {
					            url = SetUrlParam(url, "uty=" + encodeURIComponent(o_uty.val().Trim()));
					        }

					        LocationTo(url);
					    }
					</script>

				</td>
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
				<th>
					用户ID</th>
				<th>
					用户名</th>
				<th>
					 输赢金币数</th>
				<th>
					输赢状态</th>
				<%--<th>
					操作后金币数</th>
				<th>
					类型</th>
				<th>
					操作时间</th>
				<th>
					备注</th>--%>
			</tr>
			<asp:Repeater ID="rptDataList" runat="server">
				<ItemTemplate>
					<tr>
						<td align="center" style="width:5%;">
							<%# Eval("UserID") %>
						</td>
						<td align="center" style="width:10%;">
							<%# Eval("UserName") %>
						</td>
						<td align="center" style="width:10%;">
							<%# Eval("SumMoney") %>
						</td>
						<td align="center" style="width:10%;">
							<%#Convert.ToInt64(Eval("SumMoney").ToString()) > 0 ? "赢" :Convert.ToInt64(Eval("SumMoney").ToString())==0?"平": "输"%>
						</td>
						<%--<td align="center" style="width:10%;">
							<%# Convert.ToInt64( Eval( "StartMoney" ) ) + Convert.ToInt64( Eval( "ChangeMoney" ) )%>
						</td>
						<td align="center" style="width:15%;">
							<%# (Library.MoneyChangeType)Convert.ToInt32(Eval("ChangeType"))%>
						</td>
						<td align="center" style="width:10%;">
							<%# Eval("DateTime")%>
						</td>
						<td style="width:30%;">
							<%# Eval("Remark")%>
						</td>--%>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
			<tr>
				<td colspan="4">
				总变化数：<%=SumMoney %>
					<div id="page_link" class="page_link">
					 
						<webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="%CurrentPageIndex%/%PageCount%，每页%PageSize%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" UrlPaging="True" AlwaysShow="True" PageSize="20">
						</webdiyer:AspNetPager>
					</div>
					<asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='10'>暂无记录...</td></tr>"></asp:Literal>
				</td>
			</tr>
			</table>		
	</form>
</body>
</html>
