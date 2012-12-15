<%@ Page Title="" Language="C#" MasterPageFile="~/MainMaser.Master" AutoEventWireup="true" CodeBehind="UserReg.aspx.cs" Inherits="QPS.Web.UserReg" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">

</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">

<script type="text/javascript">
    var curStatus = null;
    function txtUser_onfouce() {

    }

    function txtUser_onblur() {
        $.ajax({
            type: "GET",
            url: "CheckUserName.aspx",
            dataType: "html",
            data: "userName=" + $("#txtUser").val(),
            beforeSend: function (XMLHttpRequest) {
                $("#showResult").text("正在查询...");
                $("#showResult").css("color", "blue");
            },
            success: function (msg) {
                if (msg == "yes") {
                    $("#showResult").html("用户名可用");
                    $("#showResult").css("color", "green");
                }
                else {
                    $("#showResult").html("用户名已被注册");
                    $("#showResult").css("color", "red");
                }
            },
            complete: function (XMLHttpRequest, textStatus) {
                //隐藏正在查询图片
            },
            error: function () {
                //错误处理
            }
        });
    }

    function btn_Reg_onClick() {
        var usertype = null;
        var item = null;

        reg = /^[A-Za-z0-9]+$/;
        if (!reg.test($("#txtUser").val())) {
            alert("用户名只能是数字和字母！");
            return;
        }

        reg = /[\u4e00-\u9fa5]{2,6}/;
        if (!reg.test($("#txtNickname").val())) {
            alert("用户昵称的格式不对，请重新输入！");
            return;
        }

        reg = /(^189\d{8}$)|(^13\d{9}$)|(^15\d{9}$)/;
        if (!reg.test($("#txtShouj").val())) {
            alert("输入的手机号有错误,请重新输入！");
            return;
        }

        reg = /^\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*$/;
        if (!reg.test($("#txtEm").val())) {
            alert("输入的邮箱格式有错误，请重新输入！");
            return;
        }

        if ($("#txtUser").val().length < 6 || $("#txtUser").val().length > 12) {
            alert("用户名 的长度不对，请重新输入！");
            return;
        }
        if ($("#txtPwd").val().length < 6 || $("#txtPwd").val().length > 20) {
            alert("密码 的长度不对，请重新输入！");
            return;
        }
        if ($("#txtNickname").val().length < 2 || $("#txtNickname").val().length > 6) {
            alert("用户昵称 的长度不对，请重新输入！");
            return;
        }
        if ($("#txtPwd").val() != $("#txtRePwd").val()) {
            alert("确认密码与原密码不一致 ，请重新输入！");
            return;
        }

        if (document.getElementById("checkbox_id").checked == true) {
            if (document.getElementById("radio_user").checked == true) {
                usertype = "user";
            }
            else {
                usertype = "enterprise";
            }
            $.ajax({
                type: "GET",
                url: "DoUserReg.aspx",
                dataType: "html",
                data: "username=" + $("#txtUser").val() + "&add=" + $("#txtDz").val() + "&mail=" + $("#txtEm").val() + "&phone=" + $("#txtShouj").val() + "&pwd=" + $("#txtPwd").val() + "&nickname=" + $("#txtNickname").val() + "&type=" + "user",
                beforeSend: function (XMLHttpRequest) {
                    $("#progress").text("正在提交数据...");
                    $("#progress").css("color", "red");
                },
                success: function (msg) {
                    if (msg == "1") {
                        if (usertype == "user") {
                            alert("创建用户成功!");
                        }
                        else if (usertype == "enterprise") {
                            alert("创建企业用户成功，等待管理员审核!");
                        }
                        window.location.href = "UserLogin.aspx";
                    }
                    else {
                        alert("创建用户失败！");
                        $("#txtPwd").val("");
                        $("#txtRePwd").val("");
                    }
                },
                complete: function (XMLHttpRequest, textStatus) {
                    $("#progress").text("");
                },
                error: function () {
                    $("#progress").text("");
                }
            });
        }

    }

</script>
<!--mid[[-->
<div class="mid">
     <div class="nyleft">
          <div class="ptxz">
               <a href="http://game.87win.cn/download/八棋赢简洁版.exe">&nbsp;</a>
          </div>
          <div class="lxfs">
               <span><a href="tencent://message/?uin=2637416916&Site=八棋赢棋牌游戏&Menu=yes">企业QQ<br/>在线客服</a></span>
          </div>
     </div>
     <div class="nyright">
          <div class="yjtop"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
          <div class="yjmid">
               <div class="titled">欢迎注册成为八旗赢棋牌联盟用户</div>
               <div id="xzmenu">
                    <div id="Div1">
                 <input type="radio" name="usertype" id="radio_user" value="user" checked="checked" />普通用户
                 <input type="radio" name="usertype" id="radio_enter" value="enter" />企业用户
               </div>
               </div>
               <div class="zcnra" id="cotant_1">
                    <ul>
                        <li><h3>用户名：</h3><input type="text" name="txtUser" id="txtUser" class="zca1" onfocus="txtUser_onfouce()" onblur="txtUser_onblur()"/><p id="showResult">*用户名由6-12位　字符　字母　数字构成</p></li>
                        <li><h3>密码：</h3><input type="password" name="txtPwd" id="txtPwd" class="zca1"  /><p>*密码由6-20位　英文　字母　或数字组成</p></li>
                        <li><h3>确认密码：</h3><input type="password" name="txtRePwd" id="txtRePwd" class="zca1"  /><p>*和上面密码相同</p></li>
                        <li><h3>昵称：</h3><input type="text" name="txtNickname" id="txtNickname" class="zca1" /><p>*用户昵称由2-6位　汉字字构成</p></li>
                        <li><h4>完善信息：</h4></li>
                        <li><h3>手机号：</h3><input type="text" name="txtShouj" id="txtShouj" class="zca1" /></li>
                        <li><h3>邮箱：</h3><input type="text" name="txtEm" id="txtEm" class="zca1" /></li>
                        <li><h3>地址：</h3><input type="text" name="txtDz" id="txtDz" class="zca1" /></li>
                        <li> 
                        <input type="button" id="btn_Reg" class="zca6" value="" onclick="btn_Reg_onClick()" />   
                             <input type="checkbox" name="checkbox1" id="checkbox_id" class="zca7"/>
                             <h5>我已阅读并同意<a href="Alert.aspx">使用条款</a></h5>
                             <br /><p id="progress" style="text-align:left"></p>
                        </li>
                    </ul>
             </div>

          </div>
          <div class="yjend"><div style="clear:both; overflow:hidden; height:0; font-size:1px; "></div></div>
     </div>
</div>
<!--mid]]-->
</asp:Content>
