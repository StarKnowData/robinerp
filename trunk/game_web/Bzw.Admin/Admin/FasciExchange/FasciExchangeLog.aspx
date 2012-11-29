<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="FasciExchangeLog.aspx.cs" Inherits="Admin_FasciExchange_FasciExchangeLog" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <title></title>
    <script src="/Public/Js/jquery.js" type="text/javascript"></script>
	<script src="/Public/Js/DatePicker/WdatePicker.js"></script>
	<script src="/Public/Js/public.js" type="text/javascript"></script> 
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<style type="text/css">
	 
		body {
	background-color: #FFFFFF;
	margin-top: 0px;
}
	</style>
</head>
<body>
    <form id="form1" runat="server">
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" class="admin_table2" >
			 
		 <tr>
				<td class="title_03" colspan="11" bgcolor="F2F8FF">
					<strong><font color="red">	魅力值兑换记录</font></strong></td>
			</tr>
		 <tr>
				<td style="height: 29px" bgcolor="F2F8FF" class="title_05">玩家帐号：<input type="text" id="txtKey" name="txtKey" maxlength="50" style="width: 99px" class="put" />
				 
			&nbsp; 按时段：从
			&nbsp;<input type="text" readonly="readonly" id="txtBeginDate" name="txtBeginDate" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd',maxDate:'#F{$dp.$D(\'txtEndDate\')}'});" size="8" class="put"/>
			&nbsp;到&nbsp;<input type="text" readonly="readonly" id="txtEndDate" name="txtEndDate" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'});" size="8" class="put" />
			&nbsp;<input type="button" value="搜 索" onclick="OnSearch();" class="put" />
			&nbsp;&nbsp; &nbsp;

					<script type="text/javascript" >
					    var bd = $("#txtBeginDate");  //变量和控件ID绑定  zhoushenghua
					    var ed = $("#txtEndDate");
					    var o = $("#txtKey");
					    var pkey = "请输入玩家帐号";


					    bd.val(decodeURIComponent(GetRequest("bd", ""))); //获取URL中传过来的值 zhoushenghua
					    ed.val(decodeURIComponent(GetRequest("ed", "")));
					    o.val(decodeURIComponent(GetRequest("key", pkey)));


					    if (GetRequest("key", "") == "") {
					        o.css("color", "gray");
					    }
					    else {
					        o.css("color", "black")
					    }
					    o.focus(function() { if (o.val().Trim() == pkey) { o.css("color", "black"); o.val(""); } });
					    o.blur(function() { if (o.val().Trim() == "") { o.css("color", "gray"); o.val(pkey); } });

					    //搜索按钮
					    function OnSearch() {

					        if (bd.val().Trim() != "" || ed.val().Trim() != "" || (o.val().Trim() != pkey && o.val().Trim() != "")) {
					            var url = SetUrlParam(location.href, "key=" + ((o.val().Trim() != pkey && o.val().Trim() != "") ? encodeURIComponent(o.val().Trim()) : ""));
					            url = SetUrlParam(url, "bd=" + encodeURIComponent(bd.val().Trim()));

					            LocationTo(SetUrlParam(url, "ed=" + encodeURIComponent(ed.val().Trim())));
					            return;
					        }
					        alert("请先输入您要搜索的玩家帐号，或选择要查看的时段。");
					    }
							</script>

				<input type="button" onclick="RefreshMe();" value="刷 新" /></td>
			</tr></table>
				<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td style="height: 5px">
				</td>
			</tr>
		</table>
			<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
						<tr> <th>
						记录ID</th>
							 
								<th>奖品名称</th>
							 
                            <th>
								用户ID
								</th>
								<th>用户名</th>
								<th>道具数</th>
								<th>魅力值</th>
								<th>兑换时间</th>
								<th>兑换状态</th>
							  
				 
						</tr>
						<asp:Repeater ID="rptDataList" runat="server">
							<ItemTemplate>
								<tr>
								<td><%=tableids = tableids+1%></td>
								<td><%#Eval("PropName") %></td>
								<td><%#Eval("UserID") %></td>
								<td><%#Eval("UserName") %></td>
								<td><%# Eval("PropCount")%></td> 
								<td><%#Eval("CharmValue") %></td>
								<td><%#Eval("InputDate")%></td>
								<td><%#Eval("Status").ToString()=="1"?"已兑换":"<a href='FasciExchangeLog.aspx?act=edit&id="+Eval("Log_ID")+"' onclick='javascript:return confirm(\"确定要更新兑换记录状态为已处理吗？\");'>未处理</a>" %></td>
								 		
								</tr>
							</ItemTemplate>
						</asp:Repeater>
						<asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='15'>没有记录...</td></tr>"></asp:Literal>
					<tr>
				<td colspan='11' align='right'>
					<div id="page_link" class="page_link">
						<webdiyer:AspNetPager runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Never" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" UrlPaging="True" AlwaysShow="True" PageSize="20">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
				</table>	 
		 
    </form>
</body>
</html>
