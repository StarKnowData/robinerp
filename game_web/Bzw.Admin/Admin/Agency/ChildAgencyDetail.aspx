<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_ChildAgencyDetail" Codebehind="ChildAgencyDetail.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<title>子代理查看</title>
	<style type="text/css">
	*{font-family:Arial,'宋体'; font-size:12px;}
	</style>
</head>
<body style="font-size: 12px; margin-top: 20px;">
	<form id="form1" runat="server">
		<% if(info != null){ %>
		<table cellpadding="3" align="center" style="border-collapse: collapse;" border="0">
			<tr>
				<th align="right">
					代理帐号：</th>
				<td>
					<%=info["AgencyName"].ToString() %>
				</td>
			</tr>
			<tr>
				<th align="right">
					真实姓名：</th>
				<td>
					<%=info["TrueName"].ToString() %>
				</td>
			</tr>
			<tr>
				<th align="right">
					手机号码：</th>
				<td>
					<%=info["MobilPhone"].ToString() %>
				</td>
			</tr>
			<tr>
				<th align="right">
					固定电话：</th>
				<td>
					<%=info["Phone"].ToString() %>
				</td>
			</tr>
			<tr>
				<th align="right">
					联系地址：</th>
				<td>
					<%=info["Address"].ToString() %>
				</td>
			</tr>
			<tr>
				<th align="right">
					邮编：</th>
				<td>
					<%=info["PostalCode"].ToString() %>
				</td>
			</tr>
			<tr>
				<th align="right">
					QQ：</th>
				<td>
					<%=info["QQNum"].ToString() %>
				</td>
			</tr>
			<tr>
				<th align="right">
					邮箱：</th>
				<td>
					<%=info["Email"].ToString() %>
				</td>
			</tr>
			<tr>
				<th align="right">
					帐号<%=UiCommon.StringConfig.MoneyName %>：</th>
				<td>
					<%=UiCommon.StringConfig.MoneyChu100( info["Account"]) %>
				</td>
			</tr>
			<tr>
				<th align="right">
					门票比例：</th>
				<td>
					<%=info["SpareValue"].ToString()%>%
				</td>
			</tr>
			<tr>
				<th align="right">
					注册时间：</th>
				<td>
					<%=string.IsNullOrEmpty( info["RegisterTime"].ToString() ) ? "" :( (DateTime)info["RegisterTime"] ).ToString( "yyyy-MM-dd dddd" )%>
				</td>
			</tr>
			<tr>
				<th align="right">
					资料修改时间：</th>
				<td>
					<%=string.IsNullOrEmpty( info["UpdateTime"].ToString() ) ? "" :( (DateTime)info["UpdateTime"] ).ToString( "yyyy-MM-dd dddd" )%>
				</td>
			</tr>
			<tr>
				<th align="right">
					最后登录时间：</th>
				<td>
					<%=string.IsNullOrEmpty( info["LastLoginDateTime"].ToString() ) ? "" :( (DateTime)info["LastLoginDateTime"] ).ToString( "yyyy-MM-dd dddd" )%>
				</td>
			</tr>
			<tr>
				<th align="right">
					最后登录IP：</th>
				<td>
					<%=info["LastLoginIP"].ToString()%>
				</td>
			</tr>
			<tr>
				<th align="right">
					二级域名：</th>
				<td>
					<%=info["DomainUrl"].ToString()%>
				</td>
			</tr>
			<tr>
				<th align="right">
					帐号状态：</th>
				<td>
					<%=(byte)info["IsTaboo"] == 1 ? "启用" : "<span style='color:red;'>禁用</span>"%>
				</td>
			</tr>
			<%--<tr>
				<th align="right">
					收款方式：</th>
				<td>
					<%=( (long)info["ActualSpareValue"] == 1 ) ? "银行转帐" : ( ( (long)info["ActualSpareValue"] == 2 ) ? "支付宝" : "财付通" )%>
				</td>
			</tr>
			<tr>
				<th align="right" valign="top">
					收款帐号：</th>
				<td>
					<%=( (long)info["ActualSpareValue"] == 1 ) ? "银行帐号：" + info["AccountNO"].ToString() + "<br />户名：" + info["AccountName"].ToString() + "<br />开户行：" + info["BankName"].ToString() + "<br />开户行地址：" + info["BankAddress"].ToString()
					: ( ( (long)info["ActualSpareValue"] == 2 ) ? info["PayorNo"].ToString() : info["TenpayNo"].ToString() )%>
				</td>
			</tr>--%>
		</table>
		<%} %>
		<div style="font-size: 1px; text-align: center; margin-top: 20px;">
			<input type="button" value="返回" onclick="history.back();" />
		</div>
	</form>
</body>
</html>
