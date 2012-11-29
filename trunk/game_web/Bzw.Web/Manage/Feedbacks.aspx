<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_Feedbacks"  %>

<%@ Register Assembly="Pager" Namespace="Wuqi.Webdiyer" TagPrefix="webdiyer" %>
<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>
		
	</title>
	
	<link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/common.js"></script>
	<script type="text/javascript" src="/Public/Js/Global.js"></script>
</head>
<body>
    <div id="container">
<!--header-->
	 <WebTop:Control ID="webTopOne" runat="server"/> 
<!--content-->
 
      <div id="left">
        <Left:Control ID="leftOne" runat="server" />
        <WebService:Control ID="webServiceOne" runat="server" />
      </div>
       <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    查看留言</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 查看留言</p>
            </div>
            <div id="sub_nr" style="margin-top: 10px;">
           <div  class="cz">
						<asp:Repeater ID="rpList" runat="server">
							<ItemTemplate>
								<table width="100%" border="0" cellspacing="0" cellpadding="0" class="tableMessage">
									<tr>
									<th align="left"  height="30" >标题：</th><td><%# Eval("msgtitle")%></td>
								  </tr>
								  <tr><th align="left"  height="30" >内容：
								  </th>
									<td >
									<%# Eval("msgtext") %>
									</td>
								  </tr>
								  <tr>
								  <th>留言状态：</th>
									<td height="23"  class="textgray"><%# GetState(Eval("ispass"))%></td>
								  </tr>
								  <tr>
								  <th>回复内容：</th>
									 <td ><%# Eval("msgreply")%></td>
								  </tr>
								 <tr>
								 <th>回复时间：</th>
								 <td><%# Eval("msgreplytime") %></td>
								 </tr>
								   
								</table>
							</ItemTemplate>
						</asp:Repeater>
						</div>
					<!--pageNumber-->
					<div class="sabrosus">
						<webdiyer:AspNetPager ID="anpPageIndex" runat="server" AlwaysShow="True"
							CustomInfoHTML="当前为第%CurrentPageIndex%/%PageCount%页，每页%PageSize%条，共%RecordCount%条"
							FirstPageText="&lt;" LastPageText="&gt;" NextPageText="下一页" PrevPageText="上一页"
							ShowPageIndexBox="Never" UrlPaging="True" PageIndexBoxType="DropDownList" SubmitButtonText="Go"
							TextAfterPageIndexBox="页" TextBeforePageIndexBox="转到" NumericButtonCount="5" CurrentPageButtonClass="current" ShowPrevNext="False" PageSize="10">
						</webdiyer:AspNetPager>
					</div>
                 
     
     <div class="clear"></div>
      </div><!--right End-->
  <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
    </div><!--content End-->
</div>
<!--footer-->
	<WebFooter:Control ID="webFooterone" runat="server" /> 
</body>
</html>

 
