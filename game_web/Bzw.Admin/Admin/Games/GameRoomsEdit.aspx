<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Games_GameRoomsEdit"
	CodeBehind="GameRoomsEdit.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<style type="text/css">
		<!
		-- body
		{
			background-color: #FFFFFF;
			margin-top: 0px;
		}
		-- ></style>
	<script src="/Public/Js/public.js" type="text/javascript"></script>
	<script src="/Public/Js/jquery.js" type="text/javascript"></script>
	<script src="/Public/Js/admin.js" type="text/javascript"></script>
 
</head>
<script language="javascript" type="text/javascript">
    $(document).ready(function() {

        var TaxType = parseInt("<%=TaxType %>");
        if (TaxType == 0) {//只显示门票
            $("#selTaxType").css("display", "none");
            $("#spanTaxType").html("<%=UiCommon.StringConfig.RoomTaxName %>");
            $("#spanTax").html("金币");
        }
        else {
            $("#selTaxType").css("display", "block");
            $("#spanTaxType").html("");
        }
        if ($("#selTaxType option:selected").val() == 0) {
            $("#spanTax").html("金币");
        }
        else {
            $("#spanTax").html("%注意：税率配置范围在0-100%之间！");
        }

    });

    function On_Change() {
        if ($("#selTaxType option:selected").val() == 0) {
            $("#spanTax").html("金币");
        }
        else {
            $("#spanTax").html("%注意：税率配置范围在0-100%之间！");

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
<body>
	<form method="POST" id="myform" action="" runat="server" onsubmit='return CheckForm();'>
	<table width="100%" border="1" align="center" cellpadding="5" cellspacing="0" bordercolor="A4B6D7"
		bgcolor="F2F8FF" class="admin_table">
		<tr>
			<td colspan="2" class="title_03">
				<strong>修改游戏房间页面</strong>
			</td>
		</tr>
		<tr id="ShowUser" runat="server">
		   	<td width="16%" align="right">租赁玩家：</td>
		   <td width="84%" align="left">
		        玩家ID：<asp:Label ID="lblUserID" runat="server"></asp:Label>&nbsp;玩家名：<asp:Label ID="lblUserName" runat="server"></asp:Label>   <font color="red">此房间的所有税收归该玩家所有</font>
		   </td>
		</tr>
		<tr>
			<td width="16%" align="right">
				游戏场类别：
			</td>
			<td width="84%" align="left">
				<select name="ComType" id="ComType">
					<option value="1" <%=(SComType=="1"?"selected=selected":"") %>>积分场</option>
					<%--<option value="2" <%=(SComType=="2"?"selected=selected":"") %>>比赛场</option>--%>
					<option value="3" <%=(SComType=="3"?"selected=selected":"") %>>金币场</option>
				</select>
			</td>
		</tr>
		<tr>
			<td align="right">
				游戏类型：
			</td>
			<td align="left">
				<asp:dropdownlist id="kindid" runat="server">
				</asp:dropdownlist>
				<a href="GameTypesAdd.aspx">添加游戏类别</a>
			</td>
		</tr>
		<tr>
			<td align="right">
				游戏名称：
			</td>
			<td align="left">
				<asp:dropdownlist id="ComName" runat="server">
				</asp:dropdownlist>
				<a href="GameNamesAdd.aspx">添加游戏名称</a>
			</td>
		</tr>
		<tr>
			<td align="right">
				游戏房间ID号：
			</td>
			<td align="left">
				<input name="nameid"  type="text" id="nameid" value="<%=Snameid %>" size="10" disabled="disabled" class="put" />
			</td>
		</tr>
		<!--
<tr>
  <td align="right">游戏客户端名称：</td>
  <td align="left"><input name="ComProcess" type="text" id="ComProcess" value="bpy_video.ico" />
    （XXX.ico）</td>
</tr>
-->
		<tr>
			<td align="right">
				游戏房间名称：
			</td>
			<td align="left">
				<input name="RoomName" type="text" id="RoomName" value="<%=SRoomName %>" class="put"
					maxlength="30" />
			</td>
		</tr>
		<tr>
			<td align="right">
				服务器IP地址：
			</td>
			<td align="left">
				<input name="ServiceIP" type="text" id="ServiceIP" value="<%=SServiceIP %>" class="put"
					maxlength="15" />
			</td>
		</tr>
		<tr>
			<td align="right">
				服务端ID号：
			</td>
			<td align="left">
				<input name="ServerInfoID" type="text" id="ServerInfoID" size="10" value="<%=SServerInfoID %>"
					class="put" maxlength="20" />（跟当前游戏的服务端ID号要一致，不能会导致不能找到房间！修改后需重启服务器。）
			</td>
		</tr>
		<tr>
			<td align="right">
				桌子数：
			</td>
			<td align="left">
				<input name="DeskCount" type="text" id="DeskCount" size="10" value="<%=SDeskCount %>"
					class="put" maxlength="2" />
				最多45桌
			</td>
		</tr>
		<tr>
			<td align="right">
				人数上限：
			</td>
			<td align="left">
				<input name="MaxPeople" type="text" id="MaxPeople" size="10" value="<%=SMaxPeople %>"
					class="put" maxlength="3" />
				最多180人
			</td>
		</tr>
		<tr>
			<td align="right">
				房间收费类型：
			</td>
			<td align="left">
				<select id="selTaxType" name="selTaxType" onchange="On_Change();">
					<option value="0" <%=(Type=="0"?"selected=selected":"") %>>
						<%=UiCommon.StringConfig.RoomTaxName %></option>
					<option value="1" <%=(Type=="1"?"selected=selected":"") %>>税率</option>
				</select>
				<span id="spanTaxType"></span>
				<input id="txtTax" name="txtTax" type="text" size="10" value="<%=Stax %>" class="put" maxlength="8" />
				<span id="spanTax"></span>
				
			</td>
		</tr>
		<tr>
			<td align="right">
				倍数：
			</td>
			<td align="left">
				<input name="BasePoint" type="text" id="BasePoint" size="10" value="<%=SBasePoint %>"
					class="put" maxlength="4" />
				只对金币产生倍数效果，对积分不产生倍数效果
			</td>
		</tr>
		<tr>
			<td align="right">
				最少金币限制：
			</td>
			<td align="left">
				<input name="LessPoint" type="text" id="LessPoint" size="10" value="<%=SLessPoint %>"
					class="put" maxlength="8" />
				进入此房间所需要的最少金币数
			</td>
		</tr>
		<tr>
			<td align="right">
				房间规则：
			</td>
			<td align="left">
				<input type="text" size="10" name="RoomRule" id="RoomRule" value="<%=SRoomRule %>"
					onclick="openRoomRuleDiv('RoomRuleSet.aspx?RoomRule=<%=SRoomRule %>',350,320)" class="put"/>
			</td>
		</tr>
		<tr>
			<td align="right">
				玩家金币最高限制：
			</td>
			<td align="left">
				<input name="MaxPoint" type="text" id="MaxPoint" class="put" value="<%=SMaxPoint %>" size="20"
					maxlength="19" />
				玩家进入此房间不能超过此金币数
			</td>
		</tr>
		<tr>
		    <td align="right">练习房间进入默认金币：</td>
		    <td align="left"><input name="ExercisePoint" id="ExercisePoint" class="put" value="<%=SExercisePoint %>" size="20" maxlength="19" />只有练习房才需要配置此项</td>
		</tr>
			<tr>
			<td align="right">
				房间密码：
			</td>
			<td align="left">
				<input type="password" size="10" name="RoomPassword"  class="put" id="RoomPassword" /><asp:Literal runat="server" ID="ltMsg" Text="此密码只针对百人类游戏，不需要可为空"></asp:Literal>
				<asp:CheckBox ID="cbClearPassword" Visible="false" runat="server" />
			</td>
		</tr>
		<tr>
			<td align="right">
				房间排序：
			</td>
			<td align="left">
				<input type="text" size="10" name="IDSort" id="IDSort" value="<%=SIDSort %>" class="put"
					maxlength="4" />（值越小排名越前）
			</td>
		</tr>
		<tr>
			<td align="right">
				游戏用表名称：
			</td>
			<td align="left">
				<input name="LockTable" type="text" id="LockTable" size="30" value="<%=SLockTable %>"
					class="put" maxlength="20" />
				（填写名称即可，系统会自动在名称后加上房间ID号）
			</td>
		</tr>
		<tr>
			<td align="right">
				游戏结果记录表：
			</td>
			<td align="left">
				<input name="MatchTable" type="text" id="MatchTable" size="30" value="<%=SMatchTable %>"
					class="put" maxlength="20" />
			</td>
		</tr>
		<tr>
			<td align="right">
				游戏IP限制表：
			</td>
			<td align="left">
				<input name="IPRuleTable" type="text" id="IPRuleTable" size="30" value="<%=SIPRuleTable %>"
					class="put" maxlength="20" />
			</td>
		</tr>
		<tr>
			<td align="right">
				游戏用户限制表：
			</td>
			<td align="left">
				<input name="UserNameRuleTable" type="text" id="UserNameRuleTable" size="30" value="<%=SUserNameRuleTable %>"
					class="put" maxlength="20" />
			</td>
		</tr>
		<tr>
			<td align="right">
				是否激活此房间：
			</td>
			<td align="left">
				<input name="bEnableRoom" type="radio" value="1" <%= (SbEnableRoom.ToString().ToLower()=="1" ? "checked" : "") %>
					class="put" />
				激活
				<input type="radio" name="bEnableRoom" value="0" <%= (SbEnableRoom.ToString().ToLower()=="0" ? "checked" : "") %>
					class="put" />
				不激活
			</td>
		</tr>
		<tr>
			<td align="right">
				分布式管理名称：
			</td>
			<td align="left">
				<input name="ServiceName" type="text" id="ServiceName" value="<%=SServiceName %>"
					class="put" maxlength="30" />
			</td>
		</tr>
		<tr>
			<td align="right">
				版本号：
			</td>
			<td align="left">
				<input name="Version" type="text" id="Version" size="10" value="<%=SVersion %>" class="put"
					maxlength="7" />
				房间的版本号，如：1.0 注意请对应到当前游戏版本号
			</td>
		</tr>
		<tr>
			<td align="right">
				房间欢迎信息：
			</td>
			<td align="left">
				<input name="RoomWelcome" type="text" id="RoomWelcome" value="<%=SRoomWelcome %>"
					size="50" class="put" maxlength="50" />
			</td>
		</tr>
		<tr>
			<td align="right">
				游戏时欢迎信息：
			</td>
			<td align="left">
				<input name="RallWelcome" type="text" id="RallWelcome" value="<%=SRallWelcome %>"
					size="50" class="put" maxlength="50" />
			</td>
		</tr>
		<tr>
			<td align="right">
				逃跑：
			</td>
			<td align="left">
				<input name="RunPublish" type="text" id="RunPublish" value="<%=SRunPublish %>" size="10"
					class="put" maxlength="7" />
				积分场逃跑扣积分；金币场逃跑扣金币*倍数,同时也扣积分；比赛场无效
			</td>
		</tr>
		<tr>
			<td align="right">
				混战场房间ID：
			</td>
			<td align="left">
				<input name="txtBattleRoomID" type="text" id="txtBattleRoomID" size="10" value="<%=SBattleRoomID %>"
					class="put" />填写混战场房间ID&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;混战场纪录表：<input type="text"
						class="put" name="txtBattleMatchTable" id="txtBattleMatchTable" value="TBattleMatchTable" />
			</td>
		</tr>
		<tr>
			<td align="right">
				比赛ID：
			</td>
			<td align="left">
				<input name="txtContestID" type="text" id="txtContestID" size="10" value="<%=SContestID %>" class="put" />填写比赛ID 
			</td>
		</tr>
		 <tr>
                <td align="right">游戏时长：</td>
                <td align="left"><asp:TextBox ID="txtPlayTimes" CssClass="put" MaxLength="9" Width="35px" runat="server" Text=""> </asp:TextBox>（分钟）赠送金币时所需的游戏时长</td>
            </tr>
              <tr>
                <td align="right">游戏时长金币数：</td>
                <td align="left"><asp:TextBox ID="txtPlayTimesMoney"  CssClass="put" MaxLength="9" Width="35px" runat="server" Text=""> </asp:TextBox></td>
            </tr>
              <tr>
                <td align="right">游戏第一轮：</td>
                <td align="left"><asp:TextBox ID="txtPlayCounts_1" CssClass="put" MaxLength="9" Width="35px" runat="server" Text=""> </asp:TextBox>第一轮赠送金币时所需的游戏局数</td>
            </tr>
              <tr>
                <td align="right">游戏第一轮金币数：</td>
                <td align="left"><asp:TextBox ID="txtPlayCountsMoney_1" CssClass="put" MaxLength="9" Width="35px" runat="server" Text=""></asp:TextBox></td>
            </tr>
                 <tr>
                <td align="right">游戏第二轮：</td>
                <td align="left"><asp:TextBox ID="txtPlayCounts_2" CssClass="put" MaxLength="9" Width="35px" runat="server" Text=""></asp:TextBox>第二轮赠送金币时所需的游戏局数</td>
            </tr>
              <tr>
                <td align="right">游戏第二轮金币数：</td>
                <td align="left"><asp:TextBox ID="txtPlayCountsMoney_2" CssClass="put" MaxLength="9" Width="35px" runat="server" Text=""></asp:TextBox></td>
            </tr>
                 <tr>
                <td align="right">游戏第三轮：</td>
                <td align="left"><asp:TextBox ID="txtPlayCounts_3" CssClass="put" MaxLength="9" Width="35px" runat="server" Text=""></asp:TextBox>第三轮赠送金币时所需的游戏局数</td>
            </tr>
              <tr>
                <td align="right">游戏第三轮金币数：</td>
                <td align="left"><asp:TextBox ID="txtPlayCountsMoney_3" CssClass="put" MaxLength="9" Width="35px" runat="server" Text=""></asp:TextBox></td>
            </tr>
              <tr>
                <td align="right">每局时长：</td>
                <td align="left"><asp:TextBox ID="txtSendTimeLength" CssClass="put" MaxLength="9" Width="35px" runat="server" ></asp:TextBox>秒  &nbsp;每局时长大于等于此值，赠送金币，</td>
            </tr>
            <tr>
                <td align="right">每局时长赠送<%=UiCommon.StringConfig.MoneyName %>数：</td>
                <td align="left"><asp:TextBox ID="txtSendCount" runat="server" MaxLength="19"  CssClass="put" Width="35px" ></asp:TextBox></td>
            </tr>
		<tr>
			<td>
				<input type="hidden" name="action" value="edit" />
				<input type="hidden" name="action2" value="edit" />
				<input type="hidden" name="id" value="20004" />
			</td>
			<td align="left">
				<asp:button id="Button1" runat="server" text="填好提交" onclick="EditGameRooms" class="put" />
				<input type="button" name="Submit2" value="返回" class="put" onclick="javascript:history.back();" />
			</td>
		</tr>
	</table>
	</form>
</body>
</html>
