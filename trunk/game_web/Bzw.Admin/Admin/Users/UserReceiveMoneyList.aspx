<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="UserReceiveMoneyList.aspx.cs" Inherits="Admin_Users_UserReceiveMoneyList" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <title></title>
    <script src="/Public/Js/jquery.js" ></script>

	<script src="/Public/Js/public.js"></script>
 
	<script src="/Public/Js/DatePicker/WdatePicker.js"></script>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
 
</head>
<body>
    <form id="form1" runat="server">
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" class="admin_table2">
			 
				<tr>
				<td class="title_03" bgcolor="F2F8FF">
					<strong>查看玩家的领取金币记录</strong></td>
			</tr>
			<tr>
				<td style="height: 29px" bgcolor="F2F8FF" class="title_05">玩家帐号：<input type="text" id="txtKey" name="txtKey" maxlength="50" style="width: 99px" class="put" />
				 
			&nbsp; 按时段：从
			&nbsp;<input type="text" readonly="readonly" id="txtBeginDate" name="txtBeginDate" class="put" style="width:75px;" onfocus="WdatePicker({maxDate:'#F{$dp.$D(\'txtEndDate\')}',dateFmt:'yyyy-MM-dd'})" />
			&nbsp;到&nbsp;<input type="text" id="txtEndDate" name="txtEndDate" readonly="readonly" style="width:75px;" class="put" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'})" />
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
					<table width="100%"  border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" style="border-collapse: collapse;" >
						<tr>
						 <th>记录ID</th>
						 <th>玩家ID</th>
							<th>
								玩家</th>
								
							
							<th>
								领取金币数</th>
								<th>领取次数</th>
							 
                            <th>
								最后一次领取时间</th>
							 
				 
						</tr>
						<asp:Repeater ID="rptDataList" runat="server">
							<ItemTemplate>
								<tr><td>
								<%=rowid+=1 %></td>
									<td>
										<%# Eval("UserId")%>
										
									</td>
									<td>
										<%# Eval("UserName")%>
									</td>
									 

									<td><%# Eval("ReceiveMoneyCount")%></td>
								 	<td>
									 <%#Eval("ReceiveCount") %>
									</td>
									<td>
										<%#Eval("LastReceiveTime")%>
									</td>
								
                                     				
								</tr>
							</ItemTemplate>
						</asp:Repeater>
						<asp:Literal runat="server" ID="ltNonData" Text="<tr><td colspan='15'>没有记录...</td></tr>"></asp:Literal></table>
					<table width="100%">
						<tr>
							<td style="font-size: 12px; color: #0099ff; background-color: #e6feda;">
								<webdiyer:AspNetPager PageSize="20" runat="server" ID="anpPageIndex" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" AlwaysShow="True" PagingButtonSpacing="10px" UrlPaging="True">
								</webdiyer:AspNetPager>
							</td>
						</tr>
					</table>
		 
    </form>
</body>
</html>
