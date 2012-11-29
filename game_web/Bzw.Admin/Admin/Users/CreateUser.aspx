<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Users_CreateUser" CodeBehind="CreateUser.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<title>无标题页</title>
	<link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
	<style type="text/css">
		<!
		-- body
		{
			background-color: #F2F8FF;
			margin-top: 0px;
		}
		.red
		{
			color: red;
		}
		-- ></style>
</head>
<body>
	<form id="form1" runat="server" method="post" onsubmit="return checkform(this)">
	<input type="hidden" name="act" id="act" value="post" />
	<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#A4B6D7"
		bgcolor="F2F8FF" class="admin_table2">
		<tr>
			<td class="title_03">
				<strong>会员管理</strong>
			</td>
		</tr>
	</table>
	<table width="100%" border="0" cellspacing="0" cellpadding="0">
		<tr>
			<td style="height: 5px">
			</td>
		</tr>
	</table>
	<table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
		bgcolor="F2F8FF" class="admin_table">
		<tr>
			<td class="title_03" colspan="19">
				<strong>新增玩家</strong>
			</td>
		</tr>
		<tr>
			<td align="right" width="40%" style="height:20px;">
				用户名：
			</td>
			<td colspan="2" align="left"  style="height:20px;">
				<input name="u" type="text" id="u" class="put" maxlength="12" onblur="checkusername()" /><div id="usernamemsg" class="red">
				</div>
			</td>
		</tr>
		<tr>
			<td align="right">
				用户昵称：
			</td>	
			<td colspan="2" align="left">
				<input name="n" type="text" id="n" class="put" maxlength="12" onblur="checknickname()" /><div id="usernickmsg" class="red"></div>
			</td>
		</tr>
		<tr>
			<td align="right">
				密码：
			</td>
			<td colspan="2" align="left">
				<input name="pwd" type="text" id="pwd" class="put" maxlength="12" onblur="checkpwd()" /><div
					id="userpwdmsg" class="red">
				</div>
			</td>
		</tr>
		<tr style="display:none;">
			<td  align="right" valign="middle">
				真实姓名：
			</td>
			<td colspan="2" align="left" valign="middle" >
				<input name="realname" type="text" id="realname" maxlength="9" onblur="chkRealName()" class="put" /><div id="realnamemsg" class="red"></div>
			</td>
		</tr>
		<tr style="display:none;">
			<td  align="right" valign="middle">
				身份证号：
			</td>
			<td colspan="2" align="left" valign="middle" >
				<input name="idcard" id="idcard" type="text" class="put" maxlength="18" onblur="chkidcard()"  /><div id="idcardmsg" class="red"></div>
			</td>
		</tr>
		<tr>
			<td align="right">
				&nbsp;
			</td>
			<td colspan="2" align="left">
				<asp:Button ID="CreateUser" runat="server" Text=" 创 建 " CssClass="put" OnClick="CreateUserClick" /><asp:Label
					ID="ErrorLabel" ForeColor="red" runat="server" Text=""></asp:Label>
			</td>
		</tr>

	</table>
	</form>
	<script type="text/javascript">

		function checkusername() {
			var txtUserName = document.getElementById('u');
			var txtmsg = document.getElementById('usernamemsg');
			if (txtUserName.value.length == 0) {
				txtmsg.innerHTML = "用户名不能为空！";
				return false;
			}
			if (!/^[0-9a-zA-Z]{6,12}$/.test(txtUserName.value)) {
				txtmsg.innerHTML = "用户名长度6～12个字符，由字母、数字组成";
				return false;
			}

			txtmsg.innerHTML = "";
			return true;
		}

		function checknickname() {
			var txtNick = document.getElementById('n');
			var txtmsg = document.getElementById('usernickmsg');
			if (txtNick.value.length == 0) {
				txtmsg.innerHTML = "昵称不能为空！";

				return false;
			}
			//valid regx----------------- /^[_A-Za-z0-9\u4e00-\u9fa5]{2,20}$/.test(txt.value)
			if (txtNick.value.length < 2 || txtNick.value.length > 12) {
				txtmsg.innerHTML = "昵称长度为2-12位！";

				return false;
			}
			txtmsg.innerHTML = "";
			return true;
		}



		function checkpwd() {

			var txtPwd = document.getElementById('pwd');
			var txtmsg = document.getElementById('userpwdmsg');
			//valid is null--------------
			if (txtPwd.value.length == 0) {
				txtmsg.innerHTML = "密码不能为空！";

				return false;
			}
			if (!/^[0-9a-zA-Z]{6,20}$/.test(txtPwd.value)) {
				txtmsg.innerHTML = "密码为6-20位！";

				return false;
			}
			txtmsg.innerHTML = "";
			return true;
		}


		/***验证真实姓名***/
		function chkRealName() {
			var txt = document.getElementById("realname");
			var tip = document.getElementById("realnamemsg");
			//纯中文
			var che = /^[\u4e00-\u9fa5 ]{2,9}$/;
			if (!che.test(txt.value)) {
				tip.innerHTML = '真实姓名不规范，只能输入2-9位中文。';
				return false;
			}
			else {
				tip.innerText = '';
				return true;
			}
			/**	
			else{
			if(txt.value.trim().length>0){
			if(!che.test(txt.value)){
			tip.className="note_no";
			tip.innerText='真实姓名不规范，只能输入2-9位中文。';
			return false;
			}
			else{
			tip.className="note_yes";
			tip.innerText='真实姓名规范。';
			return true;
			}
			}
			else{
			tip.className="note";
			tip.innerText='请填写真实中文姓名，填写后将不可改。。';
			return true;
			}
			}*/
		}

		function chkidcard() {
			var txt = document.getElementById('idcard');
			var tip = document.getElementById("idcardmsg");

			if (!idcard()) {
				tip.innerHTML = '身份证号无效！';
				return false;
			}
			else {
				tip.innerText = '';
				return true;
			}

			/*   else
			{
			if(txt.value.trim().length>0)
			{
			if(!idcard())
			{
			tip.className="note_no";
			tip.innerText='身份证号码无效！';
			return false;
			}
			else
			{
			tip.className="note_yes";
			tip.innerText='恭喜您，身份证号码检测通过。';
			return true;
			}
			}
			else{
			tip.className="note";
			tip.innerText='请填写真实的身份证号，填写后将不可改。';
			return true;
			}
			}*/

		}
		/*---------------验证身份证是否合法------------------*/
		function idcard() {
			var vl = document.getElementById("idcard").value;
			var tst = /^\d{18}$|^\d{17}(\d|x|X)$|^\d{15}$/;
			if (!tst.test(vl)) {		//验证是否为18位数字或17为数字+X或15位数字	
				return false;
			}
			if (vl.length == 15) {
				var address = "11x22x35x44x53x12x23x36x45x54x13x31x37x46x61x14x32x41x50x62x15x33x42x51x63x21x34x43x52x64x65x71x81x82x91";
				var sf = vl.substring(0, 2);
				if (address.indexOf(sf) == -1) {	//省份验证
					//alert("地址错误");
					return false;
				}
				var birth = "19" + vl.substr(6, 6);
				var year = parseInt("19" + vl.substr(6, 2));
				var month = vl.substr(8, 2);
				var day = vl.substr(10, 2);
				if (chkdate(birth, year, month, day) == -1) {	//生日的验证
					return false;
				}
				return true;
			}
			if (vl.length == 18) {
				var address = "11x22x35x44x53x12x23x36x45x54x13x31x37x46x61x14x32x41x50x62x15x33x42x51x63x21x34x43x52x64x65x71x81x82x91"; //省份验证
				var sf = vl.substring(0, 2);
				if (address.indexOf(sf) == -1) {
					//alert("地址错误");
					return false;
				}
				var birth = vl.substr(6, 8);
				var year = parseInt(vl.substr(6, 4));
				var month = vl.substr(10, 2);
				var day = vl.substr(12, 2);
				if (parseInt(year) > 2010 || parseInt < 1900) { //年份范围验证
					//alert("年份错误");
					return false;
				}
				if (chkdate(birth, year, month, day) == -1) {	 //生日的验证
					return false;
				}
				var rightcode = new Array("1", "0", "X", "9", "8", "7", "6", "5", "4", "3", "2"); //有效校正码
				var heft = new Array("7", "9", "10", "5", "8", "4", "2", "1", "6", "3", "7", "9", "10", "5", "8", "4", "2"); //身份证前17位每位占有权重
				var cardarr = vl.substr(0, 17).split("");
				var sum = 0;
				for (var i = 0; i < 17; i++) {
					sum += parseInt(cardarr[i]) * parseInt(heft[i]);
				}
				sum = sum % 11;
				if (rightcode[sum].toUpperCase() != vl.substr(17)) {
					//alert("校正码错误");
					return false;
				}
			}
			//alert("恭喜您,测试通过");
			return true;
		}

		function checkform(f) {

			if (!checkusername()) {
				document.getElementById('u').focus();
				return false;
			}
			if (!checknickname()) {
				document.getElementById('n').focus();
				return false;
			}
			if (!checkpwd()) {
				document.getElementById('pwd').focus();
				return false;
			}
//			if (!chkidcard()) {

//				document.getElementById('idcard').focus();
//				return false;
//			}
//			if (!chkRealName()) {

//				document.getElementById('realname').focus();
//				return false;
//			}

			return true;
		}
		//valid regx-----------------
     
        
        
	</script>
</body>
</html>
