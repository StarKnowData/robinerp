<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_BankTransLog"  %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<%@ Register TagName="WebLogBannister" TagPrefix="BZW" Src="~/Public/WebLogBannister.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>
		
	</title>
	
	  <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/common.js"></script>
	<script type="text/javascript" src="/Public/Js/DatePicker/WdatePicker.js"></script>
	<script type="text/javascript" src="/Public/Js/Global.js"></script>
	<script type="text/javascript" src="/Public/Js/jquery.js"></script>
	<script type="text/javascript" src="/Public/Js/public.js"></script>

</head>
<body>
	<form id="form1" runat="server">
    <div id="container">
<!--header-->
	  <WebTop:Control ID="webTopOne" runat="server" pageType="7"/> 
<!--content-->
 
      <div id="left">
		<Left:Control ID="LeftOne" runat="server" />
      </div>
      <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    转账记录</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 交易记录</p>
            </div>
            <div id="sub_nr" style="margin-top: 10px;">
 
						<!--Log Bannister-->
						<BZW:WebLogBannister ID="weblogbannister1" runat="server" />
						<script type="text/javascript">
							SetLogNav(4);
						</script>
						  <div class="rank_title"><%=type == 1 ? "转入记录" : "转出记录"%></div>
							<table width="100%" border="0" cellspacing="0" cellpadding="0" class="tab01">
								<tr>
									<td style="text-align: left; text-indent: 20px; padding: 0 0 3px 0;">
										<a id="tin" href="BankTransLog.aspx?type=1" >转入记录</a>&nbsp;
										<span><a id="tout" href="BankTransLog.aspx?type=0" style="">转出记录</a></span>
										<span style="margin-left: 50px; vertical-align: middle;">按时间段搜索：从&nbsp;<input type="text"
											id="txtBeginDate" size="8" class="in" style="vertical-align: middle;" onfocus="WdatePicker({maxDate:'#F{$dp.$D(\'txtEndDate\')}',dateFmt:'yyyy-MM-dd'})" />&nbsp;
											到：<input type="text" id="txtEndDate"  class="in" size="8" style="vertical-align: middle;" onfocus="WdatePicker({minDate:'#F{$dp.$D(\'txtBeginDate\')}',dateFmt:'yyyy-MM-dd'})" />&nbsp;
											<input type="button" value=" 搜索 " onclick="OnSearch();" class="but_011" />
											&nbsp;
											<input type="button"  value=" 刷 新 " onclick="RefreshMeDelParam('[?&]{1}bd=(\\d){4}-(\\d){2}-(\\d){2}&ed=(\\d){4}-(\\d){2}-(\\d){2}');" class="but_022" />
										</span>

										<script>
											var bd=$("#txtBeginDate");
											var ed=$("#txtEndDate");
											var tin=$("#tin");
											var tout=$("#tout");
											var ubd=decodeURIComponent(GetRequest("bd",""));
											var ued=decodeURIComponent(GetRequest("ed",""));
											var type=decodeURIComponent(GetRequest("type",""));
											if(ubd != "")
												bd.val(ubd);
											if(ued != "")
												ed.val(ued);
											
											if (type=="0"){
												tin.css({ "text-decoration":"underline", "font-weight":"" }); 
												tout.css({"text-decoration":"none", "font-weight":"bold" });
												}
											else{
												tin.css({ "text-decoration":"none", "font-weight":"bold" }); 
												tout.css({"text-decoration":"underline", "font-weight":"" });
											}
											function OnSearch()
											{
												if( bd.val().Trim() == "" && ed.val().Trim() == "")
												{
													alert("请先输入起止时间再搜索。");
													return;
												}
												var url = location.href;												
												if(bd.val().Trim() != "")
													url = SetUrlParam(url,"bd=" + encodeURIComponent(bd.val().Trim()));
												if(ed.val().Trim() != "")
													url = SetUrlParam(url,"ed=" + encodeURIComponent(ed.val().Trim()));											
												LocationTo(url);
											}
											
										</script>

									</td>
								</tr>
							</table>
							   <div id="zx">
							<asp:Panel ID="PanelTransOut" runat="server">
								<table width="100%" border="0" cellspacing="0" cellpadding="0" class="tab01">
								 <thead>
									<tr>
										<th>
											序号</th>
										<th>
											转账时间</th>
										<th>
											转账前</th>
										<th>
											转账金额</th>
										<th>
											手续费</th>
										<th>
											转账后</th>
										<th>
											转入帐号</th>
										<th>
											到账金额</th>
									</tr>
									</thead>
									<asp:Repeater ID="rpList" runat="server">
										<ItemTemplate>
											<tr align="center">
												<td>
													<%=Rowid+=1%>
												</td>
												<td>
													<%#Eval("TransTime")%>
												</td>
												<td>
													<%#UiCommon.StringConfig.AddZeros(Eval( "TransBefore" ))%>
												</td>
												<td>
													<%#UiCommon.StringConfig.AddZeros(Eval( "Money" ))%>
												</td>
												<td>
													<%#UiCommon.StringConfig.AddZeros(Eval( "Tax" ))%>
												</td>
												<td>
													<%#UiCommon.StringConfig.AddZeros(Eval( "TransAfter" ))%>
												</td>
												<td>
													<%# Eval("UserNameZZ")%>
												</td>
												<td>
													<%#UiCommon.StringConfig.AddZeros( Convert.ToInt64( Eval( "Money" ) ) - Convert.ToInt64( Eval( "Tax" ) ) ) %>
												</td>
											</tr>
										</ItemTemplate>
									</asp:Repeater>
								</table>
								<div class="clear">
								</div>
								<div class="sabrosus">
									<webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True"
									CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
									FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
									ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
									TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5" CurrentPageButtonClass="current" ShowPrevNext="False" PageSize="15">
								</webdiyer:AspNetPager>
								</div>
							</asp:Panel>
							<asp:Panel ID="PanelTransIn" runat="server">
								<table width="100%" border="0" cellspacing="0" cellpadding="0" class="tab01">
								 <thead>
									<tr>
										<th>
											序号</th>
										<th>
											转账时间</th>
										<th>
											转账前</th>
										<th>
											转账金额</th>
										<th>
											手续费</th>
										<th>
											转账后</th>
										<th>
											转账人</th>
										<th>
											到账金额</th>
									</tr>
									</thead>
									<asp:Repeater ID="rpListIn" runat="server">
										<ItemTemplate>
											<tr align="center">
												<td>
													<%=Rowid+=1%>
												</td>
												<td>
													<%#Eval("TransTime")%>
												</td>
												<td>													
													<%#UiCommon.StringConfig.AddZeros(Eval( "ZZ_TransBefore" ))%>
												</td>
												<td>
													<%#UiCommon.StringConfig.AddZeros(Eval( "Money" ))%>
												</td>
												<td>
													<%#UiCommon.StringConfig.AddZeros(Eval( "Tax" ))%>
												</td>
												<td>													
													<%#UiCommon.StringConfig.AddZeros(Eval( "ZZ_TransAfter" ))%>
												</td>
												<td>
													<%#Eval("UserName")%>
												</td>
												<td>													
													<%#UiCommon.StringConfig.AddZeros( Convert.ToInt32( Eval( "Money" ) ) - Convert.ToInt32( Eval( "Tax" ) ) ) %>
												</td>
											</tr>
										</ItemTemplate>
									</asp:Repeater>
								</table>
								<div class="clear">
								</div>
								<div class="sabrosus">
									<webdiyer:AspNetPager ID="AspNetPager1" runat="server" AlwaysShow="True"
									CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
									FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
									ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
									TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5" CurrentPageButtonClass="current" ShowPrevNext="False" PageSize="15">
								</webdiyer:AspNetPager>
								</div>
							</asp:Panel>
							</div>
						</div> <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
    </div>
     <div class="clear"></div>
      </div><!--right End-->
  
     
</form>
<!--footer-->
	<WebFooter:Control ID="webFooterone" runat="server" /> 
</body>
</html>
