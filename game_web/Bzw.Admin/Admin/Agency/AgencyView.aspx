<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_AgencyView" Codebehind="AgencyView.aspx.cs" %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head2" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>代理商信息</title>
    <link href="../Css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/public.js"></script>
</head>
<body>
    <form id="form2" runat="server">     
        <table width="100%" border="0" align="center" cellpadding="5" cellspacing="0" bgcolor="F2F8FF" class="admin_table2" style="border-collapse: collapse; border: 1px solid;">
			<tr>
				<th align="left">
					代理商信息</th>
			</tr>
		</table>
		<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
	        <tr>
	            <td>
					代理帐号：<input type="text" id="txtKey" name="txtKey" maxlength="20" />
					&nbsp;真实姓名：<input type="text" id="txtTrueName" name="txtTrueName" maxlength="20" />

					&nbsp;<input type="button" value=" 搜 索 " onclick="OnSearch();" />&nbsp;<input type="button" onclick="RefreshMe();" value=" 刷 新 " />
					<script type="text/javascript">
						var o = $("#txtKey");
						var tn = $("#txtTrueName");

						var pkey = "请输入玩家帐号";
						
						//从地址的查询参数中赋值						
						o.val(decodeURIComponent(GetRequest("key",""))); //o.val(decodeURIComponent(GetRequest("key",pkey)));
						tn.val(decodeURIComponent(GetRequest("tn","")));

						
						//搜索按钮
						function OnSearch()
						{
						    if(o.val().Trim() != "" || tn.val().Trim() != "" )
							{
								var url = SetUrlParam(location.href,"key="+ encodeURIComponent(o.val().Trim()) );
								LocationTo(SetUrlParam(url,"tn=" + encodeURIComponent(tn.val().Trim())));
								return;
							}
							alert("请先输入您要搜索的代理商帐号、真实姓名。");
						}
					</script>
                    
	            </td>
	        </tr>
		</table>
        <table width="100%" border="1" align="center" cellpadding="1" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
           <tr align="center">
                <th>
                    代理ID</th>
                <th>
                    代理帐号</th>
                <th>
                    真实姓名</th>
                <th>
                    帐号金币</th>
                <th>
                    注册时间</th>
                <th>
                    直属玩家数</th>
                <th>
                    直属代理数</th>
                <th>
                    门票比例</th>
                <th>
                    上级代理</th>
                <th>
                    未结算门票</th>
                <th>
                    状态</th>
                <th width="18%">
                    操作</th>
            </tr>
            <asp:Repeater ID="rpList" runat="server">
                <ItemTemplate>
                    <%# ( ( Container.ItemIndex + 1 ) % 2 ) == 0 ? "  <tr align='center' bgcolor='#F7F8F8' height='25px' onmouseout=\"this.style.backgroundColor='#F7F8F8'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >" : "  <tr align='center' bgcolor='#ffffff' height='25px' onmouseout=\"this.style.backgroundColor='#ffffff'\" onmouseover=\"this.style.backgroundColor='#E1E1E1'\" >"%>
                        <td><%# Eval("AgencyID")%></td>
                        <td><%# Eval("AgencyName")%></td>
                        <td><%# Eval("TrueName")%></td>
                        <td><%# UiCommon.StringConfig.MoneyChu100(Eval("Account"))%></td>
                        <td><%# Eval("RegisterTime")%></td>
                        <td><%# Eval("MyDownPlayerCount")%></td>
                        <td><%# Eval("MyDownAgencyCount")%></td>
                        <td><%# Eval("SpareValueRate")%>%</td>
						<td><%# Eval("ParentAgencyName")%></td>
						<td><%# UiCommon.StringConfig.MoneyChu100(Eval("NotBaMoney"))%></td>
						<td><font style='color: <%# Convert.ToInt32(Eval("IsTaboo")) ==1?"black":"red"%>'>
									<%# Convert.ToInt32(Eval("IsTaboo")) ==1? "正常":"禁用"%>
								</font>
						</td>
                        <td>
                           <a href="<%# "LinkCurrentDownAgency.aspx?AgencyName=" + Eval("AgencyName")+"&url="+ Utility.Common.CurrentPageUrl%>">查看推广</a>
                           &nbsp;|&nbsp;<a href="<%# "AgencyView.aspx?action=zhstate&id=" + Eval("AgencyID")+ "&istaboo="+ Eval("IsTaboo") + "&url="+Utility.Common.CurrentPageUrl%>"><%# Convert.ToInt32(Eval("IsTaboo")) ==1? "停用帐号":"启用帐号"%></a>
                           <br /><a href="<%# "AgencyDetailInfo.aspx?agencyid="+Eval("AgencyID")+"&url="+ Utility.Common.CurrentPageUrl %>">修改资料</a>
						    &nbsp;|&nbsp;<a href="<%# "AgencyMoneyModify.aspx?agencyName=" + Eval("AgencyName")+"&url="+ Utility.Common.CurrentPageUrl%>">修改金币</a>
						    <br /><a href="<%# "AgencyView.aspx?action=balance&id="+Eval("AgencyID")+"&url="+ Utility.Common.CurrentPageUrl %> " onclick='return confirm("确定要进行结算吗？");' title='点击进行结算'>门票结算</a>
						    &nbsp;|&nbsp;<a href="<%# "MyEarningMoney.aspx?id="+Eval("AgencyID")+"&n="+Eval("AgencyName")+"&url="+ Utility.Common.CurrentPageUrl %>">收益报表</a>
						    <br /><a href="<%# "AgencyPopedomSet.aspx?agencyName="+ Server.UrlEncode( Eval("AgencyName").ToString() ) +"&url="+ Utility.Common.CurrentPageUrl %>">权限设置</a>
						    <%# Convert.ToInt32(Eval("ParentAgencyID")) == 0 ? "" : "&nbsp;|&nbsp;<a href=\"AgencyView.aspx?action=del&id=" + Eval("AgencyID") + "&url=" + Utility.Common.CurrentPageUrl + "\" onclick=\"javascript:return confirm('你确定要删除这个代理商帐号吗？删除后将不能恢复!!');\">删除帐号</a>"%>
						    
						    <!--a href="<%# "../../Agency/UserManager/AgencyWasteBook.aspx?uid="+Eval("AgencyID")+"&plist=1&url="+ Utility.Common.CurrentPageUrl %>">收支流水账</a-->
                        </td>
                    </tr>
                </ItemTemplate>
            </asp:Repeater>
            <asp:Literal runat="server" ID="NoDataList" Text="<tr><td colspan='17' align='center' bgcolor='#ffffff'>暂无数据...</td></tr>"></asp:Literal>
        </table>
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7" bgcolor="F2F8FF" class="admin_table">
			<tr>
			    <td style="display:none;"><asp:Button ID="Button1" runat="server" Text="批量删除" Style="background-color:lightgrey" OnClick="btnBatch_Click" OnClientClick="return GetSelectedValue()" /></td>
				<td align="left">
					<div id="page_link" class="page_link">
						<webdiyer:AspNetPager PageSize="20" UrlPaging="True" runat="server" ID="WebPager1" CustomInfoHTML="%CurrentPageIndex%/%PageCount%，每页%PageSize%条，共%RecordCount%条" FirstPageText="首页" LastPageText="尾页" NextPageText="下一页" NumericButtonCount="5" PageIndexBoxType="DropDownList" PrevPageText="上一页" ShowCustomInfoSection="Left" ShowPageIndexBox="Always" SubmitButtonText="Go" TextAfterPageIndexBox="" TextBeforePageIndexBox="" AlwaysShow="True">
						</webdiyer:AspNetPager>
					</div>
				</td>
			</tr>
		</table>
    </form>
    <script type="text/javascript">
    function SelectAll(obj)
    {
         var theTable= obj.parentElement.parentElement.parentElement;
         var i ;
         var j = obj.parentElement.cellIndex;
         for(i=0;i<theTable.rows.length;i++)
         {
            var objCheckBox = theTable.rows[i].cells[j].firstChild;
            if(objCheckBox.checked!=null)
            {
                objCheckBox.checked = obj.checked;
            }            
         }             
    }
    function GetSelectedValue()
    {
        var selectedlist = new Array();
        var selectedCheck =document.getElementsByName("cbxCheck");
        var hdfSelected =document.getElementById("hdfSelected");
        for(var i=0;i<selectedCheck.length;i++ )
        {
            if(selectedCheck[i].checked)
            {
                selectedlist.push(selectedCheck[i].value);
            }
        }
        if(selectedlist.length<=0)
        {
            alert("至少选择一条");
            return false;
        }
        hdfSelected.value = selectedlist.toString();
        return true;
    }
	</script>
</body>
</html>
