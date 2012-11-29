<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Books_book" Codebehind="book.aspx.cs" %>

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
</head>
<body>
	<form id="form1" runat="server">
		<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
				<td class="title_03" colspan="11">
					<strong>反馈留言显示</strong></td>
			</tr>
			<tr>
				<td>
					序号/全选<input name="cbxAllCheck" type="checkbox" onclick="SelectAll(this)" /></td>
				<td>
					标题</td>
				<td>
					留言人</td>
				<td>
					留言人Email</td>
				<td>
					留言时间</td>
				<td>
					审核
				</td>
				<td>
					操作</td>
			</tr>
			<asp:Repeater ID="BookList" runat="server">
				<ItemTemplate>
					<tr>
						<td>
							<input name="cbxCheck" type="checkbox" value="<%#Eval("MsgID")%>" /><%=TableID=TableID+1 %> 
						</td>
						<td>
							<%# Eval("MsgTitle") %>
						</td>
						<td>
							<%# Eval("MsgName") %>
						</td>
						<td>
							<%# Eval("Msgmail") %>
						</td>
						<td>
							<%# Eval("MsgTime") %>
						</td>
						<td>
							<%# Eval("Ispass").ToString().ToLower() =="true" ? "<font color=\"red\">已审核</font>" :"未审核"%>
						</td>
						<td>
							<a href='BookInfo.aspx?id=<%# Eval("Msgid") %>'>回复</a>&nbsp;&nbsp;<a href='BookDel.aspx?id=<%# Eval("MsgID") %>' onclick="javascript:return confirm('您确定要删除该条留言吗？');">删除</a></td>
					</tr>
				</ItemTemplate>
			</asp:Repeater>
			<asp:Label ID="NoBookList" runat="server" Text="<tr><td colspan='12' align='center'>暂无任何记录！</td></tr>" Visible="false"></asp:Label>
			
		</table>
		
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7" bgcolor="F2F8FF" class="admin_table" style="margin-top:5px;">
			<tr>
			<td width="30%" >
			        <input type="button" value="批量删除" onclick="return AllDel()" class="put" />
			    </td>
				<td align="left">
					<webdiyer:AspNetPager PageSize="10" ID="anpPageIndex" runat="server" AlwaysShow="True" CustomInfoHTML="第%CurrentPageIndex%页，共%PageCount%页；每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" UrlPaging="True">
					</webdiyer:AspNetPager>
				</td>
			</tr>
		</table>
		
		
		
		<script type="text/javascript">
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
                
                //alert(location.href+ '&batchaction=batchdel&uid=' + selectedlist.toString());
	            document.location.href =location.href+ '?batchaction=batchdel&uid=' + selectedlist.toString();
	            
	        }
	        return true;
	    }
	   
	</script>
	
	</form>
</body>
</html>
