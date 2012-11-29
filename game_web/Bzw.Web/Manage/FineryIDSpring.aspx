<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.FineryIDSpring" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
  <title>
      
    </title>
  
  <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/common.js"></script>
	<script type="text/javascript" src="/Public/Js/Global.js"></script>
	<script type="text/javascript" src="/Public/Js/password_check.js"></script>
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
                    激活靓号</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 激活靓号</p>
            </div>
            <div id="sub_nr" style="margin-top: 10px;">
 
		<div id="memText01">
               <form id="frmLogin" runat="server" onsubmit="return onFormSubmit(this);">
					  <div class="cz">
					<table width="100%" border="0">
						<tr>
						<th width="20%" height="30" align="right" scope="row">
							您的靓号：</th>
						<td>
							<%=fineryid %></td>
						</tr>
						<tr>
						<th width="20%" height="30" align="right" scope="row">
							靓号密码验证：</th>
						<td>
						<input name="pwd" type="password" id="pwd" maxlength="20" onblur="chkPwd()" style="width:149px;"/>											
						<span class="red">*</span>
						<span class="note" id="pwdspan">请输入您购买时设定的靓号密码</span></td>
						</tr>
                   </table>
                   </div>
				  <div class="cz">
					   <table width="100%" border="0">
							<tr>
								<th width="20%" height="30" align="right" scope="row">
									设定靓号用户名：</th>
								<td colspan="2">
									<input name="username" type="text" class="btn5" id="username" maxlength="12" onblur="chkUserName(msgUsername)" />
									<font class="red">*</font>
									<span class="note" id="unamespan">用户名长度6～12个字符，由字母、数字组成。</span></td>
							</tr>
							<tr>
								<th height="20" align="right" scope="row">
									设定靓号昵称：</th>
								<td colspan="2">
									<input name="nickname" type="text" id="nickname" maxlength="12" onblur="chkNickName(msgNickname)" />
										<span class="red">*</span>
										<span class="note" id="nickspan">字母、数字、特殊符号、中文组成，长度为2-12位。</span></td>
							</tr>
						</table>
					</div>
					<table width="100%" border="0">
						<tr>
							<td style="text-align:center;">
								<input type="submit" name="btnSubmit" id="btnSubmit" runat="server" onserverclick=" Button1_Click"  value="确定激活" class="but_011"/>
							</td>
						</tr>
					</table>
               </form>
		</div>
      </div>  
       <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
    </div>
     <div class="clear"></div>
      </div><!--right End-->
 
     
<!--footer-->
	<WebFooter:Control ID="webFooterone" runat="server" /> 
</body>
</html>
<script type="text/javascript">
	var msgUsername = '用户名长度6～12个字符，由字母、数字组成。';
	var msgNickname = '字母、数字、特殊符号、中文组成，长度为2-12位。';
	var msgPwd2 = '请再输入一遍您上面输入的密码。';
	function chkUserName(msg) {
		var txt = document.getElementById('username');
		var tip = document.getElementById("unamespan");

		//valid is null--------------
		if (txt.value.trim().length == 0) {
			//txt.focus();死循环
			tip.className = "note_no";
			tip.innerText = msg;
			return false;
		}
		//valid regx-----------------
		if (!/^[0-9a-zA-Z]{6,12}$/.test(txt.value)) {
			tip.className = "note_no";
			tip.innerText = msg;
			return false;
		}
		//valid is exsits---------------
		var urlData = '/Public/XmlHttpUser.aspx?type=regnameexist&username=' + escape(txt.value);
		//alert(urlData);
		var strReturn = AjaxCall(urlData);
		//alert(strReturn);
		if (strReturn == "1") {
			tip.className = "note_no";
			tip.innerText = '对不起，该用户名已经存在。';
			return false;
		} else if (strReturn == "0") {
			tip.innerText = '恭喜您，该用户名可以注册。';
		}

		tip.className = "note_yes";
		tip.innerHTML = "恭喜您，用户名通过验证";
		return true;
	}


	/*===Check NickName========================*/
	function chkNickName(msg) {
		var txt = document.getElementById('nickname');
		var tip = document.getElementById("nickspan");

		//valid is null--------------
		if (txt.value.trim().length == 0) {
			tip.className = "note_no";
			tip.innerText = msg;
			return false;
		}
		//valid regx----------------- /^[_A-Za-z0-9\u4e00-\u9fa5]{2,20}$/.test(txt.value)
		if (txt.value.trim().length < 2 || txt.value.trim().length > 12) {
			tip.className = "note_no";
			tip.innerText = msg;
			return false;
		}
		//valid is exsits------------
		var urlData = '/Public/XmlHttpUser.aspx?type=nickexist&nickname=' + escape(txt.value);
		//alert(urlData);
		var strReturn = AjaxCall(urlData);
		//alert(strReturn);
		if (strReturn == "1") {
			tip.className = "note_no";
			tip.innerText = '对不起，该用户昵称已经存在。';
			return false;
		} else if (strReturn == "0") {
			tip.innerText = '恭喜您，该用户昵称可以注册。';
		}

		tip.className = "note_yes";
		return true;
	}

	/*===Check Pwd========================*/
	function chkPwd() {
		var txt = document.getElementById('pwd');
		var tip = document.getElementById("pwdspan");

		//valid is null--------------
		if (txt.value.trim().length == 0) {
			tip.className = "note_no";
			return false;
		}
		//valid regx-----------------
		if (!/^[0-9a-zA-Z]{6,20}$/.test(txt.value)) {
			tip.className = "note_no";
			return false;
		}

		tip.className = "note_yes";
		return true;

	}

function onFormSubmit(f) {
		if (!chkUserName(msgUsername)) {
			document.getElementById('username').focus();
			return false;
		}

		if (!chkPwd()) {
			document.getElementById('pwd').focus();
			return false;
		}

		if (!chkNickName(msgNickname)) {
			document.getElementById('nickname').focus();
			return false;
		}
		return true;
	}
	//-->
</script>
