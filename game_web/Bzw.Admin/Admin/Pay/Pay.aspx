<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Pay_Pay" Codebehind="Pay.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
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

	<script type="text/javascript" src="/Public/Js/jquery.js"></script>

	<script type="text/javascript" src="/Public/Js/public.js"></script>

	<script type="text/javascript" src="/Public/Js/DatePicker/WdatePicker.js"></script>

</head>
<body>
	<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table2">
		<tr>
			<td class="title_03" colspan="2">
				<strong>点卡充值管理</strong></td>
		</tr>
		<tr>
			<td class="title_05">
				<a href="Pay.aspx?pay=1">已充值点卡列表</a><br />
				<a href="Pay.aspx?pay=0">未充值点卡列表</a></td>
			<td class="title_05" align="right">
				<% if( typepay == "1" )
	   { %>
				时间从：<input type="text" id="txtBeginDate" class="put" onfocus="WdatePicker({maxDate:'#F{$dp.$D(\'txtEndDate\')}',dateFmt:'yyyy-MM-dd'})" />&nbsp; 
				到：<input type="text" id="txtEndDate" class="put" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'})" />&nbsp;
				<input type="text" id="txtUserName" class="put" />&nbsp;
				<input type="button" value=" 搜 索 " class="put" onclick="OnSearch();" />&nbsp;
				<input type="button" class="put" value=" 刷 新 " onclick="RefreshMe();" /><br />

				<script>
						var o = $("#txtUserName");
						var bd = $("#txtBeginDate");
						var ed = $("#txtEndDate");
						var pkey = "请输入充值用户名";
						var uk = decodeURIComponent(GetRequest("un",""));
						var ubd = decodeURIComponent(GetRequest("bd",""));
						var ued = decodeURIComponent(GetRequest("ed",""));
						if(uk == "")
						{
							o.val(pkey);
							o.css("color","gray");
						}
						else
						{
							o.val(uk);
							o.css("color","black");
						}
						if(ubd != "")
							bd.val(ubd);
						if(ued != "")
							ed.val(ued);
						o.focus(function(){if(o.val().Trim() == pkey){o.val("");o.css("color","black");}});
						o.blur(function(){if(o.val().Trim() == ""){o.val(pkey);o.css("color","gray");}});
						//搜索事件
						function OnSearch()
						{
							if((o.val().Trim() == "" || o.val().Trim() == pkey) && bd.val().Trim() == "" && ed.val().Trim() == "")
							{
								alert("请先输入充值用户名或起止时间再搜索。");
								return;
							}
							var url = location.href;
							if(o.val().Trim() != "" && o.val().Trim() != pkey)
								url = SetUrlParam(url, "un=" + encodeURIComponent(o.val().Trim()));
							if(bd.val().Trim() != "")
								url = SetUrlParam(url,"bd=" + encodeURIComponent(bd.val().Trim()));
							if(ed.val().Trim() != "")
								url = SetUrlParam(url,"ed=" + encodeURIComponent(ed.val().Trim()));
							LocationTo(url);
						}
				</script>

				<%}
	  else
	  {
				%>
				&nbsp;<%
						  } %>
						  <asp:Literal runat="server" ID="ltSumInfo"></asp:Literal>
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
			<td width="13%" align="center" valign="top">
				<table width="100%" border="0" align="center" cellpadding="5" cellspacing="0">
					<tr>
						<td align="center">
							<a href='Pay.aspx?pay=<%=typepay %>'><b>
								<%=typepay.ToLower() =="1" ? "<font color=\"red\">已充值卡列表</font>" :"未充值卡列表" %>
							</b></a>
						</td>
					</tr>
					<asp:Repeater runat="server" ID="rptMoneyList">
						<ItemTemplate>
							<tr>
								<td align="center">
									&nbsp;&nbsp;<%# "<a href='Pay.aspx?" + ( string.IsNullOrEmpty( typepay ) ? "" : "pay=" + typepay + "&" ) + "money=" + Eval( "Money" ).ToString() + (!string.IsNullOrEmpty(bd) && BCST.Common.CommonManager.String.IsDateTime(bd) ? "&bd=" + bd : "") + (!string.IsNullOrEmpty(ed) && BCST.Common.CommonManager.String.IsDateTime(ed) ? "&ed=" + ed : "") + (string.IsNullOrEmpty(un) ? "" : "&un=" + un) + "'>" + Eval( "Money" ).ToString() + "元面值</a>"%>
								</td>
							</tr>
						</ItemTemplate>
					</asp:Repeater>
				</table>
			</td>
			<td width="87%" align="center" valign="top">
				<form action="" method="get" name="newsform">
					<asp:Repeater ID="rptDataList" runat="server">
						<HeaderTemplate>
							<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" style="border-collapse: collapse">
								<tr>
								<td>全选<input name="cbxAllCheck" type="checkbox" onclick="SelectAll(this)" /></td>
									<td width="5%">
										序号</td>
									<td width="15%">
										卡号</td>
									<td width="10%">
										密码</td>
									<td width="5%">
										面值</td>
									<td width="10%">
										充值者</td>
									<td width="10%">
										充值IP</td>
										<td width="6%">
										充值前金额</td>
										<td width="10%">
										充值后金额</td>
									<td width="10%">
										充值时间</td>
									<td width="8%">
										属性</td>
									<td width="6%">
										删除</td>
								</tr>
						</HeaderTemplate>
						<ItemTemplate>
							<tr>
									 <td><input name="cbxCheck" type="checkbox" value="<%#Eval("ID")%>" /></td>
								<td align='center'>
									<%# ( Container.ItemIndex + 1 ) + anpPageIndex.PageSize * ( anpPageIndex.CurrentPageIndex - 1 ) %>
								</td>
						
								<td align='left'>
									<%# Eval("num") %>
								</td>
								<td align='left'>
									<%# Eval("pwd") %>
								</td>
								<td>
									<%# Eval("jine") %>
								</td>
								<td>
									<%# Eval("player") %>
								</td>
								<td>
									<%# Eval("ip") %>
								</td>
								<td>
									<%# Eval("BMoney") %>
								</td>
								<td>
									<%# Eval("AMoney") %>
								</td>
								<td>
									<%# Eval("tm") %>
								</td>
								<td>
									<%# Eval("pay").ToString().ToLower() == "true" ? "<font color=\"red\">充 值</font>" : "未充值"%>
								</td>
								<td>
									<a href="PayDel.aspx?id=<%# Eval("ID") %>&url=<%=Server.UrlEncode(Request.Url.AbsoluteUri) %>" onclick="javascript:return confirm('您确定要删除当前记录吗？删除后将不能恢复!!');">删除</a></td>
							</tr>
						</ItemTemplate>
					</asp:Repeater>
					<asp:Label ID="ltNonData" runat="server" Text="暂无任何数据！"></asp:Label>
					<tr>
					 
						<td colspan="7" align="right">
							<input type="button" value="批量删除" onclick="return AllDel()" class="put" /> 
					<input type="button" value="删除全部未充值点卡" class="put" onclick="return NoUseDel()" />
					<input type="button"  value="删除全部已充值点卡" class="put" onclick="return UseDel()" />
							<div id="page_link" class="page_link">
								<webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Never" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" UrlPaging="True" AlwaysShow="True" PageSize="20">
								</webdiyer:AspNetPager>
							</div>
						</td>
					</tr>
				</form>
			</td>
		</tr>
	</table>
	<script type="text/javascript" language="javascript"> 
	    function SelectAll(obj) {
	        var theTable = obj.parentElement.parentElement.parentElement;
	        var i;
	        var j = obj.parentElement.cellIndex;
	        for (i = 0; i < theTable.rows.length; i++) {
	            var objCheckBox = theTable.rows[i].cells[j].firstChild;
	            if (objCheckBox.checked != null) {
	                objCheckBox.checked = obj.checked;
	            }
	        }
	    }
	    var selectedlist = new Array();
	    function GetSelectedValue() {
	      
	        var selectedCheck = document.getElementsByName("cbxCheck");
	        //var hdfSelected =document.getElementById("hdfSelected");
	        for (var i = 0; i < selectedCheck.length; i++) {
	            if (selectedCheck[i].checked) {
	                selectedlist.push(selectedCheck[i].value);
	            }
	        }
	        if (selectedlist.length <= 0) {
	            alert("至少选择一条记录");
	            return false;
	        } 
	        //hdfSelected.value = selectedlist.toString();
	      
	    }
	    function AllDel() {
	        GetSelectedValue();
	        if (confirm("您确定要删除所选的记录吗？删除后将不能恢复!!")) {
	            alert(location.href + '&batchaction=batchdel&uid=' + selectedlist.toString());
	            document.location.href =location.href+ '&batchaction=batchdel&uid=' + selectedlist.toString();
	            
	        }
	        return true;
	    }
	    function NoUseDel() {
	        location.href = location.href + "&batchaction=nousedel";
	        return true ;
	    }
	    function UseDel() {
	        location.href = location.href + "&batchaction=usedel";
	        return true;
	    }
	</script>
</body>
</html>
