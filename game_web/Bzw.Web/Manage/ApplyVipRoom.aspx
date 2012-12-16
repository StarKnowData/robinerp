<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_ApplyVipRoom" %>

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
    <script type="text/javascript" src="/Public/Js/jquery.js"></script>
    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

    <script type="text/javascript" src="/Public/Js/public.js"></script>

    <script type="text/javascript" src="/Public/Js/DatePicker/WdatePicker.js"></script>

    <style type="text/css">
        .tab03
        {
        }
        .tab03 tr
        {
            height: 30px;
        }
        .tl
        {
            width: 17%;
            height: 30px;
            text-align: right;
            vertical-align: middle;
        }
        .tr
        {
            width: 83%;
            height: 30px;
            text-align: left;
            vertical-align: middle;
            color: #333;
        }
        .green
        {
            padding-left: 15px;
            color: Green;
        }
    </style>
</head>
<body>

    <script type="text/javascript" src="/Public/Js/dialog.js"></script>

    <div id="container">
        <!--header-->
        <WebTop:Control ID="webtop1" runat="server" />
        <!--content-->
        <div id="left">
            <Left:Control ID="leftOne" runat="server" />
            <WebService:Control ID="webServiceOne" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    房间租赁申请</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 房间租赁申请</p>
            </div>
            <div id="sub_nr" style="margin-top: 10px;">
                <div class="rank_title">
                    房间租赁申请</div>
                <div id="zx">
                    <div id="reg">
                        <form id="frmLogin" runat="server" onsubmit="return onFormSubmit();">
                        <div style="text-align: center;">
                            <asp:Label ID="lbMsg" ForeColor="red" runat="server"></asp:Label>
                        </div>
                        <table width="100%" border="0" align="center" cellpadding="0" cellspacing="6" class="tab03">
                            <tr>
                                <td class="tl">
                                    用户名：
                                </td>
                                <td class="tr">
                                    <%=username %>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    登录密码：
                                </td>
                                <td class="tr">
                                    <input name="LoginPsw" type="password" class="btn5" id="LoginPsw" maxlength="20" />
                                    <span class="red">*</span><span class="note" id="pwdspan">请输入您的登录密码</span>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    电子邮箱：
                                </td>
                                <td class="tr">
                                    <input name="Email" type="text" class="btn5" id="Email" maxlength="20" onblur="chkEmail()" />
                                    <span class="note" id="emailspan">请填写您最常用请填写您最常用的电子邮箱 </span>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    QQ：
                                </td>
                                <td class="tr">
                                    <input name="QQ" type="text" class="btn5" id="QQ" maxlength="12" onblur="chkQQ()" /><span
                                        class="note" id="qqspan"></span>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    电话号码：
                                </td>
                                <td class="tr">
                                    <input name="Mobile" type="text" class="btn5" id="Mobile" maxlength="11" onblur="chkPhone()" />
                                    <span class="red">*</span><span id="mobilespan" class="note">请填写您的手机号码，前面不加0，审核通过将以短信通知</span>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    游戏名称：
                                </td>
                                <td class="tr">
                                    <asp:DropDownList ID="NameID" runat="server" onchange="getRent(this.value)">
                                    </asp:DropDownList>
                                    <span class="red">*</span>请选择游戏 <span class="green" id="everydayrent"></span>
                                    <input type="hidden" id="hdEverydayRent" value="" />
                                    <asp:HiddenField ID="hdBankMoney" runat="server" />
                                </td>
                            </tr>

                            <script type="text/javascript">
                                //获取房间租金
                                function getRent(gameid) {

                                    var urlData = '/Public/XmlHttpUser.aspx?type=roomrent&gameid=' + escape(gameid);
                                    var strReturn = AjaxCall(urlData);
                                    if (strReturn == "0") {
                                        $("#everydayrent").html("获取房间租金失败");
                                    } else {
                                        $("#everydayrent").html("一天租金为" + strReturn + "金币");
                                        $("#hdEverydayRent").val(strReturn);
                                    }
                                    var days = $("#BuyDays").val();
                                    needMoney(days);
                                }


                                //总共需要金币
                                function needMoney(days) {
                                    if (days != "") {
                                        var unit = $("#hdEverydayRent").val();
                                        var money = $("#hdBankMoney").val();

                                        if (unit != "") {
                                            var tip = "";
                                            var all = parseFloat(unit) * parseFloat(days);
                                            tip = "总共需要" + all + "金币";
                                            if (money != "" && all > parseFloat(money))
                                                tip = tip + "  <span class='red'>您的金币不够，请先充值</span>";
                                            $("#allmoney").html(tip);
                                        }
                                    }
                                    else {
                                        $("#allmoney").html("");
                                    }
                                }
 
    
    
   
    
                            </script>

                            <tr>
                                <td class="tl">
                                    租凭房间时长：
                                </td>
                                <td class="tr">
                                    <asp:DropDownList ID="BuyDays" runat="server" onchange="needMoney(this.value)">
                                    </asp:DropDownList>
                                    天 <span class="red">*</span> <span class="green" id="allmoney"></span>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    租凭房间日期：
                                </td>
                                <td class="tr">
                                    <input name="BeginDate" type="text" class="btn5" id="BeginDate" maxlength="20" onfocus="WdatePicker({minDate:'%y-%M-#{%d+1}'})" />
                                    <span class="note" id="ejpwdspan"><span class="red">*</span>既开通房间日期，必须大于今天日期，开通时间统一为早上10点</span>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    房间名称：
                                </td>
                                <td class="tr">
                                    <input name="RoomName" type="text" class="btn5" id="RoomName" maxlength="12" />
                                    <span class="note" id="ejpwd2span"><span class="red">*</span>请填写房间名称，长度2到12个字符之间</span>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    房间密码：
                                </td>
                                <td class="tr">
                                    <input name="RoomPsw" id="RoomPsw" class="btn5" type="password" maxlength="16" />
                                    请填写房间密码，长度在2到16个字符之间。不需要可为空
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    确定房间密码：
                                </td>
                                <td class="tr">
                                    <input name="Psw2" type="password" class="btn5" id="Psw2" maxlength="16" />
                                    <span class="note" id="roompass2span">请确认你房间的密码</span>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    桌子数：
                                </td>
                                <td class="tr">
                                    <input name="DeskNum" type="text" class="btn5" id="DeskNum" value="10" maxlength="2" />
                                    <span class="note" id="desknumspan">填写该游戏房间中总共的桌子数目，最多45桌</span>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    人数上限：
                                </td>
                                <td class="tr">
                                    <input name="MaxPeople" type="text" class="btn5" id="MaxPeople" value="50" maxlength="3" />
                                    <span class="note" id="promoterspan">填写该房间最多能容纳多少人进入，最多180人</span>
                                </td>
                            </tr>

                            <script type="text/javascript">
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
                                        $("#spanTax").html("%注意：税率配置范围在0-100%之间");
                                    }

                                });
                                function On_Change() {
                                    if ($("#selTaxType option:selected").val() == 0)
                                        $("#spanTax").html("金币");
                                    else
                                        $("#spanTax").html("%注意：税率配置范围在0-100%之间");
                                }
 
                            </script>

                            <tr>
                                <td class="tl">
                                    房间收费类型：
                                </td>
                                <td class="tr">
                                    <select id="selTaxType" name="selTaxType" onchange="On_Change();">
                                        <option value="0" <%=(TaxType=="0"?"selected=selected":"") %>>
                                            <%=UiCommon.StringConfig.RoomTaxName %></option>
                                        <option value="1" <%=(TaxType=="1"?"selected=selected":"") %>>税率</option>
                                    </select><span id="spanTaxType" class="note"></span>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                </td>
                                <td class="tr">
                                    <input id="txtTax" name="txtTax" type="text" size="10" value="0" class="btn5" maxlength="8" />
                                    <span class="red">*</span> <span class="note" id="spanTax"></span>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    倍数：
                                </td>
                                <td class="tr">
                                    <input name="BasePoint" id="BasePoint" type="text" class="btn5" value="1" maxlength="9" />
                                    <span class="red">*</span> <span class="note" id="SpanBasePoint">只对金币产生倍数效果，对积分不产生倍数效果</span>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    最少金币限制：
                                </td>
                                <td class="tr">
                                    <input name="LessPoint" id="LessPoint" type="text" value="0" class="btn5" maxlength="9" />
                                    <span class="red"></span><span class="note" id="SpanLessPoint">填写进入此房间所需要的最少金币数</span>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    最高金币限制：
                                </td>
                                <td class="tr">
                                    <input name="MaxPoint" id="MaxPoint" type="text" class="btn5" value="0" maxlength="19" />
                                    <span class="red"></span><span class="note" id="SpanMaxPoint">玩家进入此房间不能超过此金币数,为0则不限制</span>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    房间欢迎信息：
                                </td>
                                <td class="tr">
                                    <input name="RoomWelcome" id="RoomWelcome" type="text" class="btn5" style="width: 300px;"
                                        maxlength="4" />
                                    <span class="red"></span><span class="note" id="SpanRoomWelcome"></span>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    游戏时欢迎信息：
                                </td>
                                <td class="tr">
                                    <input name="RallWelcome" id="RallWelcome" type="text" style="width: 300px;" class="btn5"
                                        maxlength="4" />
                                    <span class="red"></span><span class="note" id="SpanRallWelcome"></span>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    备注：
                                </td>
                                <td class="tr">
                                    <asp:TextBox ID="Remark" runat="server" TextMode="MultiLine" Style="width: 300px;
                                        height: 50px; padding: 2px; color: #2E66A1">
                                
                                    </asp:TextBox>
                                    <span class="red"></span><span class="note" id="Span7"></span>
                                </td>
                            </tr>
                            <tr>
                                <td class="tl">
                                    验证码：
                                </td>
                                <td class="tr">
                                    <asp:TextBox ID="txtValidCode" runat="server" Width="60px" MaxLength="4" CssClass="fr_input"></asp:TextBox>
                                    <span class="red">*</span>
                                    <img src="/Public/Getcode.aspx" onclick="this.src='/Public/Getcode.aspx?token='+tokenKey();"
                                        alt="点击换一张图片" style="vertical-align: baseline; cursor: pointer; width: 60px;
                                        height: 20px; padding-top: 3px;" />
                                    <span class="note" id="Span8">看不清，点击图片换一张</span>
                                </td>
                            </tr>
                            <tr style="padding-top: 20px; height: 60px;">
                                <td class="tl">
                                </td>
                                <td class="tr">
                                    <asp:Button ID="Button1" runat="server" Text=" " OnClick="AddApplyVipRoom" Class="but_01" />
                                    <input type="reset" name="Submit2" class="but_02" value="  " />
                                </td>
                            </tr>
                        </table>
                        </form>
                    </div>
                    <div class="clear">
                    </div>
                </div>
            </div> <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
            <div class="clear">
            </div>
        </div>

        <script type="text/javascript">
            /*===Check Email========================*/
            function chkEmail(msg) {
                var txt = document.getElementById('Email');
                var tip = document.getElementById("emailspan");

                if (txt.value.trim().length > 0) {

                    //valid regx-----------------
                    if (!/^[-_A-Za-z0-9]+@([_A-Za-z0-9\u4e00-\u9fa5]+\.)+[A-Za-z0-9]{2,4}$/.test(txt.value)) {
                        tip.className = "note_no";
                        tip.innerText = '请按正确格式填写电子邮箱。';
                        return false;
                    }
                    tip.innerText = '恭喜您，电子邮箱检测通过。';

                    tip.className = "note_yes";
                    return true;
                }
                else {
                    tip.className = "note";
                    return true;

                }
            }
            /*===Check QQ========================*/
            function chkQQ() {
                var txt = document.getElementById('QQ');
                var tip = document.getElementById("qqspan");
                regqq = /^[0-9]{4,12}$/;
                if (txt.value.trim().length > 0) {
                    if (!regqq.test(txt.value)) {
                        tip.className = "note_no";
                        tip.innerText = "QQ只能为4-12位的数字";
                        return false;
                    }
                    else {
                        tip.className = "note_yes";
                        tip.innerText = "恭喜您，QQ检测通过。";
                        return true;
                    }
                }
                else {

                    return true;
                }
            }
            /*====Check Mobile==============*/
            function chkPhone() {
                var txt = document.getElementById('Mobile');
                var tip = document.getElementById("mobilespan");
                if (txt.value.trim().length > 0) {
                    //            tip.className="note_no";
                    //            tip.innerText='请填写您的电话号码，以便联系。';
                    //            document.getElementById('mobile').value='';
                    //            return false;
                    //         }
                    if (!/^0{0,1}(13[0-9]|15[0-9])[0-9]{8}$/.test(txt.value)) {
                        tip.className = "note_no";
                        tip.innerText = '电话号码不正确！';
                        return false;
                    }
                    else {
                        tip.className = "note_yes";
                        tip.innerText = '恭喜您，电话号码检测通过。';
                        return true;
                    }
                }
                else {
                    tip.className = "note_no";
                    tip.innerText = '请填写真实手机号码,审核通过将以短信通知。';
                    return false;
                }
            }
            function onFormSubmit() {


                var LoginPsw = $("#LoginPsw").val();

                var NameID = $("#NameID").val();
                var BuyDays = $("#BuyDays").val();
                var BeginDate = $("#BeginDate").val();
                var RoomName = $("#RoomName").val();
                var RoomPsw = $("#RoomPsw").val();


                var Psw2 = $("#Psw2").val();
                var DeskNum = $("#DeskNum").val();
                var MaxPeople = $("#MaxPeople").val();
                var selTaxType = $("#selTaxType").val();
                var txtTax = $("#txtTax").val();

                var BasePoint = $("#BasePoint").val();
                var LessPoint = $("#LessPoint").val();
                var MaxPoint = $("#MaxPoint").val();
                var RoomWelcome = $("#RoomWelcome").val();
                var RallWelcome = $("#RallWelcome").val();

                var Remark = $("#Remark").val();
                var txtValidCode = $("#txtValidCode").val();
                var hdEverydayRent = $("#hdEverydayRent").val();
                var hdBankMoney = $("#hdBankMoney").val();

                var urlData, strReturn;



                if (LoginPsw == "") {
                    alert("请填写登录的密码！"); $("#LoginPsw").focus();
                    return false;
                }
                if (!chkEmail()) {
                    document.getElementById("Email").focus();
                    return false;
                }
                if (!chkQQ()) {
                    document.getElementById("QQ").focus();
                    return false;
                }
                if (!chkPhone()) {
                    document.getElementById("Mobile").focus();
                    return false;
                }
                if (NameID == "") {
                    alert("请选择游戏的名称！"); $("#NameID").focus();
                    return false;
                }

                if (BuyDays == "") {
                    alert("请选择租赁房间的时长！"); $("#BuyDays").focus();
                    return false;
                }

                if (BeginDate == "") {
                    alert("请选择租赁房间的日期！");
                    return false;
                }
                if (RoomName == "") {
                    alert("请填写租赁房间名称！"); $("#RoomName").focus();
                    return false;
                }

                if (txtTax == "") {
                    alert("请填写房间收费类型值！"); $("#txtTax").focus();
                    return false;
                }

                if (BasePoint == "") {
                    alert("请填写倍数！"); $("#BasePoint").focus();
                    return false;
                }

                if (txtValidCode == "") {
                    alert("请填写验证码！"); $("#txtValidCode").focus();
                    return false;
                }

                if (txtValidCode != "") {
                    urlData = '/Public/XmlHttpUser.aspx?type=validcode&code=' + escape(txtValidCode);
                    strReturn = AjaxCall(urlData);
                    if (strReturn == "-1") {
                        alert("验证码已经失效，请输入新的验证码。");
                        return false;
                    }
                    else if (strReturn == "1") {
                        alert("验证码输入错误，请重新输入。");
                        return false;
                    }
                }

                return true;

            }


 
        </script>

        <!--right End-->
    </div>
    <!--content End-->
    <!--footer-->
    <WebFooter:Control ID="webFooter" runat="server" />
</body>
</html>
