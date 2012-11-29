<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Games_GameRoomsAdd"
	EnableEventValidation="false" CodeBehind="GameRoomsAdd.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<script src="/Public/Js/public.js" type="text/javascript"></script>
	<script src="/Public/Js/jquery.js" type="text/javascript"></script>
	<script src="/Public/Js/admin.js" type="text/javascript"></script>
	  <script type="text/javascript" src="/Public/Js/Global.js"></script>
	<style type="text/css">
		body {
			background-color: #FFFFFF;
			margin-top: 0px;
		}

		select
		{
		    z-index:0;
		    }
		</style>
	<script language="javascript" type="text/javascript">
		$(document).ready(function() {
		
		var TaxType = parseInt("<%=TaxType %>");
		if (TaxType == 0) {//只显示门票
			$("#selTaxType").css("display","none");
			$("#spanTaxType").html("<%=UiCommon.StringConfig.RoomTaxName %>");
			$("#spanTax").html("金币");
		}
		else {
			$("#selTaxType").css("display","block");
			$("#spanTaxType").html("");
		}
		if( $("#selTaxType option:selected").val() == 0 )
		{
			$("#spanTax").html("金币");
		}
		else
		{
			$("#spanTax").html("%注意：税率配置范围在0-100%之间！");
		}
        
	});
	
	function On_Change()
	{
		if( $("#selTaxType option:selected").val() == 0 )
		{
			$("#spanTax").html("金币");
		}
		else
		{
			$("#spanTax").html("%注意：税率配置范围在0-100%之间！");
		}
	}
	
		function disable() {
			if ($("input[name='raTaxType']:checked").val() == "0") {
				$("#TaxPercent").attr("disabled", "true");
				$("#Ticket").removeAttr("disabled");
			}
			else {
				$("#TaxPercent").removeAttr("disabled");
				$("#Ticket").attr("disabled", "true");
			}

		}

		function CheckForm() {

			

			if (document.getElementById("kindid").value == '') {
				alert('温馨提示：\n\n游戏类别不能为空！');
				document.getElementById("kindid").focus();
				return false;
			}

			//    if(document.getElementById("NameID").value == '') {
			//    alert('温馨提示：\n\n游戏名称不能为空！');
			//    document.getElementById("NameID").focus();
			//    return false;
			//  }
			//  
			if (document.getElementById("RoomName").value == '') {
				alert('温馨提示：\n\n请输入房间名称！');
				document.getElementById("RoomName").focus();
				return false;
			}
			if (document.getElementById("ServiceIP").value == '') {
				alert('温馨提示：\n\n请服务器IP！');
				document.getElementById("ServiceIP").focus();
				return false;
			}
			if (document.getElementById("DeskCount").value == '') {
				alert('温馨提示：\n\n桌子人数不能为空！');
				document.getElementById("DeskCount").focus();
				return false;
			}
			if (document.getElementById("ServiceName").value == '') {
				alert('温馨提示：\n\n服务器DLL名称不能为空！');
				document.getElementById("ServiceName").focus();
				return false;
			}
            



		}
	</script>
	<script language="JavaScript" type="text/javascript">
			<!--
		//以XML求取数据
		//参数:
		//obj,当前动作的下拉框
		//fullName:要填充的下拉框
	    function XmlPost(obj, fullName) {
	        
			//求取当前下拉框的值
			var svalue = obj.value;
			//定义要填充的对象
			var fullObj = document.all(fullName);
			//定义取值地址
			var webFileUrl = "?sortid=" + svalue;
			//定义返回值
			var result = "";
			
			//开始取值过程
//			var xmlHttp = new ActiveXObject("MSXML2.XMLHTTP");
//			xmlHttp.open("POST", webFileUrl, false);
			//			xmlHttp.send("");
			result = AjaxCall(webFileUrl);
			//result = xmlHttp.responseText;
		 
			//如果有取到值,则根据格式进行拆分
			//注意如果选择了第一行"请选择"空行时,是取不到值的,因此多加了一个条件
			if (result != "" && svalue != "") {
				//先清空原有的值
				fullObj.length = 0;
				//拆分值成数组
				var piArray = result.split(",");
				//循环数组
				for (var i = 0; i < piArray.length; i++) {
					//再拆分成ID及名称
					var ary1 = piArray[i].toString().split("|");
					//逐一添加项
					fullObj.options.add(new Option(ary1[1].toString(), ary1[0].toString()));
					var NameIDs = (ary1[0]);
					 
					document.getElementById("NameIDs").value = (ary1[0]);
				}
			}
			else {
				//如果没有取到值,则清空要填充的下拉框的值
				fullObj.length = 0;
				fullObj.options.add(new Option("暂无任何名称", ""));
			}
		}
			//-->
	</script>
</head>
<body>
	<form id="myform" runat="server" onsubmit='return CheckForm();'>
	<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
		bgcolor="F2F8FF" class="admin_table">
		<tr>
			<td colspan="2" class="title_03">
				<strong>添加游戏房间</strong>
			</td>
		</tr>
		<tr>
			<td width="16%" align="right">
				游戏场类别：
			</td>
			<td width="84%" align="left">
		 
				<select name="ComType" id="ComType" class="put" >
					<option value="1">积分场</option>
					<%--<option value="2">比赛场</option>--%>
					<option value="3">金币场</option>
			 
				</select>
			 
			</td>
		</tr>
		<tr>
			<td align="right">
				游戏类型：
			</td>
			<td align="left">
				<asp:DropDownList ID="kindid" runat="server">
				</asp:DropDownList>
				<a href="GameTypesAdd.aspx">添加游戏类别</a>
			</td>
		</tr>
		<tr>
			<td align="right">
				游戏名称：
			</td>
			<td align="left">
				<asp:DropDownList ID="NameID" runat="server">
				</asp:DropDownList>
				<a href="GameNamesAdd.aspx">添加游戏名称</a>
				<input type="hidden" id="NameIDs" name="NameIDs"/>
			</td>
		</tr>
		<tr>
			<td align="right">
				游戏房间名称：
			</td>
			<td align="left">
				<input name="RoomName" type="text" id="RoomName" class="put" maxlength="30" />例如：斗地主金币场
			</td>
		</tr>
		<tr>
			<td align="right">
				服务器IP地址：
			</td>
			<td align="left">
				<input name="ServiceIP" type="text" id="ServiceIP" value="<%=LoginIp %>" class="put"
					maxlength="15" />例如：255.255.255.255
			</td>
		</tr>
		<tr>
			<td align="right">
				桌子数：
			</td>
			<td align="left">
				<input name="DeskCount" type="text" id="DeskCount" class="put" size="10" value="10"
					maxlength="2" />填写该游戏房间中总共的桌子数目,最多45桌
			</td>
		</tr>
		<tr>
			<td align="right">
				人数上限：
			</td>
			<td align="left">
				<input name="MaxPeople" type="text" id="MaxPeople" class="put" size="10" value="50"
					maxlength="3" />填写该房间最多能容纳多少人进入,最多180人
			</td>
		</tr>
		<tr>
			<td align="right">
				房间收费类型：
			</td>
			<td align="left">
				<select id="selTaxType" name="selTaxType" onchange="On_Change();">
					<option value="0" <%=(TaxType=="0"?"selected=selected":"") %>>
						<%=UiCommon.StringConfig.RoomTaxName %></option>
					<option value="1" <%=(TaxType=="1"?"selected=selected":"") %>>税率</option>
				</select>
				<span id="spanTaxType"></span>
				<input id="txtTax" name="txtTax" type="text" size="10" value="0" class="put" maxlength="8" />
				<span id="spanTax"></span>
				
			</td>
		</tr>
		<tr>
			<td align="right">
				倍数：
			</td>
			<td align="left">
				<input name="BasePoint" type="text" id="BasePoint" class="put" value="1" size="10"
					maxlength="8" />只对金币产生倍数效果，对积分不产生倍数效果
			</td>
		</tr>
		<tr>
			<td align="right">
				最少金币限制：
			</td>
			<td align="left">
				<input name="LessPoint" type="text" id="LessPoint" class="put" value="0" size="10"
					maxlength="8" />
				填写进入此房间所需要的最少金币数
			</td>
		</tr>
		<tr>
			<td align="right">
				房间规则：
			</td>
			<td align="left">
				<input type="text" size="10" name="RoomRule" class="put" id="RoomRule" value="640"
					onclick="javascript:openRoomRuleDiv('RoomRuleSet.html',350,350);" />
			</td>
		</tr>
		<tr>
			<td align="right">
				玩家最高金币限制：
			</td>
			<td align="left">
				<input name="MaxPoint" type="text" id="MaxPoint" class="put" value="0" size="20"
					maxlength="19" />
				玩家进入此房间不能超过此金币数,为0则不限制
			</td>
		</tr>
		<tr>
		    <td align="right">练习房间进入默认金币：</td>
		    <td align="left"><input name="ExercisePoint" id="ExercisePoint" class="put" value="50000" size="20" maxlength="19" />只有练习房才需要配置此项</td>
		</tr>
		<tr>
			<td align="right">
				房间密码：
			</td>
			<td align="left">
				<input type="password" size="10" name="RoomPassword" class="put" id="RoomPassword" />(此密码只针对百人类游戏，不需要可为空)
			</td>
		</tr>
		<tr>
			<td align="right">
				房间排序：
			</td>
			<td align="left">
				<input type="text" size="10" name="IDSort" class="put" id="IDSort" value="0" maxlength="4" />（值越小排名越前）
			</td>
		</tr>
		<tr>
			<td align="right">
				是否激活此房间：
			</td>
			<td align="left">
				<input type="radio" name="bEnableRoom" value="1" checked="checked" class="put" />
				激活
				<input type="radio" name="bEnableRoom" value="0" class="put" />
				不激活
			</td>
		</tr>
		<tr>
			<td align="right">
				分布式管理名称：
			</td>
			<td align="left">
				<input name="ServiceName" type="text" id="ServiceName" value="bzgame" class="put"
					maxlength="30" />此名称与服务器端的LocalService.ini 文件中的m_ServiceName值相对应
			</td>
		</tr>
		<tr>
			<td align="right">
				版本号：
			</td>
			<td align="left">
				<input name="Version" type="text" id="Version" size="10" value="1.0" class="put"
					maxlength="7" />
				在此写房间的版本号，如：1.0 注意请对应到当前游戏版本号
			</td>
		</tr>
		<tr>
			<td align="right">
				房间欢迎信息：
			</td>
			<td align="left">
				<input name="RoomWelcome" type="text" id="RoomWelcome" value="欢迎您进入游戏中心" size="50"
					class="put" maxlength="50" />
			</td>
		</tr>
		<tr>
			<td align="right">
				游戏时欢迎信息：
			</td>
			<td align="left">
				<input name="RallWelcome" type="text" id="RallWelcome" value="欢迎您进入游戏中心" size="50"
					class="put" maxlength="50" />
			</td>
		</tr>
		<tr>
			<td align="right">
				&nbsp;逃跑：
			</td>
			<td align="left">
				<input name="RunPublish" type="text" id="RunPublish" value="0" size="10" class="put"
					maxlength="7" />积分场逃跑扣积分；金币场逃跑扣金币*倍数,同时也扣积分；比赛场无效
			</td>
		</tr>
		<tr>
			<td align="right">
				混战场房间ID：
			</td>
			<td align="left">
				<input name="txtBattleRoomID" type="text" id="txtBattleRoomID" size="10" class="put" />填写混战场房间ID&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;混战场纪录表：<input
					type="text" class="put" name="txtBattleMatchTable" id="txtBattleMatchTable" value="TBattleMatchTable" />
			</td>
		</tr>
		<tr>
			<td align="right">
				比赛ID：
			</td>
			<td align="left">
				<input name="txtContestID" type="text" id="txtContestID" size="10" class="put" value="0" />填写比赛ID 
			</td>
		</tr>
		<tr>
		    <td align="right">生成相同的比赛房间数：</td>
		    <td align="left"><input name="txtRoomCounts" id="txtRoomCounts" size="10" maxlength="2" class="put" value="1" />&nbsp;<font color="red">仅限比赛房万人房专用</font></td>
		</tr>
		     <tr>
                <td align="right">游戏时长：</td>
                <td align="left"><asp:TextBox ID="txtPlayTimes" CssClass="put" MaxLength="9" Width="35px" runat="server">0</asp:TextBox>（分钟）赠送金币时所需的游戏时长</td>
            </tr>
              <tr>
                <td align="right">游戏时长金币数：</td>
                <td align="left"><asp:TextBox ID="txtPlayTimesMoney"  CssClass="put" MaxLength="9" Width="35px" runat="server">0</asp:TextBox></td>
            </tr>
              <tr>
                <td align="right">游戏第一轮：</td>
                <td align="left"><asp:TextBox ID="txtPlayCounts_1" CssClass="put" MaxLength="9" Width="35px" runat="server">0</asp:TextBox>第一轮赠送金币时所需的游戏局数</td>
            </tr>
              <tr>
                <td align="right">游戏第一轮金币数：</td>
                <td align="left"><asp:TextBox ID="txtPlayCountsMoney_1" CssClass="put" MaxLength="9" Width="35px" runat="server">0</asp:TextBox></td>
            </tr>
                 <tr>
                <td align="right">游戏第二轮：</td>
                <td align="left"><asp:TextBox ID="txtPlayCounts_2" CssClass="put" MaxLength="9" Width="35px" runat="server">0</asp:TextBox>第二轮赠送金币时所需的游戏局数</td>
            </tr>
              <tr>
                <td align="right">游戏第二轮金币数：</td>
                <td align="left"><asp:TextBox ID="txtPlayCountsMoney_2" CssClass="put" MaxLength="9" Width="35px" runat="server">0</asp:TextBox></td>
            </tr>
                 <tr>
                <td align="right">游戏第三轮：</td>
                <td align="left"><asp:TextBox ID="txtPlayCounts_3" CssClass="put" MaxLength="9" Width="35px" runat="server">0</asp:TextBox>第三轮赠送金币时所需的游戏局数</td>
            </tr>
              <tr>
                <td align="right">游戏第三轮金币数：</td>
                <td align="left"><asp:TextBox ID="txtPlayCountsMoney_3" CssClass="put" MaxLength="9" Width="35px" runat="server">0</asp:TextBox></td>
            </tr>
             <tr>
                <td align="right">每局时长：</td>
                <td align="left"><asp:TextBox ID="txtSendTimeLength" CssClass="put" MaxLength="9" Width="35px" runat="server">0</asp:TextBox>秒  &nbsp;每局时长大于等于此值，赠送金币，</td>
            </tr>
            <tr>
                <td align="right">每局时长赠送<%=UiCommon.StringConfig.MoneyName %>数：</td>
                <td align="left"><asp:TextBox ID="txtSendCount" runat="server" MaxLength="19"  CssClass="put" Width="35px" >0</asp:TextBox></td>
            </tr>
		<tr>
			<td>
				<input type="hidden" name="action" value="add" />&nbsp;<input type="hidden" name="action2"
					value="add" />
			</td>
			<td align="left">
				<asp:Button ID="Button1" runat="server" Text="填好提交" OnClick="AddRoomGame" Class="put" />
				<input type="reset" name="Submit2" value="清空重写" class="put" />
			</td>
		</tr>
	</table>
	</form>
</body>
</html>
